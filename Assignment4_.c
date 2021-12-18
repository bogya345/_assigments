#include <iostream>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);
	int rank, n, i, message;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
	{
		std::cout << "Hello from process " << rank << "\n";
		for (i = 1; i < n; i++)
		{
			MPI_Recv(&message, i, MPI_INT, MPI_ANY_SOURCE,
					 MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			// std::cout << "Hello from process " << message << "\n";
			std::cout << "Process " << message << ":\t Message: " << message << "\n";
		}
	}
	else
	{
		// MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	
	MPI_Finalize();
	return 0;
}

/*
Assignment:
#6
Receiving messages and outputting information to the console should be carried out 
by a process with a number that matches the number of your version (6).

Send the char value of the variable equal to the rank value of the sender process and 
output to the console the information received by the root process from the other
processes.

Run:
mpic++ ./Assignment4_.cpp -o A4.exe

Output:


*/