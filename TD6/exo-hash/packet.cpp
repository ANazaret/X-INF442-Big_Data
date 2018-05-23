#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <string.h>
#include "packet.hpp"

using namespace std;

int Packet::getCid() { return cid; }
int Packet::getCost() { return cost; }
int Packet::getDev() { return dev; }
int Packet::getPort() { return port; }

string Packet::toString() {
	string ret;
	ret = to_string(cid) + "," + to_string(cost) + "," + to_string(dev) + "," + to_string(port);
	return ret;
}

map<int, Packet*> * Packet::forward(vector<int> ports) {
	// TODO, Q2 : implement this function (and return the corresponding map)

	return NULL;
}

Packet::Packet(int cid, int cost, int dev, int port) {
	this->cid = cid;
	this->cost = cost;
	this->dev = dev;
	this->port = port;
}

int Packet::compare(const Packet *p) {
	// TODO, Q1 : implement this function (and return the corresponding value)
	if (cid < p->getCid())
	  return -1;
	if (cid > p->getCid())
	  return 1;
	
	if (cost < p->getCost())
	  return -1;
	if (cost > p->getCost())
	  return 1;
	
	if (dev < p->getDev())
	  return -1;
	if (dev > p->getDev())
	  return 1;
	
	if (port < p->getPort())
	  return -1;
	if (port > p->getPort())
	  return 1;
	
	
	
	return 0;
}

// TODO, Q1 : implement overloading of operators <, >, ==, and return the correct booleans
bool Packet::operator <(const Packet& p) {
	// TODO : implement comparison and return
	if (compare(&p) == -1) { return true; }
	return false;
}
bool Packet::operator >(const Packet& p) {
	// TODO : implement comparison and return
  if (compare(&p) == 1) { return true; }
	return false;
}
bool Packet::operator ==(const Packet& p) {
	// TODO : implement comparison and return
  if (compare(&p) == 0) { return true; }
	return false;
}

Device::Device(int id, int nports) {
	this->id = id;
	for (int i=0; i<nports; i++) {
		this->ports.push_back(id*10+i);
	}
}

void Device::dumpPktsToFile(ofstream& file) {
	for (vector<string>::iterator it=seenpkts.begin(); it!=seenpkts.end(); it++) {
		file << *it << endl;
	}
}

void Device::Bootstrap() {
	cout << "[" << setw(2) << id << "] Bootstrap" << endl;

	packet = new Packet(id, 0, id, 0);

	cout << "[" << setw(2) << id << "] Elected controller : " << electedController() << endl;

	map<int, Packet*> * txed = packet->forward(ports);

	if (not txed) {
		cout << "Error ! No ports available for forwarding." << endl;
		return;
	}
		
	for (map<int, Packet*>::iterator it=txed->begin(); it!=txed->end(); it++) {
		cout << "[" << setw(2) << id << "] Transmitted packet "<< it->second->toString() <<" over port " << it->first << endl;
		seenpkts.push_back(it->second->toString());
	}
}

int Device::electedController() {
	if (packet) return packet->getCid();
	return 0;
}

void Device::processPacket(Packet* p, int port) {
	if (find(ports.begin(), ports.end(), port) == ports.end()) {
		cout << "Error : port does not exist." << endl;
		return;
	}

	cout << "[" << setw(2) << id << "] Received packet "<< p->toString() <<" over port " << port;
	seenpkts.push_back(p->toString());
	
	if (*p < *(this->packet)) {	// received packet is better
		delete packet;
		// update own packet
		Packet * newpacket = new Packet(p->getCid(), p->getCost() + 1, p->getDev(), p->getPort());
		packet = newpacket;
		cout << " ...update" << endl;
		cout << "[" << setw(2) << id << "] Elected controller : " << electedController() << endl;
		// forward on all interfaces except on the one that received it
		vector<int> tofwd;
		for (vector<int>::iterator it=ports.begin(); it!=ports.end(); it++) {
			if (*it == port) continue;
			tofwd.push_back(*it);
		}
		map<int, Packet*> * sent = packet->forward(tofwd);
		if (not sent) {
			cout << "Error ! No ports available for forwarding." << endl;
			return;
		}
		for (map<int, Packet*>::iterator it=sent->begin(); it!=sent->end(); it++) {
			cout << "[" << setw(2) << id << "] Transmitted packet "<< it->second->toString() <<" over port " << it->first << endl;
			seenpkts.push_back(it->second->toString());
		}		
		 
	}
	// otherwise ignore 
	else {
			cout << " ...ignore" << endl;
	}
}
