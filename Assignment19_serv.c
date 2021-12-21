#include <stdio.h>
#include "mpi.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
	int r = 25;
	MPI_Init(&argc, &argv);
	char port_name[MPI_MAX_PORT_NAME];
	MPI_Status status;
	MPI_Comm intercomm;
	MPI_Open_port(MPI_INFO_NULL, port_name);
	
// 	printf("portname: %s\n", port_name);
	cout << "portname: " << port_name << endl;
	
	cout << "Waiting for the client ... " << endl;
	MPI_Comm_accept(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
	cout << "Client connected " << endl;
	
	cout << "Server sent value: " << r << endl;
	
	MPI_Recv(&r, 1, MPI_INT, 0, 0, intercomm, &status);
	
	cout << "Server got value: " << r << endl;
	r = 25;
	MPI_Send(&r, 1, MPI_INT, 0, 0, intercomm);
	
	MPI_Comm_free(&intercomm);
	MPI_Close_port(port_name);
	
// 	printf("Клиент отправил %d\n", r);
	// cout << "Client sent " << r << endl;
	
	MPI_Finalize();
	return 0;
}

/*
Assignment:

Run:
mpic++ Assignment19_serv.c -o serv.exe | mpic++ Assignment19_client.c -o client

Output:
PS > mpiexec -n 1 serv
portname: ncalrpc:LAPTOP-J9VBK914[e2046380-7122-452f-8870-907d03e3ae5a] ncacn_ip_tcp:LAPTOP-J9VBK914[63470] 1
Waiting for the client ...
Client connected
Server sent value: 25
Server got value: 42
*/
