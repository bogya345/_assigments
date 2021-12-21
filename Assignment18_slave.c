#include "mpi.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
	int rank;
	MPI_Comm intercomm;
	MPI_Init(&argc, &argv);
	MPI_Comm_get_parent(&intercomm);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Send(&rank, 1, MPI_INT, 0, rank, intercomm);
	cout << "Proc. #" << rank << " : Send message(" << rank << ")" << endl; 
	MPI_Finalize();
	return 0;
}

/*
Assignment:

Run:
mpic++ Assignment18_slave.c -o slave.exe

Output:
*/
