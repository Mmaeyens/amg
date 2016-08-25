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
	int init = 0;
	int size= (ptr.size())*(ptr.size());
	res.reserve(size);
	res.push_back(0.0);
	int k = 0;
	for (int i = 0; i < vector.size(); ++i) {
	  for (int j = ptr[i]; j < ptr[i+1]; ++j) {
		while (col[k] > init){
			init +=1;
			res.push_back(0.0);
		}
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
	std::vector<double> res,vec;
	vec = vector;
	res.reserve(ptr.size());
	for (int i = 0; i < ptr.size()-1; ++i) {
	  res.push_back(0.0); // initialization of the solution vector
	}

	for (int i = 0; i < ptr.size()-1; ++i) {
	  for (int j = ptr[i]; j < ptr[i+1]; ++j) {
		  res[i] = res[i] + val[j]*vec[col[j]];
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

vector<double> coarsenVec(int n,vector<double> in){
	vector <double> hello;
	for (int i = 0; i < in.size()/4; ++i) {
		  hello.push_back(0.0); // initialization of the solution vector
		}
	for (int i=0; i < n/2;i++){
		int I = 2*i;
		for (int j=0; j <n/2;j++){
			int J = 2*j;
			hello[j + i*(n/2)]=0.25*(in[J + I*n] + in[J+1 + I*n] + in[J + (I+1)*n] + in[J +1 + (I+1)*n]);
		}
	}
	return hello;
}

vector<double> interpolateVec(int n,vector<double> in){
	vector <double> hello;
	for (int i = 0; i < in.size()*4; ++i) {
		  hello.push_back(0.0); // initialization of the solution vector
		}
	for (int i=0; i < n/2;i++){
		int I = 2*i;
		for (int j=0; j <n/2;j++){
			int J = 2*j;
			hello[J + I*(n)]=hello[J + 1 + I*(n)]= hello[J + (I+1)*(n)]=hello[J+1 + (I+1)*(n)]= in[j + i*(n/2)];
		}
	}
	return hello;
}


