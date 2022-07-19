#include<bits/stdc++.h>
using namespace std;
bool match(stack<char> p,stack<char> s){
    bool res = false;
    if(p.size()==0 && s.size()==0)return true;
    else if(p.size()==0 && s.size()>0)return false;

    else if(p.top()==s.top()){
        p.pop();s.pop();
        return match(p,s);
    }
    else if(p.top()=='?'){
        p.pop();s.pop();
        return match(p,s);
    }
    else if(p.top()=='*'){
        p.pop();
        if(p.size()==0)return true;
        while(!res && s.size()>0){
            res |= match(p,s);
            s.pop();
            if(res)return res;
        }
    }
    return false;
}
int main()
{
    string wild ="z*ho",orig = "zoho";
    stack<char> p,s;
    for(int i=0;i<wild.size();i++){
        p.push(wild[i]);
    }
    for(int i=0;i<orig.size();i++){
        s.push(orig[i]);
    }
    cout<<match(p,s);
    return 0;
}
