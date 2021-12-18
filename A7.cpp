#include <iostream>
#include <random>
#include <string>
#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sstream>

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
    for (int i = 0; i <= len; i++)
    {
        a[i] = 1;
        b[i] = 1;
    }

    printf("Start of parallel threads\n");

#pragma omp parallel shared(arr, len) num_threads(10)
    {
        int sum = 0;
        
        int threadNum = omp_get_thread_num();
        cout << "Thread #" + to_string(threadNum) + "# starts.\n";

        clock_t t = clock();

        int step = (len / 10);
        int startIndex = step * threadNum;
        int endIndex = startIndex + step;

        int max = a[startIndex];;
        if (!(startIndex + 1 < endIndex))
        {
            // cout << "#" << threadNum << "# startIndex == " << startIndex << endl;
            for (int i = startIndex + 1; i < endIndex; i++)
            {
                // cout << "#" << threadNum << "# arr[i] == " << arr[i] << endl;
                sum += a[i] + b[i];
            }
        }

        t = clock() - t;
        cout << "#" + to_string(threadNum) + "# - Max value is " + to_string(max) + "\tTimer value: " << t / ((clock_t)1000) << "\n";
        // cout << "Max value is " << max << endl;
    }

    // cout << CLOCKS_PER_SEC;

    printf("End of parallel threads");

    // char e;
    // cin >> e;

    return 0;
}

/*
gcc A1.cpp -lstdc++ -o A1.exe -fopenmp 
-openmp
*/

/* Output:
PS D:\Unic-ITMO\ParallelAlgs\_assigments> ./A1 100
Allocating array with [100] size
Start of parallel threads
Thread #8# starts.
#8# - Max value is 80   Timer value: Thread #4# starts.
#4# - Max value is 40   Timer value: 0
Thread #9# starts.
#9# - Max value is 90   Timer value: 0
Thread #6# starts.
#6# - Max value is 60   Timer value: 0
Thread #7# starts.
#7# - Max value is 70   Timer value: 0
0
Thread #0# starts.
Thread #2# starts.
#2# - Max value is 20   Timer value: 0
#0# - Max value is 0    Timer value: 0
Thread #3# starts.
Thread #1# starts.
#1# - Max value is 10   Timer value: 0
#3# - Max value is 30   Timer value: 0
Thread #5# starts.
#5# - Max value is 50   Timer value: 0
End of parallel threads
*/