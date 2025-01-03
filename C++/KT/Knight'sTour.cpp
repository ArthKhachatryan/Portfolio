#include <bits/stdc++.h> 
using namespace std; 

#define N 8 

int solKT(int x, int y, int movei, int sol[N][N], 
				int xMove[], int yMove[]); 


int isPos(int x, int y, int sol[N][N]) 
{ 
	return (x >= 0 && x < N && y >= 0 && y < N 
			&& sol[x][y] == -1); 
} 


void printSol(int sol[N][N]) 
{ 
	for (int x = 0; x < N; x++) { 
		for (int y = 0; y < N; y++) 
			cout << " " << setw(2) << sol[x][y] << " "; 
		cout << endl; 
	} 
} 

int solveKT() 
{ 
	int sol[N][N]; 

	for (int x = 0; x < N; x++) 
		for (int y = 0; y < N; y++) 
			sol[x][y] = -1; 

	int xMove[8] = { 2, 1, -1, -2, -2, -1, 1, 2 }; 
	int yMove[8] = { 1, 2, 2, 1, -1, -2, -2, -1 }; 

	sol[0][0] = 0; 

	if (solKT(0, 0, 1, sol, xMove, yMove) == 0) { 
		cout << "Solution does not exist"; 
		return 0; 
	} 
	else
		printSol(sol); 

	return 1; 
} 

int solKT(int x, int y, int movei, int sol[N][N], 
				int xMove[8], int yMove[8]) 
{ 
	int k, next_x, next_y; 
	if (movei == N * N) 
		return 1; 

	for (k = 0; k < 8; k++) { 
		next_x = x + xMove[k]; 
		next_y = y + yMove[k]; 
		if (isPos(next_x, next_y, sol)) { 
			sol[next_x][next_y] = movei; 
			if (solKT(next_x, next_y, movei + 1, sol, 
							xMove, yMove) 
				== 1) 
				return 1; 
			else
				sol[next_x][next_y] = -1; 
		} 
	} 
	return 0; 
} 

 
int main() 
{ 
	 
	solveKT(); 
	return 0; 
} 