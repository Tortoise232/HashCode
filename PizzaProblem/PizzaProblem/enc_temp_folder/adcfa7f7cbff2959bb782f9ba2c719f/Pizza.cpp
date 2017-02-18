#include "stdafx.h"
#include "Pizza.h"
#include <fstream>
#include <iostream>
//M - 0; T - 1

Pizza::Pizza(char* name)
{   //initializes a pizza
	std::ifstream myFile;
	myFile.open(name, 'r');
	int rows, columns, min, max;
	myFile >> rows >> columns >> min >> max;
	this->surface = new int*[rows];
	for (int ct = 0; ct < rows; ct++) {
		this->surface[ct] = new int[columns];
	}
	char topping;
	for (int ct = 0; ct < rows; ct++) {
		for (int ct1 = 0; ct1 < columns; ct1++)
		{
			topping = '-';
			while (topping != 'T' && topping != 'M')
				myFile >> topping;
			myFile >> topping;
			if (topping == 'M') {
				this->surface[ct][ct1] = 0;
				std::cout << 0;
			}
			else {
				this->surface[ct][ct1] = 1;
				std::cout << 1;
			}
		}
		std::cout << "\n";
	}

}

Pizza::~Pizza()
{
}
