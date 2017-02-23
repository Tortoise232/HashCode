// TrueHashCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <queue>

int videoValues[1000000] = { 0 };
float cacheValues[1000000] = { 0 };
int V, E, R, C, Csize;


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
	int currentSize;
	int id;
	std::vector<Video> actualVideos;
	Cache(int id, int maxSize) {
		this->id = id;
		this->currentSize = maxSize;
	}

};

//videos are just ints;
//caches;



std::vector<Video> videos;
std::vector<Cache> caches;
std::vector<Request> requests;
std::vector <Endpoint> endpoints;



void readData(char* filename) {
	std::ifstream data(filename, std::ios::binary);
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
//auto cmpVideos = [](const int&a, const int& b) { return videoValues[a] > videoValues[b]; };
//auto cmpCache = [](const int&a, const int& b) { return cacheValues[a] > cacheValues[b]; };

bool cmpVideos(int i1, int i2) {
	if (videoValues[i1] > videoValues[i2])
		return 1;
	return 0;
}

bool cmpCache(int i1, int i2) {
	if (cacheValues[i1] > cacheValues[i2])
		return 1;
	return 0;
}

std::priority_queue<int, std::vector<int>, decltype(&cmpVideos) > prQueueVideos(cmpVideos);
std::priority_queue<int, std::vector<int>, decltype(&cmpCache) > prQueueCache(cmpCache);



void addToPrQueue() {
	
	for (int i = 0; i < V; i++) {
		prQueueVideos.push(i);
	}
	for (int i = 0; i < C; i++) {
		prQueueCache.push(i);
		caches.push_back(*(new Cache(i, Csize)));
	}
	
}

void fillCaches() {


	std::priority_queue<int, std::vector<int>, decltype(&cmpCache) > prQueueCacheR;
	std::vector<Video>::iterator it;
	while (prQueueVideos.size() != 0) {
		//ia primul video
		int videoID = prQueueVideos.top();
		for (auto vid : videos)
			if (videoID == vid.id) {
				//gaseste toate cachurile care au loc
				prQueueCacheR = prQueueCache;
				while (prQueueCacheR.size() > 0) {
					int cacheID = prQueueCacheR.top();
					for (Cache& cach : caches)
						if (cach.currentSize > vid.size && cach.id == cacheID) {
							cach.actualVideos.push_back(vid);
							cach.currentSize -= vid.size;
							//pune video
						}
					prQueueCacheR.pop();
				}
				prQueueVideos.pop();//gaseste urmatorul video 
			}

	}
}

void writeFile() {
	/*
	std::vector<Cache> newCaches;
	for (auto cash : caches) {
		if (cash.actualVideos.size() > 0)
			newCaches.push_back(cash);
	}
	std::ofstream dataOut("me_at_the_zoo.out", std::ios::out);
	dataOut << newCaches.size() << "\n";
	for (auto cash : newCaches) {
		dataOut << cash.id << " ";
		for (auto vid : cash.actualVideos)
			dataOut << vid.id << " ";
		dataOut << "\n";
	}
	dataOut.close();
	*/

	std::vector<Cache> newCaches;
	for (auto cash : caches) {
		if (cash.actualVideos.size() > 0)
			newCaches.push_back(cash);
	}
	std::ofstream dataOut("me.out", std::ios::out);
	dataOut << newCaches.size() << "\n";
	for (auto cash : newCaches) {
		dataOut << cash.id << " ";
		for (auto vid : cash.actualVideos)
			dataOut << vid.id << " ";
		dataOut << "\n";
	}
	dataOut.flush();
	dataOut.close();
}



int main()
{

	readData("trending_today.in");
	std::cout << videos.size() << "\n";
	std::cout << endpoints.size() << "\n";
	std::cout << requests.size() << "\n";
	std::cout << caches.size() << "\n";
	addToPrQueue();
	fillCaches();
	writeFile();
    return 0;
}

