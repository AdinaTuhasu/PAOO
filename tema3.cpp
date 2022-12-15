#include<iostream>
#include <memory>

using namespace std;


class Uncopyable
{
    protected:
        Uncopyable() {}
        ~Uncopyable() {}

    private:
        Uncopyable(const Uncopyable&);
        Uncopyable& operator=(const Uncopyable&);
};

 
class Person
{   
    private:
        std::string theName;
        std::string theSex;
        int age;
        bool personLocked;

    public:
        /* Default Constructor */
        Person(): theName("nonExistent"),theSex("nonExistent"),age(0), personLocked(false){}

        /* Constructor */
        Person(const std::string& name, const std::string& sex, const int &age,const bool &personLocked)
        :theName(name), 
        theSex(sex), 
        age(age), 
        personLocked(personLocked)
        {}
        
        /* Custom Copy Constructor, commented due to Item 6 */
        Person(const Person& other) :theName(other.theName), theSex(other.theSex), age(other.age), personLocked(other.personLocked)
        {}

        /* Custom assignment operator */
        Person& operator=(const Person& rhs)
        {
            if(this == &rhs)
            {
                std::cout<<"Objects are identical!\n";
                return *this;
            }
            this->theSex = rhs.theSex;
            this->theName = rhs.theName;
            this->age = rhs.age;
            this->personLocked = rhs.personLocked;
            return *this;
        }

        /* Custom Destructor */
        ~Person()
        {
            std::cout<<"Object has been completely removed from memory!\n";
        }

        void show()
        {
            std::cout<<"Person: " << this->theName << "\nSex: " << this->theSex << "\n" << this->age << " years old\n";
        }


        bool getPersonLocked()
        {
            return this->personLocked;
        }

        void setPersonLocked(bool value)
        {
            this->personLocked = value;
        }

        string getTip(){
          return theSex;

        }

    
};


//Metoda care returneaza un pointer la un obiect Person alocat dinamic
Person* createPerson(const std::string& name, const std::string& sex, const int &age,const bool &personLocked)
{
    return new Person(name, sex, age,personLocked);
}

void printNewPerson(const std::string& name, const std::string& sex, const int &age,const bool &personLocked)
{   //primim resursa in momentul crearii la auto_ptr
    std::auto_ptr<Person> pPerson(createPerson(name,sex,age,personLocked));
    pPerson -> show();
}//la iesire,stergem resursa pPerson prin destructorul auto_ptr

//item14 features
void lockObject(Person& person)
{
    person.setPersonLocked(true);
    std::cout<<"Blocam persoana.\n";//blocheaza Persoana indicata de person
};

void unlockObject(Person& person)
{
    person.setPersonLocked(false);
    std::cout<<"Deblocam persoana.\n";
};

class LockedPerson: private Uncopyable
{
    public:
         LockedPerson(Person& other): pPerson(other)
        {
            //lock the person
            lockObject(pPerson);
        }
        ~LockedPerson()
        {
            //unlock the person automatically by destructor
            unlockObject(pPerson);
            std::cout<<"Object has been completely removed from memory!\n";
        }
    private:
        Person& pPerson;
};

int main()
{
    //item 13 with "auto_ptr"
    std::auto_ptr<Person> Person1(createPerson("Tuhasu Adina","feminin",22,false));
    Person1 -> show();

    auto_ptr<Person> Person2(Person1); // Person2 pointeaza acum spre obiectul creat
    Person2 -> show();  
    
    //item 13 "shared_ptr"
    shared_ptr<Person> Person3(createPerson("Pop Dan","masculin",24,false));
    Person3->show();

    shared_ptr<Person> Person4(Person3);   // Person3 si Person4 pointeaza acum spre acelasi obiect returnat de createPerson
   Person4->show();  

    //item 14
    Person Person5("Ion","masculin", 21, false);
    {
        LockedPerson Person6(Person5);     
        
    }
    cout<<'\n'<<"Gen: "<<Person5.getTip()<<" Locked value: "<<Person5.getPersonLocked()<<'\n';


    
    return 0;
}