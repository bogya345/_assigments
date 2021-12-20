#include "mpi.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
	int rank, size, i, rbuf;
	MPI_Init(&argc, &argv);
	MPI_Group group, new_group;
	MPI_Comm new_comm;
	int ranks[128], new_rank;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_group(MPI_COMM_WORLD, &group);

	for (i = 0; i < size / 2; i++) ranks[i] = i;

	if (rank < size / 2) MPI_Group_incl(group, size / 2, ranks, &new_group);
	else MPI_Group_excl(group, size / 2, ranks, &new_group);
	
	MPI_Comm_create(MPI_COMM_WORLD, new_group, &new_comm);
	MPI_Allreduce(&rank, &rbuf, 1, MPI_INT, MPI_SUM, new_comm);
	MPI_Group_rank(new_group, &new_rank);
	
	//Display values: "rank =, newrank =, rbuf ="
	cout << "rank = " << rank << "\tnew_rank = " << new_rank << "\trbuf = " << rbuf << endl;
	
	MPI_Finalize();
}


/*
Assignment:
Understand the new functions in Assignment15.c. 
Append part of code

Run:
mpic++ Assignment15.cpp -o A15.exe

Output:
PS > mpiexec ./A15 -n 8
rank = 3        new_rank = 3    rbuf = 6
rank = 2        new_rank = 2    rbuf = 6
rank = 1        new_rank = 1    rbuf = 6
rank = 0        new_rank = 0    rbuf = 6
rank = 7        new_rank = 3    rbuf = 22
rank = 5        new_rank = 1    rbuf = 22
rank = 6        new_rank = 2    rbuf = 22
rank = 4        new_rank = 0    rbuf = 22
*/