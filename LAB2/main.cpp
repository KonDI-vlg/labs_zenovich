#include <iostream>
#include <fstream>

using namespace std;
int maxNumber(int *arr, int n)
{
    int max = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    int d = 0;
    while (max > 0)
    {
        max /= 10;
        d++;
    }
    return d;
}

void printArray(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

void sortKarman(int *arr, int n, int m, int k)
{
    int *source = new int[n];
    int *b = new int[m];
    int j, x;
    for (j = 1, x = 0; x < k; j *= 10, x++)
    {
        for (int i = 0; i < n; i++)
        {
            source[i] = arr[i];
        }
        for (int i = 0; i < m; i++)
        {
            b[i] = 0;
        }
        for (int i = 0; i < n; i++)
        {
            b[(arr[i] / j) % 10]++;
        }

        int summNum = 0;
        for (int i = 0; i < m; i++)
        {
            int tmp = b[i];
            b[i] = summNum;
            summNum += tmp;
        }

        for (int i = 0; i < n; i++)
        {
            int c = source[i];
            arr[b[c / j % 10]] = c;
            b[(c / j) % 10]++;
        }
    }
}

int main()
{
    ifstream in;
    in.open("input.txt");
    // ofstream fout("output.txt");
    char N[256];
    int k = 0;
    int n = 50;
    int *A = new int[50];
    if (in.is_open())
    {
        while (in >> N)
        {
            A[k++] = stoi(N);
        }
        in.close();
    }
    sortKarman(A, n, 10, maxNumber(A, n));
    printArray(A, n);
}