#include<bits/stdc++.h>
using namespace std;

unordered_map<char,int> precd;

void doProcess(stack<int> &nums,stack<char> &opr){

        int a = nums.top();nums.pop();
        int b = nums.top();nums.pop();
        if(opr.top()=='+'){
            nums.push(a+b);
        }
        else if(opr.top()=='-'){
            nums.push(b-a);
        }
        else if(opr.top()=='*'){
            nums.push(a*b);
        }
        else{
            if(a==0){
                cout<<"Cannot divide by 0";
                exit(0);
            }
            nums.push(b/a);
        }
        opr.pop();
}

int main()
{
    string s="( 2 + 5 ) * 3 - 8 / 3"; 
    precd = {{'*',2},{'/',2},{'+',1},{'-',1}};
    stack<int> nums;
    stack<char> opr;
    for(int i=0;i<s.size();i++){
        if(s[i]==' ')continue;
        if(isdigit(s[i])){
            int n = 0;
            while(i<s.size() && isdigit(s[i])){
                n=n*10+(s[i]-'0');
                i++;
            }
            i--;
            nums.push(n);
        }
        else if(s[i]=='('){
            opr.push(s[i]);
        }
        else if(s[i]==')'){
            while(opr.top()!='(')
                doProcess(nums,opr);
            opr.pop();
        }
        else{
            while(!opr.empty() && precd[s[i]]<=precd[opr.top()]){
                doProcess(nums,opr);
            }
            opr.push(s[i]);
        }
    }

    while(!nums.empty() && !opr.empty()){
        doProcess(nums,opr);
    }
    cout<<nums.top();
    return 0;
}
