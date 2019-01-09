#pragma once
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
struct Links
{
	double weight;
	double deltaWeight;
};

class Neuron;
typedef std::vector<Neuron> Layer;

class Neuron
{
public:
	Neuron(int outputs, int index);
	~Neuron();
	void feedFoward(const Layer& prev);
	double outPutValue;
	std::vector<Links> outPutWeights;
	static double randomNumber();
	double sumDerivate(const Layer& next);
	void OutputGradients(double value);
	
	void HiddenGradients(const Layer& hidden);
	void UpdateWeights(Layer& prev);

	int id;
	double gradient;
	double eta=0.15;
	double alpha=0.5;
private:
	double TransferFunction(double sum);
	double DerivateFunction(double val);

};


