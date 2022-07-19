#include <iostream>

using namespace std;
float Division(float num, float den)
{
    try {
        return (num / den);
    }
    catch (...) {
        cout << "Zero Division Error\n";
    }
} 
class memoryError : public exception {
    long long int size = 0;
public:
    memoryError();
    memoryError(long long int size) {
        this->size = size;
    }
    const char* what() const throw()
    {
        return "Memory Overflow! size="+size;
    }
};
void Memory(long long int size) {
    try {
        int* a = (int*)malloc(sizeof(int) * size);
        if (a == NULL) {
            memoryError E(size);
            throw E;
        }
    }
    catch (exception& e) {
        cout << e.what() << endl;
    }
}
void dataTypeMismatch() {
    try {
        int x = atoi("123a");
    }
    catch (...) {
        cout << "Data Type Mismatch\n";
    }
}
void outOfBoundIndex(int index) {
    try {
        int arr[10];
        if (index >= 10 || index < 0)throw 0;
        arr[index] = 0;
    }
    catch (...) {
        cout << "Index Of Bound Error\n";
    }
}
int main()
{
    //part 1 -----------------------------------
    Division(5,0);
    cout << "After Zero Division error\n";
    Memory(10000000000000);
    cout << "After Memory overflow error\n";
    dataTypeMismatch();
    cout << "After Format Mismatch\n";
    outOfBoundIndex(12);
    cout << "After Index Out Of Bound\n";
    cout << "Exception Handling Accomplished!\n";
    //-----------------------------------------

    //part 2 ----------------------------------
    //exception in outer try block
    cout << "exception in outer try block\n";
    try {
        cout << "Outer Try Block\n";
        throw 0;
        try {
            cout << "Inner Try Block\n";
        }
        catch (int x) {
            cout << "Inner Catch Block\n";
        }
    }
    catch (int x) {
        cout << "Outer try Block\n";
    }

    //exception in inner try block
    cout << "exception in inner try block\n";
    try {
        cout << "Outer Try Block\n";
        try {
            cout << "Inner Try Block\n";
            throw 0;
        }
        catch (int x) {
            cout << "Inner Catch Block\n";
        }
    }
    catch (int x) {
        cout << "Outer try Block\n";
    }

    //no exception
    cout << "no exception\n";
    try {
        cout << "Outer Try Block\n";
        try {
            cout << "Inner Try Block\n";
        }
        catch (int x) {
            cout << "Inner Catch Block\n";
        }
    }
    catch (int x) {
        cout << "Outer try Block\n";
    }

    //rethrowing catched exception
    cout << "rethrowing catched exception\n";
    try {
        cout << "Outer Try Block\n";
        try {
            cout << "Inner Try Block\n";
            throw 0;
        }
        catch (int x) {
            cout << "Inner Catch Block\n";
            throw x;
        }
    }
    catch (int x) {
        cout << "Outer try Block"<<x<<endl;
    }

    //part 3 --------------------------------


}