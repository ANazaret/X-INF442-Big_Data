#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "hash.hpp"

using namespace std;

KnotHash::KnotHash(vector<char> line) {			// Constructor
	for (int i=0; i< line.size(); ++i) lgts.push_back(line[i]);
	lgts.push_back(17);
	lgts.push_back(31);
	lgts.push_back(73);
	lgts.push_back(47);
	lgts.push_back(23);
	}

void KnotHash::initializeLists(int module) {
	for (int i=0; i<module; i++) {
		list.push_back(i);
		newlist.push_back(0);
		temp.push_back(0);
	}
}

vector<int> KnotHash::singleRound(int module, int& skip, int& position, int& addpos) {
	//TODO, Q3 :  implement this function (and return the corresponding vector)

	return list;
}

vector<int> KnotHash::getHash(int module, int shrink) {

	vector<int> ret;

	if (module%shrink) {
		cout << "Invalid hashing parameters" << endl;
		exit(-1);
	}

	int llgts = lgts.size();

	int skip = 0;
	int position = 0;
	int addpos = 0;

	initializeLists(module);

	for (int round = 0; round < 64; ++round)
		list = singleRound(module, skip, position, addpos);

	int revpos = -addpos;
	while (revpos < 0) revpos += module;
	for (int i = revpos; i < module; ++i) newlist[i-revpos] = list[i];
	for (int i = 0; i < revpos; ++i)      newlist[i+module-revpos] = list[i];

	int dense[shrink];
	for (int i = 0; i < shrink; ++i) {
	  dense[i] = newlist[i*shrink];
	  for (int j = i*shrink+1; j < (i+1)*shrink; ++j) dense[i] ^= newlist[j];
	}

	for (int i = 0; i < shrink; ++i) {
	  int p = dense[i] / shrink;
	  int q = dense[i] % shrink;

	  ret.push_back(p);
	  ret.push_back(q);
	}
	return ret;
}
