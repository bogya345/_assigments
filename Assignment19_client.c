#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
	int rank, value;
	MPI_Init(&argc, &argv);
	char port_name[MPI_MAX_PORT_NAME];
	MPI_Comm intercomm;
	strcpy(port_name, argv[1]);
	
	cout << "Attempt to connect " << endl;
	MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
	cout << "Server connection " << endl
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	cout << "Client sent value: " << value << endl;
	MPI_Send(&rank, 1, MPI_INT, 0, 0, intercomm);
	
	MPI_Rec($value, 1, MPI_INT, 0, 0, intercomm);
	cout << "Client got value: " << value << endl;
	
	MPI_Finalize();
	return 0;
}
