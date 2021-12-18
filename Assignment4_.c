#include <iostream>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);
	int rank, n, i, message;
	// n = 10;
	// rank = 10;
	// std::cout << n << "\n";
	// std::cout << rank << "\n";

	int myMsg = 6;

	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// std::cout << "Here num of process: " << MPI_Comm_size << "\n";

	if (rank == 6)
	{
		std::cout << "Hello from process " << rank << "\n";
		for (i = 0; i < n; i++)
		{
			if (i == 6) { continue; }
			// MPI_Recv(&message, i, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			MPI_Recv(
				&message			// address of the begginng of the recieved data location
				, 1					// number of elements recieve
				, MPI_INT			// datatype
				, i					// is the number of th sending process (source)
				, MPI_ANY_TAG		// message indentifier (name)
				, MPI_COMM_WORLD	// communicator
				, &status			// message attributes
				);
			// std::cout << "Hello from process " << message << "\n";
			std::cout << "Process " << i << ":\t Message: " << message << "\n";
		}
	}
	else
	{
		// MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Send(
			&myMsg,			// address of the begining of the transferred data location
			1,				// number of elements set
			MPI_INT, 		// datatype
			6, 				// is the number of receiving process (destination)
			0, 				// message identifier
			MPI_COMM_WORLD	// communicator
			);
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
PS > mpiexec ./A4 -n 7
Hello from process 6
Process 0:       Message: 6
Process 1:       Message: 6
Process 2:       Message: 6
Process 3:       Message: 6
Process 4:       Message: 6
Process 5:       Message: 6
Process 7:       Message: 6

*/