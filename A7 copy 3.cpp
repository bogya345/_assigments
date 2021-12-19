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
    const int len = 100;

    cout << "Allocating array with [" << len << "] size" << endl;
    int *a = new int[len];
    int *b = new int[len];
    for (int i = 0; i < len; i++)
    {
        a[i] = 1;
        b[i] = 1;
    }

    int rank, n, i, message;
    int sum = 0;
    int startInd = -1;
    int distributedSum[PROCNUM];
    for (i = 0; i < len; i++)
    {
        distributedSum[i] = 0;
    }
    int step, startIndex, endIndex;
    int z;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (z = 0; z < 8; z++)
    {
        if (z == rank)
        {
            // cout << "jopa" << endl;
            step = int(len / 8);
            startIndex = step * rank;
            endIndex = startIndex + step;
            cout << len << "\t" << step << "\t" << startIndex << "\t" << endIndex << endl;
        }
    }

    int tmp = 0;
    for (i = startIndex; i < endIndex; i++)
    {
        tmp += a[i] * b[i];
        // distributedSum[rank] += a[i] * b[i];
        // sum += a[i] * b[i];
    }
    distributedSum[rank] = tmp;
    // sum = sum + tmp;

    MPI_Barrier(MPI_COMM_WORLD);

    cout << "Sum from proccess #" << rank << " : " << distributedSum[rank] << endl;

    MPI_Finalize();

    sum += distributedSum[rank];

    cout << sum << endl;

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