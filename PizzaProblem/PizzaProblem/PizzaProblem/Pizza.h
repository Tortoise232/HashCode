#pragma once
#include <string>
class Pizza
{
private:
	static int min;
public:
	int** surface;
	void setMin(int min) {
		this->min;
	}

	int getMin() {
		return this->min;
	}

	Pizza(char* filename);
	~Pizza();
	//void readPizza(char* name);
};

