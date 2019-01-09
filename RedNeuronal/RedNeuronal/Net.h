#pragma once
#include "Neuron.h"
#include <iostream>
class Net
{
public:
	Net(const std::vector<int>& topology);
	void feedFoward(const std::vector<double> &inputVals);
	void backProp();
	~Net();
	void Display();
	
private:
	std::vector<Layer> layers;
	double error;
};

