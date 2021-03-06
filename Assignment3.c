#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);
	int rank, n, i, message;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0)
	{
		cout << "Hello from process " << rank << "\n";
		for (i = 1; i < n; i++)
		{
			MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			cout << "Hello from process " << message << endl;
		}
	}
	else
		MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}

/* 
Run: 
gcc ./Assignment3.c -lstdc++ -o Assignment3.exe -fopenmp

Output:
PS > mpiexec ./A3
Hello from process 0
Hello from process 7
Hello from process 2
Hello from process 5
Hello from process 3
Hello from process 6
Hello from process 1
Hello from process 4
*/
