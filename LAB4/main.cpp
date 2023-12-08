#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>

using namespace std;

ifstream in;





int rangMatrix(vector<vector<double>> x) {
  int n = x.size();
  int m = x[0].size();
  int rang = 0;
   int i = 0;
   int j = 0;
   vector<vector<double>> y = x;
   while (i < n && j < m) {
      int k = i;
      while (k < n && y[k][j] == 0) {
         k++;
      }
      if (k == n) {
         j++;
         continue;
      }
      if (k != i) {
         for (int t = 0; t < m; t++) {
            swap(y[i][t], y[k][t]);
         }
      }
      for (int t = 0; t < n; t++) {
         if (t == i) {
            continue;
         }
         double c = y[t][j] / y[i][j];
         for (int k = 0; k < m; k++) {
            y[t][k] -= y[i][k] * c;
         }
      }
      i++;
      j++;
      rang++;
   }
   return rang;
}

void printAnswer(vector<vector<double>> x, vector<double> y,int rang){
  if ( rang < x[0].size()){
    for(int i = 0; i < rang;i++){
      string suff;
      for(int j = 0; j < x[0].size();j++){
        if(i != j and x[i][j] != 0)
          suff.append(to_string(x[i][j] * (-1))).append("*x").append(to_string(j+1)).append(" ");
      }
      cout << "x" << i+1 << " = " << y[i] << ' ' << suff << endl;
    }
  }
  else{
    for (int i = 0; i < y.size(); i++)
      cout << "x" << i + 1 << " = " << y[i] << endl;
  }
}

vector<vector<double>> mergeMatrix(vector<vector<double>> x, vector<double> y){
  int n = x.size();
  int m = x[0].size();
  
  vector<vector<double>> k(n,vector<double>(m+1));

  for(int i = 0; i < n; i++){
     for(int j = 0; j < m; j++){
       k[i][j] = x[i][j];
     }
   }
   for(int i = 0; i < n; i++){
     k[i][m] = y[i];
   }
   return k;

}

void printSystemOfEquation(vector<vector<double>> x, vector<double> y){
  int n = x.size();
  int m = x[0].size();
  for(int i = 0; i < n; i++){
     for(int j = 0; j < m; j++){
       cout << x[i][j] << "*x" << j + 1 << " ";
     }
     cout << "= " << y[i] << endl;
   }
}

tuple<vector<vector<double>>,vector<double>> gaussMethod(vector<vector<double>> x, vector<double> y, bool infinity = false){
  int n = x.size();
  int m = x[0].size();
  int k = 0, index;
  double max;
  
  double eps = 0.0001;

  while ( k < rangMatrix(x) ) {
    max = abs(x[k][k]);
    index = k;

    for( int i = k; i < n; i++){
      if ( x[i][k] == 1 and x[index][k] != 1) {
        index = i;
      }
      if ( abs(x[i][k]) > max ){
        max = abs(x[i][k]);
      }
    }

    if ( index != k) {
      for( int j = 0; j < m; j++){
       double temp = x[k][j];
       x[k][j] = x[index][j];
       x[index][j] = temp;
      }
      double temp = y[k];
      y[k] = y[index];
      y[index] = temp;
    }
    
     for( int i = k; i < n; i++){
       double temp = x[i][k];
       if ( abs(temp) < eps ) continue;
       for( int j = 0; j < m; j++){
         x[i][j] = x[i][j] / temp;
       }
       y[i] = y[i] / temp;
       if ( i == k ) continue;
       for( int j = 0; j < m; j++){
         x[i][j] = x[i][j] - x[k][j];
       }
       y[i] = y[i] - y[k];
     }
     k++;

  }


  vector<double> ans(n);

  if(infinity) {
    cout << "Infinity: true" << endl;

    
    for(int i = n - 1; i >= 0; i--){
      int cnt = 0;
      ans[i] = y[i];
      for(int j = 0; j < m; j++){
        if(cnt == 1) {
          cnt = 0;
          break;
        }
        if( x[i][j] != 0) {
          int row = i-1;
          while(row >= 0){
            int coef = x[row][j] / x[i][j];
            x[row][j] -= x[i][j] * coef;
            y[row] -= y[i] * coef;
            row--;
          }
          cnt++;
        }
      }
    }
    printSystemOfEquation(x,ans);
  }
  else{
    cout << "Infinity: false" << endl;

    for(int i = n - 1; i >= 0; i--){
      ans[i] = y[i];
      for(int j = 0; j < i; j++){
        y[j] = y[j] - x[j][i] * ans[i];
      }
    }

    for(int k = n - 1; k >=0; k--){
      for(int j = m - 1; j >= 0; j--){
        for(int i = 0; i < k; i++){
          x[i][j] -= x[k][j] * x[i][j];
        }
      }
    }
    printSystemOfEquation(x,y);
  }
  
  return make_tuple(x,ans);
}

// Main  
int main(){
  int n, m;
  in.open("input.txt");
  in >> n >> m;

  vector<vector<double>> matrix_x(n, vector<double>(m));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      in >> matrix_x[i][j];
     
  
  vector<double> matrix_y(n);

  for (int i = 0; i < n; i++)
    in >> matrix_y[i];
  
  in.close();
  

  printSystemOfEquation(matrix_x,matrix_y);

  if( rangMatrix( matrix_x ) != rangMatrix(mergeMatrix(matrix_x,matrix_y)) ){
    cout << "System has no solution" << endl;
  }
  else if (rangMatrix( matrix_x ) < m){
    vector<vector<double>> xasd;
    vector<double> yasd;
    tie(xasd,yasd) = gaussMethod(matrix_x,matrix_y,true);
    cout << "Ans: " << endl;
    printAnswer(xasd,yasd,rangMatrix(matrix_x));
  }
  else{
    vector<vector<double>> xasd;
    vector<double> yasd;
    tie(xasd,yasd) = gaussMethod(matrix_x, matrix_y);
    cout << "Ans: " << endl;
    printAnswer(xasd,yasd,rangMatrix(matrix_x));
  }
  return 0;
}




// Возможна ошибка с переменной infinity