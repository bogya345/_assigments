#include <cstdlib>
#include "mpi.h"
#include <time.h>
#include <iostream>

using namespace std;

// The function of allocating memory for a two-dimensional array
double **malloc_array(long int n)
{
    double **matrix = new double *[n];
    for (int i = 0; i < n; i++)
        matrix[i] = new double[n];
    return matrix;
}

// Memory free function
void free_array(double **matrix, long int n)
{
    for (int i = 0; i < n; i++)
        delete[] matrix[i];
    delete[] matrix;
}

// The function of initializing a matrix with random numbers from [0,1]
void ones_init_matrix(double **matrix, long int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = 1;
}

// Matrix zeroing function
void zero_init_matrix(double **matrix, long int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = 0.0;
}

int main(int argc, char **argv)
{
    // const long int N = 500;
    const long int N = 1000;
    double **A, **B, **C;

    // Memory allocation for matrices A, B, C
    A = malloc_array(N);
    B = malloc_array(N);
    C = malloc_array(N);

    // Initialization of matrices
    ones_init_matrix(A, N);
    ones_init_matrix(B, N);
    zero_init_matrix(C, N);

    clock_t t;
    clock_t tTotal;

    int rank, size, i;
    int step, startInd, endInd;
    int singleSum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //matrix initialization by each process

    MPI_Barrier(MPI_COMM_WORLD); //barrier process synchronization

    // start timing for each process
    t = clock();
    // matrix multiplication
     for (int i = 0; i < N; i++)
        for (int k = 0; k < N; k++)
            for (int j = 0; j < N; j++)
                C[i][j] += A[i][k] * B[k][j];
    // end of timing
    t = clock() - t;

    // // start timing for each process
    // t = clock();
    // step = N / 8; //125
    // startInd = step * rank;
    // endInd = startInd + step;
    // // matrix multiplication
    // for (int i = 0; i < N; i++)
    //     for (int k = 0; k < N; k++)
    //         for (int j = startInd; j < endInd; j++)
    //         {
    //             // C[i][j] += A[i][k] * B[k][j];
    //             singleSum += A[i][k] * B[k][j];
    //             MPI_Reduce(&singleSum, &C[i][j], 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    //         }

    // // end of timing
    // t = clock() - t;

    // output the execution time of matrix multiplication at each process
    cout << "Proc. # " << rank << " : Time == " << t / CLOCKS_PER_SEC << " seconds" << endl;

    MPI_Reduce(&t, &tTotal, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        cout << "Total time: " << tTotal / CLOCKS_PER_SEC << endl;
    }

    MPI_Finalize();
}

/*
Assignment:

Run:
mpic++ Assignment13.cpp -o A13

Output:
PS > mpiexec -n 8 A13
Proc. # 2 : Time == 6 seconds
Proc. # 3 : Time == 6 seconds
Proc. # 1 : Time == 6 seconds
Proc. # 5 : Time == 6 seconds
Proc. # 0 : Time == 6 seconds
Proc. # 6 : Time == 6 seconds
Proc. # 4 : Time == 6 seconds
Proc. # 7 : Time == 6 seconds
Total time: 54
*/
