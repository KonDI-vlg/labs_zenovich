#include <iostream>
#include <vector>

using namespace std;

vector<int> arr;
vector<int> d;
int n, k;

void printArray(vector<int> arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

bool permission(int i)
{
    if ((arr[i] == k - 1 and d[i] == 1) or (arr[i] == 0 and d[i] == -1))
        return true;
    else
        return false;
}

int main()
{
    int i, j;
    cout << "n: ";
    cin >> n;
    cout << "k: ";
    cin >> k;
    arr.resize(n);
    d.resize(n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = 0;
        d[i] = 1;
    }
    while (true)
    {
        printArray(arr);
        for (i = 0; i < n and permission(i); i++)
            ;
        if (i == n)
            break;
        arr[i] += d[i];

        for (j = i - 1; j >= 0; j--)
        {
            d[j] = -d[j];
        }
    }
}
// Тестовый коммит
