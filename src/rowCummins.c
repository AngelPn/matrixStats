/***************************************************************************
 Public methods:
 SEXP rowCummins(SEXP x, ...)
 SEXP colCummins(SEXP x, ...)

 Authors: Henrik Bengtsson

 Copyright Henrik Bengtsson, 2014
 **************************************************************************/
#include <Rdefines.h>
#include "000.types.h"
#include "rowCummins_lowlevel.h"

SEXP rowCummins(SEXP x, SEXP dim, SEXP rows, SEXP cols, SEXP byRow) {
  int byrow;
  SEXP ans = NILSXP;
  R_xlen_t nrow, ncol;

  /* Argument 'x' and 'dim': */
  PROTECT(dim = coerceVector(dim, INTSXP));
  assertArgMatrix(x, dim, (R_TYPE_INT | R_TYPE_REAL), "x");
  nrow = asR_xlen_t(dim, 0);
  ncol = asR_xlen_t(dim, 1);

  /* Argument 'rows' and 'cols': */
  R_xlen_t nrows, ncols;
  int rowsType, colsType;
  R_xlen_t *crows = validateIndices(rows, nrow, 0, &nrows, &rowsType);
  R_xlen_t *ccols = validateIndices(cols, ncol, 0, &ncols, &colsType);

  /* Argument 'byRow': */
  byrow = asLogical(byRow);

  /* Double matrices are more common to use. */
  if (isReal(x)) {
    PROTECT(ans = allocMatrix(REALSXP, nrows, ncols));
    rowCummins_dbl(REAL(x), nrow, ncol, crows, nrows, ccols, ncols, byrow, REAL(ans));
    UNPROTECT(1);
  } else if (isInteger(x)) {
    PROTECT(ans = allocMatrix(INTSXP, nrows, ncols));
    rowCummins_int(INTEGER(x), nrow, ncol, crows, nrows, ccols, ncols, byrow, INTEGER(ans));
    UNPROTECT(1);
  }
  UNPROTECT(1); /* PROTECT(dim = ...) */

  return(ans);
} /* rowCummins() */

#undef COMP
#undef METHOD


/***************************************************************************
 HISTORY:
 2015-06-07 [DJ]
  o Supported subsetted computation.
 2014-11-26 [HB]
 o Created from rowVars.c.
 **************************************************************************/
