#include <stdio.h>
#include "mpi.h"
#include <iostream>
#define BUFSIZE 100
using namespace std;
int main(int argc, char **argv)
{
	int bufsize, num, sum;
	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_File fh;
	char buf[BUFSIZE];
	MPI_File_open(MPI_COMM_WORLD, "file.txt", MPI_MODE_RDONLY | MPI_MODE_DELETE_ON_CLOSE, MPI_INFO_NULL, &fh);
	MPI_File_set_view(fh, 0, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
	sum = 0;
	do {
		MPI_File_read(fh, buf, BUFSIZE, MPI_CHAR, &status);
		MPI_Get_count(&status, MPI_CHAR, &num);
		printf("buf=%s\n", buf);
		sum += num;
	} while (num >= BUFSIZE);
	MPI_File_close(&fh);
	//print the number of read symbols sum from the file
	cout << sum << endl;
	MPI_Finalize();
}

/*
Assignment:

Run:
mpic++ Assignment20.c -o A20

Output:
PS > mpiexec -n 1 A20
buf=Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the ¶☺
buf=industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type a¶☺
buf=nd scrambled it to make a type specimen book. It has survived not only five centuries, but also the ¶☺
buf=leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s w¶☺
buf=ith the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop p¶☺
buf=ublishing software like Aldus PageMaker including versions of Lorem Ipsum.re recently with desktop p¶☺
574
*/
