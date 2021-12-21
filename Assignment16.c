#include "mpi.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
	int rank, size, rank1;
	MPI_Init(&argc, &argv);
	MPI_Comm comm_revs;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_split(MPI_COMM_WORLD, rank%2, size - rank, &comm_revs);
	MPI_Comm_rank(comm_revs, &rank1);
	//Display rank and rank1
	cout << "rank == " << rank << "\trank1 == " << rank1 << endl;
	MPI_Comm_free(&comm_revs);
	MPI_Finalize();
}


/*
Assignment:

Run:
mpic++ Assignment16.cpp -o A16.exe

Output:
PS > mpiexec A16 -n 8
rank == 0       rank1 == 3
rank == 1       rank1 == 3
rank == 4       rank1 == 1
rank == 7       rank1 == 0
rank == 6       rank1 == 0
rank == 3       rank1 == 2
rank == 5       rank1 == 1
rank == 2       rank1 == 2
*/