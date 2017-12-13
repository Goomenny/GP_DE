#pragma once
#include "HarrixMathLibrary.h"
#include "DIFFEVO.h"
#include <random>  
template <class Tree>
class TTest
{
public:
	
	void Calculate(Tree &tree);

	double Get_reliability() { return reliability; };
	double Get_meanresult() { return meanresult; };
	double Get_meanx() { return meanx; };

private:
	TDE<Tree> optimizer;
	int runs = 50;
	double eps = 0.01;

	double reliability = 0;
	double meanresult = 0;
	double meanx = 0;
	double result;
	int D = 3; //Размерность оптимизации
	double bias[3]; //Вектор смещений оптимума

};
template <class Tree>
void TTest<Tree>::Calculate( Tree &tree) {
	
	bool found = false;
	double *x;
	double tmpx;
	double tmpmeanx=0;
	meanx = 0;
	reliability = 0;
	meanresult = 0;

	
	for (int i = 0; i < runs; i++)
	{
		std::mt19937 gen(i);
		std::uniform_real_distribution<> urd(-5, 5);
		
		for (int d = 0; d < D; d++)
		{
			bias[d] = urd(gen);
		}

		optimizer.Init(HML_TestFunction_Ackley,bias);
		result = optimizer.Start_fast(HML_TestFunction_Ackley,bias,tree);

		meanresult += fabs(result);

		x = optimizer.Get_bestx();

		tmpmeanx = 0;
		found = true;
		for (int d = 0; d < D; d++)
		{
			tmpx = (x[d] + bias[d])*(x[d] + bias[d]);
			if (tmpx > eps) found= false;
			tmpmeanx +=tmpx;
		}

		meanx += pow(tmpmeanx, 0.5);

		if (found) reliability++;
	}
	reliability /= double(runs);
	meanresult /= double(runs);
	meanx /= double(runs);

}

	