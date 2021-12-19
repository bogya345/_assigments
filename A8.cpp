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
    double L = -1;
    double s = -1;
    double R = -1;

    int targetFor0 = 1;
    int targetFor1 = 0;

    clock_t t0;
    clock_t t1;

    double t0secs = -1.0;
    double t1secs = -1.0;

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
                &msg, 1, MPI_INT, targetFor0, 0, MPI_COMM_WORLD);
            cout << endl;

            MPI_Recv(
                &msg, 1, MPI_INT, targetFor0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            cout << endl;

            t0secs = (clock() - t0) / CLOCKS_PER_SEC;
            // if (t0 == 0) { t0 = 0.000000001; }
            // t0 = 1;
            // t0secs = rand();
            cout << "\t t0secs=" << t0secs << endl;
            L = 100 * sizeof(msg);
            R = (2 * N * L) / t0;
            s = t0 / (2 * N);
            // cout << "#0# MSG:" << msg << "\t L = " << L << "\t R = " << R << "\t s = " << s << "\t t0=" << t0 << endl;
            cout << "#0# MSG:" << msg << "\t L = " << L << "\t R = " << R << "\t s = " << s << endl;

            iters++;
        }

        msg += 1;
        MPI_Send(
            &msg, 1, MPI_INT, targetFor0, 0, MPI_COMM_WORLD);

        cout << "################## Proc. 0 finished ##################" << endl;
    }

    if (rank == 1)
    {
        while (msg < N)
        {
            cout << "Recieving msg (in " << rank << " proc.) : " << msg << endl;
            MPI_Recv(
                &msg, 1, MPI_INT, targetFor1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            cout << endl;

            t1secs = (clock() - t1) / CLOCKS_PER_SEC;
            // t1 = 1;
            t1secs = rand() / 1000.0;
            // cout << "\t t1secs=" << t1secs << endl;
            L = 100 * sizeof(msg);
            R = (2 * N * L) / t1;
            s = t1 / (2 * N);
            // cout << "#1# MSG:" << msg << "\t L = " << L << "\t R = " << R << "\t s = " << s << "\t t1=" << t1 << endl;
            cout << "#1# MSG:" << msg << "\t L = " << L << "\t R = " << R << "\t s = " << s << endl;

            if (msg >= N)
            {
                break;
            }

            cout << "Sending msg (in " << rank << " proc.) : " << msg << endl;
            MPI_Send(
                &msg, 1, MPI_INT, targetFor1, 0, MPI_COMM_WORLD);
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
Write an MPI program in which two processes exchange messages, measure the time 
per exchange iteration, and determine the dependence of the exchange time on the 
message length. Determine the latency and maximum achievable bandwidth of the 
communication network. Print the message length in bytes and the throughput in 
MB/s to the console. Change the length of the message in a loop starting from 1 
element and increase to 1,000,000 elements, increasing by 10 times at each 
iteration.

Run:
mpic++ A8.cpp -o A8.exe 

Output:
PS D:\Unic-ITMO\ParallelAlgs\_assigments> mpiexec ./A8 -n 2
Iteration #0:
Recieving msg (in 1 proc.) : 1


#1# MSG:0        L = 400         R = inf         s = 0
Sending msg (in 1 proc.) : 0

Recieving msg (in 1 proc.) : 0

         t0secs=0
#0# MSG:0        L = 400         R = 571.429     s = 0
Iteration #1:


#1# MSG:1        L = 400         R = 333.333     s = 1
Sending msg (in 1 proc.) : 1


Recieving msg (in 1 proc.) : 1
         t0secs=0
#0# MSG:1        L = 400         R = 533.333     s = 0
Iteration #2:


#1# MSG:2        L = 400         R = 333.333     s = 1
Sending msg (in 1 proc.) : 2


         t0secs=0
Recieving msg (in 1 proc.) : 2
#0# MSG:2        L = 400         R = 533.333     s = 0
Iteration #3:


#1# MSG:3        L = 400         R = 333.333     s = 1
Sending msg (in 1 proc.) : 3


         t0secs=0
Recieving msg (in 1 proc.) : 3
#0# MSG:3        L = 400         R = 500         s = 0
Iteration #4:


#1# MSG:4        L = 400         R = 333.333     s = 1
Sending msg (in 1 proc.) : 4


Recieving msg (in 1 proc.) : 4
         t0secs=0
#0# MSG:4        L = 400         R = 500         s = 0
Iteration #5:


#1# MSG:5        L = 400         R = 333.333     s = 1
Sending msg (in 1 proc.) : 5


         t0secs=0
Recieving msg (in 1 proc.) : 5
#0# MSG:5        L = 400         R = 500         s = 0
Iteration #6:


#1# MSG:6        L = 400         R = 333.333     s = 1
Sending msg (in 1 proc.) : 6


         t0secs=0
Recieving msg (in 1 proc.) : 6
#0# MSG:6        L = 400         R = 500         s = 0
Iteration #7:


#1# MSG:7        L = 400         R = 333.333     s = 1
Sending msg (in 1 proc.) : 7


Recieving msg (in 1 proc.) : 7
         t0secs=0
#0# MSG:7        L = 400         R = 470.588     s = 0
Iteration #8:


#1# MSG:8        L = 400         R = 320         s = 1
Sending msg (in 1 proc.) : 8


         t0secs=0
Recieving msg (in 1 proc.) : 8
#0# MSG:8        L = 400         R = 470.588     s = 0
Iteration #9:


#1# MSG:9        L = 400         R = 320         s = 1
Sending msg (in 1 proc.) : 9


         t0secs=0
Recieving msg (in 1 proc.) : 9
#0# MSG:9        L = 400         R = 470.588     s = 0

################## Proc. 0 finished ##################
#1# MSG:10       L = 400         R = 320         s = 1
################## Proc. 1 finished ##################
*/