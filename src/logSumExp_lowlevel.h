#include <Rdefines.h>
#include <Rmath.h>
#include "000.utils.h"


/*
Native API (dynamically generated via macros):
 
double logSumExp_double(double *x, R_xlen_t *idxs, R_xlen_t nidxs, int narm, int hasna, R_xlen_t by, double *xx)
*/

#define METHOD logSumExp
#define METHOD_NAME logSumExp_double
#define RETURN_TYPE double
#define ARGUMENTS_LIST double *x, R_xlen_t *idxs, R_xlen_t nidxs, int narm, int hasna, R_xlen_t by, double *xx

#include "000.templates-gen-vector.h"
