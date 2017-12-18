/*Authors:
-Jose Miguel Acitores Cortina
-Alberto Soutullo Rendo
3º IDCD UTAD
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <intrin.h>

#include "MatrixUtilities.h"


#ifndef _MULTIPLY_MATRIX_H_
#define _MULTIPLY_MATRIX_H_


typedef struct thread_params_t {
	int	   thread_id;
	float* row;
	float* col;
	float* result;
	int    size;

}thread_params_t;

void* multiplyVector(void* args);
void  multiplyMatrix(Matrix_t* m1, Matrix_t* m2, Matrix_t* mres);

#endif 