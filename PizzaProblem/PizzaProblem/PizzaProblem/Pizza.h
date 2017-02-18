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

	Pizza(std::string filename);
	~Pizza();
	void readPizza(std::string name);
};

