#include <bits/stdc++.h>
using namespace std;

struct Student {
    string name;
    int roll_number;
    int age;
    double total_marks;
};
unordered_map<int,Student> students;
void add(){
    cout<<"=============>>>>>>>>>>Adding Student<<<<<<<<<<<<<<<=================\n";
    Student student;
    cout<<"Enter Student details::::\n\n";
    cin.ignore();
    cout<<"Name:";getline(cin,student.name);
    cout<<"Age:";cin>>student.age;
    cout<<"Roll Number:";cin>>student.roll_number;
    cout<<"Total Marks:";cin>>student.total_marks;
    cout<<"Student added successfully\n";
    students[student.roll_number] = student;
}
void onLoad(){
    ifstream file;
    file.open("data.txt",ios::in);
    if (file.is_open()){
        string line;
        while(getline(file, line)){
            if(line=="")break;
            int start = 0;
            int end = line.find(",");
            vector<string> values;
            while (end != -1) {
                values.push_back(line.substr(start, end - start));
                start = end + 1;
                end = line.find(",", start);
            }
            values.push_back(line.substr(start, end - start));
            Student student;
            student.roll_number = atoi(values[0].c_str());
            student.name = values[1];
            student.total_marks = atoi(values[2].c_str());
            student.age = atoi(values[3].c_str());
            students[student.roll_number] = student;
        }
        file.close();
    }
}
void search(){
    cout<<"=============>>>>>>>>>>Searching Student<<<<<<<<<<<<<<<=================\n";
    cout<<"Student Roll Number:";
    int roll;cin>>roll;
    if(students.find(roll)== students.end())
    cout<<"Student Not found with given roll number : "<<roll<<endl;
    else{
        Student value = students[roll];
        cout<<"Student Details---:\n";
        string t = ""+to_string(value.roll_number)+","+value.name+","+to_string(value.total_marks)+","+to_string(value.age)+"\n";
        cout << t;
    }
}
void Delete(){
    cout<<"=============>>>>>>>>>>Deleting Student<<<<<<<<<<<<<<<=================\n";
    cout<<"Student Roll Number:";
    int roll;cin>>roll;
    if(students.find(roll)== students.end())
    cout<<"Student Not found with given roll number : "<<roll<<endl;
    else{
        students.erase(roll);
        cout<<"Deleted student\n";
    }
}
void onExit(){
    ofstream file;
    file.open("data.txt",ios::out);
    if (file.is_open()){
        for(const auto & [key,value] : students){
            string t = ""+to_string(value.roll_number)+","+value.name+","+to_string(value.total_marks)+","+to_string(value.age)+"\n";
            file << t;
        }
    }
    file.close();
}
void printStudents(){
    cout<<"=================>>>>>>>>>>Student Records<<<<<<<<<<<<<<<<<<<==========================\n";
    for(const auto & [key,value] : students){
        string t = ""+to_string(value.roll_number)+","+value.name+","+to_string(value.total_marks)+","+to_string(value.age)+"\n";
        cout << t;
    }
}
int main(){
    onLoad();
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
                break;
            default:
                cout<<"Wrong Choice------:(\n";
        }
    }
    onExit();
    return 0;
}