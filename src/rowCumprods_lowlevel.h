#include <Rdefines.h>
#include "000.types.h"
#include "000.utils.h"

/*
Native API (dynamically generated via macros):
 
void rowCumprods_int(int *x, R_xlen_t nrow, R_xlen_t ncol, R_xlen_t *rows, R_xlen_t Rf_nrows, R_xlen_t *cols, R_xlen_t Rf_ncols, int byrow, int *ans)
void rowCumprods_dbl(double *x, R_xlen_t nrow, R_xlen_t ncol, R_xlen_t *rows, R_xlen_t Rf_nrows, R_xlen_t *cols, R_xlen_t Rf_ncols, int byrow, int *ans)
*/

#define METHOD rowCumprods
#define RETURN_TYPE void
#define ARGUMENTS_LIST X_C_TYPE *x, R_xlen_t nrow, R_xlen_t ncol, R_xlen_t *rows, R_xlen_t nrows, R_xlen_t *cols, R_xlen_t ncols, int byrow, ANS_C_TYPE *ans

#define X_TYPE 'i'
#include "000.templates-gen-matrix.h"
#define X_TYPE 'r'
#include "000.templates-gen-matrix.h"
