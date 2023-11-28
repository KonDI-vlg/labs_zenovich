#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>

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

vector<vector<double>> zeroMatrix(int n, int m){
    vector<vector<double>> a(n);
    a.assign(n,vector<double>(m));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(i==j)
                a[i][j] = 1;
            else
                a[i][j] = 0;
        }
    }
    return a;
}

void printSystem(vector<vector<double>> a, vector<double> y)
{
  for (int i = 0; i < y.size(); i++)
  {
    for (int j = 0; j < a[0].size(); j++)
    {
      cout << a[i][j] << "x" << j;
      if (j < a[0].size() - 1)
        cout << " + ";
    }
    cout << " = " << y[i] << endl;
  }
  return;
}

void printAnswer(vector<vector<double>> a, vector<double> y)
{
  if (a[0].size() != y.size()){
    for(int i = 0; i < y.size();i++)
      if ( y[i] == 0 ) break;
  }
  for (int i = 0; i < y.size(); i++)
  {
    string suff = "";
    for (int j = 0; j < a[0].size(); j++)
    {
      if ( abs(a[i][j]) == 0 ) continue;
      if (i == j) cout << a[i][j] << "x" << j;
      if (j < a[0].size() - 1)
        suff.append(" - ").append(to_string(round(a[i][j+1]))).append("x").append(to_string(j+1));
    }
    if (y[i] == 0) continue;
    cout << " = " << y[i] << suff << endl;
  }
  return;
}

vector<double> gauss(vector<vector<double>> sourceMatrix, vector<double> matrix_y)
{
  double max;
  int k = 0, index;
  int n = matrix_y.size();
  double eps = 0.001;
  vector<double> x_ans(n);

  while (k < n)
  { 
    // cout << "<---- Temp ---->" << endl;
    // printSystem(sourceMatrix,matrix_y);
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
//    if (max < eps)
//    {
//      // нет ненулевых диагональных элементов
//      cout << "Решение получить невозможно из-за нулевого столбца ";
//      cout << index << " матрицы A" << endl;
//      exit(1);
//    }
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
      if (abs(temp) < eps)
        continue; // для нулевого коэффициента пропустить
      for (int j = 0; j < n; j++)
        sourceMatrix[i][j] = abs(sourceMatrix[i][j] / temp) < eps ? 0 : sourceMatrix[i][j] / temp;
      matrix_y[i] = abs(matrix_y[i] / temp) < eps ? 0 : matrix_y[i] / temp;
      if (i == k)
        continue; // уравнение не вычитать само из себя
      for (int j = 0; j < n; j++)
        sourceMatrix[i][j] = abs(sourceMatrix[i][j] - sourceMatrix[k][j]) < eps ? 0 : sourceMatrix[i][j] - sourceMatrix[k][j];
      matrix_y[i] = abs(matrix_y[i] - matrix_y[k]) < eps ? 0 : matrix_y[i] - matrix_y[k];
    }
    k++;
  }
  // обратная подстановка
  for (k = n - 1; k >= 0; k--)
  {
    x_ans[k] = abs(matrix_y[k]) < eps ? 0 : matrix_y[k];
    for (int i = 0; i < k; i++){
      matrix_y[i] = matrix_y[i] - sourceMatrix[i][k] * x_ans[k];
      }
  }
  printAnswer(sourceMatrix,x_ans);
  return x_ans;
}

int main()
{
  ifstream in;
  int matrix_size_n, matrix_size_m;
  string matrix_element;

  in.open("input.txt");
  in >> matrix_size_n;
  in >> matrix_size_m;

  vector<vector<double>> sourceMatrix(matrix_size_n);
  vector<vector<double>> zero_m = zeroMatrix(matrix_size_n,matrix_size_m);
  vector<double> y(matrix_size_n);
  vector<double> x(matrix_size_n);



  // Расширили матрицу
  sourceMatrix.assign(matrix_size_n, vector<double>(matrix_size_m));

  // Заполнили x-коэффициенты системы уравнений
  for (int i = 0; i < matrix_size_n; i++)
  {
    for (int j = 0; j < matrix_size_m; j++)
    {
      in >> matrix_element;
      sourceMatrix[i][j] = stod(matrix_element);
    }
  }

  // Заполнили y-значения системы уравнений
  for (int i = 0; i < matrix_size_n; i++)
  {
    in >> matrix_element;
    y[i] = stod(matrix_element);
  }
  // Вывели исходник
  cout << "<---- Source evaluation ---->" << endl;
  printSystem(sourceMatrix, y);

  cout << "<---- Answer ---->" << endl;
  // Решили и вывели ответ
  x = gauss(sourceMatrix,y);

  
  // printSystem(zero_m,x);
}