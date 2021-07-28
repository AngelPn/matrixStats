#include <Rdefines.h>
#include "000.types.h"
#include "000.utils.h"

/*
Native API (dynamically generated via macros):
 
void rowCounts_int(int *x, R_xlen_t nrow, R_xlen_t ncol, R_xlen_t *rows, R_xlen_t Rf_nrows, R_xlen_t *cols, R_xlen_t Rf_ncols, int value, int what, int narm, int hasna, int *ans)
void rowCounts_dbl(double *x, R_xlen_t nrow, R_xlen_t ncol, R_xlen_t *rows, R_xlen_t Rf_nrows, R_xlen_t *cols, R_xlen_t Rf_ncols, int value, int what, int narm, int hasna, int *ans)
void rowCounts_lgl(int *x, R_xlen_t nrow, R_xlen_t ncol, R_xlen_t *rows, R_xlen_t Rf_nrows, R_xlen_t *cols, R_xlen_t Rf_ncols, int value, int what, int narm, int hasna, int *ans)
*/

#define METHOD rowCounts
#define RETURN_TYPE void
#define ARGUMENTS_LIST X_C_TYPE *x, R_xlen_t nrow, R_xlen_t ncol, R_xlen_t *rows, R_xlen_t nrows, R_xlen_t *cols, R_xlen_t ncols, X_C_TYPE value, int what, int narm, int hasna, int *ans

#define X_TYPE 'i'
#include "000.templates-gen-matrix.h"
#define X_TYPE 'r'
#include "000.templates-gen-matrix.h"
#define X_TYPE 'l'
#include "000.templates-gen-matrix.h"
