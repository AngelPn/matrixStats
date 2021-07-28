#include <Rdefines.h>
#include "000.types.h"
#include "000.utils.h"

/*
Native API (dynamically generated via macros):
 
void signTabulate_int(int *x, R_xlen_t nx, R_xlen_t *idxs, R_xlen_t nidxs, double *ans)
void signTabulate_dbl(double *x, R_xlen_t nx, R_xlen_t *idxs, R_xlen_t nidxs, double *ans)
*/

#define METHOD signTabulate
#define RETURN_TYPE void
#define ARGUMENTS_LIST X_C_TYPE *x, R_xlen_t nx, R_xlen_t *idxs, R_xlen_t nidxs, double *ans

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
