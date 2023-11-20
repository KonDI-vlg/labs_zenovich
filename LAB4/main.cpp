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

vector<double> gauss(vector<vector<double>> sourceMatrix, vector<double> matrix_y)
{
  double max;
  int k = 0, index;
  int n = matrix_y.size();

  vector<double> x_ans(n);
  
  while (k < n)
  {
    // Поиск строки с максимальным sourceMatrix[i][k]
    max = abs(sourceMatrix[k][k]);
    index = k;
    for (int i = k + 1; i < n; i++)
    {
      if (abs(sourceMatrix[i][k]) > max)
      {
        max = abs(sourceMatrix[i][k]);
        index = i;
      }
    }
    // Перестановка строк
    if (max <= 0)
    {
      // нет ненулевых диагональных элементов
      cout << "Решение получить невозможно из-за нулевого столбца ";
      cout << index << " матрицы A" << endl;
      exit(1);
    }
    for (int j = 0; j < n; j++)
    {
      double temp = sourceMatrix[k][j];
      sourceMatrix[k][j] = sourceMatrix[index][j];
      sourceMatrix[index][j] = temp;
    }
    double temp = matrix_y[k];
    matrix_y[k] = matrix_y[index];
    matrix_y[index] = temp;
    // Нормализация уравнений
    for (int i = k; i < n; i++)
    {
      double temp = sourceMatrix[i][k];
      if (abs(temp) <= 0)
        continue; // для нулевого коэффициента пропустить
      for (int j = 0; j < n; j++)
        sourceMatrix[i][j] = sourceMatrix[i][j] / temp;
      matrix_y[i] = matrix_y[i] / temp;
      if (i == k)
        continue; // уравнение не вычитать само из себя
      for (int j = 0; j < n; j++)
        sourceMatrix[i][j] = sourceMatrix[i][j] - sourceMatrix[k][j];
      matrix_y[i] = matrix_y[i] - matrix_y[k];
    }
    k++;
  }
  // обратная подстановка
  for (k = n - 1; k >= 0; k--)
  {
    x_ans[k] = matrix_y[k];
    for (int i = 0; i < k; i++)
      matrix_y[i] = matrix_y[i] - sourceMatrix[i][k] * x_ans[k];
  }
  return x_ans;
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