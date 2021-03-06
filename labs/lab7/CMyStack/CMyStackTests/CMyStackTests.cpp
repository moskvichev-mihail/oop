// CMyStackTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../CMyStack/CMyStack.h"

CStack<string> strStack;
CStack<int> intStack;
CStack<float> floatStack;

TEST_CASE("Stack_can")
{
	cout << "Stack_can" << endl;
	SECTION("push_and_return_elements")
	{
		cout << "push_and_return_elements" << endl;
		SECTION("string")
		{
			cout << "string" << endl;
			string pushStr = "Hello!";
			strStack.Push(pushStr);
			CHECK(pushStr == strStack.GetTop());
		}
		SECTION("integer_number")
		{
			cout << "integer_number" << endl;
			int pushInt = 1000;
			intStack.Push(pushInt);
			CHECK(pushInt == intStack.GetTop());
		}
		SECTION("float_number")
		{
			cout << "float_number" << endl;
			float pushFloat = 13.37f;
			floatStack.Push(pushFloat);
			CHECK(pushFloat == floatStack.GetTop());
		}
	}
	SECTION("pop_elements_when")
	{
		cout << "pop_elements_when" << endl;
		SECTION("stack_is_not_empty")
		{
			cout << "stack_is_not_empty" << endl;
			CStack<int> numbersStack;
			int start = 0;
			int end = 10;

			for (int number = start; number <= end; number++)
			{
				numbersStack.Push(number);
			}

			for (int reverseNumber = end - 1; reverseNumber >= start; reverseNumber--)
			{
				numbersStack.Pop();
				CHECK(reverseNumber == numbersStack.GetTop());
			}
		}
		SECTION("stack_is_empty")
		{
			cout << "stack_is_empty" << endl;
			CStack<float> floatStack;
			CHECK_NOTHROW(floatStack.Pop());
		}
	}
	SECTION("return_information_about_empty_when")
	{
		cout << "return_information_about_empty_when" << endl;
		SECTION("stack_is_empty")
		{
			cout << "stack_is_empty" << endl;
			CStack<string> stack;
			CHECK(stack.Empty());
		}
		SECTION("stack_is_not_empty")
		{
			cout << "stack_is_not_empty" << endl;
			CStack<int> stack;
			stack.Push(1000);
			CHECK(!stack.Empty());
		}
	}
	SECTION("be_destroyed")
	{
		cout << "be_destroyed" << endl;
		SECTION("without_stack_overflow_exception")
		{
			cout << "without_stack_overflow_exception" << endl;
			CStack<float> floatStack;
			float fNum = 13.33f;
			size_t elemCount = 20000;
			for (size_t i = 0; i < elemCount; i++)
			{
				floatStack.Push(fNum);
			}
			CHECK_NOTHROW(floatStack.~CStack());
		}
	}
	SECTION("Clear_stack_when")
	{
		cout << "Clear_stack_when" << endl;
		SECTION("stack_is_empty")
		{
			cout << "stack_is_empty" << endl;
			CStack<string> stack;
			stack.Clear();
			CHECK(stack.Empty());
		}
		SECTION("stack_is_not_empty")
		{
			cout << "stack_is_not_empty" << endl;
			CStack<string> stack;
			stack.Push("Hello");
			stack.Push("World!");
			stack.Clear();
			CHECK(stack.Empty());
		}
	}
	SECTION("Stack_have")
	{
		cout << "Stack_have" << endl;
		SECTION("copy_constructor")
		{
			cout << "copy_constructor" << endl;
			CStack<string> copiedStack;
			copiedStack.Push("Hello");
			copiedStack.Push("World!");
			CStack<string> newStack(copiedStack);
			CHECK(copiedStack.GetTop() == newStack.GetTop());
			CHECK(copiedStack.GetTop() == newStack.GetTop());
		}
		SECTION("move_constructor")
		{
			cout << "move_constructor" << endl;
			CStack<string> movingStack;
			movingStack.Push("string");
			CStack<string> newStack(move(movingStack));
			CHECK(newStack.GetTop() == "string");
			CHECK_THROWS_AS(movingStack.GetTop(), logic_error);
		}
		SECTION("copied_assign_operator")
		{
			cout << "copied_assign_operator" << endl;
			CStack<int> stackForInsertion;
			CStack<int> copiedStack;
			for (int i = -10; i < 10; i++)
			{
				stackForInsertion.Push(1);
				copiedStack.Push(1);
			}
			stackForInsertion = copiedStack;
			while (!stackForInsertion.Empty() && !copiedStack.Empty())
			{
				CHECK(stackForInsertion.GetTop() == copiedStack.GetTop());
				stackForInsertion.Pop();
				copiedStack.Pop();
			}
		}
		SECTION("moving_assign_operator")
		{
			cout << "moving_assign_operator" << endl;
			CStack<int> stackForInsertion;
			CStack<int> movingStack;
			for (int i = -10; i < 10; i++)
			{
				movingStack.Push(1);
			}
			CHECK_NOTHROW(movingStack.GetTop());
			stackForInsertion = move(movingStack);
			CHECK_THROWS_AS(movingStack.GetTop(), logic_error);
			while (!stackForInsertion.Empty())
			{
				CHECK(stackForInsertion.GetTop() == 1);
				stackForInsertion.Pop();
			}
		}
	}
	SECTION("Stack_can_throw_exception_when_")
	{
		cout << "Stack_can_throw_exception_when_" << endl;
		SECTION("get_top_from_empty_stack")
		{
			cout << "get_top_from_empty_stack" << endl;
			CStack<string> stack;
			CHECK_THROWS_AS(stack.GetTop(), logic_error);
		}
	}
	SECTION("Stack_copied_assign_operator")
	{
		cout << "Stack_copied_assign_operator" << endl;
		SECTION("can_work_with_itself")
		{
			cout << "can_work_with_itself" << endl;
			const float number = 12.0099f;
			CStack<float> simpleStack;
			simpleStack.Push(number);
			simpleStack = simpleStack;
			CHECK(simpleStack.GetTop() == number);
			simpleStack.Pop();
			CHECK_THROWS_AS(simpleStack.GetTop(), logic_error);
		}
	}
	SECTION("Stack_moving_assign_operator")
	{
		cout << "Stack_moving_assign_operator" << endl;
		SECTION("can_work_with_itself")
		{
			cout << "can_work_with_itself" << endl;
			const float number = 12.0099f;
			CStack<float> simpleStack;
			simpleStack.Push(number);
			simpleStack = move(simpleStack);
			CHECK(simpleStack.GetTop() == number);
			simpleStack.Pop();
			CHECK_THROWS_AS(simpleStack.GetTop(), logic_error);
		}
	}
}