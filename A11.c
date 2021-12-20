#include <iostream>
#include "mpi.h"
using namespace std;
int main(int argc, char **argv)
{
	int rank, size, prev, next;
	int buf[2];
	int sendTag = 0;
	int recvTag = 0;
	MPI_Init(&argc, &argv);
	MPI_Request reqs[4];
	MPI_Status stats[4];
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	prev = rank - 1;
	next = rank + 1;

	sendTag = 1;
	recvTag = 1;
	
	if (rank == 0) prev = size - 1;
	if (rank == size - 1) next = 0;

	MPI_Sendrecv(
		&rank		// address of the data to be sent
		,1			// number of sent variables
		,MPI_INT	// type of data being sent
		,prev		// dest
		,rank		// tag of the sent message
		,&buf[0]		//is the number of received 
		,1				// count of received
		,MPI_INT		// datatype
		,next			// source
		,next			// tag of the received
		,MPI_COMM_WORLD	// communicator
		,stats	// status
	);

	MPI_Sendrecv(
		&rank		// address of the data to be sent
		,1			// number of sent variables
		,MPI_INT	// type of data being sent
		,next		// dest
		,rank		// tag of the sent message
		,&buf[1]		//is the number of received 
		,1				// count of received
		,MPI_INT		// datatype
		,prev			// source
		,prev			// tag of the received
		,MPI_COMM_WORLD	// communicator
		,stats	// status
	);

	// MPI_Irecv(&buf[0], 1, MPI_INT, prev, 5, MPI_COMM_WORLD, &reqs[0]);
	// MPI_Irecv(&buf[1], 1, MPI_INT, next, 6, MPI_COMM_WORLD, &reqs[1]);
	// MPI_Isend(&rank, 1, MPI_INT, prev, 6, MPI_COMM_WORLD, &reqs[2]);
	// MPI_Isend(&rank, 1, MPI_INT, next, 5, MPI_COMM_WORLD, &reqs[3]);
	// MPI_Waitall(4, reqs, stats);
	
	//Your code here.
	//Here you need to display the number of the current process, and what it receives from the previous and next processes.
	cout << "Proc. #" << rank << " : \t" << "buf[0] == " << buf[0] << "\tbuf[1] == " << buf[1] << endl;
	
	MPI_Finalize();
}

/*
Assignment:
Based on Assignment 10, write a program for ring topology exchange using the MPI_Sendrecv() function.

Run:
mpic++ Assignment11.c -o A11.exe

Output:
PS > mpiexec ./A11 -n 8
Proc. #1 :      buf[0] == 2     buf[1] == 0
Proc. #0 :      buf[0] == 1     buf[1] == 7
Proc. #4 :      buf[0] == 5     buf[1] == 3
Proc. #3 :      buf[0] == 4     buf[1] == 2
Proc. #5 :      buf[0] == 6     buf[1] == 4
Proc. #7 :      buf[0] == 0     buf[1] == 6
Proc. #6 :      buf[0] == 7     buf[1] == 5
Proc. #2 :      buf[0] == 3     buf[1] == 1
*/