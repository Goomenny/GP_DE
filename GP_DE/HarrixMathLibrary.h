#pragma once
#include <math.h>
const double HML_PI = 3.14159265358979323846;
const double HML_PI_2 = 1.57079632679489661923;
const double HML_PI_4 = 0.785398163397448309616;
//Тестовые функции для оптимизации
double HML_TestFunction_Ackley(double *x, double *bias, int VHML_N, long *nfeval);				//x=0 f(x)=0
double HML_TestFunction_Griewangk(double *x, double *bias, int VHML_N, long *nfeval);			//x=0 f(x)=0
double HML_TestFunction_HyperEllipsoid(double *x, double *bias, int VHML_N, long *nfeval);		//x=0 f(x)=0
double HML_TestFunction_ParaboloidOfRevolution(double *x, double *bias,int VHML_N, long *nfeval);//x=0 f(x)=0
double HML_TestFunction_Rastrigin(double *x, double *bias, int VHML_N, long *nfeval);			//x=0 f(x)=0
double HML_TestFunction_RastriginNovgorod(double *x, double *bias, int VHML_N, long *nfeval);	//x=0 f(x)=0
double HML_TestFunction_Rosenbrock(double *x, double *bias, int VHML_N, long *nfeval);			//x=1 f(x)=0  преведена к x=0
double HML_TestFunction_RotatedHyperEllipsoid(double *x, double *bias, int VHML_N, long *nfeval);//x=0 f(x)=0
double HML_TestFunction_Schwefel(double *x, double *bias, int VHML_N, long *nfeval);			//x=420.968746 f(x)=зависит от VHML_N
double HML_TestFunction_StepFunction(double *x, double *bias, int VHML_N, long *nfeval);		//x=0 f(x)=-1 преведена к f(x)=0
double HML_TestFunction_SumVector(int *x, double *bias, int VHML_N, long *nfeval);				//x=0 f(x)=0


double HML_TestFunction_EggHolder(double x, double y);
double HML_TestFunction_Wave(double x);
double HML_TestFunction_AdditivePotential(double x, double y);
double HML_TestFunction_Bosom(double x, double y);
double HML_TestFunction_Himmelblau(double x, double y);
double HML_TestFunction_InvertedRosenbrock(double x, double y); 
double HML_TestFunction_Katnikov(double x, double y);
double HML_TestFunction_Multiextremal(double x);
double HML_TestFunction_Multiextremal2(double x);
double HML_TestFunction_Multiextremal3(double x, double y);
double HML_TestFunction_Multiextremal4(double x, double y);
double HML_TestFunction_MultiplicativePotential(double x, double y);
double HML_TestFunction_Rana(double x, double y);
double HML_TestFunction_RastriginWithChange(double x, double y);
double HML_TestFunction_RastriginWithTurning(double x, double y);
double HML_TestFunction_ReverseGriewank(double x, double y);
double HML_TestFunction_ShekelsFoxholes(double x, double y);
double HML_TestFunction_Sombrero(double x, double y);

template <class T> T HML_SumSquareVector(T *VHML_Vector, int VHML_N);


//---------------------------------------------------------------------------
template <class T> T HML_SumSquareVector(T *VHML_Vector, int VHML_N)
{
	/*
	Функция вычисляет сумму квадратов элементов вектора.
	Входные параметры:
	VHML_Vector - указатель на исходный массив;
	VHML_N - размер массива.
	Возвращаемое значение:
	Сумма элементов массива.
	*/
	T VHML_Result = 0;
	for (int i = 0; i<VHML_N; i++)
		VHML_Result += VHML_Vector[i] * VHML_Vector[i];

	return VHML_Result;
}
//---------------------------------------------------------------------------