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
	double meanresult; //Среднее решение
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
	double Get_meanresult() { return meanresult; };
	void Set_fitness(double newfitness) { fitness = newfitness; };

};

class TPopulation_DE : public TPopulation<TTree_DE> {
public:


	void Calculate_fitness();
	string Get_tree_formula(int i) { return tree[i].Get_formula(); };

private:

};

class TGp_DE : public TGp<TPopulation_DE>
{

public:

	int Start_fast(bool);
	string Get_formula();
	void Init(bool, int, int, int, int, int, int, int, int, int, double, int);  //Инициализация
	double Get_value(double *);


};
