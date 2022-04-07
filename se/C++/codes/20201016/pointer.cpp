#include <iostream>
using namespace std;

int add(int a,int b){
  return a+b;
}

int mul(int a,int b){
  return a*b;
}

int main(){

  int a = 1;
  int* p = &a;

  cout << &(*p) << endl;  //a的地址（64位二进制）
  cout << *(&a) << endl;  //a的内容

  int* p2 = NULL;
  p2 = p;
  int** p3 = &p2;

  cout << p2 << endl;     //p1的地址
  cout << &p2 << endl;    //p2的地址
  cout << p3 << endl;     //p2的地址
  cout << *p3 << endl;    //p1的地址
  cout << **p3 << endl;   //a的内容

  int b[] = {1,2,3,4,5};
  int* p4 = b;
  //int* p4 = &b[0];
  cout << b << endl;
  cout << b[2] << endl;   //数组b中第三个元素
  cout << *(b+2) << endl; //数据b中第三个元素
  cout << *(++p4) << endl;//数组b中第二个元素
  cout << *(p4++) << endl;//数组b中第二个元素（p4已经改变了，指向b中第二个元素，++先用后加，所以输出显示数组第二个元素，但是此时p4已经指向b中第三个元素）
  cout << *(p4-2) << endl;//数组b中第一个元素

  int c[3][2] = {{1,2},{3,4},{5,6}};
  int (*p6)[2] = c;//数组指针
  int* p5[3] = {c[0],c[1],c[2]};//指针数组
  int** p7 = p5;
  //int** p7 = c; 二维数组不等于二级指针，二维数组要用数组的指针的方式去理解
  int* p8 = &c[0][0];
  for(int i = 0;i<3;++i){
    for(int j = 0;j<2;++j){
      cout << p8[i*2+j];
    }
  }
  cout << endl;

  int(*f)(int,int);//定义的函数输入两个int，返回一个int
  f = add;
  //f = &add;
  cout << f(2,3) << endl;
  //cout << (*f)(2,3) << endl;
  f=mul;
  cout << f(2,3) << endl;

  int x=1,y=1;
  int* p9 = &x;
  int* p10 = &y;
  //if(p9=p10) 缺少了一个=，判断的是将p10赋值于p9后p9的值
  
  system("pause");
  return 0;
}
