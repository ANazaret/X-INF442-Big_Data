#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Packet {
  int cid;
  int cost;
  int dev;
  int port;
  
public:

  int getCid();
  int getCost();
  int getDev();
  int getPort();
  
  Packet(int cid, int cost, int dev, int port);
  //~Packet();
  
  bool operator <(const Packet& p);
  bool operator >(const Packet& p);
  bool operator ==(const Packet& p);

  int compare(const Packet* p);
  string toString();
  
  map<int, Packet*> * forward(vector<int> ports);
};

class Device {
	int id;
	vector<int> ports;
	Packet* packet;
	vector<string> seenpkts;

public:	
	Device(int id, int nports);
	~Device();
	
	void Bootstrap();
	void processPacket(Packet* p, int port);
	int electedController();
	
	void dumpPktsToFile(ofstream& file);
};