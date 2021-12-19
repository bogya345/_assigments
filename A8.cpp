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

    const int len = 10000;
    const int N = 10;
    int L = -1;
    int s = -1;
    int R = -1;

    int targetFor0 = 1;
    int targetFor1 = 0;

    clock_t t0;
    clock_t t1;

    int t0secs = -1;
    int t1secs = -1;

    int rank, n, i, msg;

    msg = 1;
    int iters = 0;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        while (iters < N)
        {
            cout << "Iteration #" << iters << ": " << endl;

            msg = iters;
            t0 = clock();
            
            MPI_Send(
                &msg
                , 1
                , MPI_INT
                , targetFor0
                , 0
                , MPI_COMM_WORLD
                );
            cout << endl;

            MPI_Recv(
                &msg
                , 1
                , MPI_INT
                , targetFor0
                , MPI_ANY_TAG
                , MPI_COMM_WORLD
                , &status
                );
            cout << endl;

            t0 = (clock() - t0) / 1000;
            // if (t0 == 0) { t0 = 0.000000001; }
            t0 = 1;
            cout << "\t t0=" << t0 << endl;
            L = 100 * sizeof(msg);
            R = (2 * N * L) / t0;
            s = t0 / (2 * N);
            cout << "#0# MSG:" << msg << "\t L = " << L << "\t R = " << R << "\t s = " << s << endl;

            iters++;
        }

        msg += 1;
        MPI_Send(
                &msg
                , 1
                , MPI_INT
                , targetFor0
                , 0
                , MPI_COMM_WORLD
                );

        cout << "################## Proc. 0 finished ##################" << endl;
    }

    if (rank == 1)
    {
        while (msg < N)
        {
            cout << "Recieving msg (in " << rank << " proc.) : " << msg << endl;
            MPI_Recv(
                &msg
                , 1
                , MPI_INT
                , targetFor1
                , MPI_ANY_TAG
                , MPI_COMM_WORLD
                , &status
                );
            cout << endl;

            t1 = (clock() - t1) / 1000;
            t1 = 1;
            cout << "\t t1=" << t1 << endl;
            L = 100 * sizeof(msg);
            R = (2 * N * L) / t1;
            s = t1 / (2 * N);
            cout << "#1# MSG:" << msg << "\t L = " << L << "\t R = " << R << "\t s = " << s << "\t t1=" << t1 << endl;

            if (msg >= N) { break; }

            cout << "Sending msg (in " << rank << " proc.) : " << msg << endl;
            MPI_Send(
                &msg
                , 1
                , MPI_INT
                , targetFor1
                , 0
                , MPI_COMM_WORLD
                );
            cout << endl;

            t1 = clock();
        }

        cout << "################## Proc. 1 finished ##################" << endl;
    }

    MPI_Finalize();

    // char e;
    // cin >> e;

    return 0;
}

/*
Assignment:

Run:
mpic++ A8.cpp -o A8.exe 

Output:

*/