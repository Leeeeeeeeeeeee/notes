#include <iostream>
using namespace std;

class Student {
public:
  int id;
  Student(){  //不传参数时id的默认值
    id=0;
    cout << "Student()" << endl;
  }
  Student(int _id){ //带参数的构造函数
    id=_id;
    cout << "Student(int _id)" << endl;
  }
  Student(const Student& s){  //拷贝构造函数
    id=s.id;
    cout << "Student(const Student & s)" << endl;
  }

};

void fun1(Student s){

}

Student fun2(){
  Student s = Student(1);
  return s;
}

int main(){
  Student s1;
  Student s2=Student();
  Student s3={};
  cout << s1.id << endl;  //0
  cout << s2.id << endl;  //0
  cout << s3.id << endl << endl;  //0

  Student s11();  //不能用这种表示方法，不会调用构造函数，编译器会把这句话当做函数声明
  cout << typeid(s11).name() << endl;
  cout << typeid(s1).name() << endl;

  Student s4(1);  //这样是可以的
  Student s5 = Student(1);
  Student s6 = {1};
  cout << s4.id << endl;  //1
  cout << s5.id << endl;  //1
  cout << s6.id << endl << endl;  //1

  Student s7(s1);
  Student s8 = Student(s1);
  Student s9 = {s1};
  Student s10 = s1; //Student s10 = Student(s1);
  cout << s7.id << endl;
  cout << s8.id << endl;
  cout << s9.id << endl;
  cout << s10.id << endl << endl;

  //Student s1; 调用了第一个构造函数
  //fun1(Student(s1)); 调用了第三个构造函数

  //Student s1; 调用了第一个构造函数

  //fun1(s1); 调用了第三个构造函数
  //Student s12=fun2(); 调用了第二个构造函数
}
