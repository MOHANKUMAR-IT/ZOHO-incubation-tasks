#include <bits/stdc++.h>

using namespace std;
template <typename T> class Queue{
    vector<T> q;
public:
    Queue(){
        cout<<"Queue created\n";
    }
    void push(T data){
        q.push_back(data);
    }
    bool isempty(){
        return q.size()==0;
    }
    T top(){
        if(isempty()){
            return NULL;
        }
        return q[0];
    }
    int size(){
        return q.size();
    }
    void pop(){
        if(isempty())return;;
        q.erase(q.begin());
    }
};
int main()
{
    Queue<int> queue;
    for(int i=0;i<10;i++)queue.push(i);
    cout<<"Queue size:"<<queue.size()<<endl;
    cout<<"Is empty:"<<(queue.isempty()?"Yes":"No");
    Queue<string> queue1;
    queue1.push("Hello");
    queue1.push(",zoho");
    while(!queue1.isempty()){
        cout<<queue1.top();
        queue1.pop();
    }
    return 0;
}
