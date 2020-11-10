#include <iostream>
#include <stdexcept>

using namespace std;

class elementL2
{
public:
	int inf;
	elementL2* next;
	elementL2* prev;
	elementL2()
	{
		next = nullptr;
		prev = nullptr;
		inf = 0;
	}
	~elementL2()
	{
		if (next != nullptr)
			next->prev = prev;
		if (prev != nullptr)
			prev->next = next;
	}
};

class List
{
public:
	elementL2* head;
	elementL2* last;
	size_t size;
	List()
	{
		head = nullptr;
		last = nullptr;
		size = 0;
	}
	bool isEmpty() { return (head == nullptr); }

	size_t get_size() { return size; }

	void push_back(int inf)
	{
		elementL2* input = new elementL2;
		input->inf = inf;
		size++;
		if (isEmpty())
		{
			head = input;

		}
		else
		{
			last->next = input;
			input->prev = last;
		}
		last = input;
	}

	void push_front(int inf)
	{
		elementL2* input = new elementL2;
		input->inf = inf;
		size++;
		if (isEmpty())
		{
			head = input;
			last = input;
		}
		else
		{
			head->prev = input;
			input->next = head;
			head = input;
		}

	}

	void pop_back()
	{
		if (isEmpty())
			throw runtime_error("List is empty\n");
		elementL2* last2 = last->prev;
		delete last;
		last = last2;
		if (last == nullptr)
		{
			head = last;
		}
		size--;
	}

	void pop_front()
	{
		if (isEmpty())
			throw runtime_error("List is empty\n");
		elementL2* Head = head->next;
		delete head;
		head = Head;
		if (head == nullptr)
			last = head;
		size--;
	}
	elementL2* at(size_t index)
	{
		if (index >= size)
			throw out_of_range("Index must be greater than 0 and less than size of list\n");
		if (index == 0)
			return head;
		if (index == (size - 1))
			return last;
		elementL2* Cur = head;
		for (int count = 0; count < index; count++)
		{
			Cur = Cur->next;
		}
		return Cur;
	}

	void insert(int inf, size_t index)
	{
		if (index == 0)
			push_front(inf);
		else
		{
			try
			{
				elementL2* input = new elementL2;
				input->inf = inf;
				input->next = at(index);
				input->prev = at(index)->prev;
				at(index)->prev = input;
				input->prev->next = input;
				size++;
			}
			catch (out_of_range & exception) { throw out_of_range(exception.what()); }
		}
	}

	void remove(size_t index)
	{
		try
		{
			if (index == 0)
				pop_front();
			else if (index == (size - 1))
				pop_back();
			else
			{
				delete at(index);
				size--;
			}
		}
		catch (runtime_error & exception) { throw runtime_error(exception.what()); }
		catch (out_of_range & exception) {
			throw out_of_range(exception.what());
		}
	}

	void set(int inf, size_t index)
	{
		try
		{
			at(index)->inf = inf;
		}
		catch (out_of_range & exception)
		{
			throw out_of_range(exception.what());
		}
	}

	void insert_list(List* L, size_t index)
	{
		if ((L == nullptr) || (L->isEmpty()))
			throw runtime_error("Input list is empty\n");
		for (int i = 0; i < L->size; i++)
		{
			if ((isEmpty() && (index == 0)) || ((index + i) == size))
			{
				push_back(L->at(i)->inf);
			}
			else
			{
				try
				{
					insert(L->at(i)->inf, index + i);
				}
				catch (out_of_range & exception) { throw out_of_range(exception.what()); }
			}
		}
	}

	void print_to_console()
	{
		if (isEmpty())
			throw runtime_error("List is empty\n");
		elementL2* Cur = head;
		while (Cur != nullptr)
		{
			cout << Cur->inf << ' ';
			Cur = Cur->next;
		}
		cout << '\n';
	}

	void clear()
	{
		while (!isEmpty())
			pop_front();
	}

	~List() { clear(); }
};

int main()
{
	List L1;
	List L2;
	L1.push_back(1);
	L1.push_back(1);
	L2.push_back(2);
	L2.push_back(2);
	L1.print_to_console();
	L2.print_to_console();
	L1.insert_list(&L2, 2);
	L1.print_to_console();
}	