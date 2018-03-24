/*
   Lab Name - Compiler Design
   Objective - Removal of Left Recursion from a CFG
   Name - Anup Agrawal
   Roll No. - UE143014
   Date - 22/02/2017
*/

#include<bits/stdc++.h>
using namespace std;
vector<string> v;
vector<string> p;
vector<string> a;
vector<string> b;
vector<string> ans;
vector<string> all;

void input()
{
    int n;
    cout<<"*************** Enter Number of Variables ******************************"<<endl;
    cin>>n;
    cout<<"*************** Enter Productions **************************************"<<endl;
    string s;
    for(int i=0;i<n;i++)
    {
        cin>>s;
        v.push_back(s);
    }
}

vector<string> breakProductions(string t)
{
    vector<string> tempv;
    string temps = "";
    for(int i=2;i<t.length();i++)
    {
        if(t[i] == '|')
        {
            tempv.push_back(temps);
            temps = "";
        }
        else{
            temps = temps + string(1,t[i]);
        }
    }
    tempv.push_back(temps);
    return tempv;
}

void printVector(vector<string> tempv)
{
    for(int i=0;i<tempv.size();i++)
    {
        cout<<tempv[i]<<endl;
    }
    cout<<endl;
}

bool IsLeftRecursive(vector<string> p, char start)
{
    bool flag = false;
    for(int i=0;i<p.size();i++)
    {
        string temps;
        temps = p[i];
        if(temps[0] == start)
        {
            flag = true;
        }
    }
    if(flag)
    {
        return true;
    }
    else{
        return false;
    }
}

vector<string> AlphaFinder(vector<string> p, char start)
{
    vector<string> tempv;
    for(int i=0;i<p.size();i++)
    {
        string temps;
        temps = p[i];
        if(temps[0] == start)
        {
            temps = temps.substr(1,temps.length()-1);
            tempv.push_back(temps);
        }
    }
    return tempv;
}

vector<string> BetaFinder(vector<string> p, char start)
{
    vector<string> tempv;
    for(int i=0;i<p.size();i++)
    {
        string temps;
        temps = p[i];
        if(temps[0] != start)
        {
            tempv.push_back(temps);
        }
    }
    return tempv;
}

vector<string> RemoveLeftRecursion(vector<string> a, vector<string> b, char start)
{
    string temps = "";
    string dash = "'";
    string sign = "-";
    vector<string> tempv;
    temps = start + sign;
    for(int i=0;i<b.size();i++)
    {
      if(i == (b.size()-1))
         {
             temps = temps + b[i] + start + dash;
         }
      else{
            temps = temps + b[i] + start + dash + '|' ;
         }
    }
    tempv.push_back(temps);
    temps = "";
    temps = start + dash + '-' ;
    for(int i=0;i<a.size();i++)
    {
      if(i == (a.size()-1))
         {
             temps = temps + a[i] + start + dash;
         }
      else{
            temps = temps + a[i] + start + dash + '|' ;
         }
    }
    temps = temps + '|' + '$';
    tempv.push_back(temps);
    return tempv;
}

void leftRecursion()
{
    for(int i=0;i<v.size();i++)
    {
        string temp;
        char start;
        temp = v[i];
        start = temp[0];
        p = breakProductions(v[i]);
        if(IsLeftRecursive(p,start))
        {
            cout<<"********** Yes, It is a left Recursive Production  "<<v[i]<<" ***********"<<endl;
            a = AlphaFinder(p,start);
            cout<<"********************* Alpha **************************************** "<<endl;
            printVector(a);
            b = BetaFinder(p,start);
            cout<<"********************* Beta *****************************************"<<endl;
            printVector(b);
            ans = RemoveLeftRecursion(a,b,start);
            cout<<"*************** Non-Left Recursive Productions *********************"<<endl;
            printVector(ans);
            all.insert(all.end(),ans.begin(),ans.end());
        }
        else{
            cout<<"******** No, It is not a Left Recursive Production  "<<v[i]<<" *************"<<endl;
            all.push_back(v[i]);
        }
    }
    cout<<"**************** Final Grammar ***********************"<<endl<<endl;
    printVector(all);
}

int main()
{
    input();
    leftRecursion();
    cout<<"************ Let's See what happens, in the case of left factoring ********************"<<endl;
    return 0;
}

