#include <bits/stdc++.h>

using namespace std;
template <typename T> class DeQueue{
    list<T> q;
public:
    DeQueue(){
        cout<<"Queue created\n";
    }
    void push_back(T data){
        q.push_back(data);
    }
    void pop_back(){
        if(isempty())return;
        q.pop_back();
    }
    void push_front(T data){
        q.push_front(data);
    }
    void pop_front(){
        if(isempty())return;
        q.pop_front();
    }
    bool isempty(){
        return q.size()==0;
    }
    T front(){
        if(isempty()){
            return NULL;
        }
        return q.front();
    }
    T rear(){
        if(isempty())return NULL;
        return q.back();
    }
    int size(){
        return q.size();
    }
};
int main()
{
    DeQueue<int> queue;
    queue.push_back(1);
    queue.push_front(0);
    cout<<"Front:"<<queue.front()<<" ,Rear:"<<queue.rear()<<endl;
    queue.pop_front();
    cout<<"Performing pop front operation--->>\n";
    cout<<"Front:"<<queue.front()<<endl;
    return 0;
}
