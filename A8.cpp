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
Recieving msg (in 1 proc.) : 1
Iteration #0:


         t1=1
#1# MSG:0        L = 400         R = 8000        s = 0   t1=1
Sending msg (in 1 proc.) : 0

Recieving msg (in 1 proc.) : 0

         t0=1
#0# MSG:0        L = 400         R = 8000        s = 0
Iteration #1:


         t1=1
#1# MSG:1        L = 400         R = 8000        s = 0   t1=1
Sending msg (in 1 proc.) : 1


Recieving msg (in 1 proc.) : 1
         t0=1
#0# MSG:1        L = 400         R = 8000        s = 0
Iteration #2:


         t1=1
#1# MSG:2        L = 400         R = 8000        s = 0   t1=1
Sending msg (in 1 proc.) : 2


Recieving msg (in 1 proc.) : 2
         t0=1
#0# MSG:2        L = 400         R = 8000        s = 0
Iteration #3:


         t1=1
#1# MSG:3        L = 400         R = 8000        s = 0   t1=1
Sending msg (in 1 proc.) : 3


Recieving msg (in 1 proc.) : 3
         t0=1
#0# MSG:3        L = 400         R = 8000        s = 0
Iteration #4:


         t1=1
#1# MSG:4        L = 400         R = 8000        s = 0   t1=1
Sending msg (in 1 proc.) : 4


Recieving msg (in 1 proc.) : 4
         t0=1
#0# MSG:4        L = 400         R = 8000        s = 0
Iteration #5:


         t1=1
#1# MSG:5        L = 400         R = 8000        s = 0   t1=1
Sending msg (in 1 proc.) : 5


Recieving msg (in 1 proc.) : 5
         t0=1
#0# MSG:5        L = 400         R = 8000        s = 0
Iteration #6:


         t1=1
#1# MSG:6        L = 400         R = 8000        s = 0   t1=1
Sending msg (in 1 proc.) : 6


         t0=1
Recieving msg (in 1 proc.) : 6
#0# MSG:6        L = 400         R = 8000        s = 0
Iteration #7:


         t1=1
#1# MSG:7        L = 400         R = 8000        s = 0   t1=1
Sending msg (in 1 proc.) : 7


Recieving msg (in 1 proc.) : 7
         t0=1
#0# MSG:7        L = 400         R = 8000        s = 0
Iteration #8:


         t1=1
#1# MSG:8        L = 400         R = 8000        s = 0   t1=1
Sending msg (in 1 proc.) : 8


Recieving msg (in 1 proc.) : 8
         t0=1
#0# MSG:8        L = 400         R = 8000        s = 0
Iteration #9:


         t1=1
#1# MSG:9        L = 400         R = 8000        s = 0   t1=1
Sending msg (in 1 proc.) : 9


         t0=1
Recieving msg (in 1 proc.) : 9
#0# MSG:9        L = 400         R = 8000        s = 0

################## Proc. 0 finished ##################
         t1=1
#1# MSG:10       L = 400         R = 8000        s = 0   t1=1
################## Proc. 1 finished ##################
*/