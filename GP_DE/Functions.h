#pragma once
#include "HarrixMathLibrary.h"
#include "DIFFEVO.h"
#include <random>  
template <class Tree>
class TTest
{
public:
	
	void Calculate(Tree &tree, int runs, int strategy) {

		bool found = false;
		double *x;
		double tmpx;
		double tmpmeanx = 0;
		meanx = 0;
		reliability = 0;
		meanresult = 0;

		testmeanx = 0;
		testreliability = 0;
		testmeanresult = 0;

		for (int i = 0; i < runs; i++)
		{
			std::mt19937 gen(i);
			std::uniform_real_distribution<> urd(-5, 5);

			for (int d = 0; d < D; d++)
			{
				bias[d] = urd(gen);
			}

			optimizer.Init(HML_TestFunction_StepFunction, strategy, bias);
			result = optimizer.Start_fast(HML_TestFunction_StepFunction, bias, tree);

			meanresult += fabs(result);

			x = optimizer.Get_bestx();

			tmpmeanx = 0;
			found = true;
			for (int d = 0; d < D; d++)
			{
				tmpx = (x[d] + bias[d])*(x[d] + bias[d]);
				if (tmpx > eps) found = false;
				tmpmeanx += tmpx;
			}

			meanx += pow(tmpmeanx, 0.5);

			if (found) reliability++;
		}
		reliability /= double(runs);
		meanresult /= double(runs);
		meanx /= double(runs);

		/*
		for (int i = runs; i < 2 * runs; i++)
		{
			std::mt19937 gen(i);
			std::uniform_real_distribution<> urd(-5, 5);

			for (int d = 0; d < D; d++)
			{
				bias[d] = urd(gen);
			}

			optimizer.Init(HML_TestFunction_Griewangk, strategy, bias);
			result = optimizer.Start_fast(HML_TestFunction_Griewangk, bias, tree);

			testmeanresult += fabs(result);

			x = optimizer.Get_bestx();

			tmpmeanx = 0;
			found = true;
			for (int d = 0; d < D; d++)
			{
				tmpx = (x[d] + bias[d])*(x[d] + bias[d]);
				if (tmpx > eps) found = false;
				tmpmeanx += tmpx;
			}

			testmeanx += pow(tmpmeanx, 0.5);

			if (found) testreliability++;
		}*/
		testreliability /= double(runs);
		testmeanresult /= double(runs);
		testmeanx /= double(runs);

	}

	double Get_reliability() { return reliability; };
	double Get_meanresult() { return meanresult; };
	double Get_meanx() { return meanx; };

	double Get_testreliability() { return testreliability; };
	double Get_testmeanresult() { return testmeanresult; };
	double Get_testmeanx() { return testmeanx; };

private:
	TDE<Tree> optimizer;
	int runs = 10;
	double eps = 0.05;

	double reliability = 0;
	double meanresult = 0;
	double meanx = 0;

	double testreliability = 0;
	double testmeanresult = 0;
	double testmeanx = 0;

	double result;
	int D = 5; //Размерность оптимизации
	double bias[5]; //Вектор смещений оптимума

};
