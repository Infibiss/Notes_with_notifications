#include <fstream>
#include <windows.h>
#include <vector>
#include <sstream>
#include <ctime>

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
	time_t now = time(0);
	char* realtime = ctime(&now);
	int rday = (realtime[8] - '0') * 10 + (realtime[9] - '0'); 
	int rmonth; string rm = {realtime[4], realtime[5], realtime[6]};
	if(rm == "Jar")      rmonth = 1;
	else if(rm == "Feb") rmonth = 2;
	else if(rm == "Mar") rmonth = 3;
	else if(rm == "Apr") rmonth = 4;
	else if(rm == "May") rmonth = 5;
	else if(rm == "Jun") rmonth = 6;
	else if(rm == "Jul") rmonth = 7;
	else if(rm == "Aug") rmonth = 8;
	else if(rm == "Sep") rmonth = 9;
	else if(rm == "Oct") rmonth = 10;
	else if(rm == "Nov") rmonth = 11;
	else if(rm == "Dec") rmonth = 12;
	int ryear = (realtime[20] - '0') * 1000 + (realtime[21] - '0') * 100 + (realtime[22] - '0') * 10 + (realtime[23] - '0');
	int realh = (realtime[11] - '0') * 10 + (realtime[12] - '0'), realm = (realtime[14] - '0') * 10 + (realtime[15] - '0');

	if(realh == h && realm == m && ryear == year && rmonth == month && rday == day)
		return true;
	else
		return false;
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

int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	while(1){
		ifstream in("NOTES.txt");

		string s;
		while(getline(in, s)){
			vector <string> result;
			split(result, s, '-');

			GetTime(result[result.size() - 1]);
			GetDate(result[result.size() - 2]);

			if(CheckTime()){
				string note = "";
				GetNote(result, note);

				MessageBox(NULL, &note[0], "NOTE", MB_OK);
			}
		}
		in.close();
		Sleep(30000);	
	}
	
	return 0;
}