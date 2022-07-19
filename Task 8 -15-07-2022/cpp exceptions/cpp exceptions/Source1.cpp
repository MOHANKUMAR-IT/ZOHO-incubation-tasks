#include <bits\stdc++.h>
using namespace std;

class AgeNotWithinRangeException : exception{
    public:
        const char* what() const throw()
        {
            return "Age Not Within Range 15-21\n";
        }
};

class NameNotValidException : exception{
    public:
        const char* what() const throw()
        {
            return "Name should Not contain numbers or special characters\n";
        }
};

class InvalidCourseException : exception{
    public:
        const char* what() const throw()
        {
            return "Choose available courses only!\n";
        }
};

class MoreThanOneObject : exception{
    public:
        const char* what() const throw()
        {
            return "Student already Created!\n";
        }
};

vector<string> courses{"python","cpp","java"};

class Student{
    int roll_no;
    string name;
    int age;
    
    string course;
    public:
    static bool created;
    Student(int roll_no,int age,string course,string name)
    :roll_no(roll_no),age(age),course(course),name(name)
    {   
        if(!created)created = true;
        else{
            MoreThanOneObject e;
            throw e;
        }
        if(!(age<21 && age>15)){
            AgeNotWithinRangeException e;
            throw e;
        }
        for(int i=0;i<name.size();i++){
            if(isalpha(name[i]) || name[i]==' ')continue;
            NameNotValidException e;
            throw e;
        }
        transform(course.begin(), course.end(), course.begin(), ::tolower);

        if(find(courses.begin(),courses.end(),course)==courses.end()){
            InvalidCourseException e;
            throw e;
        }
        cout<<"New Student Created-"<<name<<endl;
    }
};
bool Student::created = false;
int main(){
    Student student1(59,20,"cpp","Mohan Kumar R");
    Student student2(50,20,"java","Logeshavan R");
    return 0;
}