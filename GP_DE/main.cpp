#define _USE_MATH_DEFINES
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <fstream>
#include <iostream>
#include "GP_DE.h"


using namespace std;

int main() {
	srand(time(NULL));
	/*
	TTree_DE tree;
	tree.Init(4, 7, 1, 2);
	TTest<TTree_DE> test;
	ofstream fout;
	for (int  i = 1; i < 11; i++)
	{
		test.Calculate(tree, 25, i);


		fout.open("base_strat_statistics.txt", ios_base::app);
		fout << test.Get_meanx() << endl;

		fout.close();

	}
	*/




	TGp_DE gp;


	int n_var = 7;

	int inheriters = 3;
	int size_of_population = 100; //Размер популяции
	int max_number_of_populations = 100;  //Макс число поколений
	int type_of_selection = 2;  //Тип селекции      0=prop; 1=rang; 2=tour;
	int size_of_tour = 5; //Размер турнира для турнирной селекции
	int type_of_crossover = 1; //Тип скрещивания     0- стандартное 1-одноточечное
	int type_of_mutation = 1;
	int max_deep = 7;
	int dimension = n_var;
	int growth = 1; // 0- Полный рост 1- неполный
	double probability_of_mutation = 5 / 100.;  //Вероятность мутации
	double accuracy = 0.05; //Точность поиска
	bool selfconfiguration = false; // Самонастройка true/false

	gp.Init(selfconfiguration, size_of_population, max_number_of_populations, type_of_selection, size_of_tour, type_of_crossover, max_deep, dimension, growth, type_of_mutation, probability_of_mutation, inheriters);

	gp.Start_fast(false);

	cout << "+++++++" << endl;
	for (int i = 0; i < gp.Get_stats().size(); i++)
	{
		cout << gp.Get_stats()[i][0] << endl;
	}
	cout << "+++++++" << endl;
	for (int i = 0; i < gp.Get_stats().size(); i++)
	{
		cout << gp.Get_stats()[i][1] << endl;
	}



	cout << gp.Get_formula() << endl;
	cout << gp.Get_fitness() << endl;
	cout << gp.Get_bestmeanresult() << endl;
	cout << gp.Get_deep() << endl;

	/*
	TTree_symbolic Tree[5];
	for (int i = 0; i < 5; i++)
	{
		Tree[i].Init(4, 7, 0, 2);
	}


	for (int j = 0; j < 3; j++)
	{
		#pragma omp parallel for
		for (int i = 0; i < 5; i++)
		{
			//for (int  j = 0; j < 2; j++)

			TTest<TTree_symbolic> test;
			test.Calculate(Tree[i]);
			cout << Tree.Get_formula() << endl << test.Get_meanresult() << endl << test.Get_reliability() << endl << test.Get_meanx() << endl;
			//cout << "--" << endl;


		}

		cout << "-----" << endl;
	}
	*/
	/*
	test.Calculate(Tree);
	cout << Tree.Get_formula() << endl << test.Get_meanresult() << endl << test.Get_reliability() << endl << test.Get_meanx() << endl;
	cout << "--" << endl;
	test.Calculate(Tree);
	cout << Tree.Get_formula() << endl << test.Get_meanresult() << endl << test.Get_reliability() << endl << test.Get_meanx() << endl;
	*/
	//regress();

	//Tree.Calculate_fitness();
	//cout<< Tree.Get_formula()<<endl<<Tree.Get_fitness()<<endl;

	//cout<<optimizer.Start_fast(HML_TestFunction_Griewangk, Tree);

	//double var[7]{ 0,1,1,3,4,5,6 };

	//cout<<Tree.Get_result(var)<<endl;

	system("pause");
	return 0;
}