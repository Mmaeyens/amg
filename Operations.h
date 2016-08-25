/*
 * Operations.h
 *
 *  Created on: Jul 11, 2016
 *      Author: Jean23
 */

#ifndef SRC_OPERATIONS_H_
#define SRC_OPERATIONS_H_


//#include <stdio.h>
//#include <iostream>
//#include <fstream>
#include <vector>
#include <math.h>
using namespace std;

vector<double> crsVectTransposeMult(std::vector<int>    &ptr,
									std::vector<int>    &col,
									std::vector<double> &val,
									std::vector<double> &vector);

vector<double> crsVectMult(std::vector<int>    &ptr,
						   std::vector<int>    &col,
						   std::vector<double> &val,
						   std::vector<double> &vector);

vector<double> vectorSubstract(vector<double> x,
							   vector<double> y);

vector<double> vectorAdd(vector<double> x,
						 vector<double> y);

double norm(vector<double> input);

vector<double> coarsenVec(int n,
							   vector<double> in);

vector<double> interpolateVec(int n,
							   vector<double> in);

#endif /* SRC_OPERATIONS_H_ */
