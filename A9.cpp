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
    const int len = 8;
    double a[len], b[len], c[len];
    double singleA, singleB;
    int i = 0;
    // double aa[2];
    for (i = 0; i < PROCNUM; i++)
    {
        a[i] = -1;
        b[i] = -1;
    }

    int rank, n;
    double sum = 0;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // singleValue = 1;
    // a[rank] = rank;
    singleA = rank;
    // cout << "Proc. #" << rank << " : \t" << a[rank] << endl;
    cout << "Proc. #" << rank << " : \t" << singleA << endl;

    // MPI_Reduce(&a, &b, len, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&singleA, &singleB, len, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        cout << "Sum: " <<  singleB << endl;
    }

    MPI_Finalize();

    // char e;
    // cin >> e;

    return 0;
}

/*
Assignment:
Write an MPI program in which the global vector addition operation is modeled by a 
doubling (cascade) scheme using point-to-point data transfers. Compare the execution time 
of such a simulation using the MPI_Reduce procedure on as many processes as possible. 
Each process stores an array of 1,000,000 elements equal to ‘1’

Run:
mpic++ A9.cpp -o A9.exe 

Output:
PS > mpiexec ./A9 -n 8
Proc. #1 :      1
Proc. #2 :      2
Proc. #6 :      6
Proc. #3 :      3
Proc. #4 :      4
Proc. #7 :      7
Proc. #0 :      0
Proc. #5 :      5
Sum: 28
*/