/*
   Lab Name - Compiler Design
   Objective - Coversion of regular expression into finite automata
   Name - Anup Agrawal
   Roll No. - UE143014
   Date - 08/02/2017
*/

#include<bits/stdc++.h>
using namespace std;

vector< vector<string> > table;
int state = 0;


string ConvertIntoString(int number)
{
    stringstream ss ;
	ss << number ;
	return ss.str();
}

bool IsOperand(char C)
{
	if(C == 'a' || C == 'b')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool IsOperator(char C)
{
	if(C == '|' || C == '.')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int GetOperatorWeight(char op)
{
	int weight = -1;
	switch(op)
	{
	case '|':
		weight = 10;
		break;
	case '.':
		weight = 20;
		break;
	}
	return weight;
}

bool HasHigherPrecedence(char op1, char op2)
{
	int op1Weight = GetOperatorWeight(op1);
	int op2Weight = GetOperatorWeight(op2);
	return ((op1Weight > op2Weight) ?  true : false);
}

string ConvertIntoPostfix(string re)
{
	stack<char> S;
	string postfix = "";
	for(int i = 0;i<re.length();i++)
        {
            if(re[i] == ' ' || re[i] == ',') continue;
            else if(IsOperator(re[i]))
                    {
                        if(!S.empty()&& HasHigherPrecedence(S.top(),re[i]))
                        {
                            postfix += S.top();
                            S.pop();
                        }
                        S.push(re[i]);
                    }
            else if(re[i] == '*')
            {
                postfix+= re[i];
            }
            else if(IsOperand(re[i]))
                    {
                        postfix +=re[i];
                    }

            else if (re[i] == '(')
                    {
                        S.push(re[i]);
                    }

            else if(re[i] == ')')
                    {
                        while(!S.empty() && S.top() !=  '(')
                                {
                                    postfix += S.top();
                                    S.pop();
                                }
                    S.pop();
                    }
        }

	while(!S.empty())
        {
            postfix += S.top();
            S.pop();
        }
    cout<< "Postfix Expression for Entered Regular Expression ----> "<<postfix<<endl;
	return postfix;
}

void Only_a_b(int &in , int &fi , char ch) {
	vector<string> temp ;
	if(state == 0)
    {
	in = state ;
	fi = state + 1 ;
	state += 1 ;
    }
    else{
    in = state + 1;
    fi = state + 2;
    state += 2;
    }
	temp . push_back(ConvertIntoString(in)) ;
	temp . push_back(ConvertIntoString(fi)) ;
	temp . push_back(string(1 , ch)) ;
	table . push_back(temp) ;
	temp . clear() ;
}

void ReConcatenationRe(int &in , int &fi , int in1 , int fi1 , int in2 , int fi2) {
	in = in1 ;
	fi = fi2 ;
	vector<string> temp ;
	temp . push_back(ConvertIntoString(fi1)) ;
	temp . push_back(ConvertIntoString(in2)) ;
	temp . push_back("E") ;
	table . push_back(temp) ;
	temp . clear() ;
}

void ReUnionRe(int &in , int &fi , int in1 , int fi1 , int in2 , int fi2) {
	in = state + 1 ;
	fi = state + 2 ;
	state += 2 ;
	vector<string> temp ;
	temp . push_back(ConvertIntoString(in)) ;
	temp . push_back(ConvertIntoString(in1)) ;
	temp . push_back("E") ;
	table . push_back(temp) ;
	temp . clear() ;
	temp . push_back(ConvertIntoString(in)) ;
	temp . push_back(ConvertIntoString(in2)) ;
	temp . push_back("E") ;
	table . push_back(temp) ;
	temp . clear() ;
	temp . push_back(ConvertIntoString(fi1)) ;
	temp . push_back(ConvertIntoString(fi)) ;
	temp . push_back("E") ;
	table . push_back(temp) ;
	temp . clear() ;
	temp . push_back(ConvertIntoString(fi2)) ;
	temp . push_back(ConvertIntoString(fi)) ;
	temp . push_back("E") ;
	table . push_back(temp) ;
	temp . clear() ;
}

void ReClosure(int &in , int &fi , int in1 , int fi1) {
	in = state + 1 ;
	fi = state + 2 ;
	state += 2 ;
	vector<string> temp ;
	temp . push_back(ConvertIntoString(fi1)) ;
	temp . push_back(ConvertIntoString(in1)) ;
	temp . push_back("E") ;
	table . push_back(temp) ;
	temp . clear() ;
	temp . push_back(ConvertIntoString(in)) ;
	temp . push_back(ConvertIntoString(in1)) ;
	temp . push_back("E") ;
	table . push_back(temp) ;
	temp . clear() ;
	temp . push_back(ConvertIntoString(in)) ;
	temp . push_back(ConvertIntoString(fi)) ;
	temp . push_back("E") ;
	table . push_back(temp) ;
	temp . clear() ;
	temp . push_back(ConvertIntoString(fi1)) ;
	temp . push_back(ConvertIntoString(fi)) ;
	temp . push_back("E") ;
	table . push_back(temp) ;
	temp . clear() ;
}

void ReSolveRe(int &in , int &fi , string str) {
	str = ConvertIntoPostfix(str) ;
	vector<pair<int , int> > solve ;
	for(int i = 0 ; i < str . length() ; i ++) {
		if(str[i] == 'a' || str[i] == 'b') {
			Only_a_b(in , fi , str[i]) ;
			solve . push_back(make_pair(in , fi)) ;
		} else {
			if(str[i] == '.') {
				int in2 = solve[solve . size() - 1] . first ;
				int fi2 = solve[solve . size() - 1] . second ;
				int in1 = solve[solve . size() - 2] . first ;
				int fi1 = solve[solve . size() - 2] . second ;
				solve . pop_back() ;
				solve . pop_back() ;
				ReConcatenationRe(in , fi , in1 , fi1 , in2 , fi2) ;
				solve . push_back(make_pair(in , fi)) ;
			}
			if(str[i] == '|') {
				int in2 = solve[solve . size() - 1] . first ;
				int fi2 = solve[solve . size() - 1] . second ;
				int in1 = solve[solve . size() - 2] . first ;
				int fi1 = solve[solve . size() - 2] . second ;
				solve . pop_back() ;
				solve . pop_back() ;
				ReUnionRe(in , fi , in1 , fi1 , in2 , fi2) ;
				solve . push_back(make_pair(in , fi)) ;
			}
			if(str[i] == '*') {
				int in1 = solve[solve . size() - 1] . first ;
				int fi1 = solve[solve . size() - 1] . second ;
				solve . pop_back() ;
				ReClosure(in , fi , in1 , fi1) ;
				solve . push_back(make_pair(in , fi)) ;
			}
		}
	}
}

void PrintSol() {
	cout <<"State\ta\tb\tE\n" ;
	for(int i = 0 ; i < table . size() ; i ++) {
		if(table[i][2] == "a") {
			cout << table[i][0] << "\t" << table[i][1] << "\t_\t_\n" ;
		}
		if(table[i][2] == "b") {
			cout << table[i][0] << "\t_\t" << table[i][1] << "\t_\n" ;
		}
		if(table[i][2] == "E") {
			cout << table[i][0] << "\t_\t_\t" << table[i][1] << "\n" ;
		}
	}
}
int main()
{
    string input;
    int in;
    int fi;
    cout<<"********** Enter a Regular Expression **********"<<endl;
    cin>>input;
    ReSolveRe(in,fi,input);
    cout<<endl<<"Intial State ---> "<<in<<endl<<endl<<"Final State  ---> "<<fi<<endl<<endl;
    PrintSol();
    return 0;
}
