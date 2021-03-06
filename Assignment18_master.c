#include "mpi.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
	int size, rank1, rank2 ,i;
	MPI_Status status;
	MPI_Comm intercomm;
	char slave[10] = "./slave";
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_spawn(slave, MPI_ARGV_NULL, 2, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm, MPI_ERRCODES_IGNORE);
	MPI_Recv(&rank1, 1, MPI_INT, 0, 0, intercomm, &status);
	MPI_Recv(&rank2, 1, MPI_INT, 1, 1, intercomm, &status);
	//Display "Slaves rank1 and rank2 are working", instead of the words rank1 and rank2 their values should be displayed.
	cout << "Slaves " << rank1 <<" and " << rank2 << " are working" << endl;
	MPI_Finalize();
	return 0;
}


/*
Assignment:

Run:
mpic++ Assignment18_master.c -o A18m.exe

Output:
PS > mpiexec -n 1 A18m
Proc. #0 : Send message(0)
Proc. #1 : Send message(1)
Slaves 0 and 1 are working
*/
