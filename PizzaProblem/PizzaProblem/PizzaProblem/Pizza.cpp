#include "stdafx.h"
#include "Pizza.h"
#include <fstream>
#include <iostream>
//M - 0; T - 1

Pizza::Pizza(char* name)
{   //initializes a pizza
	std::ifstream myFile;
	myFile.open(name, std::ios::binary);
	int rows, columns, min, max;
	myFile >> rows >> columns >> min >> max;
	std::cout << "MINIMUM DE INGREDIENTE: " << min << "\n";
	std::cout << "SLICE MAXIM: " << max << "\n";
	this->surface = new int*[rows];
	for (int ct = 0; ct < rows; ct++) {
		this->surface[ct] = new int[columns];
	}
	char topping;
	for (int ct = 0; ct < rows; ct++) {
		for (int ct1 = 0; ct1 < columns; ct1++)
		{
			
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
