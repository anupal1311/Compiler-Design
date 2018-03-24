/*
   Lab Name - Compiler Design
   Objective - Bottom-Up parser
   Name - Anup Agrawal
   Roll No. - UE143014
   Date - 05/04/2017
*/

#include<bits/stdc++.h>
using namespace std;

vector<string> v;
string instr;
stack<char> stk;
queue<char> que;
string action;
string rule;
int error = 0;
char qtop;
char stop;
char ch = 'Y';

void shift();
void reduce();

void displayStack(stack<char> a)
{
    stack <char> b;
    string s,temp;
    while(!a.empty())
   {
       temp=a.top();
       s.insert(0,temp);
       b.push(a.top());
       a.pop();
   }
   cout<<s;
   while(!b.empty())
   {
       a.push(b.top());
       b.pop();
   }
}

void displayQueue(queue<char> a)
{
    queue <char> b;
   string s,temp;

   while(!a.empty())
   {
       temp=a.front();
       s+=temp;
       b.push(a.front());
       a.pop();
   }
   cout<<s;
   while(!b.empty())
   {
       a.push(b.front());
       b.pop();
   }
}

void input()
{
    string str;
    int n;
    cout<<"*************** Enter Number of Variables ******************************"<<endl;
    cin>>n;
    cout<<"*************** Enter Productions **************************************"<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>str;
        v.push_back(str);
    }
    cout<<"Enter a input string"<<endl;
    cin>>instr;
}
/*
void reverseStr(string &a)
{
    int n = a.length();
    for (int i=0; i<n/2; i++)
       swap(a[i], a[n-i-1]);
}
*/
void display(string action, string rule)
{
            displayStack(stk);
            cout<<"\t\t\t\t";
            displayQueue(que);
            cout<<"\t\t\t\t";
            cout<<action;
            cout<<"\t\t\t\t";
            cout<<rule<<endl<<endl;
}

void shift()
{
    if(que.front() != '$')
    {
        qtop = que.front();
        stk.push(qtop);
        que.pop();
        display("shift","None");
        reduce();
    }
    else if(stk.top() == 'S' && stk.size() == 2 && que.front()=='$')
{
    cout<<"String is Successfully Parsed"<<endl;
}

    else{
     cout<<"String is NOT Parsed"<<endl;
    }
}

void reduce()
{
    int update =0;
    stack <char> b;
    string s,temp;
    bool flag = false;
    if(stk.top() != '$' && stk.top() != 'S')
    {
        do{
            update = 0;
            flag = false;
        for(int i=1;i<stk.size();i++)
        {
            for(int j=1;j<=i;j++)
            {
                update = 0;
                flag = false;
                temp=stk.top();
                s.insert(0,temp);
                b.push(stk.top());
                stk.pop();
            }
         for(int k=0;k<v.size();k++)
         {
            string temps;
            string tempss;
            char inc;
            temps = v[k];
            tempss = temps;
            temps =  temps.substr(2,temps.length()-2);
            if(temps == s)
            {
                flag = true;
                s = "";
                update = 1;
                inc = tempss[0];
                stk.push(inc);
                display("reduce",tempss);
                while(!b.empty())
                {
                    b.pop();
                }
            }
         }
        if(flag == false)
        {
                s = "";
                while(!b.empty())
                {
                    stk.push(b.top());
                    b.pop();
                }
        }
        }}while(update == 1);
        shift();
    }
else if(stk.top() == 'S')
{
    cout<<"String is Successfully Parsed"<<endl;
}

else{
     cout<<"String is NOT Parsed"<<endl;
}
}

void intialize()
{
    cout<<"******************* BUP *******************"<<endl;
    input();
    int i=0;
    while(instr[i]!='\0')
        {
            que.push(instr[i]);
            i++;
        }
        que.push('$');
        stk.push('$');
        cout<<"Stack"<<"\t\t\t\t"<<"Queue"<<"\t\t\t\t"<<"Action"<<"\t\t\t\t"<<"Production"<<endl<<endl;
        display("None","None");
}


void allclear()
{
    v.clear();
    while(!stk.empty())
    {
        stk.pop();
    }
    while(!que.empty())
    {
        que.pop();
    }
}

int main()
{
    while(ch=='Y' || ch=='y')
    {
    intialize();
    shift();
    cout<<"Wnat to parse more strings, please enter Y/y"<<endl;
    cin>>ch;
    if(ch=='y' || ch=='Y')
    {
    system("cls");
    allclear();
    }
    else{
        exit(0);
    }
    }
return 0;
}

