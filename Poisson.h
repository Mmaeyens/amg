/*
 * Poisson.h
 *
 *  Created on: Jul 11, 2016
 *      Author: Jean23
 */

#ifndef SRC_POISSON_H_
#define SRC_POISSON_H_


//#include <stdio.h>
//#include <iostream>
//#include <fstream>
#include <vector>


int poisson(int n,
            std::vector<int> &ptr,
            std::vector<int> &col,
            std::vector<double> &val,
            std::vector<double> &rhs);


#endif /* SRC_POISSON_H_ */
