/*
   Lab Name - Compiler Design
   Objective - Static Operator Precedence Parser
   Name - Anup Agrawal
   Roll No. - UE143014
   Date - 19/04/2017
*/
#include<bits/stdc++.h>
using namespace std;

stack<int> resultstk;
string tab[5][5];
stack<char> stk;
stack<char> out;
queue<char> que;
char ch='Y';
char qtop;
char stop;
int operation = 0;
string infix = "";
string postfix;
string instr;
stack<string> poststk;

void display(string);
void reduce();
void shift();


void line(int ter)
  {
      ter=ter*5;
      cout<<"  ";
    for(int i=1;i<=ter;i++)
      cout<<"--";
    cout<<"\n";
   }

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

void shift()
{
    if(que.front() != '$')
    {
        qtop = que.front();
        stk.push(qtop);
        que.pop();
        display("shift");
    }
    else if(stk.top() == '$' && que.front() == '$')
{
    cout<<"String is Successfully Parsed"<<endl;
}

    else{
     cout<<"String is NOT Parsed"<<endl;
    }
}


bool Isoperator(char ch)
{
        if(ch == '+')
        {
            operation = 1;
            return true;
        }
        else if(ch == '-')
        {
            operation = 2;
            return true;
        }
        else if(ch == '*')
        {
            operation = 3;
            return true;
        }
        else if(ch == '/')
        {
            operation = 4;
            return true;
        }
    else{
        return false;
    }
}

bool Isoperand(char ch)
{
    if(ch =='1' || ch =='2' ||  ch =='3' ||  ch =='4')
    {
        return true;
    }
    else{
        return false;
    }
}

void reduce()
{
    if(stk.top() != '$')
{
    out.push(stk.top());
    stk.pop();
    display("Reduce");
}
else if(stk.top() == 'S')
{
    cout<<"String is Successfully Parsed"<<endl;
}

else{
     cout<<"String is NOT Parsed"<<endl;
}
}


void input()
{
    string str;
    cout<<"Enter a input string"<<endl;
    cin>>instr;
}


void table()
{
    cout<<"Enter in table function"<<endl;
    tab[0][0] = "#" ;
    tab[0][1] = "i" ;
    tab[0][2] = "+" ;
    tab[0][3] = "*" ;
    tab[0][4] = "$" ;

    tab[1][0] = "i" ;
    tab[2][0] = "+" ;
    tab[3][0] = "*" ;
    tab[4][0] = "$" ;

    tab[1][1] = "" ;
    tab[1][2] = ">" ;
    tab[1][3] = ">" ;
    tab[1][4] = ">" ;

    tab[2][1] = "<" ;
    tab[2][2] = ">" ;
    tab[2][3] = "<" ;
    tab[2][4] = ">" ;

    tab[3][1] = "<" ;
    tab[3][2] = ">" ;
    tab[3][3] = ">" ;
    tab[3][4] = ">" ;

    tab[4][1] = "<" ;
    tab[4][2] = "<" ;
    tab[4][3] = "<" ;
    tab[4][4] = "" ;

    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            cout<<tab[i][j]<<"\t";
        }
        cout<<endl;
    }
}

void display(string action)
{
            displayStack(stk);
            cout<<"\t\t\t";
            displayQueue(que);
            cout<<"\t\t\t";
            cout<<action;
            cout<<"\t\t\t";
            displayStack(out);
            cout<<endl;
}


int findindicesrow(string d)
{
    int c=0;
    for(int i=0;i<5;i++)
    {
        if(tab[0][i] == d)
        {
            c = i;
        }
    }
    return c;
}

int findindicescolumn(string d)
{
    int c=0;
    for(int i=0;i<5;i++)
    {
        if(tab[i][0] == d)
        {
            c = i;
        }
    }
    return c;
}

void PostToIn()
{
    string temp;
    while(!out.empty())
    {
        temp = out.top();
        postfix.insert(0,temp);
        out.pop();
    }
    char ch;
    int temp1;
    int first;
    int second;
    int result;
    string op1;
    string op2;
    for(int i=0;i<postfix.length();i++)
    {
        ch = postfix[i];
        if(Isoperand(ch))
        {
            temp = ch;
            stringstream convertch(temp);
            convertch>>temp1;
            poststk.push(temp);
            resultstk.push(temp1);
        }
        else if(Isoperator(ch))
        {
            op1 = poststk.top();
            first = resultstk.top();
            poststk.pop();
            resultstk.pop();
            op2 = poststk.top();
            second = resultstk.top();
            poststk.pop();
            resultstk.pop();
            infix = op2 + ch + op1;
            poststk.push(infix);
            switch(operation)
            {
            case 1:
                resultstk.push(second + first);
                cout<<"\t\t\t\t\t\t\t\t\t"<<infix<<","<<second << "+" <<first <<"---->"<<resultstk.top()<<endl;
                break;
            case 2:
                resultstk.push(second - first);
                cout<<"\t\t\t\t\t\t\t\t\t"<<infix<<","<<second << "-" <<first <<"---->"<<resultstk.top()<<endl;
                break;
            case 3:
                resultstk.push(second * first);
                cout<<"\t\t\t\t\t\t\t\t\t"<<infix<<","<<second << "*" <<first <<"---->"<<resultstk.top()<<endl;
                break;
            case 4:
                resultstk.push(second / first);
                cout<<"\t\t\t\t\t\t\t\t\t"<<infix<<","<<second << "/" <<first <<"---->"<<resultstk.top()<<endl;
                break;
            }
        }
    }
    for(int i=0;i<infix.length();i++)
    {
        out.push(infix[i]);
    }
    display("None");
    cout<<"\t\t\t\t\t\t\t\t\t"<<resultstk.top()<<" --Answer"<<endl;
}


void traverse()
{
    cout<<"In traverse "<<endl;
    string tempqtop;
    string tempstop;
    int row;
    int column;
    for(int i=0;i< 2* instr.length();i++)
    {
        qtop = que.front();
        if(qtop == '1' || qtop == '2' || qtop == '3' || qtop == '4')
        {
            qtop = 'i';
        }
        tempqtop = qtop;
        stop = stk.top();
        if(stop == '1' || stop == '2' || stop == '3' || stop == '4')
        {
            stop = 'i';
        }
        tempstop = stop;
        column = findindicesrow(tempqtop);
        row = findindicescolumn(tempstop);
        if(tab[row][column] == "<")
        {
            shift();
        }
        else if(tab[row][column] == ">")
        {
            reduce();
        }
        else{
            cout<<"************** ERROR *************"<<endl;
        }
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
        cout<<"Stack"<<"\t\t\t"<<"Queue"<<"\t\t\t"<<"Action\t\t\t"<<"Output"<<endl<<endl;
        display("None");
}

void allclear()
{
    while(!stk.empty())
    {
        stk.pop();
    }
    while(!que.empty())
    {
        que.pop();
    }
    while(!out.empty())
    {
        out.pop();
    }
    while(!resultstk.empty())
    {
        out.pop();
    }
    while(!poststk.empty())
    {
        out.pop();
    }
    infix = "";
    postfix = "";
    operation =0;
}

int main()
{
    while(ch=='Y' || ch=='y')
    {
    intialize();
    table();
    traverse();
    PostToIn();
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
