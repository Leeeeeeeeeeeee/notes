#include <iostream>
using namespace std;

class Student{
public:
  int id;
};

void test1(){
  Student s1 = Student(); //可以使用
  //系统给的默认构造函数中，如果写了有参的构k [kan]造函数，则不自动添加默认构造函数
  //如果写了拷贝构造函数，也不给默认构造函数
  Student s2 = Student(s2); //可以使用

  cout << s1.id << endl;
  cout << s2.id << endl;
}

int main(){
  test1();
}
