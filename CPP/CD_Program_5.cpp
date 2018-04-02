/*
   Lab Name - Compiler Design
   Objective - LL(1) Parser
   Name - Anup Agrawal
   Roll No. - UE143014
   Date - 22/02/2017
*/


#include<bits/stdc++.h>
using namespace std;
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
int main()
{
    int i=0,n=0,j,k,flag=1,update=0,epsilon=1;
    char ch,ch1;
    string temp,temp1;
    string str[10],tok[20][20],var[10],tok1[20][20],c,parse[50],table[20][20];
    fstream fin,fout;
    fin.open("output3.txt",ios::in);
    unordered_map <string, string> m;
    unordered_map <string, string> q;
    unordered_map <string,int> row;
    unordered_map <string,int> column;
     string t[20][20];
     string first[10][2];
     string terminal[20];
     int ter=0;

     while(!fin.eof())
    {
        getline(fin,str[i]);
            if(!str[i].empty())
            {
             n++;
             var[i]=str[i][0];
            first[i][0]=var[i];
            i++;
            }
    }

    cout<<"**********************************************************************"<<endl;
    for(i=0;i<n;i++)
    {
        k=0;
        for(j=2;str[i][j]!='\0';j++)
        {
            if(str[i][j]=='|'||str[i][j]=='>')
            {
                j++;
                for(;str[i][j]!='\0'&&str[i][j]!='|';j++)
                  {
                      tok[i][k]+=str[i][j];
                      tok1[i][k]+=str[i][j];
                  }
                j--;
                k++;
            }
        }
    }
 //first code-------------------------------------------------------
    do{
        update=0;
        for(i=0;i<n;i++)
        {
            for(j=0;(!(tok[i][j].empty()));j++)
            {
                 ch=tok[i][j][0];
               if(!(isupper(ch))&&m[var[i]].find(ch)==-1)
               {
                   m[var[i]]+=ch;
                   t[i][j]+=ch;
                   update=1;
               }
               if(isupper(ch))
               {
                   k=0;
                    c;
                   c+=ch;
                   while(m[c][k]!='\0')
                   {
                       if(m[var[i]].find(m[c][k])==-1&&m[c][k] != 'e')
                       {
                           m[var[i]]+=m[c][k];
                           t[i][j]+=m[c][k];

                           update=1;

                       }
                       else if(m[c][k]=='e')
                       {
                           tok[i][j].erase(tok[i][j].begin());
                           if(tok[i][j].empty())
                           {
                                m[var[i]]+='e';
                                t[i][j]+=m[var[i]];

                           }
                           else
                            j--;
                       }
                       k++;
                   }
                   c.clear();
               }
            }
        }

    }while(update==1);
   //first code ends-----------------------------------------------
 cout<<"======="<<"First:"<<"======="<<endl;
    for(i=0;i<n;i++)
    {
        first[i][1]+=m[var[i]];
      cout<<var[i]<<":"<<first[i][1]<<endl;
    }

  //follow code starts----------------------------------------------
q[var[0]]+='$';

   do{
        update=0;
        for(i=0;i<n;i++)
        {
            for(j=0;(!(tok1[i][j].empty()));j++)
            {
                for(k=0;tok1[i][j][k]!='\0';k++)
                    {
                    string c1;
                      ch=tok1[i][j][k];

                      int next=k;
                      epsilon=1;
                      if(isupper(ch))
                       {
                           while(epsilon==1)
                           {
                               epsilon=0;

                                next=next+1;
                                c+=ch;
                              ch1=tok1[i][j][next];
                             // cout<<ch1<<endl;
                              c1+=ch1;
                              if(isupper(ch1))
                              {
                                  int l=0;

                                  while(m[c1][l]!='\0')
                                  {
                                      if(q[c].find(m[c1][l])==-1&&m[c1][l]!='e')
                                      {
                                           q[c]+=m[c1][l];
                                           update=1;
                                      }
                                      else if(m[c1][l]=='e')
                                       {
                                         epsilon=1;
                                       }

                                      l++;
                                  }


                              }
                              else if(q[c].find(ch1)==-1&&ch1!='e')
                                    {
                                         q[c]+=ch1;
                                         update=1;
                                    }
                                else if(ch1=='\0')
                                {
                                     int l=0;

                                  while(q[var[i]][l]!='\0')
                                  {
                                      if(q[c].find(q[var[i]][l])==-1)
                                      {
                                           q[c]+=q[var[i]];
                                           update=1;

                                      }
                                    l++;

                                  }
                                }

                              c.clear();
                              c1.clear();
                             }
                          }
                    }
            }
        }

    }while(update==1);

    cout<<"======="<<"Follow:"<<"======="<<endl;
   for(i=0;i<n;i++)
    {

      cout<<var[i]<<":"<<q[var[i]]<<endl;
    }

    //Follow code ends-----------------------------------------------------

    //Parse table starts---------------------------------------------------

    for(i=0;i<n;i++)
        for(j=0;(!(tok1[i][j].empty()));j++)
            for(k=0;tok1[i][j][k]!='\0';k++)
             {
                ch=tok1[i][j][k];
                if(!isupper(ch)&&ch!='e'&&temp1.find(ch)==-1)
                {
                    terminal[ter]=ch;
                    temp1+=ch;
                    ter++;
                }
            }
    terminal[ter++]='$';
    for(i=0;i<n;i++)
    {
        row[var[i]]=i;
    }
    for(i=0;i<ter;i++)
    {
         column[terminal[i]]=i;
    }

    for(i=0;i<n;i++)
    {
        for(j=0;j<ter;j++)
        {
            for(k=0;(!(tok1[i][k].empty()));k++)
            {
                for(int z=0;t[i][k][z]!='\0';z++)
                {
                    string h;
                    h=t[i][k][z];
                       if(h==terminal[j])
                       {
                           int t1;

                           t1=column[h];
                           table[i][t1]=tok1[i][k];
                       }
                }
            }
        }
    }
    for(i=0;i<n;i++)
    {
        if(m[var[i]].find('e')==1)
        {
            string t2;
            int len;
            t2=q[var[i]];
            len=t2.length();
            for(j=0;j<len;j++)
            {
                string t3;
                t3=t2[j];
                char t4=t2[j];

                if(!(t4=='\0'))
                   table[i][column[t3]]='e';

            }
        }
    }
   for(i=0;i<n;i++)
      {
          for(j=0;j<ter;j++)
          {
              if(!(table[i][j].empty()))
              {
                  string str;
                  str+=var[i];
                  str+="->";
                  table[i][j].insert(0,str);
              }

          }
      }
   cout<<endl<<"================================Parse Table================================"<<"\n\n\n";
    for(i=0;i<ter;i++)
      cout<<setw(10)<<terminal[i];
      cout<<endl;
      line(ter);
      for(i=0;i<n;i++)
      {
          cout<<var[i];
        for(j=0;j<ter;j++)
        {
            cout<<setw(10)<<table[i][j];
        }
        cout<<endl;
        line(ter);
      }
 cout<<"\n\n\n";
//-------------------------------------------Parse table ends----------------------------------------
string pstring,terminal1;
for(i=0;i<ter;i++)
{
    terminal1+=terminal[i];
}

char s1,ans;
int a1=0,error=0;
s1=var[0][0];
stack<char> stk;
queue<char> que;
stk.push('$');
stk.push(s1);
char qtop,stop;


do{
        cout<<"Enter the string to parse:";
        cin>>pstring;
        string st,qt,tval;

        while(pstring[a1]!='\0')
        {
            que.push(pstring[a1]);
            a1++;
        }
        que.push('$');
        while(!que.empty()&&!stk.empty())
        {
            displayStack(stk);
            cout<<"\t\t\t";
            displayQueue(que);
            cout<<"\t\t\t";
            cout<<tval;
            tval.erase();
            cout<<endl;
            qtop=que.front();

            stop=stk.top();
            if(qtop==stop)
            {
               que.pop();
               stk.pop();
            }
            else if(stop=='e')
            {
                stk.pop();
            }
            else if(qtop!=stop)
            {

                if(terminal1.find(stop)==1)
                {
                    error=1;
                    break;
                }
                else
                {
                    st=stop;
                    qt=qtop;
                    int r1,c1;
                    r1=row[st];
                    c1=column[qt];
                    tval=table[r1][c1];
                    if(tval.empty())
                    {
                      error=1;
                      cout<<"Error";
                      break;
                    }
                    else
                    {
                        stk.pop();
                        i=0;
                        while(tval[i]!='\0')
                            i++;
                        i--;
                        while(tval[i]!='>')
                        {
                            if(tval[i]!=' ')
                               {
                                    stk.push(tval[i]);
                               }
                            i--;
                        }
                    }

                }
            }
        }
        if(error==0&&que.empty()&&stk.empty())
        cout<<"String is parsed";
        else
          {
              cout<<"String not parsed";
          }
       cout<<"\nDo you want to parse more string(y/n):";
       cin>>ans;
  }while(ans=='Y'||ans=='y');

 }

