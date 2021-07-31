#include <Rdefines.h>
#include "000.types.h"
#include "000.utils.h"
#include <R_ext/Error.h>

/*
Native API (dynamically generated via macros):
 
double weightedMedian_int(int *x, R_xlen_t nx, double *w, R_xlen_t *idxs, R_xlen_t nidxs, int narm, int interpolate, int ties)
double weightedMedian_dbl(double *x, R_xlen_t nx, double *w, R_xlen_t *idxs, R_xlen_t nidxs, int narm, int interpolate, int ties)
*/

#define METHOD weightedMedian
#define RETURN_TYPE double
#define ARGUMENTS_LIST X_C_TYPE *x, R_xlen_t nx, double *w, R_xlen_t *idxs, R_xlen_t nidxs, int narm, int interpolate, int ties

#define X_TYPE 'i'
#include "000.templates-gen-vector.h"

#define X_TYPE 'r'
#include "000.templates-gen-vector.h"
