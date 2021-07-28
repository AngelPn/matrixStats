#include <Rdefines.h>
#include <R_ext/Constants.h>
#include "000.types.h"
#include "000.utils.h"

/*
Native API (dynamically generated via macros):
 
double sum2_int(int *x, R_xlen_t nx, R_xlen_t *idxs, R_xlen_t nidxs, int narm)
double sum2_dbl(double *x, R_xlen_t nx, R_xlen_t *idxs, R_xlen_t nidxs, int narm)
*/

#define METHOD sum2
#define RETURN_TYPE double
#define ARGUMENTS_LIST X_C_TYPE *x, R_xlen_t nx, R_xlen_t *idxs, R_xlen_t nidxs, int narm

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
