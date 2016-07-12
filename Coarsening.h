/*
 * Coarsening.h
 *
 *  Created on: Jul 11, 2016
 *      Author: Jean23
 */

#ifndef SRC_COARSENING_H_
#define SRC_COARSENING_H_


//#include <stdio.h>
//#include <iostream>
//#include <fstream>
#include <vector>



int createCoarse(int size,
                 std::vector<int>    &ptr,
                 std::vector<int>    &col,
                 std::vector<double> &val);


#endif /* SRC_COARSENING_H_ */
