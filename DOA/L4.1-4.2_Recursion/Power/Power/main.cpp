#include <iostream>

using namespace std;
int power(int x, unsigned int exp);

int main()
{
	int x = -2, exp = 1, y;

	y=power(x, exp);


	cout << y << endl;
	return 0;

}

int power(int x, unsigned int exp)
{
	if (exp == 0)
	{
		return 1;
	}
	/*else if (exp == 1)
	{
		return x;
	}*/
	return x * power(x, exp - 1);
}