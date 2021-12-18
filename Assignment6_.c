#include <iostream>
#include <mpi.h>
using namespace std;
int main(int argc, char **argv)
{
	int rank, size, ibuf;
	MPI_Status status;
	float rbuf;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	ibuf = rank;
	rbuf = 1.0 * rank;
	if (rank == 1) MPI_Send(&ibuf, 1, MPI_INT, 0, 5, MPI_COMM_WORLD);
	if (rank == 2) MPI_Send(&rbuf, 1, MPI_FLOAT, 0, 5, MPI_COMM_WORLD);
	if (rank == 0) {
		MPI_Probe(MPI_ANY_SOURCE, 5, MPI_COMM_WORLD, &status);
		if (status.MPI_TAG == 5) {
			MPI_Recv(&ibuf, 1, MPI_INT, 1, 5, MPI_COMM_WORLD, &status);
			MPI_Recv(&rbuf, 1, MPI_FLOAT, 2, 5, MPI_COMM_WORLD, &status);
			cout << "Process 0 recv " << ibuf << " from process 1, " << rbuf << " from process 2\n";
		}
		else if (status.MPI_TAG == 5) {
			MPI_Recv(&rbuf, 1, MPI_FLOAT, 2, 5, MPI_COMM_WORLD, &status);
			MPI_Recv(&ibuf, 1, MPI_INT, 1, 5, MPI_COMM_WORLD, &status);
			cout << "Process 0 recv " << rbuf << " from process 2, " << ibuf << " from process 1\n";
		}
	}
	MPI_Finalize();
}

/*
Assignment:
Assignment 6. MPI. MPI. Retrieving information about the message
attributes.
Compile the example Assignment6.c in detail, run it and explain it. 
Transform the program using the MPI_TAG field of the status structure in the 
condition

Run:
1)
mpic++ ./Assignment6.c -o A6_1.exe 

2)
mpic++ ./Assignment6_.c -o A6_2.exe 

Output:
1)
PS > mpiexec ./A6_1 -n 7
Process 0 recv 1 from process 1, 2from process 2

2)
PS > mpiexec ./A6_2 -n 7
Process 0 recv 1 from process 1, 2from process 2

*/