#pragma once

#include<cstdio>
#include<cstring>
#include<iostream>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

string key[32] = {"auto","break","case","char","const","continue","default","do","double",
"else","enum","extern","float","for","goto","if","int","long","register","return","short",
"signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile",
"while"};

char change[4] = { '\n','\r','\t',' ' };
int number = 1;

int isKey(string word)
{
	for (int i = 0; i < 32; i++) {
		if (key[i] == word)
			return i;
	}
	return -1;
}

int isChange(char a)
{
	for (int i = 0; i < 4; i++) {
		if (a == change[i])return 1;
	}
	return 0;
}

int isLetter(char a)
{
	if ((a >= 'a' && a <= 'z') || a >= 'A' && a <= 'Z') {
		return 1;
	}
	return 0;
}

int isIdentifier(char a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')||(a=='_')||(a>='0'&&a<='9')) {
		return 1;
	}
	return 0;
}

int isNumber(char a)
{
	if (a >= '0' && a <= '9') {
		return 1;
	}
	return 0;
}

int numberReapeatPoint(string word) {
	int a= word.find('.');
	if (a >= 0)return 0;
	else return 1;
}


void read_prog(string& prog)
{
	char c;
	while (scanf("%c", &c) != EOF) {
		prog += c;
	}
}

void Analysis() 
{
	string prog;
	read_prog(prog);
	int i = 0;
	char c = ' ';
	string word = "";
	bool end = 0;
	int l = prog.length();
	for (i = 0; i<l; i++) {
		if (i+1==l)end = 1;
		word = "";
		c = prog[i];
		if (isChange(c)) {}
		else if (isLetter(c)) {//识别标识符和保留字
			while (isLetter(c)) {
				word += c;
				i++;
				c = prog[i];
			}
			i--;
			if (isKey(word)>=0) {
				int t = isKey(word);
				if(!end)
					cout << number << ": <" << word << ',' << t + 1 << '>' << endl;
				else
					cout << number << ": <" << word << ',' << t + 1 << '>';
				number++;
			}
			else if (isKey(word) < 0) {
				if (c == '_' || (c >= '0' && c <= '9'))i++;
				while (isIdentifier(c)) {
					word += c;
					i++;
					c = prog[i];
				}
				if(!end)
					cout << number << ": <" << word << ",81>" << endl;
				else
					cout << number << ": <" << word << ",81>" ;
				number++;
			}
		}
		else if (isNumber(c)||(c=='.'&&word!="")||(c=='-'&&word==""&&isNumber(prog[i+1]))) {//识别常数
			while (isNumber(c)||(c=='-')||(c=='.'&&numberReapeatPoint(word))) {
				word += c;
				i++;
				c = prog[i];
			}
			if(!end)
				cout << number << ": <" << word << ",80>" << endl;
			else
				cout << number << ": <" << word << ",80>" ;
			number++;
			i--;
		}
		else if(c=='/'){
			word += c;
			i++;
			c = prog[i];
			if (c=='=') {
				if (!end)
					cout << number << ": <" << word << ",51>" << endl;
				else
					cout << number << ": <" << word << ",51>";
				number++;
			}
			else if (c == '/') {
				word += c;
				i++;
				c = prog[i];
				while (c != '\n') {
					word += c;
					i++;
					c = prog[i];
				}
				if (!end)
					cout << number << ": <" << word << ",79>" << endl;
				else
					cout << number << ": <" << word << ",79>";
				number++;
			}
			else if (c == '*') {
				word += c;
				i++;
				c = prog[i];
				while ((c != '*') &&( prog[i + 1] != '/')|| (c == '*') && (prog[i + 1] != '/')) {
					word += c;
					i++;
					c = prog[i];
				}
				word += "*/";
				i++;
				if (!end)
					cout << number << ": <" << word << ",79>" << endl;
				else
					cout << number << ": <" << word << ",79>";
				number++;
			}
			else {
				if (!end)
					cout << number << ": <" << word << ",50>" << endl;
				else
					cout << number << ": <" << word << ",50>";
				number++;
			}
		}
		else if (c == '-') {
			word += c;
			i++;
			c = prog[i];
			if (c == '-') {
				word += c;
				if (!end)
					cout << number << ": <" << word << ",34>" << endl;
				else
					cout << number << ": <" << word << ",34>";
				number++;
			}
			else if (c == '=') {
				word += c;
				if (!end)
					cout << number << ": <" << word << ",35>" << endl;
				else
					cout << number << ": <" << word << ",35>";
				number++;
			}
			else if (c == '>') {
				word += c;
				if (!end)
					cout << number << ": <" << word << ",36>" << endl;
				else
					cout << number << ": <" << word << ",36>";
				number++;
			}
			else {
				if (!end)
					cout << number << ": <" << word << ",33>" << endl;
				else
					cout << number << ": <" << word << ",33>";
				i--;
				number++;
			}
		}
		else if (c == '!') {
			word += c;
			i++;
			c = prog[i];
			if (c == '=') {
				word += c;
				if (!end)
					cout << number << ": <" << word << ",38>" << endl;
				else
					cout << number << ": <" << word << ",38>";
				number++;
			}
			else {
				if (!end)
					cout << number << ": <" << word << ",37>" << endl;
				else
					cout << number << ": <" << word << ",37>";
				i--;
				number++;
			}
		}
		else if (c == '%') {
		word += c;
		i++;
		c = prog[i];
		if (c == '=') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",40>" << endl;
			else
				cout << number << ": <" << word << ",40>";
			number++;
		}
		else if (c == 'd') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",81>" << endl;
			else
				cout << number << ": <" << word << ",81>";
			number++;
		}
		else if (c == 'f') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",81>" << endl;
			else
				cout << number << ": <" << word << ",81>";
			number++;
		}
		else if (c == 's') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",81>" << endl;
			else
				cout << number << ": <" << word << ",81>";
			number++;
		}
		else if (c == 'c') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",81>" << endl;
			else
				cout << number << ": <" << word << ",81>";
			number++;
		}
		else if (c == 'e') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",81>" << endl;
			else
				cout << number << ": <" << word << ",81>";
			number++;
		}
		else if (c == 'i') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",81>" << endl;
			else
				cout << number << ": <" << word << ",81>";
			number++;
		}
		else if (c == 'o') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",81>" << endl;
			else
				cout << number << ": <" << word << ",81>";
			number++;
		}
		else if (c == 'u') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",81>" << endl;
			else
				cout << number << ": <" << word << ",81>";
			number++;
		}
		else if (c == 'x') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",81>" << endl;
			else
				cout << number << ": <" << word << ",81>";
			number++;
		}
		else if (c == 'p') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",81>" << endl;
			else
				cout << number << ": <" << word << ",81>";
			number++;
		}
		else {
			if (!end)
				cout << number << ": <" << word << ",39>" << endl;
			else
				cout << number << ": <" << word << ",39>";
			i--;
			number++;
		}
		}
		else if (c == '&') {
		word += c;
		i++;
		c = prog[i];
		if (c == '&') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",42>" << endl;
			else
				cout << number << ": <" << word << ",42>";
			number++;
		}
		else if (c == '=') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",43>" << endl;
			else
				cout << number << ": <" << word << ",43>";
			number++;
		}
		else {
			if (!end)
				cout << number << ": <" << word << ",41>" << endl;
			else
				cout << number << ": <" << word << ",41>";
			i--;
			number++;
		}
		}

		else if (c == '(') {
		word += c;
		if (!end)
			cout << number << ": <" << word << ",44>" << endl;
		else
			cout << number << ": <" << word << ",44>";
		number++;
		}

		else if (c == ')') {
		word += c;
		if (!end)
			cout << number << ": <" << word << ",45>" << endl;
		else
			cout << number << ": <" << word << ",45>";
		number++;
		}

		else if (c == '*') {
		word += c;
		i++;
		c = prog[i];
		if (c == '=') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",47>" << endl;
			else
				cout << number << ": <" << word << ",47>";
			number++;
		}
		else {
			if (!end)
				cout << number << ": <" << word << ",46>" << endl;
			else
				cout << number << ": <" << word << ",46>";
			i--;
			number++;
		}
		}

		else if (c == ',') {
		word += c;
		if (!end)
			cout << number << ": <" << word << ",48>" << endl;
		else
			cout << number << ": <" << word << ",48>";
		number++;
		}

		else if (c == '.') {
		word += c;
		if (!end)
			cout << number << ": <" << word << ",49>" << endl;
		else
			cout << number << ": <" << word << ",49>";
		number++;
		}

		else if (c == ':') {
		word += c;
		if (!end)
			cout << number << ": <" << word << ",52>" << endl;
		else
			cout << number << ": <" << word << ",52>";
		number++;
		}

		else if (c == ';') {
		word += c;
		if (!end)
			cout << number << ": <" << word << ",53>" << endl;
		else
			cout << number << ": <" << word << ",53>";
		number++;
		}

		else if (c == '?') {
		word += c;
		if (!end)
			cout << number << ": <" << word << ",54>" << endl;
		else
			cout << number << ": <" << word << ",54>";
		number++;
		}

		else if (c == '[') {
		word += c;
		if (!end)
			cout << number << ": <" << word << ",55>" << endl;
		else
			cout << number << ": <" << word << ",55>";
		number++;
		}

		else if (c == ']') {
		word += c;
		if (!end)
			cout << number << ": <" << word << ",56>" << endl;
		else
			cout << number << ": <" << word << ",56>";
		number++;
		}

		else if (c == '^') {
		word += c;
		i++;
		c = prog[i];
		if (c == '=') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",58>" << endl;
			else
				cout << number << ": <" << word << ",58>";
			number++;
		}
		else {
			if (!end)
				cout << number << ": <" << word << ",57>" << endl;
			else
				cout << number << ": <" << word << ",57>";
			i--;
			number++;
		}
		}

		else if (c == '{') {
		word += c;
		if (!end)
			cout << number << ": <" << word << ",59>" << endl;
		else
			cout << number << ": <" << word << ",59>";
		number++;
		}

		else if (c == '|') {
		word += c;
		i++;
		c = prog[i];
		if (c == '|') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",61>" << endl;
			else
				cout << number << ": <" << word << ",61>";
			number++;
		}
		else if (c == '=') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",62>" << endl;
			else
				cout << number << ": <" << word << ",62>";
			number++;
		}
		else {
			if (!end)
				cout << number << ": <" << word << ",60>" << endl;
			else
				cout << number << ": <" << word << ",60>";
			i--;
			number++;
		}
		}

		else if (c == '}') {
		word += c;
		if (!end)
			cout << number << ": <" << word << ",63>" << endl;
		else
			cout << number << ": <" << word << ",63>";
		number++;
		}

		else if (c == '~') {
		word += c;
		if (!end)
			cout << number << ": <" << word << ",64>" << endl;
		else
			cout << number << ": <" << word << ",64>";
		number++;
		}

		else if (c == '+') {
		word += c;
		i++;
		c = prog[i];
		if (c == '+') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",66>" << endl;
			else
				cout << number << ": <" << word << ",66>";
			number++;
		}
		else if (c == '=') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",67>" << endl;
			else
				cout << number << ": <" << word << ",67>";
			number++;
		}
		else {
			if (!end)
				cout << number << ": <" << word << ",65>" << endl;
			else
				cout << number << ": <" << word << ",65>";
			i--;
			number++;
		}
		}

		else if (c == '<') {
		word += c;
		i++;
		c = prog[i];
		if (c == '<') {
			word += c;
			i++;
			c = prog[i];
			if (c == '=') {
				word += c;
				if (!end)
					cout << number << ": <" << word << ",70>" << endl;
				else
					cout << number << ": <" << word << ",70>";
				number++;
			}
			else {
				if (!end)
					cout << number << ": <" << word << ",69>" << endl;
				else
					cout << number << ": <" << word << ",69>";
				i--;
				number++;
			}
		}
		else if (c == '=') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",71>" << endl;
			else
				cout << number << ": <" << word << ",71>";
			number++;
		}
		else {
			if (!end)
				cout << number << ": <" << word << ",68>" << endl;
			else
				cout << number << ": <" << word << ",68>";
			i--;
			number++;
		}
		}

		else if (c == '=') {
		word += c;
		i++;
		c = prog[i];
		if (c == '=') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",73>" << endl;
			else
				cout << number << ": <" << word << ",73>";
			number++;
		}
		else {
			if (!end)
				cout << number << ": <" << word << ",72>" << endl;
			else
				cout << number << ": <" << word << ",72>";
			i--;
			number++;
		}
		}

		else if (c == '>') {
		word += c;
		i++;
		c = prog[i];
		if (c == '>') {
			word += c;
			i++;
			c = prog[i];
			if (c == '=') {
				word += c;
				if (!end)
					cout << number << ": <" << word << ",77>" << endl;
				else
					cout << number << ": <" << word << ",77>";
				number++;
			}
			else {
				if (!end)
					cout << number << ": <" << word << ",76>" << endl;
				else
					cout << number << ": <" << word << ",76>";
				i--;
				number++;
			}
		}
		else if (c == '=') {
			word += c;
			if (!end)
				cout << number << ": <" << word << ",75>" << endl;
			else
				cout << number << ": <" << word << ",75>";
			number++;
		}
		else {
			if (!end)
				cout << number << ": <" << word << ",74>" << endl;
			else
				cout << number << ": <" << word << ",74>";
			i--;
			number++;
		}
		}

		else if (c == '"') {
		word += c;
		if (!end)
			cout << number << ": <" << word << ",78>" << endl;
		else
			cout << number << ": <" << word << ",78>";
		number++;
		}

		else {

		}
	}
}