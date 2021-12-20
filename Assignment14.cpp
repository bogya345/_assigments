#include <stdio.h>
#include "mpi.h"
#include <iostream>
#define n 1000

using namespace std;

void smod5(void *a, void *b, int *l, MPI_Datatype *type)
{
	int i;
	for (i = 0; i < *l; i++)
		((int *)b)[i] = (((int *)a)[i] + ((int *)b)[i]) % 5;
}

void absMax(void *a, void *b, int *l, MPI_Datatype *type)
{
	for (int i = 0; i < *l; i++)
	{
		for (int j = 1; j < n; j++)
		{
			if (((int *)a)[j] > ((int *)b)[i])
			{
				((int *)b)[i] = ((int *)a)[j];
			}
		}
	}
}

void max(void *a, void *b, int *l, MPI_Datatype *type)
{
	for (int j = 0; j < n; j++)
	{
		if (((int *)a)[j] > ((int *)b)[j])
		{
			((int *)b)[j] = ((int *)a)[j];
		}
	}
	// for (int i = 1; i < n; i++)
	// {
	// 	if (((int *)a)[i] > ((int *)b)[*l])
	// 	{
	// 		((int *)b)[*l] = ((int *)a)[i];
	// 	}
	// }
}

int main(int argc, char **argv)
{
	int rank, size, i;
	int a[n];
	int b[n];
	MPI_Init(&argc, &argv);
	MPI_Op op, maxVal;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	for (i = 0; i < n; i++)
		a[i] = i + rank + 1;
	// a[i] = i;
	printf("process %d a[0] = %d\n", rank, a[0]);
	MPI_Op_create(&smod5, 1, &op);
	MPI_Reduce(a, b, n, MPI_INT, op, 0, MPI_COMM_WORLD);
	MPI_Op_free(&op);
	if (rank == 0)
		printf("b[0] = %d\n", b[0]);

	// MPI_Barrier(MPI_COMM_WORLD);

	MPI_Op_create(&max, 1, &maxVal);
	MPI_Reduce(a, b, n, MPI_INT, maxVal, 0, MPI_COMM_WORLD);
	MPI_Op_free(&maxVal);
	if (rank == 0)
	{
		cout << "Own result : \t     b[0] == " << b[0] << "\tb[50] == " << b[50] << "\tb[n-1] == " << b[n-1] << endl;
	}

	// MPI_Barrier(MPI_COMM_WORLD);

	MPI_Reduce(a, b, n, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	if (rank == 0)
	{
		cout << "Result via MPI_MAX : b[0] == " << b[0] << "\tb[50] == " << b[50] << "\tb[n-1] == " << b[n-1] << endl;
	}

	MPI_Finalize();
}


/*
Assignment:
Understand the new functions in Assignment14.c. 
Create your own global function for finding the maximum element, 
compare the correctness of execution with the MPI_MAX operation in the MPI_Reduce() function

Run:
mpic++ Assignment14.cpp -o A14.exe

Output:
PS > mpiexec ./A14 -n 8
process 0 a[0] = 1
b[0] = 1
Own result :         b[0] == 8  b[50] == 58     b[n-1] == 1007
Result via MPI_MAX : b[0] == 8  b[50] == 58     b[n-1] == 1007
process 1 a[0] = 2
process 7 a[0] = 8
process 6 a[0] = 7
process 3 a[0] = 4
process 2 a[0] = 3
process 5 a[0] = 6
process 4 a[0] = 5
*/