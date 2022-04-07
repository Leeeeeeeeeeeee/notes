#include <iostream>
#include <string>
using namespace std;

struct Teacher{
  string name;
  int age;
  char gender;
};

typedef struct Student{
  string name;
  int age;
  char gender;
}Stu;

void func1(Stu s){
  s.age=38;
}

void func2(Stu* s){
  s->age=38;
}

int main(){
  struct Teacher t1;
  t1.name="Xueyuan Gong";
  t1.age=18;
  t1.gender='M';
  cout << "(" << t1.name.c_str() << "," << t1.age << "," << t1.gender << ")" << endl;

  Stu s1={"Steven",18,'M'};
  cout << "(" << s1.name.c_str() << "," << s1.age << "," << s1.gender << ")" << endl;

  Stu s_s[2]={{"Lydia",18,'F'},{"Samantha",18,'F'}};
  cout << "(" << s_s[0].name.c_str() << "," << s_s[0].age << "," << s_s[0].gender << ")" << endl;
  cout << "(" << s_s[1].name.c_str() << "," << s_s[1].age << "," << s_s[1].gender << ")" << endl;

  Stu* s3=&s1;
  cout << "(" << s3->name.c_str() << "," << s3->age << "," << s3->gender << ")" << endl;

  Stu s4={"Evelyn",18,'M'};
  cout << "before: (" << s4.name.c_str() << "," << s4.age << "," << s4.gender << ")" << endl;
  func1(s4);
  cout << "func1:  (" << s4.name.c_str() << "," << s4.age << "," << s4.gender << ")" << endl;
  func2(&s4);
  cout << "func2:  (" << s4.name.c_str() << "," << s4.age << "," << s4.gender << ")" << endl;


  return 0;
}
