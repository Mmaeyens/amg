/*
 * GaussSeidel.cpp
 *
 *  Created on: Jul 11, 2016
 *      Author: Jean23
 */


#include "GaussSeidel.h"


vector<double> GS(int iterations,
                               std::vector<int>    &ptr,
                               std::vector<int>    &col,
                               std::vector<double> &val,
                               std::vector<double> &rhs,
                               std::vector<double> oldsol)
{
    vector<double> residual = rhs;
    vector<double> newsol=rhs;
    for (int i = 0; i < rhs.size(); ++i) {
        newsol[i] =0.0;// initialization of the solution vector
    }
    for (int z=0;z<iterations;++z){
        for(int i = 0; i < rhs.size(); ++i) {
            double sum1 = 0.0; // first sum coef
            double sum2 = 0.0;
            int diag = 4;
            int start = ptr[i];
            int end = ptr[i+1];
            for(;start < end; ++start){

                int j=start;
                if(col[j] < i){
                    sum1 += val[j] * newsol[col[j]];

                }

                else{
                    break;
                }
            }
            if (col[start]== i){
                diag=val[start];
            }
            for(;start < end; ++start){

                int j=start;
                if(col[j]  > i){
                    sum2 += val[j] * oldsol[col[j]];
                }
            }
            newsol[i] = (rhs[i] - sum1 - sum2)/(diag);

        }
        oldsol = newsol;
    }
    return oldsol;
}

