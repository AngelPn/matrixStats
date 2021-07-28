#include <Rdefines.h>
#include "000.types.h"
#include "000.utils.h"

/*
Native API (dynamically generated via macros):
 
double mean2_int(int *x, R_xlen_t nx, R_xlen_t *idxs, R_xlen_t nidxs, int narm, int refine)
double mean2_dbl(double *x, R_xlen_t nx, R_xlen_t *idxs, R_xlen_t nidxs, int narm, int refine)
*/

#define METHOD mean2
#define RETURN_TYPE double
#define ARGUMENTS_LIST X_C_TYPE *x, R_xlen_t nx, R_xlen_t *idxs, R_xlen_t nidxs, int narm, int refine

#define X_TYPE 'i'
#include "000.templates-gen-vector.h"
#define X_TYPE 'r'
#include "000.templates-gen-vector.h"
