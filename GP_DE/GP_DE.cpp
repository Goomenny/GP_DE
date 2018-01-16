#include "GP_DE.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
TNode_DE::TNode_DE() {
	unarvalue = NULL;
	state = NULL;
	constant = NULL;
	type = NULL;

	num_var = NULL;

	value = NULL;

	func = NULL;
	arn = NULL;
	num_parent = NULL;
	n_child = NULL;
	child = 0;
	argument = 0;
	num_self = NULL;
	symbol = "";
	index = "";
}
//---------------------------------------------------------------------------
TNode_DE::TNode_DE(const TNode_DE &other) {
	this->unarvalue = other.unarvalue;
	this->state = other.state;
	this->constant = other.constant;
	this->type = other.type;

	this->num_var = other.num_var;

	this->value = other.value;
	this->func = other.func;
	this->arn = other.arn;
	this->num_parent = other.num_parent;
	this->n_child = other.n_child;
	this->num_self = other.num_self;
	this->num_layer = other.num_layer;
	this->argument = 0;
	//	if (type)
	{
		this->symbol = other.symbol;
		this->index = other.index;
	}
	this->child = new int[this->n_child];

	for (int i = 0; i < this->n_child; i++) {
		this->child[i] = other.child[i];
	}



}
//---------------------------------------------------------------------------
TNode_DE& TNode_DE::operator=(const TNode_DE &other) {//перегрузка оператора присваивания

	if (this == &other)
		return *this; // присвоение самому себе, ничего делать не надо

	delete[] child;
	this->unarvalue = other.unarvalue;
	this->state = other.state;
	this->constant = other.constant;
	this->type = other.type;

	this->num_var = other.num_var;

	this->value = other.value;
	this->func = other.func;
	this->arn = other.arn;
	this->num_parent = other.num_parent;
	this->n_child = other.n_child;
	this->num_self = other.num_self;
	this->num_layer = other.num_layer;
	this->argument = 0;
	//	if (type)
	{
		this->symbol = other.symbol;
		this->index = other.index;
	}
	this->child = new int[this->n_child];

	for (int i = 0; i < this->n_child; i++) {
		this->child[i] = other.child[i];
	}
	return *this;

}
//---------------------------------------------------------------------------
void TNode_DE::Init(bool gtype, int gfunc, int gn_var, int inheriters) {

	state = false;
	type = gtype;
	func = rand() % 3;
	if (type)
	{
		if (func > 1) {
			n_child = 1; 
			arn = 1;
			
			child = new int[n_child];
			Set_symbol(func);

			unarvalue = rand() % 20001 / 10000. - 1;
			
		}
		else {
			n_child = 2; //Бинарное дерево
			arn = 2;


			child = new int[n_child];

			Set_symbol(func);
		}
		

	}
	else
	{
		n_child = 0;
		arn = 0;


		constant = rand() % 2;
		constant = false;
		n_child = 0;
		arn = 0;

		if (constant) {

			switch (rand()%6) {
			case 0:
				value = 0;
				break;
			case 1:
				value = 0.5;
				break;
			case 2:
				value = 1;
				break;
			case 3:
				value = M_PI;
				break;
			case 4:
				value = M_E;
				break;
			case 5:
				value = rand() % 20001 / 10000. - 1;
				break;
			}
	
			//value = rand() % 20001 / 10000. - 1;

		}
		else {
			value = NULL;
			num_var = rand() % gn_var;
		}

	}


}

//---------------------------------------------------------------------------
TNode_DE::~TNode_DE() {
	delete[] child;
}

//---------------------------------------------------------------------------
//Регрессия
double TNode_DE::Get_result(double *gvar) {
	if (type) {

		switch (func) {
		case 0:
			value = Sum<TNode_DE>(argument, child, n_child, gvar);
			break;
		case 1:
			value = Minu<TNode_DE>(argument, child, n_child, gvar);
			break;
		case 2:
			value = unarvalue* argument[child[0]].Get_result(gvar);
			break;
		case 3:
			value = sin(argument[child[0]].Get_result(gvar));
			break;
		}
	}
	else if (!constant) {
		value = gvar[num_var];
	}

	return value;

}
//---------------------------------------------------------------------------
string TNode_DE::Get_formula(string gsymbol) {
	string formula; //Формула данного узла
	if (type) {
		if (num_layer != 0)	formula = "(";

		if (n_child != 1) {
			for (int i = 0; i < n_child; i++) {
				formula += argument[child[i]].Get_formula(argument[child[i]].symbol);
				if (i < n_child - 1) formula += gsymbol;
			}
		}
		else {
			if (func > 2) {
				formula += gsymbol;
				formula += "[";
				formula += argument[child[0]].Get_formula(argument[child[0]].symbol);
				formula += "]";
			}
			else {
				formula += argument[child[0]].Get_formula(argument[child[0]].symbol);
				formula += gsymbol;
				formula += to_string(unarvalue);
			}
		}
		if (num_layer != 0) formula += ")";


	}
	else
		if (constant) {
			if (value<0)
			{
				formula += "(";
				formula += to_string(value);
				formula += ")";
			}
			else formula = to_string(value);
		}
		else if (num_var == 0)
		{
			formula = "self";
		}
		else if (num_var == 1)
		{
			formula = "best";
		}
		else
		{
			formula = "ind";
			formula += to_string(num_var - 2);
		}

	return formula;

}


void TNode_DE::Set_argument(TNode_DE *arg)
{
	argument = arg;
}

int TNode_DE::Get_n_heirs() {

	if (type) {
		int max = 0, tmp = 0;

		for (int i = 0; i < n_child; i++) {
			tmp = argument[child[i]].Get_n_heirs();
			if (tmp>max)
				max = tmp;
		}

		return max + 1;

	}
	else return 0;

}




TTree_DE::TTree_DE() {
	meanresult = 0;

}
//---------------------------------------------------------------------------

TTree_DE::~TTree_DE() {

}
//---------------------------------------------------------------------------

TTree_DE::TTree_DE(const TTree_DE &other) {


	this->meanresult = other.meanresult;
}
//---------------------------------------------------------------------------
/*TTree_DE& TTree_DE::operator=(const TTree_DE &other) {//перегрузка оператора присваивания

if (this == &other)
return *this; // присвоение самому себе, ничего делать не надо

this->meanresult  = other.meanresult ;

return *this;
}*/
//---------------------------------------------------------------------------

string TTree_DE::Get_formula() {
	return node[0][0].Get_formula(node[0][0].Get_symbol());
}
inline double TTree_DE::Get_result(double *gvar) {
	return node[0][0].Get_result(gvar);
}
void TTree_DE::Mutate(int type_of_mutation, double probability_of_mutation) {
	double ran = 0;
	int last_func = 0;
	int a[3] = { 0,1 }, b[2] = { 2 };
	switch (type_of_mutation) {
	case 0:
		probability_of_mutation = 1. / (5 * deep);
		break;
	case 1:
		probability_of_mutation = 1. / deep;
		break;
	case 2:
		probability_of_mutation = 5. / deep;
		break;
	case 3:
		break;
	}
	for (int i = 0; i < deep; i++) {
		for (int j = 0; j < n_node[i]; j++) {
			if (node[i][j].Get_type()) {
				last_func = node[i][j].Get_func();
				ran = rand() % 100001;
				ran /= 100000.;
				if (probability_of_mutation>ran) {

					while (node[i][j].Get_func() == last_func&&last_func!=2) {
						if (last_func <2) {
							node[i][j].Set_func(a[rand() % 2]);
						}
						else {
							node[i][j].Set_func(b[rand() % 2]);
						}
					}

					node[i][j].Set_symbol(node[i][j].Get_func());
					if (node[i][j].Get_func() == 2) node[i][j].Set_unarvalue(rand() % 20001 / 10000. - 1);
				}
			}
			else {

				if (node[i][j].Get_constant() ) {
					switch (rand() % 6) {
					case 0:
						node[i][j].Set_value(0);
						break;
					case 1:
						node[i][j].Set_value(0.5);
						break;
					case 2:
						node[i][j].Set_value(1);
						break;
					case 3:
						node[i][j].Set_value(M_PI);
						break;
					case 4:
						node[i][j].Set_value(M_E);
						break;
					case 5:
						node[i][j].Set_value(rand() % 20001 / 10000. - 1);
						break;
					}
				}


			}
		}
	}
}
//---------------------------------------------------------------------------


void TPopulation_DE::Calculate_fitness(int runs) {


#pragma omp parallel for
	for (int i = 0; i < size_of_population; i++) {
		TTest<TTree_DE> test;
		test.Calculate(tree[i],runs,11);
		//tree[i].Set_fitness( test.Get_reliability());
		//tree[i].Set_testfitness(test.Get_testreliability());
		tree[i].Set_fitness(1. / (1. + test.Get_meanresult()));
		tree[i].Set_testfitness(1. / (1. + test.Get_testmeanresult()));

		tree[i].Set_meanresult(test.Get_meanresult());
		tree[i].Set_meanx(test.Get_meanx());
		tree[i].Set_reliability(test.Get_reliability());

		tree[i].Set_testmeanresult(test.Get_testmeanresult());
		tree[i].Set_testmeanx(test.Get_testmeanx());
		tree[i].Set_testreliability(test.Get_testreliability());
	}
#pragma omp barrier 
}


void TGp_DE::Init(bool selfconfiguration, int size_of_population, int max_number_of_populations, int type_of_selection, int size_of_tour, int type_of_crossover, int max_deep, int dimension, int growth, int type_of_mutation, double probability_of_mutation, int inheriters) {
	first_solution = 0;
	found = false;

	//Резервируем память для массивов с примененными операторами
	this->type_of_selection.resize(size_of_population);
	this->size_of_tour.resize(size_of_population);
	this->type_of_crossover.resize(size_of_population);
	this->type_of_mutation.resize(size_of_population);


	// Записываем остальные настройки
	this->selfconfiguration = selfconfiguration;
	this->size_of_population = size_of_population;
	this->max_number_of_populations = max_number_of_populations;
	this->dimension = dimension;
	this->probability_of_crossover = probability_of_crossover;
	this->probability_of_mutation = probability_of_mutation;


	this->max_deep = max_deep;
	this->dimension = dimension;
	this->growth = growth;
	this->inheriters = inheriters;

	if (!selfconfiguration) {
		for (int i = 0; i < size_of_population; i++) {
			this->type_of_selection[i] = type_of_selection;
			this->size_of_tour[i] = size_of_tour;
			this->type_of_crossover[i] = type_of_crossover;
			this->type_of_mutation[i] = type_of_mutation;
		}
	}
	else {
		//Сбрасываем вероятности выбора операторов
		Reset_probabilities();
		// Выбираем операторы для первой эволюции
		Select_operators();
	}

	//Случайно инициализируем первое поколение
	last_population.Init(size_of_population);
	last_population.Init_randomly_tree(max_deep, dimension, growth, inheriters);
	//Инициализируем место для следующиего поколения
	new_population.Init(size_of_population);

}
//---------------------------------------------------------------------------
double TGp_DE::Get_value(double *var) {
	return last_population.Get_best_value(var);
}
//---------------------------------------------------------------------------
string TGp_DE::Get_formula() {
	return last_population.Get_best_formula();
}

//---------------------------------------------------------------------------
int TGp_DE::Start_fast(bool restart) {

	ofstream fout;
	

	fitness.clear();

	if (restart) {

		for (int i = 1; i < size_of_population; i++) {
			last_population.ReInit_trees(max_deep, dimension, growth, inheriters);
		}

		if (selfconfiguration) {
			//Сбрасываем вероятности выбора операторов
			Reset_probabilities();
			// Выбираем операторы для первой эволюции
			Select_operators();
		}
	}


	for (int i = 0; i < max_number_of_populations + 1; i++) {

		last_population.Calculate_fitness(25);//10+5*(i/5));
		last_population.Find_best();

		tmp.clear();
		double sum = 0;
		for (int ind = 0; ind<size_of_population; ind++) {
			sum += last_population.Get_tree_fitness(ind);
		}
		tmp.push_back(sum / size_of_population);
		tmp.push_back(last_population.Get_best_fitness());
		fitness.push_back(tmp);
		
		fout.open("statistics.txt", ios_base::app);

		for (int ind = 0; ind<size_of_population; ind++) {
			fout<< i << "\t" <<last_population.Get_tree_fitness(ind) <<"\t" << 
				//last_population.Get_tree_testfitness(ind) << "\t" << 
				last_population.Get_tree_meanresult(ind) << "\t" << 
				//last_population.Get_tree_testmeanresult(ind) << "\t" << 
				last_population.Get_tree_meanx(ind) << "\t" << 
				//last_population.Get_tree_testmeanx(ind) << "\t" << 
				last_population.Get_tree_reliability(ind) << "\t" << 
				//last_population.Get_tree_testreliability(ind) << "\t" << 
				last_population.Get_tree_formula(ind) <<endl;
		}
		fout.close();

		if (last_population.Get_best_fitness() == 1 && found == false)
		{
			first_solution = i;
			found = true;
			break;
		}

		if (i<max_number_of_populations) {


			if (selfconfiguration && i != 0)
			{
				//Пересчитываем вероятности операторов

				tmp.clear();
				for (int ind = 0; ind<size_of_population; ind++) {
					tmp.push_back(last_population.Get_tree_fitness(ind));
				}
				Recount_probabilities(tmp);
				Select_operators();
			}

			last_population.Selection(selfconfiguration, type_of_selection, size_of_tour);
			new_population.Evolve(last_population, type_of_crossover);
			new_population.Mutate(type_of_mutation, probability_of_mutation);

			last_population = new_population;


		}
	}

	if (found)
		return 1;
	else
		return 0;


}
