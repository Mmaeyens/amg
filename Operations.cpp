/*
 * Operations.cpp
 *
 *  Created on: Jul 11, 2016
 *      Author: Jean23
 */

#include "Operations.h"

vector<double> crsVectTransposeMult(
	    std::vector<int>    &ptr,
	    std::vector<int>    &col,
	    std::vector<double> &val,
	    std::vector<double> &vector)
{
	std::vector<double> res;

	int size= (ptr.size())*(ptr.size());
	res.reserve(size);
	for (int i = 0; i < size; ++i) {
		res.push_back(0.0);; // initialization of the solution vector
	}
	int k = 0;
	for (int i = 0; i < vector.size(); ++i) {
	  for (int j = ptr[i]; j < ptr[i+1]; ++j) {
	    res[col[k]] = res[col[k]] + val[k]*4*vector[i];
	    ++k;
	  }
	}
	return res;
}

vector<double> crsVectMult(
	    std::vector<int>    &ptr,
	    std::vector<int>    &col,
	    std::vector<double> &val,
	    std::vector<double> &vector
		)
{
	std::vector<double> res;
	res.reserve(ptr.size());
	for (int i = 0; i < ptr.size()-1; ++i) {
	  res.push_back(0.0); // initialization of the solution vector
	}

	for (int i = 0; i < ptr.size()-1; ++i) {
	  for (int j = ptr[i]; j < ptr[i+1]; ++j) {
		  int k = j ;
	    res[i] = res[i] + val[k]*vector[col[k]];
	  }
	}
	return res;
}

vector<double> vectorSubstract(vector<double> x,vector<double> y){
	for (int i = 0; i < x.size();++i){
		x[i]=x[i] - y[i];
	}
	return x;
}

double norm(vector<double> input){
	double result =0;
	for (int i =0; i<input.size();++i){
		result += input[i]*input[i];
	}
	result = sqrt(result);
	return result;
}

vector<double> vectorAdd(vector<double> x,vector<double> y){
	for (int i = 0; i < x.size();++i){
		x[i]=x[i] + y[i];
	}
	return x;
}

