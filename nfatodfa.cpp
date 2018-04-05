#include<iostream>
#include<string>
using namespace std;

struct nfa{
	string state;
	string aNext;
	string bNext;
}NFA[20];

struct dfa{
	string state;
	string stateRe;
	string aNext;
	string bNext;
}DFA[20];

int lineNFA;
int lineDFA=0;
string list="ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//nfa格式化输入
void inputNfa(){
	for(int i = 0; ; i++){
		//输入state
		cin>>NFA[i].state;
		//输入aNext
		string temp;
		cin>>temp;
		if(temp[1]=='N')
			NFA[i].aNext="";
		else{
			int d=0;
			for(unsigned  int j = 0; j<temp.length();j++){
				if(temp[j]!='{'&&temp[j]!='}'&&temp[j]!=','){
					NFA[i].aNext.push_back(temp[j]);
					d++;
				}
			}
		}
		//输入bNext
		cin>>temp;
		if(temp[1]=='N')
			NFA[i].bNext="";
		else{
			int d=0;
			for(unsigned  int j = 0; j<temp.length();j++){
				if(temp[j]!='{'&&temp[j]!='}'&&temp[j]!=','){
					NFA[i].bNext.push_back(temp[j]);
					d++;
				}
			}
		}
		if(NFA[i].state=="f"){
			lineNFA = i+1;
			break;
		}
	}
}

//在nfa中的位置
int showNfaLoc(char next){
	int i;
	for(i=0;i<lineNFA;i++)
		if(next==NFA[i].state[0]){
			//cout<<next<<"在nfa中的位置是"<<i<<endl;
			return i;
		}
		return -1;
}


//是否在现有DFA中出现过
bool isAppearInDFA(string next){
	for(int i=0;i<lineDFA;i++){
		if(next==DFA[i].state)
			return true;
	}
	return false;
}

//状态查重
string replaceRepeat(string str){
	for(unsigned int i=0;i<str.length();i++)
		for(unsigned int j=i+1;j<str.length();j++){
			if(str[i]==str[j]){
				str.replace(j,1,"");
			}
		}
		return str;
}

//转化为dfa
void toDfa(){
	DFA[0].state = NFA[0].state;
	DFA[0].stateRe=list[0];
	int d=0;
	for(int i = 0;  ;i++){
		//state
		DFA[i].aNext="";
		DFA[i].bNext="";
		for(unsigned int j=0;j<DFA[i].state.length();j++){
			int loc = showNfaLoc(DFA[i].state[j]);
			DFA[i].aNext.append(NFA[loc].aNext);
			DFA[i].bNext.append(NFA[loc].bNext);
		}
		DFA[i].aNext = replaceRepeat(DFA[i].aNext);
		DFA[i].bNext = replaceRepeat(DFA[i].bNext);

		DFA[i].stateRe = list[i];
		lineDFA=i+1;
		//aNext
		if(!isAppearInDFA(DFA[i].aNext)){
			if(DFA[i].aNext.length()!=0){
				d++;
				lineDFA=d;
				DFA[d].state = DFA[i].aNext;
			}
		}
		//bNext
		if(!isAppearInDFA(DFA[i].bNext)){
			if(DFA[i].bNext.length()!=0){
				d++;
				lineDFA=d;
				DFA[d].state=DFA[i].bNext;
			}
		}
		
		if(DFA[i].state=="f")
			break;
			
		if(i==d-1)
			break;
		
	}
}

//state输出格式化
string replaceState(string str){
	string ex="{";

	if(str.length()==1){
		ex.push_back(str[0]);
	}
	else{
		for(unsigned int i=0;i<str.length();i++){
			ex.push_back(str[i]);
			ex.push_back(',');
		}
	}
	ex.push_back('}');
	return ex;
}

//后继输出格式化
string replaceNext(string str){
	for(int i=0;i<lineDFA;i++)
		if(str==DFA[i].state){
			str=list[i];
		}
	return str;
}

int main(){
	inputNfa();
	toDfa();	
	for(int i=0;i<lineDFA;i++){
		string state;
		state = replaceState(DFA[i].state);
		cout<<state;
		cout<<DFA[i].stateRe;
		DFA[i].aNext=replaceRepeat(DFA[i].aNext);
		DFA[i].aNext=replaceNext(DFA[i].aNext);
		cout<<DFA[i].aNext;
		DFA[i].bNext=replaceRepeat(DFA[i].bNext);
		DFA[i].bNext=replaceNext(DFA[i].bNext);
		cout<<DFA[i].bNext<<endl;
	}


}
