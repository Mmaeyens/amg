/*
 * main.cpp
 *
 *  Created on: Jul 11, 2016
 *      Author: Jean23
 */
using namespace std;
#include "Poisson.h"
#include "Coarsening.h"
#include "GaussSeidel.h"
#include "Operations.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ctime>

vector<double> recursive(int iter,int N,double H,vector<double> U){
	std::cout << H << "\n";
	vector<double> val2,rhs2,sol2;
	vector<int> col2,ptr2;
	//Create matrix that is a solution of the homogenous poisson problem;
	poisson(N,ptr2,col2,val2,rhs2,H);

	for (int i = 0; i < rhs2.size(); ++i) {
			sol2.push_back(0.0);// initialization of the solution vector
			}
	//if N<4 algorithm won't work anymore and N needs to be even
	if (N%2 == 0 && N!=4){
		sol2 = GS(iter,ptr2,col2,val2,U,sol2);
		vector<double> mult =crsVectMult(ptr2,col2,val2,sol2);

		mult = vectorSubstract(U,mult);
		mult = coarsenVec(N,mult);
		U = recursive(iter,N/2,H*2,mult);
		sol2 = vectorAdd(U,sol2);
	}
	U = interpolateVec(N*2,sol2);
	return U;
}

int main(){
	std::vector<int> ptr;
	std::vector<int> col;
	std::vector<double> val;
	std::vector<double> rhs;
	std::vector<double> realsol,sol,sol3,sol4;

	/*
	 * VARIABLES:
	 * N = size poisson problem (HAS TO BE A MULTIPLE OF 2 AND BIGGER OR EQUAL TO 4)
	 * iter = amount of iterations every amg step
	 *
	 */

	int N=128;
	int iter = 6;
	double H = 1.0/(N+1);
	//Create matrix that is a solution of the homogenous poisson problem;
	poisson(N,ptr,col,val,rhs,H);
	for (int i = 0; i < rhs.size(); ++i) {
		    sol.push_back(0);// initialization of the solution vector
		    }
	realsol = sol;
	sol3= sol;
	//Create solution vector with a lot of gs iterations to compare for error calculation.
	realsol = GS(5000,ptr,col,val,rhs,sol);
	//start clock to check time it takes to do algorithm
	std::clock_t start;
	double duration,duration2;

	start = std::clock();
	//Do "iter" gs iterations to smooth the problem
	sol = GS(iter,ptr,col,val,rhs,sol);
	//Calculate Uh
	vector<double> mult =crsVectMult(ptr,col,val,sol);
	//Calculate residual
	mult = vectorSubstract(rhs,mult);
	//project residual on coarser matrix
	mult = coarsenVec(N,mult);
	//start recursive algorithm
	mult = recursive(iter,N/2,H*2,mult);
	//add E1 to Uh
	sol = vectorAdd(mult,sol);
	//do some post smoothing iterations
	sol = GS(iter,ptr,col,val,rhs,sol);

	//end clock for amg algorithm
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

	sol3 = GS(3*iter,ptr,col,val,rhs,sol3);
	//end clock for normal gauss seidel to compare
	duration2 = (( std::clock() - start ) / (double) CLOCKS_PER_SEC)- duration;
	double errorNorm= norm(vectorSubstract(realsol,sol3))/norm(realsol);
	double errorNorm2= norm(vectorSubstract(realsol,sol))/norm(realsol);
	std::cout <<"norm GS:"<< errorNorm << "\n";
	std::cout <<"norm amg:"<< errorNorm2 << "\n";
	std::cout <<"duration amg:"<< duration << "\n";
	std::cout <<"duration GS:"<< duration2 << "\n";
	/*for (std::vector<double>::const_iterator i = sol.begin(); i != sol.end(); ++i){
						    std::cout << *i<< ' ';}
							std::cout << '\n';*/

	return 1;
}





