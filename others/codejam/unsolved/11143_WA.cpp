#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define int64 long long
#define maxi(a,b) ((a)>(b)?(a):(b))
#define mini(a,b) ((a)<(b)?(a):(b))
using namespace std;

int Decode(string);
string Encode(int);

struct Block{
	int a, b;
	string str;
	Block(){}
	Block(int _a, int _b, string _msg = ""):a(_a), b(_b), str(_msg){}
	bool operator<(const Block& p) const
	{
		if(a != p.a)
			return a < p.a;
		return b < p.b;
	}
	void increase(int offset)
	{
		a += offset;
		b += offset;
	}
	void Print(int offset, bool print_newline)
	{
		cout << Encode(a-offset) << " --> " << Encode(b-offset) << endl;

//		if (!print_newline)
//			str.erase(std::remove(str.end()-1, str.end(), '\n'), str.end());

		cout << str;
		if (print_newline)
			cout << endl;
	}
};
string atoi(int a, int d)
{
	string result;
	while(a)
	{
		string t("0");
		t[0] += a % 10;
		a /= 10;
		result.insert(0, t);
	}
	while((int)result.length() < d)
		result.insert(0, "0");
	return result;
}

int Decode(string s)
{
	for(int i = 0; i < (int)s.length(); i++)
		if(!isdigit(s[i]))
			s[i] = ' ';
	int arr[4];
	istringstream hin(s);
	hin >> arr[0] >> arr[1] >> arr[2] >> arr[3];
	int result = 0;
	for(int i = 0; i < 4; i++)
		result = result * (i == 3 ? 1000 : 60) + arr[i];
	return result;
}

string Encode(int idx)
{
	string result;
	int arr[4];
	for(int i = 0; i < 4; i++)
	{
		if(idx == 3)
			arr[i] = idx;
		else
			arr[i] = idx % (i == 0 ? 1000 : 60);
		idx /= (i == 0 ? 1000 : 60);
	}
	result = atoi(arr[3],2) + string(":") + atoi(arr[2],2) + string(":") + atoi(arr[1],2) + string(",") + atoi(arr[0],3);
	return result;
}

int BabiCDNumber;
int BabiCDs[6];
int BabiCuts[100][2];
int BabiCutNumber;
int SubTitleCDNumber;
int SubTitleCDs[6];
int BlockIndex;
string s;
int main()
{
	while(cin >> BabiCDNumber)
	{
		for(int i = 0; i < BabiCDNumber+1; i++)
		{
			cin >> s;
			BabiCDs[i] = Decode(s);
		}
		cin >> BabiCutNumber;
		for(int i = 0; i < BabiCutNumber; i++)
			for(int j = 0; j < 2; j++)
			{
				cin >> s;
				BabiCuts[i][j] = Decode(s);
			}
		// Sorting cuts
		for(int i = 0; i < BabiCutNumber; i++)
			for(int j = i+1; j < BabiCutNumber; j++)
				if(BabiCuts[i][0] < BabiCuts[j][0])
				{
					swap(BabiCuts[i][0], BabiCuts[j][0]);
					swap(BabiCuts[i][1], BabiCuts[j][1]);
				}
		cin >> SubTitleCDNumber;
		for(int i = 0; i < SubTitleCDNumber+1; i++)
		{
			cin >> s;
			SubTitleCDs[i] = Decode(s);
		}
		for(int i = 0; i < BabiCutNumber; i++)
			for(int j = 0; j < 2; j++)
				BabiCuts[i][j] -= SubTitleCDs[SubTitleCDNumber];
		int StartTime = -SubTitleCDs[SubTitleCDNumber];
		Block Blocks[1000];
		int idx = 0;
		for(int i = 0; i < SubTitleCDNumber; i++)
		{
			while(cin >> BlockIndex, BlockIndex != 0)
			{
				string s1, s2, msg;
				cin >> s1 >> s >> s2;
				Block b(Decode(s1) + StartTime, Decode(s2) + StartTime);
				getline(cin, s);
				while(getline(cin, s), s != "")
					msg += s + string("\n");
				b.str = msg;
				Blocks[idx++] = b;
			}
			StartTime += SubTitleCDs[i];
		}

		// Do the cuts
		for(int i = 0; i < BabiCutNumber; i++)
		{
			for(int j = 0; j < idx; j++)
			{
				if(Blocks[j].a < BabiCuts[i][0] && Blocks[j].b < BabiCuts[i][0])
					/*Do nothing*/;
				else if(Blocks[j].a < BabiCuts[i][0] && Blocks[j].b >= BabiCuts[i][0] && Blocks[j].b <= BabiCuts[i][1])
				{
					Blocks[j].b = BabiCuts[i][0]-1;
				}
				else if(Blocks[j].a < BabiCuts[i][0] && Blocks[j].b > BabiCuts[i][1])
				{
					Blocks[j].b -= BabiCuts[i][1] - BabiCuts[i][0] + 1;
				}
				else if(Blocks[j].a >= BabiCuts[i][0] && Blocks[j].b <= BabiCuts[i][1])
				{
					Blocks[j] = Blocks[idx-1];
					idx--;
					j--;
				}
				else if(Blocks[j].a <= BabiCuts[i][1] && Blocks[j].b > BabiCuts[i][1])
				{
					Blocks[j].a = BabiCuts[i][0];
					Blocks[j].b = BabiCuts[i][0] + (Blocks[j].b - BabiCuts[i][1] - 1);
				}
				else if(Blocks[j].a > BabiCuts[i][1])
				{
					Blocks[j].a -= (BabiCuts[i][1] - BabiCuts[i][0] + 1);
					Blocks[j].b -= (BabiCuts[i][1] - BabiCuts[i][0] + 1);
				}
			}
		}

		// Shift times
		for(int i = 0; i < idx; i++)
			Blocks[i].increase(BabiCDs[BabiCDNumber]);
		// Do other cuts
		sort(Blocks, Blocks+idx);
		int start_time = 0;
		for(int i = 0; i < SubTitleCDNumber; i++)
		{
			for(int j = 0; j < idx; j++)
				if (Blocks[j].a >= start_time && Blocks[j].a < start_time + SubTitleCDs[i] && Blocks[j].b >= start_time + SubTitleCDs[i])
				{
					Blocks[idx].a = start_time + SubTitleCDs[i];
					Blocks[idx].b = Blocks[j].b;
					Blocks[idx].str = Blocks[j].str;
					idx++;
					Blocks[j].b = start_time + SubTitleCDs[i] - 1;
				}
			start_time += SubTitleCDs[i];
		}
		// Print Output
		sort(Blocks, Blocks+idx);
		start_time = 0;
		int counter = 1, prevI = -1;
		bool print_newline = true;
		for(int i = 0; i < BabiCDNumber; i++)
		{
			for(int j = 0; j < idx; j++)
			{
				if (Blocks[j].a >= start_time
				&& Blocks[j].a < start_time + BabiCDs[i])
				{
					if (prevI == -1)
					{
						prevI = i;
					}
					else if (i != prevI)
					{
						counter = 1;
						prevI = i;
						cout << endl;
					}
					cout << counter << endl;
					if (i == BabiCDNumber-1 && j == idx-1)
						print_newline = false;
					Blocks[j].Print(start_time, print_newline);
				}
				counter++;
			}
			start_time += BabiCDs[i];
		}
	}

	return 0;
}
