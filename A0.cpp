#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    // string size;
    // stringstream ss;

    // ss << argv[1];
    // ss >> size;

    char* str = argv[1]; // declare the size of string
    // cout << " Enter a string: " <<endl;  
    // cin.getline(str, 100); // use getline() function to read a string from input stream  
    // str = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16";

    char *ptr; // declare a ptr pointer  
    ptr = strtok(str, " , "); // use strtok() function to separate string using comma (,) delimiter.  
    // cout << " \n Split string using strtok() function: " << endl;  
    cout << " \n Words in sentence: " << endl;  

    while (ptr != NULL)  
    {  
        cout << ptr  << endl; // print the string token  
        ptr = strtok (NULL, " , ");  
    }  

    return 0;
}

/*
gcc A0.cpp -lstdc++ -o A0.exe
*/

/* Output:
PS D:\Unic-ITMO\ParallelAlgs\_assigments> ./A0 'Sasha walked along the highway and sucked drying'
Words in sentence:
Sasha
walked
along
the
highway
and
sucked
drying
*/