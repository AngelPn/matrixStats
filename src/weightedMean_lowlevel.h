#include <Rdefines.h>
#include "000.types.h"
#include "000.utils.h"

/*
Native API (dynamically generated via macros):
 
double weightedMean_int(int *x, R_xlen_t nx, double *w, R_xlen_t *idxs, R_xlen_t nidxs, int narm, int refine)
double weightedMean_dbl(double *x, R_xlen_t nx, double *w, R_xlen_t *idxs, R_xlen_t nidxs, int narm, int refine)
*/

#define METHOD weightedMean
#define RETURN_TYPE double
#define ARGUMENTS_LIST X_C_TYPE *x, R_xlen_t nx, double *w, R_xlen_t *idxs, R_xlen_t nidxs, int narm, int refine

#define X_TYPE 'i'
// #include "000.templates-gen-vector.h"
#include "000.macros.h"
#include METHOD_TEMPLATE_H
RETURN_TYPE METHOD_NAME(ARGUMENTS_LIST);
#include "000.templates-types_undef.h"

#define X_TYPE 'r'
// #include "000.templates-gen-vector.h"
#include "000.macros.h"
#include METHOD_TEMPLATE_H
RETURN_TYPE METHOD_NAME(ARGUMENTS_LIST);
#include "000.templates-types_undef.h"
