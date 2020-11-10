#include "pch.h"
#include "CppUnitTest.h"
#include "../123/123.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lab1UnitTests
{
	TEST_CLASS(lab1UnitTests)
	{
	public:

		TEST_METHOD(element_constructor)
		{
			elementL2* elem = new elementL2;
			Assert::AreEqual(elem->inf, 0);
			Assert::IsNull(elem->next);
			Assert::IsNull(elem->prev);

		}
		TEST_METHOD(element_destructor)
		{
			elementL2* elem1 = new elementL2;
			elementL2* elem2 = new elementL2;
			elementL2* elem3 = new elementL2;
			elem2->inf = 1;
			elem1->prev = elem2;
			elem2->next = elem1;
			elem3->inf = 2;
			elem1->next = elem3;
			elem3->prev = elem1;
			delete elem1;
			Assert::AreEqual(elem2->next->inf, 2);
			Assert::AreEqual(elem3->prev->inf, 1);
			delete elem3;
			Assert::IsNull(elem2->next);
			delete elem2;
		}

		TEST_METHOD(_List_)
		{
			List L;
			size_t Size = 0;
			Assert::AreEqual(L.size, Size);
			Assert::IsNull(L.head);
			Assert::IsNull(L.last);
		}

		TEST_METHOD(_isEmpty_)
		{
			List L;
			Assert::IsTrue(L.isEmpty());
			L.head = new elementL2;
			L.last = L.head;
			L.size = 1;
			Assert::IsFalse(L.isEmpty());
		}

		TEST_METHOD(_push_back_)
		{
			List L;
			size_t Size = 2;
			L.push_back(1);
			L.push_back(2);
			Assert::AreEqual(L.size, Size);
			Assert::AreEqual(L.last->inf, 2);
			Assert::AreEqual(L.head->inf, 1);
			Assert::AreEqual(L.head->next->inf, 2);
			Assert::AreEqual(L.last->prev->inf, 1);
		}
		TEST_METHOD(_push_front_)
		{
			List L;
			size_t Size = 2;
			L.push_front(1);
			L.push_front(2);
			Assert::AreEqual(L.size, Size);
			Assert::AreEqual(L.last->inf, 1);
			Assert::AreEqual(L.head->inf, 2);
			Assert::AreEqual(L.head->next->inf, 1);
			Assert::AreEqual(L.last->prev->inf, 2);
		}

		TEST_METHOD(_pop_back_)
		{
			List L;
			L.push_back(1);
			L.push_back(2);
			size_t Size = 1;
			L.pop_back();
			Assert::AreEqual(L.size, Size);
			Assert::AreEqual(L.head->inf, 1);
			Assert::AreEqual(L.head->inf, L.last->inf);
			L.pop_back();
			Assert::IsTrue(L.isEmpty());
		}
		TEST_METHOD(pop_back_exception)
		{
			List L;
			bool b = 0;
			try
			{
				L.pop_back();
			}
			catch (runtime_error & exception)
			{
				b = 1;
			}
			Assert::IsTrue(b);
		}
		TEST_METHOD(_pop_front_)
		{
			List L;
			size_t Size = 1;
			L.push_back(1);
			L.push_back(2);
			L.pop_front();
			Assert::AreEqual(L.size, Size);
			Assert::AreEqual(L.head->inf, 2);
			Assert::AreEqual(L.head->inf, L.last->inf);
			L.pop_front();
			Assert::IsTrue(L.isEmpty());
		}
		TEST_METHOD(pop_front_exception)
		{
			List L;
			bool b = 0;
			try
			{
				L.pop_front();
			}
			catch (runtime_error & exception)
			{
				b = 1;
			}
			Assert::IsTrue(b);
		}

		TEST_METHOD(_at_)
		{
			List L;
			L.push_back(1);
			L.push_back(2);
			L.push_back(3);
			elementL2* elem1 = L.at(0);
			elementL2* elem2 = L.at(1);
			elementL2* elem3 = L.at(2);
			Assert::AreEqual(elem1->inf, 1);
			Assert::AreEqual(elem2->inf, 2);
			Assert::AreEqual(elem3->inf, 3);
		}
		TEST_METHOD(at_exception)
		{
			List L;
			bool b = 0;
			try
			{
				L.at(1);
			}
			catch (out_of_range & exception)
			{
				b = 1;
			}
			Assert::IsTrue(b);
		}

		TEST_METHOD(_insert_)
		{
			List L;
			size_t Size = 1;
			L.insert(1, 0);
			Assert::AreEqual(Size, L.size);
			Assert::AreEqual(L.head->inf, 1);
			L.push_front(1);
			Size = 3;
			L.insert(2, 1);
			Assert::AreEqual(Size, L.size);
			Assert::AreEqual(2, L.at(1)->inf);
		}
		TEST_METHOD(insert_exception)
		{
			List L;
			bool b = 0;
			try
			{
				L.insert(1, 1);
			}
			catch (out_of_range & exception)
			{
				b = 1;
			}
			Assert::IsTrue(b);
		}

		TEST_METHOD(_remove_)
		{
			List L;
			L.push_back(1);
			L.push_back(2);
			L.push_back(3);
			L.push_back(4);
			size_t Size = 3;
			L.remove(0);
			Assert::AreEqual(L.size, Size);
			Assert::AreEqual(L.head->inf, 2);
			L.remove(1);
			Size = 2;
			Assert::AreEqual(L.size, Size);
			Assert::AreEqual(L.at(1)->inf, 4);
			L.remove(1);
			Size = 1;
			Assert::AreEqual(L.size, Size);
			Assert::AreEqual(L.at(0)->inf, 2);
		}
		TEST_METHOD(remove_exception)
		{
			List L;
			bool b = 0;
			try
			{
				L.remove(0);
			}
			catch (runtime_error & exception)
			{
				b = 1;
			}
			Assert::IsTrue(b);
		}
		TEST_METHOD(remove_exception2)
		{
			List L;
			bool b = 0;
			try
			{
				L.remove(3);
			}
			catch (out_of_range & exception)
			{
				b = 1;
			}
			Assert::IsTrue(b);
		}

		TEST_METHOD(_set_)
		{
			List L;
			L.push_back(1);
			size_t Size = 1;
			L.set(2, 0);
			Assert::AreEqual(Size, L.size);
			Assert::AreEqual(2, L.head->inf);
		}
		TEST_METHOD(set_exception)
		{
			List L;
			bool b = 0;
			try
			{
				L.set(1, 1);
			}
			catch (out_of_range & exception)
			{
				b = 1;
			}
			Assert::IsTrue(b);
		}

		TEST_METHOD(_insert_list_)
		{
			List L1, L2, L3;
			L1.push_back(1);
			L2.push_back(2);
			L2.push_back(3);
			L1.insert_list(&L2, 1);
			L1.insert_list(&L2, 0);
			L3.insert_list(&L1, 0);
			size_t Size = 5;
			Assert::AreEqual(L1.head->inf, 2);
			Assert::AreEqual(L1.last->inf, 3);
			Assert::AreEqual(L1.size, Size);
			Assert::AreEqual(L3.size, L1.size);
			Assert::AreEqual(L3.head->inf, L1.head->inf);
			Assert::AreEqual(L3.last->inf, L1.last->inf);
		}
		TEST_METHOD(insert_list_exception1)
		{
			List L1, L2;
			bool b = 0;
			try
			{
				L1.insert_list(&L2, 1);
			}
			catch (runtime_error & exception)
			{
				b = 1;
			}
			Assert::IsTrue(b);
		}
		TEST_METHOD(insert_list_exception2)
		{
			List L1, L2;
			L1.push_back(1);
			L2.push_back(1);
			bool b = 0;
			try
			{
				L1.insert_list(&L2, 3);
			}
			catch (out_of_range & exception)
			{
				b = 1;
			}
			Assert::IsTrue(b);
		}

		TEST_METHOD(_clear_)
		{
			List L;
			L.push_back(1);
			L.push_back(2);
			L.clear();
			Assert::IsTrue(L.isEmpty());
		}
	};
}