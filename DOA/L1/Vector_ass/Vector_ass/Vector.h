#pragma once
class Vector
{
public:
	static const int SIZE = 10;
	Vector();

	//Index has to be in range of 0..SIZE for set!
	void set(int index, int number);
	//The value in array equal to number

	//Index has to be in range of 0..SIZE for set!
	int get(int index) const;
	//Returns the value of the element of which 
	//the index points to in the array

	bool contains(int number) const;
	//Returns true if the array contains the number
	//and false if it does not

	int howMany(int number) const;
	//Returns the the number of occurences in the 
	//array of the given number

	bool allUnique() const;
	//Return true if the numbers are all unique
	//and false if they are not

private:
	int data[SIZE];
};

