/*
 * GaussSeidel.h
 *
 *  Created on: Jul 11, 2016
 *      Author: Jean23
 */

#ifndef SRC_GAUSSSEIDEL_H_
#define SRC_GAUSSSEIDEL_H_


//#include <stdio.h>
//#include <iostream>
//#include <fstream>
#include <vector>
using namespace std;


vector<double> GS(int iterations,
                  std::vector<int>    &ptr,
                  std::vector<int>    &col,
                  std::vector<double> &val,
                  std::vector<double> &rhs,
                  std::vector<double> oldsol);



#endif /* SRC_GAUSSSEIDEL_H_ */
