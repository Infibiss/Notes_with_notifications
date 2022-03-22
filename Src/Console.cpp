#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <sstream>
#include <ctime>

using namespace std;

HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
void yellow(){SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN);}
void white(){SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);}
void red(){SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED);}
void green(){SetConsoleTextAttribute(hOUTPUT, FOREGROUND_GREEN);}
void printy(string s){ yellow(); cout << s; white(); }
void printw(string s){ white(); cout << s;           }
void printg(string s){ green(); cout << s; white();  }
void printr(string s){ red(); cout << s; white();    }

void split(vector <string> &result, string &s, char delim) 
{
    stringstream ss(s);
    string word;

    while(getline(ss, word, delim)) 
        result.push_back (word);

    if(result.size() == 1)
    	throw 1;
}

void GetTime(string &timer, string &s)
{
	for(int i = 0; i < s.size(); i++)
		if(s[i] >= '0' && s[i] <= '9' || s[i] == ':')
			timer += s[i];

	if(timer.size() != 5 || timer[2] != ':')
		throw 1;

	int h = (timer[0] - '0') * 10 + (timer[1] - '0'), m = (timer[3] - '0') * 10 + (timer[4] - '0');

	if(h > 24 || m > 60)
		throw 2;

	/*time_t now = time(0);
	char* realtime = ctime(&now);
	int realh = (realtime[11] - '0') * 10 + (realtime[12] - '0'), realm = (realtime[14] - '0') * 10 + (realtime[15] - '0');
	if(h * 60 + m >= realh * 60 + realm)
		throw 3;*/
}

void GetNote(vector <string> &result, string &note)
{
	for(int i = 0; i < result.size() - 1; i++)
		note += result[i];
}

void del(int pos)
{
	vector <string> text;

	ifstream in("NOTES.txt");
	string s; bool flag = false;
	for(int i = 1; getline(in, s); i++){
		if(pos != i)
			text.push_back(s);
		else
			flag = true;
	}
	in.close();

	if(!flag)
		throw 4;

	ofstream out("NOTES.txt");
	for(int i = 0; i < text.size(); i++)
        out << text[i] << '\n';
	out.close();
}

int main()
{
	printr("Commands: \"list\" | \"add\" | \"del\" | \"clear\" | \"close\" (background process)\n\n");
	a:
	try{
		while(1){
			string s; getline(cin, s);

			if(s == "add"){
				printy("\nType <note> <hh:mm>\n");
				getline(cin, s);
				vector <string> result;
				split(result, s, ' ');

				string timer = "", note = "";
				GetTime(timer, result[result.size() - 1]);
				GetNote(result, note);

				string res = note + " - " + timer;
				ofstream out("NOTES.txt", ios::in);
				out.seekp(0, ios::end);
				out.write(res.c_str(), strlen(res.c_str()));
				out << '\n';
				out.close();

				printg("Success!\n\n");
			}
			else if(s == "del"){
				printy("\nType <position of the note>\n");
				int pos; cin >> pos;

				del(pos);

				printg("Success!\n\n");
			}
			else if(s == "list"){
				ifstream in("NOTES.txt");
				string s; bool flag = false;
				cout << '\n';
				for(int i = 1; getline(in, s); i++)
					{flag = true; yellow(); cout << i << ") " << s << '\n'; white();}
				if(!flag) printy("[Empty]\n");
				cout << '\n';
				in.close();
			}
			else if(s == "close"){
				system("taskkill /f /im Background.exe");
			}
			else if(s == "clear"){
				system("cls");
				printr("Commands: \"list\" | \"add\" | \"del\" | \"clear\" | \"close\" (background process)\n\n");
			}
			else if(s != "")
				throw 1;

		}

	}

	catch (int err){
		if(err == 1)
			printr("\n[Error] -> Wrong input\n\n");
		if(err == 2)
			printr("\n[Error] -> Wrong time\n\n");
		/*if(err == 3)
			printr("\n[Error] -> Choose time in future\n\n");*/
		if(err == 4)
			printr("\n[Error] -> Wrong position\n\n");
		goto a;
	}
	CloseHandle(hOUTPUT);
}