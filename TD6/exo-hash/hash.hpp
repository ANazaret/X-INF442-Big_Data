#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//#define shrink 16
const string to16[] = {"0", "1", "2", "3", "4", "5", "6", "7",
                       "8", "9", "a", "b", "c", "d", "e", "f"};
//	const string line = "18,1,0,161,255,137,254,252,14,95,165,33,181,168,2,188";

class KnotHash {

public:
	vector<char> lgts;

	//KnotHash(vector<int> lengths);
	KnotHash(vector<char> line);
	//~KnotHash();
	
	vector<int> singleRound(int module, int& skip, int& position, int& addpos);
	vector<int> getHash(int module, int shrink);

private:
	int shrink;
	vector<int> list;
	vector<int> newlist;
	vector<int> temp;

	void initializeLists(int module);
};