#include "mpi.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
	int size, rank, position, i;
	float a[10];
	char b[10], buf[100];
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	for (i = 0; i < 10; i++) {
		a[i] = rank + 1.0;
		if (rank == 0) b[i] = 'a';
		else b[i] = 'b';
	}
	
	if (rank == 2) {
		for (i = 0; i < 10; i++) {
			cout << "a[" << i << "] == " << a[i] << "\tb[" << i << "] == " << b[i] << endl;
		}
		cout << endl;
	}
	
	position = 0;
	if (rank == 0) {
		MPI_Pack(a, 10, MPI_FLOAT, buf, 100, &position, MPI_COMM_WORLD);
		MPI_Pack(b, 10, MPI_CHAR, buf, 100, &position, MPI_COMM_WORLD);
		MPI_Bcast(buf, 100, MPI_PACKED, 0, MPI_COMM_WORLD);
	}
	else {
		MPI_Bcast(buf, 100, MPI_PACKED, 0, MPI_COMM_WORLD);
		position = 0;
		MPI_Unpack(buf, 100, &position, a, 10, MPI_FLOAT, MPI_COMM_WORLD);
		MPI_Unpack(buf, 100, &position, b, 10, MPI_CHAR, MPI_COMM_WORLD);
	}
	
	if (rank == 2) {
		for (i = 0; i < 10; i++) {
			cout << "a[" << i << "] == " << a[i] << "\tb[" << i << "] == " << b[i] << endl;
		}
		cout << endl;
	}
	
	MPI_Finalize();
}

/*
Assignment:

Run:
mpic++ Assignment17.cpp -o A17.exe

Output:
PS > mpiexec -n 8 A17
a[0] == 3       b[0] == b
a[1] == 3       b[1] == b
a[2] == 3       b[2] == b
a[3] == 3       b[3] == b
a[4] == 3       b[4] == b
a[5] == 3       b[5] == b
a[6] == 3       b[6] == b
a[7] == 3       b[7] == b
a[8] == 3       b[8] == b
a[9] == 3       b[9] == b

a[0] == 1       b[0] == a
a[1] == 1       b[1] == a
a[2] == 1       b[2] == a
a[3] == 1       b[3] == a
a[4] == 1       b[4] == a
a[5] == 1       b[5] == a
a[6] == 1       b[6] == a
a[7] == 1       b[7] == a
a[8] == 1       b[8] == a
a[9] == 1       b[9] == a
*/
