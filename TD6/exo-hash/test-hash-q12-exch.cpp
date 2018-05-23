#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include "packet.hpp"

using namespace std;

int main() {

	ofstream logfile;

	logfile.open("logfile.txt");
	
	Device * dev = new Device(2, 2);
	dev->Bootstrap();

	Packet * pkt1 = new Packet(3, 0, 3, 31);
	dev->processPacket(pkt1, 20);

	Packet * pkt2 = new Packet(1, 0, 1, 10);
	dev->processPacket(pkt2, 21);
	
	dev->dumpPktsToFile(logfile);

	logfile.close();
}
