#include <iostream>
using namespace std;

class Student{
public:
  int id;

  Student(){
    id = 0;
    cout << "Student()" << endl;
  }

  ~Student(){
    cout << "~Student()" << endl;
  }

};

class Teacher{
public:
  int* age;

  Teacher(){
    age = new int(0);
    cout << "Teacher()" << endl;
  }

  ~Teacher(){
    delete age;
    cout << "~Teacher()" << endl;
  }

  Teacher(const Teacher& t){
    age =  new int(*t.age);
    cout << "Teacher(const Teacher & s)" << endl;
  }
};

void Test1(){
  Student s1;
  Student s2(s1);

  cout << s1.id << endl;
  cout << s2.id << endl;
}

void Test2(){
  Teacher t1;
  Teacher t2(t1);

  cout << *t1.age << endl;
  cout << *t2.age << endl;
}

int main(){
  Test1();
  Test2();//默认的拷贝构造函数：浅拷贝;自建的拷贝构造函数：深拷贝


}
