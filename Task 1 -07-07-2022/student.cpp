#include <bits/stdc++.h>
using namespace std;

struct Student {
    string name;
    int roll_number;
    int age;
    double total_marks;
    Student *next;
};
Student *head,*tail;
void add(){
    cout<<"=============>>>>>>>>>>Adding Student<<<<<<<<<<<<<<<=================\n";
    Student *student = new Student();
    student->next = NULL;
    cout<<"Enter Student details::::\n\n";
    cin.ignore();
    cout<<"Name:";getline(cin,student->name);
    cout<<"Age:";cin>>student->age;
    cout<<"Roll Number:";cin>>student->roll_number;
    cout<<"Total Marks:";cin>>student->total_marks;
    cout<<"Student added successfully\n";
    if(head==NULL){
        head = student;
        tail = student;
        return;
    }
    tail->next = student;
    tail = tail->next;
}
void search(){
    Student *trav = head;
    cout<<"=============>>>>>>>>>>Searching Student<<<<<<<<<<<<<<<=================\n";
    cout<<"Student Roll Number:";
    int roll;cin>>roll;
    while(trav!=NULL){
        if(trav->roll_number==roll){
            cout<<"Student Details::::\n";
            cout<<"Name:"<< trav->name<<endl;
            cout<<"Age:"<<trav->age<<endl;
            cout<<"Total Marks:"<<trav->total_marks;

            return;
        }
        trav = trav->next;
    }
    cout<<"Student Not found with given roll number : "<<roll<<endl;
}

void Delete(){
    Student *trav = head,*prev = NULL;
    cout<<"=============>>>>>>>>>>Deleting Student<<<<<<<<<<<<<<<=================\n";
    cout<<"Student Roll Number:";
    int roll;cin>>roll;
    while(trav){
        if(trav->roll_number==roll){
            if(prev==NULL){
                head = head->next;
                free(trav);
            }
            else{
                prev->next = trav->next;
                free(trav);
            }
            cout<<"Deleted student\n";
            return;
        }
        prev = trav;
        trav = trav->next;
    }
    cout<<"Student Not found with given roll number : "<<roll<<endl;
}
void printStudents(){
    Student *trav=head;
    cout<<"=================>>>>>>>>>>Student Records<<<<<<<<<<<<<<<<<<<==========================\n";
    while(trav){
        cout<<trav->roll_number<<" "<<trav->name<<endl;
        trav=trav->next;
    }
}
int main(void)
{
    cout<<"=================>>>>>>>>>>Student Record Management<<<<<<<<<<<<<<<<<<<==========================\n";
    bool exit =false;
    while(!exit){
        cout<<endl;cout<<endl;
        int choice;
        cout<<"1.) Add Student\n2.) Search Student\n3.) Delete Student\n4.) print students\n5.) Exit\nyour choice:";
        cin>>choice;
        switch(choice){
            case 1:
                add();
                break;
            case 2:
                search();
                break;
            case 3:
                Delete();
                break;
            case 4:
                printStudents();
                break;
            case 5:
                exit = true;
            default:
                cout<<"Wrong Choice------:(\n";
        }
    }
    return(0);
}
