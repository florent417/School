#include "Vector.h"
#include <array>


Vector::Vector()
{
	for (int i = 0; i < SIZE; i++)
		data[i] = i;
}

int Vector::get(int index) const
{
	return data[index];
}

bool Vector::contains(int number) const
{
	for (size_t i = 0; i < SIZE; i++)
	{
		if (data[i] == number)
			return true;
	}
	return false;
}

int Vector::howMany(int number) const
{
	int occurrences = 0;
	for (size_t i = 0; i < SIZE; i++)
	{
		if (data[i] == number)
		{
			++occurrences;
		}
	}
	return occurrences;
}

bool Vector::allUnique() const
{
	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = i; j < SIZE; j++)
		{
			if (data[i] == data[j])
			{
				return false;
			}
		}
	}
	return true;
}