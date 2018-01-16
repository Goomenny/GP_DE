#pragma once
#include "../../GP_Templates/TNode.h"
#include "../../GP_Templates/TemplateTREE.h"
#include "../../GP_Templates/TemplatePopulation.h"
#include "../../GP_Templates/TemplateGP.h"
#include "Functions.h"

class TNode_DE : public TNode
{
private:

	TNode_DE *argument;   //Указатель на слой потомков

	double unarvalue; //Константа для унарного умножения

public:
	TNode_DE();
	~TNode_DE();
	TNode_DE(const TNode_DE&); //Копиконструктор
	TNode_DE& operator= (const TNode_DE&); // Копирование узла

	void Init(bool, int, int, int); // Инициализация

	double Get_result(double *); //Регрессия

	string Get_formula(string); // Получить формулу узла через рекурсии

	int Get_n_heirs();

	void Set_argument(TNode_DE *);
	void Set_unarvalue(double newunarvalue) { unarvalue = newunarvalue; };


};


class TTree_DE : public TTree<TNode_DE>
{

private:
	double meansquare; //Квадратичная ошибка

					   //DE

	double reliability = 0;
	double meanresult = 0;
	double meanx = 0;

	double testreliability = 0;
	double testmeanresult = 0;
	double testmeanx = 0;

	double testfitness;
public:
	TTree_DE();
	~TTree_DE();
	TTree_DE(const TTree_DE &); //Копиконструктор
								//TTree_symbolic& operator=(const TTree_symbolic &); //Копирование дерева


	void Mutate(int, double); //Мутировать с вероятностью
	string Get_formula(); // Получить формулу дерева через рекурсии
	double Get_meansquare() { return meansquare; };

	inline double Get_result(double *); 	//Получить значение дерева через рекурсии регрессия

											//DE
	
	void Set_fitness(double newfitness) { fitness = newfitness; };
	double Get_testfitness() { return testfitness; };
	void Set_testfitness(double arg) { testfitness = arg; };


	double Get_reliability() { return reliability; };
	double Get_meanresult() { return meanresult; };
	double Get_meanx() { return meanx; };

	double Get_testreliability() { return testreliability; };
	double Get_testmeanresult() { return testmeanresult; };
	double Get_testmeanx() { return testmeanx; };

	void Set_reliability(double arg) { reliability= arg; };
	void Set_meanresult(double arg) {  meanresult= arg; };
	void Set_meanx(double arg) {  meanx= arg; };

	void Set_testreliability(double arg) {  testreliability= arg; };
	void Set_testmeanresult(double arg) {  testmeanresult= arg; };
	void Set_testmeanx(double arg) {  testmeanx= arg; };


};

class TPopulation_DE : public TPopulation<TTree_DE> {
public:


	void Calculate_fitness(int runs);
	string Get_tree_formula(int i) { return tree[i].Get_formula(); };
	double Get_meanresult(int i) { return tree[i].Get_meanresult(); };
	double Get_tree_testfitness(int i) { return tree[i].Get_testfitness(); };

	double Get_tree_reliability(int i) { return tree[i].Get_reliability(); };
	double Get_tree_meanresult(int i) { return tree[i].Get_meanresult(); };
	double Get_tree_meanx(int i) { return tree[i].Get_meanx(); };

	double Get_tree_testreliability(int i) { return tree[i].Get_testreliability(); };
	double Get_tree_testmeanresult(int i) { return tree[i].Get_testmeanresult(); };
	double Get_tree_testmeanx(int i) { return tree[i].Get_testmeanx(); };

private:

};

class TGp_DE : public TGp<TPopulation_DE>
{

public:

	int Start_fast(bool);
	string Get_formula();
	void Init(bool, int, int, int, int, int, int, int, int, int, double, int);  //Инициализация
	double Get_value(double *);
	double Get_bestmeanresult() { return last_population.Get_meanresult(0); };


};
