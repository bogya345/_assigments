#include <iostream>
#include <random>
#include <string>
#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#define PROCNUM 8

using namespace std;

int main(int argc, char **argv)
{
    string size;
    stringstream ss;

    ss << argv[1];
    ss >> size;

    // cout << "LOL OK " <<  << endl;
    // const int len = stoi(size);
    const int len = 1000;

    cout << "Allocating array with [" << size << "] size" << endl;
    int *a = new int[len];
    int *b = new int[len];
    for (int i = 0; i < len; i++)
    {
        a[i] = 1;
        b[i] = 1;
    }

    // printf("Start of parallel threads\n");

    int rank, n, i, message;
    int sum = 0;
    int startInd = -1;
    int distributedSum[PROCNUM];
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {

        for (i = 0; i < (len / rank); i++)
        {
            distributedSum[0] += a[i] + b[i];
            sum += a[i] + b[i];
        }

        for (i = 1; i < PROCNUM; i++)
        {
            MPI_Send(&sum, 1, MPI_INT, i, 5, MPI_COMM_WORLD);
        }
    }
    else
    {
        // for (i = 0; i < PROCNUM; i++)
        // {
        // if (i == rank)
        // {

        MPI_Recv(&sum, 1, MPI_INT, 0, 5, MPI_COMM_WORLD, &status);
        for (i = 1; i < PROCNUM; i++)
        {
            distributedSum[rank] += a[i] + b[i];
            sum += a[i] + b[i];
        }
        
        // }
        // }
    }

    MPI_Finalize();

    for (i = 0; i < PROCNUM; i++)
    {
        cout << "Sum from proccess #" << i << " : " << distributedSum[i] << "\n";
    }

    cout << "Common variable sum = " << sum << "\n";

    // char e;
    // cin >> e;

    return 0;
}

/*
Assignment:

Run:
mpic++ ./A7.cpp -o A7.exe

Output:
PS > ./A7 -n 7

*/