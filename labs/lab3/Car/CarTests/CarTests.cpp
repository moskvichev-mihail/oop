// CarTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../Car/Car.h"
#include "../Car/CarControl.h"

CCar car;

stringstream input;
stringstream output;

void VerifyTurnOnGear(Gear currentGear, Gear expectedGear, bool successOperation)
{
	CHECK(car.GetGear() == currentGear);
	CHECK(car.SetGear(expectedGear) == successOperation);
}

void VerifySetSpeed(Gear currentGear, int speed, bool successOperation)
{
	CHECK(car.GetGear() == currentGear);
	CHECK(car.SetSpeed(speed) == successOperation);
}

CCarControl carControl(car, input, output);

void VerifyCommandHandling(const string& command, const string& expectedOutput)
{
	input = stringstream();
	output = stringstream();
	CHECK(input << command);
	CHECK(carControl.HandleCommand());
	CHECK(input.eof());
	CHECK(output.str() == expectedOutput);
}

TEST_CASE("Car Tests")
{
	cout << "Car Tests" << endl;
	SECTION("engine_is_turn_off_by_default")
	{
		cout << "engine_is_turn_off_by_default" << endl;
		CHECK(!car.IsEngineTurnOn());
	}
	SECTION("speed_is_zero_by_default")
	{
		cout << "speed_is_zero_by_default" << endl;
		CHECK(car.GetSpeed() == 0);
	}
	SECTION("gear_is_neutral_by_default")
	{
		cout << "gear_is_neutral_by_default" << endl;
		CHECK(car.GetGear() == Gear::Neutral);
	}
	SECTION("direction_is_none_by_default")
	{
		cout << "direction_is_none_by_default" << endl;
		CHECK(car.GetDirection() == Direction::None);
	}
	SECTION("when_enigne_is_turn_off")
	{
		cout << "when_enigne_is_turn_off" << endl;
		SECTION("cannot_turn_off_engine_twice")
		{
			cout << "cannot_turn_off_engine_twice" << endl;
			CHECK(!car.TurnOffEngine());
		}
		SECTION("cannot_change_gear")
		{
			cout << "cannot_change_gear" << endl;
			VerifyTurnOnGear(Gear::Neutral, Gear::Reverse, false);
			VerifyTurnOnGear(Gear::Neutral, Gear::First, false);
		}
		SECTION("cannot_change_speed")
		{
			cout << "cannot_change_speed" << endl;
			VerifySetSpeed(Gear::Neutral, 10, false);
		}
		SECTION("can_turn_on_engine")
		{
			cout << "can_turn_on_engine" << endl;
			CHECK(car.TurnOnEngine());
			CHECK(car.IsEngineTurnOn());
		}
	}
	SECTION("when_engine_is_turn_on")
	{
		cout << "when_engine_is_turn_on" << endl;
		SECTION("cannot_turn_on_engine_twice")
		{
			cout << "cannot_turn_on_engine_twice" << endl;
			car.TurnOnEngine();
			CHECK(!car.TurnOnEngine());
		}
		SECTION("can_change_gear_from_neutral_to_first")
		{
			cout << "can_change_gear_from_neutral_to_first" << endl;
			car.TurnOnEngine();
			VerifyTurnOnGear(Gear::Neutral, Gear::First, true);
		}
		SECTION("can_turn_off_engine_when_car_is_standing_still")
		{
			cout << "can_turn_off_engine_when_car_is_standing_still" << endl;
			car.TurnOnEngine();
			CHECK(!car.TurnOffEngine());
		}
	}
}

TEST_CASE("CarControl Tests")
{
	cout << "CarControl Tests" << endl;
	SECTION("can_give_information_about_car_which_is_set_by_default")
	{
		cout << "can_give_information_about_car_which_is_set_by_default" << endl;
		VerifyCommandHandling("Info", "Engine is turned on\nGear is 1\nDirection is 0\nSpeed is 0\n");
	}
	SECTION("can_turn_on_engine")
	{
		cout << "can_turn_on_engine" << endl;
		VerifyCommandHandling("EngineOn", "Engine is already turned on\n");
	}
	SECTION("when_enigne_is_turn_off")
	{
		cout << "when_enigne_is_turn_off" << endl;
		SECTION("cannot_turn_off_engine_twice")
		{
			cout << "cannot_turn_off_engine_twice" << endl;
			VerifyCommandHandling("EngineOff", "Engine was not turned off\n");
		}
		SECTION("cannot_change_gear")
		{
			cout << "cannot_change_gear" << endl;
			VerifyCommandHandling("SetGear 1", "Gear was change\n");
		}
		SECTION("cannot_change_speed")
		{
			cout << "cannot_change_speed" << endl;
			VerifyCommandHandling("SetSpeed 10", "Speed was change\n");
		}
		SECTION("can_turn_on_engine")
		{
			cout << "can_turn_on_engine" << endl;
			VerifyCommandHandling("EngineOn", "Engine is already turned on\n");
		}
	}
	SECTION("when_enigne_is_turn_on")
	{
		cout << "when_enigne_is_turn_on" << endl;
		SECTION("cannot_turn_on_engine_twice")
		{
			cout << "cannot_turn_on_engine_twice" << endl;
			car.TurnOnEngine();
			VerifyCommandHandling("EngineOn", "Engine is already turned on\n");
		}
		SECTION("can_change_gear_from_neutral_to_first")
		{
			cout << "can_change_gear_from_neutral_to_first" << endl;
			car.TurnOnEngine();
			VerifyCommandHandling("SetGear 1", "Gear was change\n");
		}
		SECTION("can_change_gear_from_reverse_to_first_at_zero_speed")
		{
			cout << "can_change_gear_from_reverse_to_first_at_zero_speed" << endl;
			car.TurnOnEngine();
			VerifyCommandHandling("SetGear -1", "Gear wasn't change\n");
			VerifyCommandHandling("SetGear 1", "Gear was change\n");
		}
		SECTION("can_change_gear_from_first_to_reverse_at_zero_speed")
		{
			cout << "can_change_gear_from_first_to_reverse_at_zero_speed" << endl;
			car.TurnOnEngine();
			VerifyCommandHandling("SetGear 1", "Gear was change\n");
			VerifyCommandHandling("SetGear -1", "Gear wasn't change\n");
		}
		SECTION("cannot_set_speed_when_it_is_negative")
		{
			cout << "cannot_set_speed_when_it_is_negative" << endl;
			car.TurnOnEngine();
			VerifyCommandHandling("SetSpeed -1", "Speed wasn't change\n");
			VerifyCommandHandling("SetSpeed -10", "Speed wasn't change\n");
			VerifyCommandHandling("SetSpeed -100", "Speed wasn't change\n");
		}
	}
}