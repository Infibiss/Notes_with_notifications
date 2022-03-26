#include <fstream>
#include <windows.h>
#include <vector>
#include <sstream>
#include <ctime>
#include <iostream>

using namespace std;

int h, m, day, month, year;

void split(vector <string> &result, string &s, char delim) 
{
    stringstream ss(s); string word;

    while(getline(ss, word, delim)) 
        result.push_back (word);
}

bool CheckTime()
{
	SYSTEMTIME r;
	GetLocalTime(&r);

	return (r.wHour >= h && r.wMinute >= m && r.wYear >= year && r.wMonth >= month && r.wDay >= day);
}

void GetDate(string &s)
{
	string date = "";
	for(int i = 0; i < s.size(); i++)
		if(s[i] >= '0' && s[i] <= '9' || s[i] == '.')
			date += s[i];
	day = (date[0] - '0') * 10 + (date[1] - '0'); 
	month = (date[3] - '0') * 10 + (date[4] - '0');
	year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');
}

void GetTime(string &s)
{
	string timer = "";
	for(int i = 0; i < s.size(); i++)
		if(s[i] >= '0' && s[i] <= '9' || s[i] == ':')
			timer += s[i];
	h = (timer[0] - '0') * 10 + (timer[1] - '0'), m = (timer[3] - '0') * 10 + (timer[4] - '0');
}

void GetNote(vector <string> result, string &note)
{
	for(int i = 0; i < result.size() - 2; i++)
		note += result[i];
}

void Mark(int pos)
{
	vector <string> text;

	ifstream inp("NOTES.txt");
	string s;
	for(int i = 1; getline(inp, s); i++){
		if(pos == i)
			s += " *";
		text.push_back(s);			
	}
	inp.close();

	ofstream out("NOTES.txt");
	for(int i = 0; i < text.size(); i++)
        out << text[i] << '\n';
	out.close();
}

int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	while(1){
		ifstream in("NOTES.txt");

		string s;
		for(int i = 1; getline(in, s); i++){
			if(s == "") break;
			if(s[s.size() - 1] == '*') continue;

			vector <string> result;
			split(result, s, '-');

			GetTime(result[result.size() - 1]);
			GetDate(result[result.size() - 2]);

			if(CheckTime()){
				string note = "";
				GetNote(result, note);

				MessageBox(NULL, &note[0], "NOTE", MB_SYSTEMMODAL | MB_ICONASTERISK | MB_ICONWARNING);
				Mark(i);
			}
		}
		in.close();
		Sleep(20000);	
	}
	
	return 0;
}