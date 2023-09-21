#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime> // содержит time()
using namespace std;

void rand_arr(int n)
{
    ofstream out;
    out.open("rand_arr.txt");
    srand(time(NULL));
    for (int i = 0; i < n and out.is_open(); i++)
    {
        out << rand() << endl;
    }
    out.close();
}

int main()
{
}