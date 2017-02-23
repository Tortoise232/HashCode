// TrueHashCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

int videoValues[1000000] = { 0 };
float cacheValues[1000000] = { 0 };


class Video {
public:
	int size;
	int id;
	Video(int size, int id) {
		this->size = size;
		this->id = id;
	}
};

class Request {
public:
	int videoID;
	int endpointID;
	int value; //cate requesturi sunt facute de la acel endpoint
	Request(int videoID, int endpointID, int value) {
		this->videoID = videoID;
		this->endpointID = endpointID;
		this->value = value;

	}
};

class  Endpoint {
public:
	int id;
	std::vector<Video> videos;
	int dataCenterLatency;
	// pair pentru ca fata de fiecare 
	//cache este un anumit latency   std::pair<cacheID,latency>
	std::vector<std::pair<int, int>> cacheLatencies; 
	
	Endpoint(int dataCenterLatency, std::vector<std::pair<int, int>> cacheLatencies, int id) {
		this->dataCenterLatency = dataCenterLatency;
		this->cacheLatencies = cacheLatencies;
		this->id = id;
	}
};

class Cache {
public:
	static int maxSize;
	int currentSize;
	std::vector<Video> actualVideos;

};

//videos are just ints;
//caches;



std::vector<Video> videos;
std::vector<Cache> caches;
std::vector<Request> requests;
std::vector <Endpoint> endpoints;



void readData(char* filename) {
	std::ifstream data(filename, std::ios::binary);
	int V, E, R, C, Csize;
	int videoSize;
	//reads nr of videos, nr of endpoints, nr of requests, nr of caches, max cache size in this order
	data >> V >> E >> R >> C >> Csize;
	


	//read videos
	for (int ct = 0; ct < V; ct++) {
		data >> videoSize;
		videos.push_back(*(new Video(videoSize, ct)));// reads videos;
	}

	//read endpoints
	int latencyToServer, nrOfConnections, cacheNr, cacheLatency;
	std::vector<std::pair<int, int>> tempPairs;
	
	
	
	for (int ct = 0; ct < E; ct++) {
		data >> latencyToServer >> nrOfConnections;
		tempPairs.clear();
		for (int ct2 = 0; ct2 < nrOfConnections; ct2++) {
			data >> cacheNr >> cacheLatency;
			tempPairs.push_back(*(new std::pair<int, int>(cacheNr, cacheLatency)));
			cacheValues[cacheNr] += 1 / cacheLatency;
		}
		endpoints.push_back(*(new Endpoint(latencyToServer, tempPairs, ct)));
	}

	//read requests
	int videoID, endpointID, value;
	for (int ct = 0; ct < R; ct++) {
		data >> videoID >> endpointID >> value;
		videoValues[videoID] += value;
		requests.push_back(*(new Request(videoID, endpointID, value)));

	}
	

}

int main()
{

	readData("me_at_the_zoo.in");
	std::cout << videos.size() << "\n";
	std::cout << endpoints.size() << "\n";
	std::cout << requests.size() << "\n";
	std::cout << caches.size() << "\n";
	for(int i = 0; i < 100000; i ++)

    return 0;
}

