#include "Neuron.h"



Neuron::Neuron(int outputs, int index)
{
	for (size_t conection = 0; conection < outputs; conection++)
	{
		outPutWeights.push_back(Links());
		outPutWeights.back().weight = Neuron::randomNumber();
	}
	id = index;
}


Neuron::~Neuron()
{
}

void Neuron::feedFoward(const Layer& prev)
{
	double sum = 0.0;

	for (size_t neuron = 0; neuron < prev.size(); neuron++)
	{
		sum += prev[neuron].outPutValue*prev[neuron].outPutWeights[id].weight;
	}
	outPutValue=TransferFunction(sum);
}

double Neuron::randomNumber()
{
	double result = 0.0;

	result = rand() % 199 + 1;

	result = result / 1000;
	//result = rand() / double(RAND_MAX);

	return result;
}

double Neuron::sumDerivate(const Layer & next)
{
	double sum = 0.0;
	for (size_t n = 0; n < next.size(); n++)
	{
		sum += outPutWeights[n].weight * next[n].gradient;
	}
	return sum;
}

void Neuron::OutputGradients(double value)
{
	double diference = value - outPutValue;
	gradient = diference * DerivateFunction(outPutValue);
}

void Neuron::HiddenGradients(const Layer & hidden)
{
	double dow = sumDerivate(hidden);
	gradient = dow * DerivateFunction(outPutValue);

}

void Neuron::UpdateWeights(Layer & prev)
{
	for (size_t n = 0; n < prev.size(); n++)
	{
		Neuron& neuron = prev[n];
		double oldDeltaWeight = neuron.outPutWeights[id].deltaWeight;

		double newDeltaWeight = (eta*neuron.outPutValue*gradient) + (alpha*oldDeltaWeight);
		neuron.outPutWeights[id].deltaWeight = newDeltaWeight;
		neuron.outPutWeights[id].weight += newDeltaWeight;

	}
}

double Neuron::TransferFunction(double sum)
{
	double result = 0.0;
	result =  1 + exp(-1*sum);
	result = 1 / result;
	return result;
}

double Neuron::DerivateFunction(double val)
{
	double result = 0.0;
	result = 1 + exp(-1 * val);
	result = result * result;
	result = (exp(-1 * val)) / result;
	return result;

}
