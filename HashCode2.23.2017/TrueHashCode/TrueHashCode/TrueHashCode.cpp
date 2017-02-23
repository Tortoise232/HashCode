// TrueHashCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>

class Video {
public:
	int size;
	int id;
};

class Requests {
public:
	int videoID;
	int endpointID;
	int value; //cate requesturi sunt facute de la acel endpoint
};

class  Endpoint {
public:
	int id;
	std::vector<Video> videos;
	int dataCenterLatency;
	// pair pentru ca fata de fiecare 
	//cache este un anumit latency   std::pair<cache,latency>
	std::vector<std::pair<int, Cache&>> cacheLatencies; 
	Endpoint(std::vector<int> videoRequests, int dataCenterLatency) {

	}
};

//videos are just ints;
//caches;

class Cache {
public:
	static int maxSize;
};

int main()
{

	//Mihai e paros!
    return 0;
}

