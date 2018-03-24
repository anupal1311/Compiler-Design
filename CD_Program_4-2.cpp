/*
   Lab Name - Compiler Design
   Objective - Apply Left Factoring for a CFG
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

vector<string> AlphaFinder(vector<string> p, char start)
{
    int cnt = 0;
    vector<string> tempv;
    string temps = "";
    string temp_s = "";
    bool flag = true;
    int sizee;
    sizee = p.size();
    string temp[sizee];
    for(int i=0;i<p.size();i++)
    {
        temp[i] = p[i];
    }
    while(flag)
    {
      if(temp[0][cnt] == temp[1][cnt])
      {
          flag = true;
          temps = temps + temp[1][cnt];
          cnt++;
      }
      else{
        flag = false;
      }
    }
    for(int i=2;i<p.size();i++)
    {
        for(int j=0;j<temps.length();j++)
        {
            if(temp[i][j] == temps[j])
            {
                temps[j] = temp[i][j];
                cout<<temps<<endl;
            }
            else{
                temps = temps.substr(0,temps.length()-(temps.length()-j));
                cout<<"***********"<<temps<<endl;
                break;
            }
        }
    }
 tempv.push_back(temps);
 return tempv;
}

vector<string> BetaFinder(vector<string> p, char start)
{
  string temps;
  string temp_s;
  vector<string> tempv;
  temps = a[0];
  for(int i=0;i<p.size();i++)
  {
    temp_s = p[i];
    if(temp_s == temps)
    {
        string s = "";
        tempv.push_back(s);
    }
    else{
    temp_s = temp_s.substr(temps.length(),temp_s.length() - temps.length());
    tempv.push_back(temp_s);
    }
  }
  return tempv;
}

bool IsLeftFactoringPoss(vector<string> p,char start)
{
    int cnt = 0;
    vector<string> tempv;
    string temps = "";
    string temp_s = "";
    bool flag = true;
    int sizee;
    sizee = p.size();
    string temp[sizee];
    for(int i=0;i<p.size();i++)
    {
        temp[i] = p[i];
    }
    while(flag)
    {
      if(temp[0][cnt] == temp[1][cnt])
      {
          flag = true;
          temps = temps + temp[1][cnt];
          cnt++;
      }
      else{
        flag = false;
      }
    }
    for(int i=2;i<p.size();i++)
    {
        for(int j=0;j<temps.length();j++)
        {
            if(temp[i][j] == temps[j])
            {
                temps[j] = temp[i][j];
            }
            else{
                temps = temps.substr(0,temps.length()-(temps.length()-j));
                break;
            }
        }
    }
    if(temps.size() != 0)
    {
        return true;
    }
    else{
        return false;
    }
}

vector<string> leftFactoredProd(vector<string> a, vector<string> b, char start)
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
             temps =  temps + start + dash + b[i] ;
         }
      else{
            temps = temps + start + dash + b[i] + '|' ;
         }
    }
    tempv.push_back(temps);
    temps = "";
    temps = start + dash + '-' ;
    for(int i=0;i<a.size();i++)
    {
      if(i == (a.size()-1))
         {
             temps = temps + a[i];
         }
      else{
            temps = temps + a[i] ;
         }
    }
    tempv.push_back(temps);
    return tempv;
}

void leftFactoring()
{
    for(int i=0;i<v.size();i++)
    {
        string temp;
        char start;
        temp = v[i];
        start = temp[0];
        p = breakProductions(v[i]);
        if(IsLeftFactoringPoss(p,start))
        {
        cout<<"******** Yes, Left Factoring can be applied for this  "<<v[i]<<" *********"<<endl;
        a = AlphaFinder(p,start);
        cout<<"********* Alpha *********"<<endl;
        printVector(a);
        b = BetaFinder(p,start);
        cout<<"******** Beta ********"<<endl;
        printVector(b);
        ans = leftFactoredProd(a,b,start);
        cout<<"********** Productions after apply Left Factoring ***********"<<endl;
        printVector(ans);
        all.insert(all.end(),ans.begin(),ans.end());
        }
        else{
            cout<<"******** No, Left Factoring cannot be applied for this  "<<v[i]<<" ********"<<endl;
            all.push_back(v[i]);
        }
    }
    cout<<"*************** Final Grammar ******************"<<endl;
    printVector(all);
}

int main()
{
    input();
    leftFactoring();
    return 0;
}
