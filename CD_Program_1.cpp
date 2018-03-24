/*
   Lab Name - Compiler Design
   Objective - To implement the idea of Lexical Analysis
   Name - Anup Agrawal
   Roll No. - UE143014
   Date - 25/01/2017 & 01/02/2017
*/
#include<iostream>
#include<fstream>
#include<string.h>
#include<sstream>
#include<vector>
#include<algorithm>
#define SIZE 100

using namespace std;

int main()
{
    ifstream in,key,op;
    ofstream out;
    in.open("third.txt",ios::in);
    key.open("keywords.txt",ios::in);
    op.open("operators.txt",ios::in);
    out.open("output.txt");
    int line = 0;
    char ch_in,ch_key,ch_op;
    ifstream in1;
    ofstream out1;
    char ch;
    int Line = 1,comment=0;
    cout<<"1. ";
    in1.open("input.txt",ios::in);
    out1.open("temp.txt");
    while(!in1.eof())
    {
        in1.get(ch);
        switch(ch)
        {
     case '"':
        {
            cout<<ch;
            in1.get(ch);
            while(ch !='"')
            {
                cout<<ch;
                in1.get(ch);
            }
            cout<<'"';
              break;
        }
     case '/' :
        in1.get(ch);
        if(ch == '/')
        {
          comment++;
          while(in1.get(ch))
          {
               if(ch == '\n')
                {
                 cout<<ch;
                 Line++;
                 cout<<Line<<". ";
                 break;
                }
          }
        }
          else if(ch == '*')
          {
            comment++;
            in1.get(ch);
            while(in1.get(ch))
            {
                if(ch == '\n')
                {
                 cout<<ch;
                 Line++;
                 cout<<Line<<". ";
                }
                if(ch == '*')
                {
                    in1.get(ch);
                    if(ch == '/')
                    {
                        break;
                    }
                }
            }
          }
          else{
            cout<<'/';
            cout<<ch;
            out1.put('/');
            out1.put(ch);
          }
          break;

     default:
        cout<<ch;
         if(ch == '\n')
        {
            Line++;
            cout<<Line<<". ";
        }
    }
    }
    cout<<endl<<"******"<<comment<<"  comments removed successfully *********"<<endl;
    in1.close();
    out1.close();
    vector<string> v;
    vector<string> keyw;
    vector<string> ope;
    vector<string> fkeyw;
    vector<string> fope;
    string word;
    string temp = "";
    vector<int> li;
    vector<int> fli;

    while(!in.eof())
    {

     in.get(ch_in);
     if(ch_in == '\n')
     {
         line++;
     }
        if(ch_in !=';' && ch_in != '(' && ch_in !=' ' && ch_in != '\n' && ch_in!=')' && ch_in != '}' && ch_in != '{' && ch_in !='<' && ch_in != '>' && ch_in !='.' && ch_in != '#')
         {
             if(ch_in != '\n')
             {
                temp += ch_in;
             }
         }
         else{
            if(temp != "")
            {
                v.push_back(temp);
                li.push_back(line);
            }
            temp ="";
         }
     }
   v.push_back("}");
   li.push_back(line);
   while(getline(key,word))
   {
       keyw.push_back(word);
   }
   while(getline(op,word))
   {
       ope.push_back(word);
   }
   cout<<" ********** Detected Keywords ***********"<<endl;
   out<<" ********** Detected Keywords ***********"<<endl;
   for(int i=0;i<v.size();i++)
   {
       for(int j=0;j<keyw.size();j++)
       {
           if(v[i] == keyw[j])
           {
               fkeyw.push_back(v[i]);
               cout<<"Line Number ---> "<<li[i]<<" --->"<<v[i]<<" ----> "<<" Keyword"<<endl;
               out<<"Line Number ---> "<<li[i]<<" --->"<<v[i]<<endl;
           }
       }
   }
   cout<<" ********** Detected Operators ***********"<<endl;
   out<<" ********** Detected Operators ***********"<<endl;
   for(int i=0;i<v.size();i++)
   {
       for(int j=0;j<ope.size();j++)
       {
           if(v[i] == ope[j])
           {
               fope.push_back(v[i]);
               cout<<"Line Number ---> "<<li[i]<<" ---> "<<v[i]<<" ----> "<<" Operator"<<endl;
               out<<"Line Number ---> "<<li[i]<<" ---> "<<v[i]<<endl;
           }
       }
   }
   cout<<"************* Identifiers **********************"<<endl;
   out<<"************* Identifiers **********************"<<endl;
   vector<string> res;
   vector<string> fres;
   set_symmetric_difference(v.begin(), v.end(),fkeyw.begin(), fkeyw.end(),back_inserter(res));
   int pos1;
   fres = v;
   for(int i=0;i<fkeyw.size();i++)
   {
        pos1 = (find(fres.begin(),fres.end(),fkeyw[i])) - fres.begin();
        fres[pos1] = "";
   }
   for(int i=0;i<fres.size();i++)
   {
       if(fres[i] == "")
       {
           fres.erase(fres.begin() + i);
           i = i - 1;
       }
   }
   int pos;
   for(int i=0;i<fres.size();i++)
   {
    pos = (find(v.begin(),v.end(),fres[i])) - v.begin();
    string s = fres[i];
    int length;
    length = s.length();
    bool flag = true;
    int asc = (int)s[0];
    if(!((asc >= 65 && asc <= 90) || (asc >=97 && asc <=122)))
    {
      flag = false;
      cout<<"Invalid Identifier : "<< s <<" ,Error : Identifier must start with an alpha at Line ----> " <<li[pos]<<endl;
      out<<"Invalid Identifier : "<< s <<" ,Error : Identifier must start with an alpha at Line ----> " <<li[pos]<<endl;
    }
    else{

        for(int j=1;j < (length - 1);j++)
        {
            asc = (int) s[j];
            if(!((asc >= 65 && asc <= 90) || (asc >=97 && asc <=122) || (asc >= 48 && asc <= 57) || (asc == 95)))
            {
                flag = false;
                cout<<"Invalid Identifier : "<< s <<" ,Error : Identifier cannot contain " <<s[j]<<" at Line ---->  "<<li[pos]<<endl;
                out<<"Invalid Identifier : "<< s <<" ,Error : Identifier cannot contain " <<s[j]<<" at Line ---->  "<<li[pos]<<endl;
            }
        }

            asc = (int) s[length -1];
            if(!((asc >= 65 && asc <= 90) || (asc >=97 && asc <=122) || (asc >= 48 && asc <= 57) || (asc == 95) || (asc == 42)))
            {
                flag = false;
                cout<<"Invalid Identifier : "<< s <<" ,Error : Identifier cannot contain " <<s[length - 1]<<" at Line ---->  "<<li[pos]<<endl;
                out<<"Invalid Identifier : "<< s <<" ,Error : Identifier cannot contain " <<s[length - 1]<<" at Line ---->  "<<li[pos]<<endl;
            }
    }
    if(flag)
    {
        cout<<"Valid Identifier in Line ----> "<<li[pos]<<" -----> "<<s<<endl<<endl;
        out<<"Valid Identifier in Line ----> "<<li[pos]<<" -----> "<<s<<endl<<endl;
    }
    else{
        cout<<"Invalid Identifier in Line ----> "<<li[pos]<<"----->"<<s<<endl<<endl;
        out<<"Invalid Identifier in Line ----> "<<li[pos]<<"----->"<<s<<endl<<endl;
    }
   }
   in.close();
   key.close();
   op.close();
   out.close();
   return 0;
}
