#include <iostream>
#include <vector>
#include <conio.h>
#include <stdlib.h>
#include "Net.h"

double matrix[]
{0.001,0.7,0.7,0.7,0.001
,0.001,0.7,0.001,0.001,0.001
,0.001,0.7,0.7,0.7,0.001
,0.001,0.001,0.001,0.7,0.001
,0.001,0.7,0.7,0.7,0.001};
typedef std::vector<int> topology;
std::vector<double> Inputs()
{
	std::vector<double> result;
	for (size_t i = 0; i < 25; i++)
	{
		result.push_back(matrix[i]);
	}
	return result;
}

int main()
{
	topology t1;
	t1.push_back(25);
	t1.push_back(12);
	t1.push_back(1);

	Net n(t1);
	while (true) {
		system("cls");
		std::cout << "Hola red neuronal" << std::endl;
		n.feedFoward(Inputs());
		n.backProp();
		n.Display();
		_getch();
		
	}

	system("pause");
	return 0;
}