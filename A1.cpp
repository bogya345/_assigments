#include <iostream>
#include <random>
#include <string>
#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>

using namespace std;

int main(int argc, char **argv)
// int main()
{
    // string size = stringstream(argv[1]);
    string size;
    stringstream ss;

    ss << argv[1];
    ss >> size;

    // cout << "LOL OK " <<  << endl;
    const int len = stoi(size);
    
    cout << "Allocating array with [" << size << "] size" << endl;
    int *arr = new int[len];
    for(int i=0; i<=len; i++) {
        // arr[i] = rand();
        arr[i] = i;
        cout << "arr[" << i << "] = " << i << endl; 
        cout << "arr[" << i << "] == " << arr[i] << endl << endl;
    }

    printf("Start of parallel threads\n");

    #pragma omp parallel shared(arr, len) num_threads(10)
    {
        int threadNum = omp_get_thread_num();
        cout << "Thread #" + to_string(threadNum) + "# starts.\n";

        clock_t t = clock();

        int step = (len/10);
        int startIndex = step * threadNum;
        int endIndex = startIndex + step;

        int max = arr[startIndex];
        // cout << "#" << threadNum << "# startIndex == " << startIndex << endl;
        for(int i=startIndex+1; i<endIndex; i++) {
            // cout << "#" << threadNum << "# arr[i] == " << arr[i] << endl;
            if(arr[i] > max) {
                max = arr[i];
            }
        }

        t = clock() - t;
        cout << "#" + to_string(threadNum) + "# - Max value is " + to_string(max) + "\tTimer value: " << t << "\n";
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