#include <Rdefines.h>
#include "000.types.h"
#include "000.utils.h"

/*
Native API (dynamically generated via macros):
 
void rowLogSumExps_double(double *x, R_xlen_t nrow, R_xlen_t ncol, R_xlen_t *rows, R_xlen_t Rf_nrows, int rowsType, R_xlen_t *cols, R_xlen_t Rf_ncols, int colsType, int narm, int hasna, R_xlen_t byrow, double *ans)
*/

#define METHOD rowLogSumExp
#define METHOD_NAME rowLogSumExps_double
#define RETURN_TYPE void
#define ARGUMENTS_LIST double *x, R_xlen_t nrow, R_xlen_t ncol, R_xlen_t *rows, R_xlen_t nrows, int rowsType, R_xlen_t *cols, R_xlen_t ncols, int colsType, int narm, int hasna, R_xlen_t byrow, double *ans

// #include "000.templates-gen-vector.h"
#include "000.macros.h"
#include METHOD_TEMPLATE_H
RETURN_TYPE METHOD_NAME(ARGUMENTS_LIST);
#include "000.templates-types_undef.h"
