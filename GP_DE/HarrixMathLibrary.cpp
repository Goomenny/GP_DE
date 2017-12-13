//HarrixMathLibrary
//Версия 4.1
//Сборник различных математических функций и шаблонов с открытым кодом на языке C++.
//https://github.com/Harrix/HarrixMathLibrary
//Библиотека распространяется по лицензии Apache License, Version 2.0.

#include "HarrixMathLibrary.h"

//СЛУЖЕБНЫЕ ДОПОЛНИТЕЛЬНЫЕ ПЕРМЕННЫЕ
double (*VHML_TempFunction)(double*,int);
int *VHML_TempInt1;
int *VHML_TempInt2;
int *VHML_TempInt3;
int *VHML_TempInt4;
double *VHML_TempDouble1;
double *VHML_TempDouble2;
double *VHML_TempDouble3;

//*****************************************************************
//Тестовые функции для оптимизации
//*****************************************************************
double HML_TestFunction_Ackley(double *gx, double *bias, int VHML_N, long *nfeval)
{

	double *x = new double[VHML_N];

	for (int i = 0; i < VHML_N; i++)
	{
		x[i] = gx[i] + bias[i];
	}
/*
Функция многих переменных: Ackley.
Тестовая функция вещественной оптимизации.
Входные параметры:
 x - указатель на исходный массив;
 VHML_N - размер массива x.
Возвращаемое значение:
 Значение тестовой функции в точке x.
*/
double VHML_Result;
double f1,f2=0;
f1=exp(-0.2*sqrt(HML_SumSquareVector(x,VHML_N)/double(VHML_N)));
for (int i=0;i<VHML_N;i++) f2=f2+cos(2.*HML_PI*x[i]);
f2=exp(f2/double(VHML_N));
VHML_Result=20.+exp(1.)-20.*f1-f2;
(*nfeval)++;
delete []x;
return VHML_Result;
}
//---------------------------------------------------------------------------
double HML_TestFunction_Griewangk(double *gx, double *bias, int VHML_N, long *nfeval)
{

	double *x = new double[VHML_N];

	for (int i = 0; i < VHML_N; i++)
	{
		x[i] = gx[i] + bias[i];
	}
/*
Функция многих переменных: функция Гриванка.
Тестовая функция вещественной оптимизации.
Входные параметры:
 x - указатель на исходный массив;
 VHML_N - размер массива x.
Возвращаемое значение:
 Значение тестовой функции в точке x.
*/
double VHML_Result=0;
double f=1;
int i;

for (i=0;i<VHML_N;i++) VHML_Result+=x[i]*x[i];
VHML_Result/=4000.;

for (i=0;i<VHML_N;i++) f=f*cos(x[i]/sqrt(i+1));

VHML_Result=VHML_Result-f+1.;

(*nfeval)++;
delete[]x;
return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_HyperEllipsoid(double *gx, double *bias, int VHML_N, long *nfeval)
{

	double *x = new double[VHML_N];

	for (int i = 0; i < VHML_N; i++)
	{
		x[i] = gx[i] + bias[i];
	}
/*
Функция многих переменных: Гипер-эллипсоид.
Тестовая функция вещественной оптимизации.
Входные параметры:
 x - указатель на исходный массив;
 VHML_N - размер массива x.
Возвращаемое значение:
 Значение тестовой функции в точке x.
*/
double VHML_Result=0;

for (int i=0;i<VHML_N;i++)
	VHML_Result += (i+1)*(i+1)*x[i]*x[i];
(*nfeval)++;
delete[]x;
return VHML_Result;
}
//---------------------------------------------------------------------------
double HML_TestFunction_ParaboloidOfRevolution(double *gx, double *bias, int VHML_N, long *nfeval)
{

	double *x = new double[VHML_N];

	for (int i = 0; i < VHML_N; i++)
	{
		x[i] = gx[i] + bias[i];
	}
/*
Функция многих переменных: Эллиптический параболоид.
Тестовая функция вещественной оптимизации.
Входные параметры:
 x - указатель на исходный массив;
 VHML_N - размер массива x.
Возвращаемое значение:
 Значение тестовой функции в точке x.
*/


double VHML_Result=0;
for (int i=0;i<VHML_N;i++) VHML_Result+=x[i]*x[i];

(*nfeval)++;
delete[]x;
return VHML_Result;
}
//---------------------------------------------------------------------------
double HML_TestFunction_Rastrigin(double *gx, double *bias, int VHML_N, long *nfeval)
{

	double *x = new double[VHML_N];

	for (int i = 0; i < VHML_N; i++)
	{
		x[i] = gx[i] + bias[i];
	}
/*
Функция многих переменных: функция Растригина.
Тестовая функция вещественной оптимизации.
Входные параметры:
 x - указатель на исходный массив;
 VHML_N - размер массива x.
Возвращаемое значение:
 Значение тестовой функции в точке x.
*/
double VHML_Result=0;
for (int i=0;i<VHML_N;i++) VHML_Result+=x[i]*x[i]-10.*cos(2.*HML_PI*x[i]);
VHML_Result+=10*VHML_N;
(*nfeval)++;
delete[]x;
return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_RastriginNovgorod(double *gx, double *bias, int VHML_N, long *nfeval)
{

	double *x = new double[VHML_N];

	for (int i = 0; i < VHML_N; i++)
	{
		x[i] = gx[i] + bias[i];
	}
/*
Функция многих переменных: функция Растригина новгородская.
Тестовая функция вещественной оптимизации.
Входные параметры:
 x - указатель на исходный массив;
 VHML_N - размер массива x.
Возвращаемое значение:
 Значение тестовой функции в точке x.
*/
double VHML_Result=0;

for (int i=0;i<VHML_N;i++) 
    VHML_Result+=x[i]*x[i]-cos(18.*x[i]*x[i]);

VHML_Result+=VHML_N;
(*nfeval)++;
delete[]x;
return VHML_Result;
}
//---------------------------------------------------------------------------
double HML_TestFunction_Rosenbrock(double *gx, double *bias, int VHML_N, long *nfeval)
{

	double *x = new double[VHML_N];

	for (int i = 0; i < VHML_N; i++)
	{
		x[i] = gx[i] + bias[i]+1; //+1 смещение относительно оригинальной
	}
/*
Функция многих переменных: функция Розенброка.
Тестовая функция вещественной оптимизации.
Входные параметры:
 x - указатель на исходный массив;
 VHML_N - размер массива x.
Возвращаемое значение:
 Значение тестовой функции в точке x.
*/
double VHML_Result=0;
for (int i=0;i<VHML_N-1;i++) VHML_Result+=100.*(x[i+1]-x[i]*x[i])*(x[i+1]-x[i]*x[i])+(1.-x[i])*(1.-x[i]);
(*nfeval)++;
delete[]x;
return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_RotatedHyperEllipsoid(double *gx, double *bias, int VHML_N, long *nfeval)
{

	double *x = new double[VHML_N];

	for (int i = 0; i < VHML_N; i++)
	{
		x[i] = gx[i] + bias[i];
	}
/*
Функция многих переменных: Развернутый гипер-эллипсоид.
Тестовая функция вещественной оптимизации.
Входные параметры:
 x - указатель на исходный массив;
 VHML_N - размер массива x.
Возвращаемое значение:
 Значение тестовой функции в точке x.
*/
double VHML_Result=0;
double f;

for (int i=0;i<VHML_N;i++)
 {
 f=0;
 for (int j=0;j<i+1;j++)
    f += x[j];
 VHML_Result += f*f;
 }
(*nfeval)++;
delete[]x;
return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_Schwefel(double *gx, double *bias, int VHML_N, long *nfeval)
{

	double *x = new double[VHML_N];

	for (int i = 0; i < VHML_N; i++)
	{
		x[i] = gx[i] + bias[i];
	}
/*
Функция многих переменных: функция Швефеля.
Тестовая функция вещественной оптимизации.
Входные параметры:
 x - указатель на исходный массив;
 VHML_N - размер массива x.
Возвращаемое значение:
 Значение тестовой функции в точке x.
*/
double VHML_Result=418.9829*VHML_N;

for (int i=0;i<VHML_N;i++)
    VHML_Result -= x[i]*sin(sqrt(fabs(x[i])));
(*nfeval)++;
delete[]x;
return VHML_Result;
}
//---------------------------------------------------------------------------
double HML_TestFunction_StepFunction(double *gx,double *bias, int VHML_N, long *nfeval)
{

	double *x = new double[VHML_N];

	for (int i = 0; i < VHML_N; i++)
	{
		x[i] = gx[i] + bias[i];
	}
/*
Функция многих переменных: Функция Step (модифицированная версия De Jong 3).
Тестовая функция вещественной оптимизации.
Входные параметры:
 x - указатель на исходный массив;
 VHML_N - размер массива x.
Возвращаемое значение:
 Значение тестовой функции в точке x.
*/
    double VHML_Result=0;

    double H=0;

    for (int i=0;i<VHML_N;i++)
        H+=fabs(int(x[i]));

    if (H!=0)
    {
        for (int i=0;i<VHML_N;i++)
            VHML_Result+=(int(x[i]))*(int(x[i]));
    }
    else
    {
        for (int i=0;i<VHML_N;i++)
            VHML_Result+=fabs(x[i]);
    }
	(*nfeval)++;
	delete[]x;
    return VHML_Result+1;
}
//---------------------------------------------------------------------------
double HML_TestFunction_SumVector(int *gx, double *bias, int VHML_N, long *nfeval)
{

	double *x = new double[VHML_N];

	for (int i = 0; i < VHML_N; i++)
	{
		x[i] = gx[i] + bias[i];
	}
/*
Сумма всех элементов бинарного вектора.
Тестовая функция бинарной оптимизации.
Входные параметры:
 x - указатель на исходный массив;
 VHML_N - размер массива x.
Возвращаемое значение:
 Значение тестовой функции в точке x.
*/
double VHML_Result=0;
for (int i=0;i<VHML_N;i++) VHML_Result+=x[i];
(*nfeval)++;
delete[]x;
return VHML_Result;
}















//---------------------------------------------------------------------------
double HML_TestFunction_Wave(double x)
{
/*
Функция одной переменных: волна.
Тестовая функция вещественной оптимизации.
Входные параметры:
 x - вещественная переменная.
Возвращаемое значение:
 Значение тестовой функции в точке (x).
*/
double VHML_Result;
VHML_Result = (exp(-x*x)+0.01*cos(200*x));
return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_AdditivePotential(double x, double y)
{
	/*
	Функция двух переменных: аддитивная потенциальная функция.
	Тестовая функция вещественной оптимизации.
	Входные параметры:
	x - первая вещественная переменная;
	y - вторая вещественная переменная.
	Возвращаемое значение:
	Значение тестовой функции в точке (x,y).
	*/
	double VHML_Result;
	double z1 = -(1. / ((x - 1.)*(x - 1.) + 0.2)) - (1. / (2.*(x - 2.)*(x - 2.) + 0.15)) - (1. / (3.*(x - 3.)*(x - 3.) + 0.3));
	double z2 = -(1. / ((y - 1.)*(y - 1.) + 0.2)) - (1. / (2.*(y - 2.)*(y - 2.) + 0.15)) - (1. / (3.*(y - 3.)*(y - 3.) + 0.3));
	VHML_Result = z1 + z2;
	return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_Bosom(double x, double y)
{
	/*
	Функция двух переменных: функция Bosom.
	Тестовая функция вещественной оптимизации.
	Входные параметры:
	x - первая вещественная переменная;
	y - вторая вещественная переменная.
	Возвращаемое значение:
	Значение тестовой функции в точке (x,y).
	*/
	double VHML_Result;
	double sk1 = -((x - 4)*(x - 4) + (y - 4)*(y - 4))*((x - 4)*(x - 4) + (y - 4)*(y - 4));
	double sk2 = -((x + 4)*(x + 4) + (y + 4)*(y + 4))*((x + 4)*(x + 4) + (y + 4)*(y + 4));

	VHML_Result = exp(sk1 / 1000.) + exp(sk2 / 1000.) + 0.15*exp(sk1) + 0.15*exp(sk2);
	return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_EggHolder(double x, double y)
{
	/*
	Функция двух переменных: функция Egg Holder.
	Тестовая функция вещественной оптимизации.
	Входные параметры:
	x - первая вещественная переменная;
	y - вторая вещественная переменная.
	Возвращаемое значение:
	Значение тестовой функции в точке (x,y).
	*/
	double VHML_Result;

	VHML_Result = -x*sin(sqrt(fabs(x - (y + 47.)))) - (y + 47)*sin(sqrt(fabs(x / 2. + 47 + y)));

	return VHML_Result;
}
//---------------------------------------------------------------------------
double HML_TestFunction_Himmelblau(double x, double y)
{
	/*
	Функция двух переменных: функция Химмельблау.
	Тестовая функция вещественной оптимизации.
	Входные параметры:
	x - первая вещественная переменная;
	y - вторая вещественная переменная.
	Возвращаемое значение:
	Значение тестовой функции в точке (x,y).
	*/
	double VHML_Result;
	VHML_Result = (x*x + y - 11)*(x*x + y - 11) + (x + y*y - 7)*(x + y*y - 7);
	return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_InvertedRosenbrock(double x, double y)
{
	/*
	Функция двух переменных: перевернутая функция Розенброка.
	Тестовая функция вещественной оптимизации.
	Входные параметры:
	x - первая вещественная переменная;
	y - вторая вещественная переменная.
	Возвращаемое значение:
	Значение тестовой функции в точке (x,y).
	*/
	double VHML_Result;

	VHML_Result = -100. / (100.*(x*x - y) + (1. - x)*(1. - x) + 600.);

	return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_Katnikov(double x, double y)
{
	/*
	Функция двух переменных: функция Катникова.
	Тестовая функция вещественной оптимизации.
	Входные параметры:
	x - первая вещественная переменная;
	y - вторая вещественная переменная.
	Возвращаемое значение:
	Значение тестовой функции в точке (x,y).
	*/
	double VHML_Result;
	double A = 0.8;
	VHML_Result = 0.5*(x*x + y*y)*(2 * A + A*cos(1.5*x)*cos(3.14*y) + A*cos(sqrt(5)*x)*cos(3.5*y));
	return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_Multiextremal(double x)
{
	/*
	Функция одной переменных: функция Multiextremal.
	Тестовая функция вещественной оптимизации.
	Входные параметры:
	x - вещественная переменная.
	Возвращаемое значение:
	Значение тестовой функции в точке (x).
	*/
	double VHML_Result;
	VHML_Result = (0.05*(x - 1.)*(x - 1.) + (3. - 2.9*exp(-2.77257*x*x))*(1 - cos(x*(4. - 50 * exp(-2.77257*x*x)))));
	return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_Multiextremal2(double x)
{
	/*
	Функция одной переменных: функция Multiextremal2.
	Тестовая функция вещественной оптимизации.
	Входные параметры:
	x - вещественная переменная.
	Возвращаемое значение:
	Значение тестовой функции в точке (x).
	*/
	double VHML_Result;
	VHML_Result = 1. - 0.5*cos(1.5*(10.*x - 0.3))*cos(31.4*x) + 0.5*cos(sqrt(5.)*10.*x)*cos(35.*x);
	return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_Multiextremal3(double x, double y)
{
	/*
	Функция двух переменных: функция Multiextremal3.
	Тестовая функция вещественной оптимизации.
	Входные параметры:
	x - первая вещественная переменная;
	y - вторая вещественная переменная.
	Возвращаемое значение:
	Значение тестовой функции в точке (x,y).
	*/
	double VHML_Result;
	VHML_Result = x*x*fabs(sin(2.*x)) + y*y*fabs(sin(2.*y)) - 1. / (5.*x*x + 5.*y*y + 0.2) + 5.;
	return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_Multiextremal4(double x, double y)
{
	/*
	Функция двух переменных: функция Multiextremal4.
	Тестовая функция вещественной оптимизации.
	Входные параметры:
	x - первая вещественная переменная;
	y - вторая вещественная переменная.
	Возвращаемое значение:
	Значение тестовой функции в точке (x,y).
	*/
	double VHML_Result;
	VHML_Result = 0.5*(x*x + x*y + y*y)*(1. + 0.5*cos(1.5*x)*cos(3.2*x*y)*cos(3.14*y) + 0.5*cos(2.2*x)*cos(4.8*x*y)*cos(3.5*y));
	return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_MultiplicativePotential(double x, double y)
{
	/*
	Функция двух переменных: мультипликативная потенциальная функция.
	Тестовая функция вещественной оптимизации.
	Входные параметры:
	x - первая вещественная переменная;
	y - вторая вещественная переменная.
	Возвращаемое значение:
	Значение тестовой функции в точке (x,y).
	*/
	double VHML_Result;
	double z1 = -(1. / ((x - 1.)*(x - 1.) + 0.2)) - (1. / (2.*(x - 2.)*(x - 2.) + 0.15)) - (1. / (3.*(x - 3.)*(x - 3.) + 0.3));
	double z2 = -(1. / ((y - 1.)*(y - 1.) + 0.2)) - (1. / (2.*(y - 2.)*(y - 2.) + 0.15)) - (1. / (3.*(y - 3.)*(y - 3.) + 0.3));
	VHML_Result = -z1*z2;
	return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_RastriginWithChange(double x, double y)
{
	/*
	Функция двух переменных: функция Растригина с изменением коэффициентов.
	Тестовая функция вещественной оптимизации.
	Входные параметры:
	x - первая вещественная переменная;
	y - вторая вещественная переменная.
	Возвращаемое значение:
	Значение тестовой функции в точке (x,y).
	*/
	double VHML_Result;

	VHML_Result = 0.1*x*x + 0.1*y*y - 4.*cos(0.8*x) - 4.*cos(0.8*y) + 8.;

	return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_RastriginWithTurning(double x, double y)
{
	/*
	Функция двух переменных: функция Растригина овражная с поворотом осей.
	Тестовая функция вещественной оптимизации.
	Входные параметры:
	x - первая вещественная переменная;
	y - вторая вещественная переменная.
	Возвращаемое значение:
	Значение тестовой функции в точке (x,y).
	*/
	double VHML_Result;

	double alpha = HML_PI_2;
	double kx = 1.5;
	double ky = 0.8;

	double A, B;
	A = x*cos(alpha) - y*sin(alpha);
	B = x*sin(alpha) + y*cos(alpha);

	VHML_Result = (0.1*kx*A)*(0.1*kx*A) + (0.1*ky*B)*(0.1*ky*B) - 4.*cos(0.8*kx*A) - 4.*cos(0.8*ky*B) + 8.;

	return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_ReverseGriewank(double x, double y)
{
	/*
	Функция двух переменных: функция ReverseGriewank.
	Тестовая функция вещественной оптимизации.
	Входные параметры:
	x - первая вещественная переменная;
	y - вторая вещественная переменная.
	Возвращаемое значение:
	Значение тестовой функции в точке (x,y).
	*/
	double VHML_Result;

	VHML_Result = 1. / ((x*x + y*y) / 200. - cos(x)*cos(y / sqrt(2.)) + 2.);

	return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_ShekelsFoxholes(double x, double y)
{
	/*
	Функция двух переменных: функция "Лисьи норы" Шекеля.
	Тестовая функция вещественной оптимизации.
	Входные параметры:
	x - первая вещественная переменная;
	y - вторая вещественная переменная.
	Возвращаемое значение:
	Значение тестовой функции в точке (x,y).
	*/
	double VHML_Result;
	double K = 500.;
	double f1, f2;
	int j, k;
	int a[2][25];

	a[0][0] = -32;
	a[0][1] = -16;
	a[0][2] = 0;
	a[0][3] = 16;
	a[0][4] = 32;
	a[0][5] = -32;
	a[0][6] = -16;
	a[0][7] = 0;
	a[0][8] = 16;
	a[0][9] = 32;
	a[0][10] = -32;
	a[0][11] = -16;
	a[0][12] = 0;
	a[0][13] = 16;
	a[0][14] = 32;
	a[0][15] = -32;
	a[0][16] = -16;
	a[0][17] = 0;
	a[0][18] = 16;
	a[0][19] = 32;
	a[0][20] = -32;
	a[0][21] = -16;
	a[0][22] = 0;
	a[0][23] = 16;
	a[0][24] = 32;

	a[1][0] = -32;
	a[1][1] = -32;
	a[1][2] = -32;
	a[1][3] = -32;
	a[1][4] = -32;
	a[1][5] = -16;
	a[1][6] = -16;
	a[1][7] = -16;
	a[1][8] = -16;
	a[1][9] = -16;
	a[1][10] = 0;
	a[1][11] = 0;
	a[1][12] = 0;
	a[1][13] = 0;
	a[1][14] = 0;
	a[1][15] = 16;
	a[1][16] = 16;
	a[1][17] = 16;
	a[1][18] = 16;
	a[1][19] = 16;
	a[1][20] = 32;
	a[1][21] = 32;
	a[1][22] = 32;
	a[1][23] = 32;
	a[1][24] = 32;

	VHML_Result = 1. / K;
	for (j = 0; j<25; j++)
	{
		f1 = 1;
		for (k = 0; k<6; k++) f1 = f1*(x - a[0][j]);
		f2 = 1;
		for (k = 0; k<6; k++) f2 = f2*(y - a[1][j]);
		VHML_Result += 1. / (j + 1. + f1 + f2);
	}

	VHML_Result = 1. / VHML_Result;

	return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_Sombrero(double x, double y)
{
	/*
	Функция одной переменных: функция Сомбреро.
	Тестовая функция вещественной оптимизации.
	Входные параметры:
	x - первая вещественная переменная;
	y - вторая вещественная переменная.
	Возвращаемое значение:
	Значение тестовой функции в точке (x,y).
	*/
	double VHML_Result;
	VHML_Result = 1. - sin(sqrt(x*x + y*y))*sin(sqrt(x*x + y*y));
	VHML_Result /= (1. + 0.001*(x*x + y*y));
	return VHML_Result;
}
//---------------------------------------------------------------------------

double HML_TestFunction_Rana(double x, double y)
{
	/*
	Функция двух переменных: функция Rana.
	Тестовая функция вещественной оптимизации.
	Входные параметры:
	x - первая вещественная переменная;
	y - вторая вещественная переменная.
	Возвращаемое значение:
	Значение тестовой функции в точке (x,y).
	*/
	double VHML_Result;
	VHML_Result = x*sin(sqrt(fabs(y + 1. - x)))*cos(sqrt(fabs(y + 1. + x))) + (y + 1.)*cos(sqrt(fabs(y + 1. - x)))*sin(sqrt(fabs(y + 1. + x)));
	return VHML_Result;
}
//---------------------------------------------------------------------------