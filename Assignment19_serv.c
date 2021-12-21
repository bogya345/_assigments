#include <stdio.h>
#include "mpi.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
	int r;
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
	
	MPI_Comm_free(&intercomm);
	MPI_Close_port(port_name);
	
// 	printf("Клиент отправил %d\n", r);
	cout << "Client sent " << r << endl;
	
	MPI_Finalize();
	return 0;
}
