#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
	int rank, value = 42;
	MPI_Init(&argc, &argv);
	char port_name[MPI_MAX_PORT_NAME];
	MPI_Comm intercomm;
	MPI_Status status;
	strcpy(port_name, argv[1]);
	
	cout << "Attempt to connect " << endl;
	MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
	cout << "Server connection " << endl;
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	cout << "Client sent value: " << value << endl;
	MPI_Send(&value, 1, MPI_INT, 0, 0, intercomm);
	
	// MPI_Recv(&value, MPI_INT, 0, intercomm);
	MPI_Recv(&value, 1, MPI_INT, 0, 0, intercomm, &status);
	cout << "Client got value: " << value << endl;
	
	MPI_Finalize();
	return 0;
}

/*
Assignment:

Run:
mpic++ Assignment19_serv.c -o serv.exe | mpic++ Assignment19_client.c -o client

Output:
PS > mpiexec -n 1 client 'ncalrpc:LAPTOP-J9VBK914[e2046380-7122-452f-8870-907d03e3ae5a] ncacn_ip_tcp:LAPTOP-J9VBK914[63470] 1'
Attempt to connect
Server connection
Client sent value: 42
Client got value: 25
*/
