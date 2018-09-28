#pragma once
#include<vector>
using namespace std;

//==================================================
// CLASS MinHeap
//==================================================
template<typename T>
class MinHeap
{
public:
	void insert(const T& x) 
	{
		// YOUR CODE GOES HERE
		//Data is pushed back at the end of the vector
		//capacity is automatically increased upon calling 
		//push back, if it's needed
		data.push_back(x);

		//The data needs to be inserted at the right
		//index, percolateup is called.
		percolateUp(data.size());
	}

	void remove() 
	{
		// YOUR CODE GOES HERE
	}

	bool isEmpty()
	{
		// YOUR CODE GOES HERE
	}

	T peek()
	{
		// YOUR CODE GOES HERE
		//Tjek det her, ikke sikkert
		return data[0];
	}

private:
	void percolateUp(int i) 
	{
		// YOUR CODE GOES HERE
		if (i > 0 && data[i] < data[parent(i)])
		{
			swap(data[i], data[parent(i)]);
			percolateUp(i - 1);
		}
	}

	void percolateDown(int i) 
	{
		// YOUR CODE GOES HERE
	}

	// Returns index of smallest of i and its parents.
	int smallest(int i) const	 {
		int small = i;

		if (left(i)  < data.size() &&
			data[i]> data[left(i)])
			small = left(i);

		if (right(i) < data.size() &&
			data[i]> data[right(i)] &&
			data[right(i)]< data[left(i)])
			small = right(i);

		return small;
	}

	void swap(int i1, int i2) {
		T temp = data[i1];
		data[i1] = data[i2];
		data[i2] = temp;
	}

	size_t parent(int i) const { return (i - 1) / 2; }
	size_t left(int i)	const { return 2 * i + 1; }
	size_t right(int i)	const { return 2 * i + 2; }

	vector<T> data;
};

