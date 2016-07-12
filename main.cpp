/*
 * main.cpp
 *
 *  Created on: Jul 11, 2016
 *      Author: Jean23
 */

#include "Poisson.h"
#include "Coarsening.h"
#include "GaussSeidel.h"
#include "Operations.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>


int main(){
	std::vector<int> ptr,ptr2;
	std::vector<int> col,col2;
	std::vector<double> val,val2;
	std::vector<double> rhs,rhs2;
	std::vector<int> ptrCoarse;
	std::vector<int> colCoarse;
	std::vector<double> valCoarse;
	std::vector<double> realsol,sol2;
	int n= 17;
	//Create matrix that is a solution of the poisson problem with boudary condition 0;
	poisson(n,ptr,col,val,rhs);
	std::vector<double> sol1;
	for (int i = 0; i < rhs.size(); ++i) {
	    	  sol1.push_back(0);// initialization of the solution vector
	    	}
	realsol = sol1;
	//Create solution vector with a lot of gs iterations to compare.
	realsol = GS(20,ptr,col,val,rhs,sol1);

	/*for (std::vector<double>::const_iterator i = realsol.begin(); i != realsol.end(); ++i){
			std::cout << *i<< ' ';}
			std::cout << '\n';*/

	//Do 5 gs iterations to coarsen the problem
	sol1 = GS(5,ptr,col,val,rhs,sol1);
	/*for (std::vector<double>::const_iterator i = sol1.begin(); i != sol1.end(); ++i){
				std::cout << *i<< ' ';}
				std::cout << '\n';*/

	//calculate residual
	vector<double> mult =crsVectMult(ptr,col,val,sol1);
	vector<double> residual = vectorSubstract(rhs,mult);

	//create reduction vector
	createCoarse(n,ptrCoarse,colCoarse,valCoarse);

	//Calculate new residual with reduction vector
	residual = crsVectMult(ptrCoarse,colCoarse,valCoarse,residual);
	/*for (std::vector<double>::const_iterator i = residual.begin(); i != residual.end(); ++i){
			    std::cout << *i<< ' ';}
				std::cout << '\n';*/

	//Create reduced vector of poisson problen
	poisson((n+1)/2,ptr2,col2,val2,rhs2);
	/*for (int i = 0; i < rhs2.size(); ++i) {
		    sol2.push_back(0);// initialization of the solution vector
		    }*/

	//do 5 Gs iterations on current solution
	sol2 = GS(5,ptr2,col2,val2,residual,sol2);

	//interpolate solution vector
	sol2 = crsVectTransposeMult(ptrCoarse,colCoarse,valCoarse,sol2);
	/*for (std::vector<double>::const_iterator i = sol2.begin(); i != sol2.end(); ++i){
						    std::cout << *i<< ' ';}
							std::cout << '\n';*/

	//sum the 2 solution vectors
	std::vector<double> sol = vectorAdd(sol1,sol2);
	/*for (std::vector<double>::const_iterator i = sol.begin(); i != sol.end(); ++i){
					    std::cout << *i<< ' ';}
						std::cout << '\n';*/

	//a few more  gs iterations starting from the current solution
	sol = GS(5,ptr,col,val,rhs,sol);
	/*for (std::vector<double>::const_iterator i = sol.begin(); i != sol.end(); ++i){
						    std::cout << *i<< ' ';}
							std::cout << '\n';*/
	return 1;
}


