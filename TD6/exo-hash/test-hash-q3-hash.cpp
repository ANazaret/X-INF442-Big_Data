#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "hash.hpp"

using namespace std;

int main(int argc, char* argv[]) {

	string filename = "logfile.txt";
	string line;
	ifstream is;
		
	if (argc < 2) {
		cout << "No filename provided, using default filename " << filename << endl;
    }
    else {
    	filename = argv[1];
    }
    
    cout << "Filename : " << filename << endl;
	//is.open("example.txt");   // open file
	is.open(filename);   // open file
	
	if (not is) {
		cout << "Error ! File not found. " << endl;
		exit(-1);
	}
	
	while (getline(is, line)) {
		 vector<char> lgts(line.begin(), line.end());
		 KnotHash knot = KnotHash(lgts);
 
		 vector<int> hash = knot.getHash(256, 16);
		 //vector <int> outp = knot.getHash(256);
 
		 cout << line << " : ";
		 for (int i=0; i<hash.size(); i++) {
			 cout << to16[hash[i]];
		 }
		 cout << endl;
	}
	is.close();
}