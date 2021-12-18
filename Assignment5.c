#include <iostream>
#include "mpi.h"
#define NTIMES 100
using namespace std;
int main(int argc, char **argv)
{
	double time_start, time_finish;
	int rank, i;
	int len;
	char *name = new char;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(name, &len);
	time_start = MPI_Wtime();
	for (i = 0; i < NTIMES; i++)
		time_finish = MPI_Wtime();
	cout << "processor " << name << ", process " << rank << "time = " << (time_finish - time_start) / NTIMES << endl;
	MPI_Finalize();
}

/*
Assignment:
Assignment 5. MPI. Determination of the execution time.
Compile and run Assignment5.c program.
Explain in detail how it works.
Determine the execution time of the program from the previous task

Run:
mpic++ ./Assignment5.c -o A5.exe 

Output:
PS > mpiexec ./A5
processor LAPTOP-J9VBK914, process 7time = 3.9e-08
processor LAPTOP-J9VBK914, process 6time = 3.8e-08
processor LAPTOP-J9VBK914, process 5time = 4.1e-08
processor LAPTOP-J9VBK914, process 4time = 6.4e-08
processor LAPTOP-J9VBK914, process 2time = 6e-08
processor LAPTOP-J9VBK914, process 0time = 3.9e-08
processor LAPTOP-J9VBK914, process 3time = 3.8e-08
processor LAPTOP-J9VBK914, process 1time = 5.3e-08

*/