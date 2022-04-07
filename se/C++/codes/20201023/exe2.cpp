//编写一个函数，输入两个3x3的二维数组（当做矩阵），求出矩阵相乘的结果并返回，要求：使用指针实现。
#include <iostream>
#define MATRIX_SIZE 3
using namespace std;
void matrixAdd(int x[MATRIX_SIZE][MATRIX_SIZE],int y[MATRIX_SIZE][MATRIX_SIZE],int z[MATRIX_SIZE][MATRIX_SIZE]){
  int i=0,j=0;
  for(i=0;i<MATRIX_SIZE;i++){
    for(j=0;j<MATRIX_SIZE;j++){
      z[i][j] = x[i][j] + y[i][j];
    }
  }
}
int main(){
  int i=0,j=0;
  int x[MATRIX_SIZE][MATRIX_SIZE];
  int y[MATRIX_SIZE][MATRIX_SIZE];
  int z[MATRIX_SIZE][MATRIX_SIZE];
  cout << "first:" << endl;
  for(i=0;i<MATRIX_SIZE;i++){
    for(j=0;j<MATRIX_SIZE;j++){
      cin >> x[i][j];
    }
  }
  cout << "second:" << endl;
  for(i=0;i<MATRIX_SIZE;i++){
    for(j=0;j<MATRIX_SIZE;j++){
      cin >> y[i][j];
    }
  }
  matrixAdd(x,y,z);
  cout << "output:" << endl;
  for(i=0;i<MATRIX_SIZE;i++){
    for(j=0;j<MATRIX_SIZE;j++){
      cout << z[i][j] << ' ';
    }
    cout << endl;
  }
  return 0;
}
