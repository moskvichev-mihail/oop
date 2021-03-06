// StringStackTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../StringStack/CStringStack.h"

TEST_CASE("StringStack Tests")
{
	cout << "StringStack Tests" << endl;
	SECTION("is_empty_by_default")
	{
		cout << "is_empty_by_default" << endl;
		CStringStack stack1;
		CHECK(stack1.IsEmpty());
	}
	SECTION("can_not_get_last_element_when_stack_is_empty")
	{
		cout << "can_not_get_last_element_when_stack_is_empty" << endl;
		CStringStack stack2;
		CHECK_THROWS_AS(stack2.GetLastElement(), logic_error);
	}
	SECTION("can_push_element")
	{
		cout << "can_push_element" << endl;
		CStringStack stack3;
		stack3.Push("String");
		CHECK(!stack3.IsEmpty());
		CHECK(stack3.GetLastElement() == "String");
	}
	SECTION("can_pop_element")
	{
		cout << "can_pop_element" << endl;
		CStringStack stack4;
		stack4.Push("string");
		CHECK(!stack4.IsEmpty());
		stack4.Pop();
		CHECK(stack4.IsEmpty());
	}
	SECTION("cant_pop_elements_when_stack_is_empty")
	{
		cout << "cant_pop_elements_when_stack_is_empty" << endl;
		CStringStack stack5;
		CHECK_THROWS_AS(stack5.Pop(), logic_error);
	}
	SECTION("can_get_size_of_stack")
	{
		cout << "can_get_size_of_stack" << endl;
		CStringStack stack6;
		stack6.Push("word");
		stack6.Push("my");
		CHECK(stack6.GetSize() == (size_t)2);
	}
	SECTION("can_delete_all_elements_in_stack")
	{
		cout << "can_delete_all_elements_in_stack" << endl;
		CStringStack stack7;
		size_t currentSize = 3;
		size_t expectedSize = 0;
		for (size_t i = 0; i < currentSize; ++i)
		{
			stack7.Push("string");
		}
		CHECK(stack7.GetSize() == currentSize);
		stack7.Clear();
		CHECK(stack7.GetSize() == expectedSize);
	}
	SECTION("can_compare_stacks")
	{
		cout << "can_compare_stacks" << endl;
		CStringStack stack8;
		CStringStack newStack8;
		newStack8.Push("This world");
		stack8.Push("This world");
		CHECK(newStack8 == stack8);
		stack8.Push("This world is mine");
		CHECK(newStack8 != stack8);
	}
	SECTION("can_not_copy_empty_stack")
	{
		cout << "can_not_copy_empty_stack" << endl;
		CStringStack stack9;
		CStringStack newStack9 = stack9;
		CHECK(newStack9.IsEmpty());
	}
}