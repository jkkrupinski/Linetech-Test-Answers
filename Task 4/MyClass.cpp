#include<iostream>

using namespace std;

template<typename n>
class MyClass
{
public:

	n& get_x()
	{
		return x;
	}

	// Parametrized constructor
	MyClass(n value)
	{
		x = value;
	}

	// Copy constructor
	MyClass(const MyClass &t)
	{
		x = t.x;
	}

	// Move constructor
	MyClass(MyClass&& other) noexcept
	{
		x = other.x;

		other.x = 0;
	}

	// Move assignment operator
	MyClass& operator=(MyClass&& other) noexcept
	{
		if (this != &other)
		{
			x = other.x;

			other.x = 0;
		}
		return *this;
	}

private:

	n x;
};