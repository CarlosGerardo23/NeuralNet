#include "Net.h"



Net::Net(const std::vector<int>& topology)
{
	srand(time(NULL));
	for (size_t layerNum = 0; layerNum < topology.size(); layerNum++)
	{
		layers.push_back(Layer());
		int numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

		for (size_t neuronNum = 0; neuronNum < topology[layerNum]; neuronNum++)
		{
			layers.back().push_back(Neuron(numOutputs,neuronNum));
		}
	}
}

void Net::feedFoward(const std::vector<double>& inputVals)
{
	for (size_t i = 0; i < inputVals.size(); i++)
	{
		layers[0][i].outPutValue = inputVals[i];
	}

	for (size_t layerNum = 1; layerNum < layers.size(); layerNum++)
	{
		Layer &prevLayer = layers[layerNum - 1];
		for (size_t neuron = 0; neuron < layers[layerNum].size(); neuron++)
		{
			layers[layerNum][neuron].feedFoward(prevLayer);
		}
	}
}

void Net::backProp()
{
	error = 0.0;
	double calculation= 1 - layers.back()[0].outPutValue;
	error += calculation * calculation;
	int debug = layers.back().size() - 1;
	//error /= layers.back().size() - 1;
	error = sqrt(error);

	layers.back()[0].OutputGradients(1);

	for (size_t layerNUm = layers.size()-2; layerNUm > 0; layerNUm--)
	{
		Layer& hiddenLayer = layers[layerNUm];
		Layer& nextLayer = layers[layerNUm + 1];
		for (size_t n = 0; n < hiddenLayer.size(); n++)
		{
			hiddenLayer[n].HiddenGradients(nextLayer);
		}
	}

	for (size_t layerNum = layers.size()-1; layerNum > 0; layerNum--)
	{
		Layer& current = layers[layerNum];
		Layer& previous = layers[layerNum - 1];

		for (size_t neuron = 0; neuron < current.size(); neuron++)
		{
			current[neuron].UpdateWeights(previous);
		}
	}

}


Net::~Net()
{
}

void Net::Display()
{
	std::cout << "Los outputs de la primera capa son: " << std::endl;
	for (size_t i = 0; i < layers[0].size(); i++)
	{
		std::cout << "Neurona: " << layers[0][i].id << "  output: " << layers[0][i].outPutValue<<std::endl;
	}
	std::cout <<std::endl<< "Los outputs de la segunda capa son: " << std::endl;
	for (size_t i = 0; i < layers[1].size(); i++)
	{
		std::cout << "Neurona: " << layers[1][i].id << "  output: " << layers[1][i].outPutValue << std::endl;
	}
	std::cout << std::endl << "Los outputs de la tercera capa son: " << std::endl;
	for (size_t i = 0; i < layers[2].size(); i++)
	{
		std::cout << "Neurona: " << layers[2][i].id << "  output: " << layers[2][i].outPutValue << std::endl;
	}
	std::cout << "-------------------"<<std::endl;
}
