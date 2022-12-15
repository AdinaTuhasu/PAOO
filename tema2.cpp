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
   Person(){};
//Person constructor
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

    Person& operator+=(const Person& rhs) { 
    cout<<"Item 10"<<endl;
     last_name+=rhs.last_name;
     first_name+=rhs.first_name;
     age+=rhs.age;
      
    return *this;
   }
    
    //copy assignment
    Person& operator=(const Person& rhs) { 
    cout<<"Item 11"<<endl;
      if(this==&rhs)
      {  cout<<"The same object"<<endl;
         return *this;
      }
     last_name=rhs.last_name;
     first_name=rhs.first_name;
     age=rhs.age;
      
    return *this;
   }

   

   //destructor 
  virtual  ~Person(){ 
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
     Student(){};

     Student(int i,int ns,const string& first_name,const string& last_name,int age): 
     Person(first_name,last_name,age),
     id(i),
     number_of_subjects(ns)
     {
    cout << "Nume student: " << this->first_name << " " << this->last_name<<" age:"<<this->age<<" id:"<<id<<" number of subjects:"<<number_of_subjects<<endl;
	
     }

     
    Student(const Student& rhs): Person(rhs) {
        cout << "Copy constructor Student" <<endl;
       this->id=rhs.id;
       this->number_of_subjects=rhs.number_of_subjects;
    }; 

     ~Student() {
        std::cout << "Destructor called" << std::endl;
    };

    // copy constructor

     Student& operator=(const Student& rhs){
      cout<<"Item 12"<<endl;
            if(this == &rhs)
            {
              cout<<"The same object"<<endl;
              return *this;

            }
            Person::operator=(rhs);
            this->id=rhs.id;
            this->number_of_subjects=rhs.number_of_subjects;
            
            return *this;
        }

     int getId(){
        return id;
     }

     int getNrofSubjects(){
        return number_of_subjects;
     }
};



int main(){
 Student s1(105,8,"Ana","Popescu",20);
 Student s2(102,6,"Andreea","Pop",23);
 Student s3; //default constructor

 s3=s1; //copy assignment operator
 Student s4(s1); //copy constructor;

 Person p1("Ion","Popescu",22);
 Person p2("Maria","Ionescu",23);
 Person p3("Adina","Tuhasu",22);

//item 10;
 p1 += p2 += p3;

 p1.show_data();

 //item 11;

 p2=p2;

 //item 12

 Student student;
 student=s1;

 student.show_data();

 
    
    
    return 0;
}