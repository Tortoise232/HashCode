#include "stdafx.h"
#include "Pizza.h"
#include <fstream>
//M - 0; T - 1
Pizza::Pizza(std::string name)
{   //initializes my stuff
	std::ifstream myFile;
	myFile.open(name.c_str(), 'r');
	int rows, columns, min, max;
	myFile >> rows >> columns >> min >> max;
	this->surface = new int*[rows];
	for (int ct = 0; ct < rows; ct++) {
		this->surface[ct] = new int[columns];
	}

}

Pizza::~Pizza()
{
}
