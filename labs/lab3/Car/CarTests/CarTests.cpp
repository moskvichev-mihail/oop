// CarTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "..\Car\Car.h"
#include "..\Car\CarControl.h"

stringstream input;
stringstream output;
CCar car;
CCarControl CarControlDependencies(car, input, output);

void VerifyCommandHandling(const string& command, const string& expectedOutput)
{
	output = stringstream();
	input = stringstream();
	CHECK(input << command);
	CHECK(CarControlDependencies.HandleCommand());
	CHECK(input.eof());
	CHECK(output.str() == expectedOutput);
}

TEST_CASE("Car tests")
{
	SECTION("CCar test")
	{
		SECTION("engine turned off by default")
		{
			CHECK(car.IsEngineTurnOn() == false);
		}
		SECTION("speed is zero by default")
		{
			CHECK(car.GetSpeed() == 0);
		}
		SECTION("gear is neutral by default")
		{
			CHECK(car.GetGear() == Gear::NEUTRAL);
		}
		SECTION("direction is stop by default")
		{
			CHECK(car.GetDirection() == Direction::NONE);
		}
		SECTION("when engine is turned off")
		{
			SECTION("can't select gear when engine turned off")
			{
				car.SetGear(Gear::NEUTRAL);
				CHECK(car.GetGear() == Gear::NEUTRAL);

				car.SetGear(Gear::FIRST);
				CHECK(car.GetGear() == Gear::NEUTRAL);

				car.SetGear(Gear::REVERSE);
				CHECK(car.GetGear() == Gear::NEUTRAL);
			}
			SECTION("can be turned on")
			{
				CHECK(car.TurnOnEngine() == true);
				CHECK(car.IsEngineTurnOn());
			}
		}
		SECTION("when engine turned on")
		{
			SECTION("can't be turned on twice")
			{
				car.TurnOnEngine();
				CHECK(car.IsEngineTurnOn());
			}
			SECTION("can be turned off")
			{
				car.TurnOnEngine();
				car.TurnOffEngine();
				CHECK(!car.IsEngineTurnOn());
			}
			SECTION("can't be turned off when speed is not equal to zero")
			{
				car.TurnOnEngine();
				car.SetGear(Gear::FIRST);
				car.SetSpeed(20);
				CHECK(!car.TurnOffEngine());
				CHECK(car.IsEngineTurnOn());
			}
			SECTION("can't be turned off twice")
			{
				car.TurnOnEngine();
				car.TurnOffEngine();
				CHECK(car.IsEngineTurnOn());
				CHECK(!car.TurnOffEngine());
				CHECK(car.IsEngineTurnOn());
			}
			SECTION("can change gear from neutral")
			{
				car.TurnOnEngine();
				car.SetGear(Gear::FIRST);
				CHECK(car.GetGear() == Gear::FIRST);

				CHECK(car.SetGear(Gear::NEUTRAL));
				CHECK(car.SetGear(Gear::FIRST));
				CHECK(car.SetSpeed(30));

				CHECK(car.SetGear(Gear::SECOND));
				CHECK(car.GetGear() == Gear::SECOND);
				CHECK(car.SetSpeed(20));

				CHECK(car.SetGear(Gear::NEUTRAL));
				CHECK(car.SetSpeed(0));
				CHECK(car.SetGear(Gear::REVERSE));
				CHECK(car.GetGear() == Gear::REVERSE);
			}
			SECTION("can't change gear when speed is out of range")
			{
				car.TurnOnEngine();
				car.SetGear(Gear::SECOND);

				CHECK(car.SetGear(Gear::NEUTRAL));
				CHECK(car.SetGear(Gear::FIRST));
				CHECK(car.SetSpeed(10));

				CHECK(!car.SetGear(Gear::SECOND));
				CHECK(car.GetGear() == Gear::FIRST);

				CHECK(car.SetGear(Gear::NEUTRAL));
				CHECK(car.SetSpeed(10));
				CHECK(!car.SetGear(Gear::REVERSE));
				CHECK(car.GetGear() == Gear::NEUTRAL);
			}
			SECTION("can change gear and speed when selected reverse gear")
			{
				car.TurnOnEngine();
				car.SetGear(Gear::REVERSE);
				CHECK(car.SetSpeed(15));
				CHECK(car.GetDirection() != Direction::BACKWARDS);

				CHECK(car.SetGear(Gear::FIRST));
				CHECK(car.SetSpeed(0));

				CHECK(car.SetGear(Gear::FIRST));
				CHECK(car.SetSpeed(15));
				CHECK(car.GetDirection() == Direction::FORWARDS);
			}
		}
	}
	SECTION("CCarControl test")
	{
		SECTION("handle empty input")
		{
			input = stringstream();
			CCarControl carController(car, input, output);
			CHECK(!carController.HandleCommand());
		}
		SECTION("handle unknown command")
		{
			input = stringstream();
			CHECK(input << "Uknown command");
			CHECK(!CarControlDependencies.HandleCommand());
		}
		SECTION("can turn on engine")
		{
			VerifyCommandHandling("EngineOn", "Car engine is already turned on\n");
		}
		SECTION("can print changed info")
		{
			car.TurnOnEngine();
			car.SetGear(Gear::FIRST);
			car.SetSpeed(20);
			VerifyCommandHandling(
				"Info", "Engine: On\nGear: 1\nSpeed: 20\nDirection: Forwards\n"
			);
		}
		SECTION("can print result of changing car characteristics")
		{
			VerifyCommandHandling("EngineOff", "Car engine is already turned off or gear not neutral or car goes\n");

			car.TurnOnEngine();
			VerifyCommandHandling("EngineOn", "Car engine is already turned on\n");

			VerifyCommandHandling("SetGear 1", "Gear was switched on 1\n");
			VerifyCommandHandling("SetGear 5", "Can't switch gear on 5\n");

			VerifyCommandHandling("SetSpeed 20", "Speed was changed on 20\n");
			VerifyCommandHandling("SetGear 2", "Gear was switched on 2\n");
			VerifyCommandHandling("SetSpeed 50", "Speed was changed on 50\n");
		}
	}
}