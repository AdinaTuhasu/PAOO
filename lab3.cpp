#include<iostream>

using namespace std;


class Uncopyable {
protected: // allow construction
Uncopyable() {} // and destruction of
~Uncopyable() {} // derived objects...
private:
Uncopyable(const Uncopyable&); // ...but prevent copying
Uncopyable& operator=(const Uncopyable&);
};

class Person: private Uncopyable { 
public:
  std::string first_name;
  std::string last_name;
  int age;
  

public:
   Person(const std::string &fn,const std::string &ln,int a)
    : first_name(fn),
      last_name(ln),
      age(a)
     {
    cout << "Name: " << first_name << " " << last_name << endl;
	cout << "age  : " << age<< endl;
	
    }
   //copy constructor
    Person(const Person& other){
    cout<<"Copy constructor called"<<endl;
    last_name=other.last_name;
    first_name=other.first_name;
    age=other.age;
    
   }

   //copy assigment operator
    Person& operator=(const Person& rhs) { 
     cout<<"Copy assigment operator called"<<endl;
    if(this!=&rhs){
    last_name=rhs.last_name;
    first_name=rhs.first_name;
    age=rhs.age;
    }
    return *this;
   }

   //destructor 
   ~Person(){ 
     cout<<"Destructor called"<<endl;
     
     
   }


  void show_data(){
    cout<<first_name<<" "<<last_name<<" age:"<<age<<endl;
  }
};

 
class Student: public Person{
    private:
    int id;
    int number_of_subjects=0;

    public:
     Student(int i,int ns,const string& first_name,const string& last_name,int age): 
     Person(first_name,last_name,age),
     id(i),
     number_of_subjects(ns)
     {
    cout << "Nume student: " << this->first_name << " " << this->last_name<<" age:"<<this->age<<" id:"<<id<<" number of subjects:"<<number_of_subjects<<endl;
	
     }

     int getId(){
        return id;
     }

     int getNrofSubjects(){
        return number_of_subjects;
     }
};



int main(){
    Person person1("Adina","Tuhasu",22);
    person1.show_data();
    Person person2(person1);
    person2.show_data();
    person2=person1;
    Student student1(103,3,"Adina","Tuhasu",22);
    student1.show_data();
    
    return 0;
}