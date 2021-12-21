#include <stdio.h>
#include "mpi.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
	int rank;
	const int bufSize = 100;
	MPI_Init(&argc, &argv);
	MPI_File fh;
	char buf[bufSize];
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_File_open(MPI_COMM_WORLD, "file1.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
	MPI_File_set_view(fh, rank * bufSize, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
	MPI_File_read_all(fh, buf, bufSize, MPI_CHAR, MPI_STATUS_IGNORE);
// 	printf("process %d, buf=%s\n", rank, buf);
	cout << "process " << rank << ", buf=" << buf << endl; 
	MPI_File_close(&fh);
	MPI_Finalize();
}

/*
Assignment:

Run:
mpic++ Assignment21.c -o A21

Output:
PS > mpiexec -n 1 A21
process 0, buf=Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the

*/