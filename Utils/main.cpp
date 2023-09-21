#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime> // содержит time()
using namespace std;

int main()
{
    ofstream out;
    out.open("rand_arr.txt");
    srand(time(NULL));
    for (int i = 0; i < 50 and out.is_open(); i++)
    {
        out << rand() << endl;
    }
    out.close();
    return 0;
}