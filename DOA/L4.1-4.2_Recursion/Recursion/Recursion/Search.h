#pragma once

bool search(int *ar, int n, int x);

bool search(int *ar, int n, int x){
	if (ar[n] == x) return true; //BC
	
	else if (n < 0) return false; //Går under 0, og findes ikke

	else return search(ar, n - 1, x);

}

