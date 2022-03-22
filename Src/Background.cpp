#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <sstream>
#include <ctime>

using namespace std;

void split(vector <string> &result, string &s, char delim) 
{
    stringstream ss(s); string word;

    while(getline(ss, word, delim)) 
        result.push_back (word);
}

void GetTime(string &timer, string &s)
{
	for(int i = 0; i < s.size(); i++)
		if(s[i] >= '0' && s[i] <= '9' || s[i] == ':')
			timer += s[i];
}

void GetNote(vector <string> result, string &note)
{
	for(int i = 0; i < result.size() - 1; i++)
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

			string timer = "";
			GetTime(timer, result[result.size() - 1]);

			time_t now = time(0);
			char* realtime = ctime(&now);

			if(realtime[11] == timer[0] && realtime[12] == timer[1] && realtime[14] == timer[3] && realtime[15] == timer[4]){
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