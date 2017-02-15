#pragma once
#include<tuple>
#include<vector>

class Drone
{
private:
	int x, y; //position in carthesian space
	int currentWeight;
	std::vector<int> carriedProducts;//x y z : x 0 products, y 1 products, z 2 products
public:
	Drone();
	int getX(); 
	int getY();
	void setX(int x);
	void setY(int y);

	~Drone();
};

