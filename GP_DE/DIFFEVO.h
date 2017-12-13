#pragma once
#include <iostream>
#include <ctime>
#include <random> 
#define MAXPOP  500
#define MAXDIM  35
#define IM1 2147483563
#define IM2 2147483399
#define IMM1 (IM1 - 1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1 + IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0 - EPS)
using namespace std;
template<class Tree>
class TDE {
private:
	int   i, j, L, n;      // counting variables                 
	int   r1, r2, r3, r4;  // placeholders for random indexes    
	int   r5;              // placeholders for random indexes    
	int   D;               // Dimension of parameter vector      
	int   NP;              // number of population members       
	int   imin;            // index to member with lowest energy 
	int   refresh;         // refresh rate of screen output      
	int   strategy;        // choice parameter for screen output 
	int   gen, genmax, seed;
	long  nfeval;          // number of function evaluations     
	double trial_energy;    // buffer variable                    
	double inibound_h;      // upper parameter bound              
	double inibound_l;      // lower parameter bound              
	double tmp[MAXDIM], best[MAXDIM], bestit[MAXDIM]; // members  
	double energy[MAXPOP];  // obj. funct. values                 
	double F, CR;           // control variables of DE            
	double emin;            // help variables                     

	long  rnd_uni_init;
	double c[MAXPOP][MAXDIM], d[MAXPOP][MAXDIM];
	double oldarray[MAXPOP][MAXDIM];
	double newarray[MAXPOP][MAXDIM];
	double swaparray[MAXPOP][MAXDIM];
	double vars[7];

	double r;

	mt19937 randeng;
	

public:
	void Init(double(*evaluate)(double[], double *, int, long *), double *bias);
	int CopyVector(double a[], double b[]);
	int CopyArray(double dest[MAXPOP][MAXDIM], double src[MAXPOP][MAXDIM]);
	
	double Start_fast(double(*evaluate)(double[],double *, int, long *),double *bias, Tree &tree );

	double *Get_bestx() { return best; };
};

template<class Tree>
void TDE<Tree>::Init(double(*evaluate)(double[], double*, int, long *), double *bias)
{

	strategy = 11;     // choice of strategy
	genmax = 200;         // maximum number of generations
	refresh = 50;        // output refresh cycle
	D = 3;             // number of parameters
	NP = 50;             // population size.
	inibound_h = 10.;     // upper parameter bound for init
	inibound_l = -10.;     // lower parameter bound for init
	F = 0.75;              // weight factor
	CR = 1.;             // crossing over factor
	seed = 3;           // random seed 

	rnd_uni_init = -(long)seed;  // initialization of rnd_uni() 
	nfeval = 0;           // reset number of function evaluations 
	randeng.seed(0);
	uniform_real_distribution<> urd(0, 1);
	// Initialization
	// Right now this part is kept fairly simple and just generates
	// random numbers in the range [-initfac, +initfac]. You might
	// want to extend the init part such that you can initialize
	// each parameter separately.

	// spread initial population members
	for (i = 0; i<NP; i++) {
		for (j = 0; j<D; j++) {
			r = urd(randeng);
			c[i][j] = inibound_l + r*(inibound_h - inibound_l);
		}

		energy[i] = evaluate(c[i], bias, D, &nfeval);
		// printf("%2d %20.8f %3d\n", i, energy[i], nfeval);
		// cin.get(ch);
	}

	emin = energy[0];
	imin = 0;
	for (i = 1; i<NP; i++) {
		if (energy[i] < emin) {
			emin = energy[i];
			imin = i;
		}
	}
}

template<class Tree>
int TDE<Tree>::CopyVector(double a[], double b[])
{
	for (int k = 0; k<MAXDIM; k++) {
		a[k] = b[k];
	}
	return 0;
}

template<class Tree>
int TDE<Tree>::CopyArray(double dest[MAXPOP][MAXDIM], double src[MAXPOP][MAXDIM])
{
	for (int j = 0; j<MAXPOP; j++) {
		for (int k = 0; k<MAXDIM; k++) {
			dest[j][k] = src[j][k];
		}
	}
	return 0;
}
template<class Tree>
double TDE<Tree>::Start_fast(double(*evaluate)(double[], double *, int, long *), double *bias, Tree & tree)
{
	CopyVector(best, c[imin]);
	CopyVector(bestit, c[imin]);

	// old population (generation G)
	// new population (generation G+1)
	CopyArray(oldarray, c);
	// new population (generation G+1)
	CopyArray(newarray, d);
	uniform_real_distribution<> urd(0, 1);
	// Iteration loop
	gen = 0; // generation counter reset
	while ((gen < genmax)) {
		gen++;
		imin = 0;

		for (i = 0; i<NP; i++) {
			// Pick a random population member 
			do {
				// Endless loop for NP < 2 !!!
				r = urd(randeng);
				r1 = (int)(r*NP);
			} while (r1 == i);

			do {
				// Endless loop for NP < 3 !!!
				r = urd(randeng);
				r2 = (int)(r*NP);
			} while ((r2 == i) || (r2 == r1));

			do {
				// Endless loop for NP < 4 !!!     
				r3 = (int)(urd(randeng)*NP);
			} while ((r3 == i) || (r3 == r1) || (r3 == r2));

			do {
				// Endless loop for NP < 5 !!!     
				r4 = (int)(urd(randeng)*NP);
			} while ((r4 == i) || (r4 == r1) || (r4 == r2) || (r4 == r3));

			do {
				// Endless loop for NP < 6 !!!     
				r5 = (int)(urd(randeng)*NP);
			} while ((r5 == i) || (r5 == r1) || (r5 == r2) || (r5 == r3) || (r5 == r4));

			// Choice of strategy
			// We have tried to come up with a sensible naming-convention: DE/x/y/z
			//   DE :  stands for Differential Evolution
			//   x  :  a string which denotes the vector to be perturbed
			//   y  :  number of difference vectors taken for perturbation of x
			//   z  :  crossover method (exp = exponential, bin = binomial)
			//
			// There are some simple rules which are worth following:
			//   1)  F is usually between 0.5 and 1 (in rare cases > 1)
			//   2)  CR is between 0 and 1 with 0., 0.3, 0.7 and 1. being worth to be tried first
			//   3)  To start off NP = 10*D is a reasonable choice. Increase NP if misconvergence=
			//       happens.
			//   4)  If you increase NP, F usually has to be decreased
			//   5)  When the DE/best... schemes fail DE/rand... usually works and vice versa


			// EXPONENTIAL CROSSOVER
			// DE/best/1/exp
			// Our oldest strategy but still not bad. However, we have found several
			// optimization problems where misconvergence occurs.

			// strategy DE0 (not in our paper)
			if (strategy == 1) {
				for (int k = 0; k<MAXDIM; k++) {
					tmp[k] = oldarray[i][k];
				}
				n = (int)(urd(randeng)*D);
				L = 0;
				do {
					tmp[n] = bestit[n] + F*(oldarray[r2][n] - oldarray[r3][n]);
					n = (n + 1) % D;
					L++;
				} while ((urd(randeng) < CR) && (L < D));
			}
			// DE/rand/1/exp
			// This is one of my favourite strategies. It works especially well when the
			// "bestit[]"-schemes experience misconvergence. Try e.g. F=0.7 and CR = 0.5
			// as a first guess.
			// strategy DE1 in the techreport
			else if (strategy == 2) {
				for (int k = 0; k<MAXDIM; k++) {
					tmp[k] = oldarray[i][k];
				}
				n = (int)(urd(randeng)*D);
				L = 0;
				do {
					tmp[n] = oldarray[r1][n] + F*(oldarray[r2][n] - oldarray[r3][n]);
					n = (n + 1) % D;
					L++;
				} while ((urd(randeng) < CR) && (L < D));
			}
			// DE/rand-to-best/1/exp
			// This strategy seems to be one of the best strategies. Try F=0.85 and CR = 1.0
			// If you get misconvergence try to increase NP. If this doesn't help you
			// should play around with all three control variables.
			// similiar to DE2 but generally better
			else if (strategy == 3) {
				for (int k = 0; k<MAXDIM; k++) {
					tmp[k] = oldarray[i][k];
				}
				n = (int)(urd(randeng)*D);
				L = 0;
				do {
					tmp[n] = tmp[n] + F*(bestit[n] - tmp[n]) + F*(oldarray[r1][n] - oldarray[r2][n]);
					n = (n + 1) % D;
					L++;
				} while ((urd(randeng) < CR) && (L < D));
			}
			// DE/best/2/exp is another powerful strategy worth trying
			else if (strategy == 4) {
				for (int k = 0; k<MAXDIM; k++) {
					tmp[k] = oldarray[i][k];
				}
				n = (int)(urd(randeng)*D);
				L = 0;
				do {
					tmp[n] = bestit[n] + (oldarray[r1][n] + oldarray[r2][n] - oldarray[r3][n] - oldarray[r4][n])*F;
					n = (n + 1) % D;
					L++;
				} while ((urd(randeng) < CR) && (L < D));
			}
			// DE/rand/2/exp seems to be a robust optimizer for many functions
			else if (strategy == 5) {
				for (int k = 0; k<MAXDIM; k++) {
					tmp[k] = oldarray[i][k];
				}
				n = (int)(urd(randeng)*D);
				L = 0;
				do {
					tmp[n] = oldarray[r5][n] + (oldarray[r1][n] + oldarray[r2][n] - oldarray[r3][n] - oldarray[r4][n])*F;
					n = (n + 1) % D;
					L++;
				} while ((urd(randeng) < CR) && (L < D));
			}
			// Essentially same strategies but BINOMIAL CROSSOVER
			// DE/best/1/bin
			else if (strategy == 6) {
				for (int k = 0; k<MAXDIM; k++) {
					tmp[k] = oldarray[i][k];
				}
				n = (int)(urd(randeng)*D);
				// perform D binomial trials
				for (L = 0; L<D; L++) {
					// change at least one parameter
					if ((urd(randeng) < CR) || L == (D - 1)) {
						tmp[n] = bestit[n] + F*(oldarray[r2][n] - oldarray[r3][n]);
					}
					n = (n + 1) % D;
				}
			}
			// DE/rand/1/bin
			else if (strategy == 7) {
				for (int k = 0; k<MAXDIM; k++) {
					tmp[k] = oldarray[i][k];
				}
				n = (int)(urd(randeng)*D);
				// perform D binomial trials */
				for (L = 0; L<D; L++) {
					// change at least one parameter
					if ((urd(randeng) < CR) || L == (D - 1)) {
						tmp[n] = oldarray[r1][n] + F*(oldarray[r2][n] - oldarray[r3][n]);
					}
					n = (n + 1) % D;
				}
			}
			// DE/rand-to-best/1/bin
			else if (strategy == 8) {
				for (int k = 0; k<MAXDIM; k++) {
					tmp[k] = oldarray[i][k];
				}
				n = (int)(urd(randeng)*D);
				for (L = 0; L<D; L++) {
					if ((urd(randeng) < CR) || L == (D - 1)) {
						tmp[n] = tmp[n] + F*(bestit[n] - tmp[n]) + F*(oldarray[r1][n] - oldarray[r2][n]);
					}
					n = (n + 1) % D;
				}
			}
			// DE/best/2/bin
			else if (strategy == 9) {
				for (int k = 0; k<MAXDIM; k++) {
					tmp[k] = oldarray[i][k];
				}
				n = (int)(urd(randeng)*D);
				for (L = 0; L<D; L++) {
					if ((urd(randeng) < CR) || L == (D - 1)) {
						tmp[n] = bestit[n] + (oldarray[r1][n] + oldarray[r2][n] - oldarray[r3][n] - oldarray[r4][n])*F;
					}
					n = (n + 1) % D;
				}
			}
			// DE/rand/2/bin
			else if (strategy == 10) {
				for (int k = 0; k<MAXDIM; k++) {
					tmp[k] = oldarray[i][k];
				}
				n = (int)(urd(randeng)*D);
				for (L = 0; L<D; L++) {
					if ((urd(randeng) < CR) || L == (D - 1)) {
						tmp[n] = oldarray[r5][n] + (oldarray[r1][n] + oldarray[r2][n] - oldarray[r3][n] - oldarray[r4][n])*F;
					}
					n = (n + 1) % D;
				}
			}
			else if (strategy == 11) {
				for (int k = 0; k<MAXDIM; k++) {
					tmp[k] = oldarray[i][k];
				}
				n = (int)(urd(randeng)*D);
				for (L = 0; L<D; L++) {
					vars[0] = tmp[n];
					vars[1] = oldarray[imin][n];
					vars[2] = oldarray[r1][n];
					vars[3] = oldarray[r2][n];
					vars[4] = oldarray[r3][n];
					vars[5] = oldarray[r4][n];
					vars[6] = oldarray[r5][n];
					if ((urd(randeng) < CR) || L == (D - 1)) {
						//tmp[n] = tree.Get_result(vars);
						//tmp[n] = tmp[n] + F*(bestit[n] - tmp[n]) + F*(oldarray[r1][n] - oldarray[r2][n]);
						tmp[n] = (oldarray[r5][n]+0.5 - (oldarray[r1][n]- oldarray[r2][n]))-0.5; // на гриванке!
					}
					n = (n + 1) % D;
				}
			}
			else {
				for (int k = 0; k<MAXDIM; k++) {
					tmp[k] = oldarray[i][k];
				}
				n = (int)(urd(randeng)*D);
				L = 0;
				do {
					tmp[n] = tree.Get_result(vars);
					n = (n + 1) % D;
					L++;
				} while ((urd(randeng) < CR) && (L < D));
			}


			// Trial mutation now in tmp[]. Test how good this choice really was.
			trial_energy = evaluate(tmp, bias, D, &nfeval);  // Evaluate new vector in tmp[]
															 // improved objective function value?
			if (trial_energy <= energy[i]) {
				energy[i] = trial_energy;
				for (int k = 0; k<MAXDIM; k++) {
					newarray[i][k] = tmp[k];
				}
				// Was this a new minimum?
				if (trial_energy<emin) {
					// reset emin to new low...
					emin = trial_energy;
					imin = i;
					for (int k = 0; k<MAXDIM; k++) {
						best[k] = tmp[k];
					}
				}
			}
			else {
				// replace target with old value
				for (int k = 0; k<MAXDIM; k++) {
					newarray[i][k] = oldarray[i][k];
				}
			}
		}

		CopyVector(bestit, best);  // Save best population member of current iteration

								   // swap population arrays. New generation becomes old one
		CopyArray(swaparray, oldarray);
		CopyArray(oldarray, newarray);
		CopyArray(newarray, swaparray);

	}

	return emin;
}
