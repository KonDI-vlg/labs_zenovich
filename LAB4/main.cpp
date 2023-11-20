#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void printMatrix(vector<vector<double>> a)
{
  for (int i = 0; i < a[0].size(); i++)
  {
    for (int j = 0; j < a.size(); j++)
    {
      cout << a[i][j] << ' ';
    }
    cout << endl;
  }
}

void printSystem(vector<vector<double>> a, vector<double> y)
{
  for (int i = 0; i < y.size(); i++)
  {
    for (int j = 0; j < y.size(); j++)
    {
      cout << a[i][j] << "x" << j;
      if (j < y.size() - 1)
        cout << " + ";
    }
    cout << " = " << y[i] << endl;
  }
  return;
}

vector<double> gauss(vector<vector<double>> a, vector<double> y)
{
  int n = y.size();

  vector<double> x(n);
  double max;
  int k, index;
  const double eps = 0.00001; // точность
  k = 0;
  while (k < n)
  {
    // Поиск строки с максимальным a[i][k]
    max = abs(a[k][k]);
    index = k;
    for (int i = k + 1; i < n; i++)
    {
      if (abs(a[i][k]) > max)
      {
        max = abs(a[i][k]);
        index = i;
      }
    }
    // Перестановка строк
    if (max < eps)
    {
      // нет ненулевых диагональных элементов
      cout << "Решение получить невозможно из-за нулевого столбца ";
      cout << index << " матрицы A" << endl;
      exit(1);
    }
    for (int j = 0; j < n; j++)
    {
      double temp = a[k][j];
      a[k][j] = a[index][j];
      a[index][j] = temp;
    }
    double temp = y[k];
    y[k] = y[index];
    y[index] = temp;
    // Нормализация уравнений
    for (int i = k; i < n; i++)
    {
      double temp = a[i][k];
      if (abs(temp) < eps)
        continue; // для нулевого коэффициента пропустить
      for (int j = 0; j < n; j++)
        a[i][j] = a[i][j] / temp;
      y[i] = y[i] / temp;
      if (i == k)
        continue; // уравнение не вычитать само из себя
      for (int j = 0; j < n; j++)
        a[i][j] = a[i][j] - a[k][j];
      y[i] = y[i] - y[k];
    }
    k++;
  }
  // обратная подстановка
  for (k = n - 1; k >= 0; k--)
  {
    x[k] = y[k];
    for (int i = 0; i < k; i++)
      y[i] = y[i] - a[i][k] * x[k];
  }
  return x;
}

int main()
{ 
  ifstream in;
  int matrix_size;
  string matrix_element;

  in.open("input.txt");
  in >> matrix_size;
  
  vector<vector<double>> sourceMatrix(matrix_size);
  vector<double> y(matrix_size);
  vector<double> x(matrix_size);
  
  
  
  // Расширили матрицу
  sourceMatrix.assign(matrix_size, vector<double>(matrix_size));

  // Заполнили x-коэффициенты системы уравнений
  for (int i = 0; i < matrix_size; i++)
  {
    for (int j = 0; j < matrix_size; j++)
    {
      in >> matrix_element;
      sourceMatrix[i][j] = stod(matrix_element);
    }
  }

  // Заполнили y-значения системы уравнений
  for (int i = 0; i < matrix_size; i++)
  {
    in >> matrix_element;
    y[i] = stod(matrix_element);
  }
  // Вывели исходник
  printSystem(sourceMatrix, y);
  // Решили и вывели ответ
  x = gauss(sourceMatrix,y);
  printSystem(sourceMatrix,x);
}