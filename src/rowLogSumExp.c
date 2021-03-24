/***************************************************************************
 Public methods:
 SEXP rowLogSumExps(SEXP lx, SEXP dim, SEXP rows, SEXP cols, SEXP naRm, SEXP hasNA, SEXP byRow, SEXP useNames)

 Authors: Henrik Bengtsson

 Copyright Henrik Bengtsson, 2013-2014
 **************************************************************************/
#include <Rdefines.h>
#include "000.types.h"
#include "rowLogSumExp_lowlevel.h"
#include "naming.h"

SEXP rowLogSumExps(SEXP lx, SEXP dim, SEXP rows, SEXP cols, SEXP naRm, SEXP hasNA, SEXP byRow, SEXP useNames) {
  SEXP ans;
  int narm, hasna, byrow;
  R_xlen_t nrow, ncol;

  PROTECT(lx = coerceVector(lx, REALSXP));
  
  /* Argument 'lx' and 'dim': */
  assertArgMatrix(lx, dim, (R_TYPE_REAL), "lx");
  nrow = asR_xlen_t(dim, 0);
  ncol = asR_xlen_t(dim, 1);

  /* Argument 'naRm': */
  narm = asLogicalNoNA(naRm, "na.rm");

  /* Argument 'hasNA': */
  hasna = asLogicalNoNA(hasNA, "hasNA");

  /* Argument 'rows' and 'cols': */
  R_xlen_t nrows, ncols;
  int rowsType, colsType;
  void *crows = validateIndices(rows, nrow, 0, &nrows, &rowsType);
  void *ccols = validateIndices(cols, ncol, 0, &ncols, &colsType);

  /* Argument 'byRow': */
  byrow = asLogical(byRow);

  if (byrow) {
    ans = PROTECT(allocVector(REALSXP, nrows));
    rowLogSumExps_double[rowsType](REAL(lx), nrow, ncol, crows, nrows, rowsType, ccols, ncols, colsType, narm, hasna, 1, REAL(ans));
  } else {
    ans = PROTECT(allocVector(REALSXP, ncols));
    rowLogSumExps_double[colsType](REAL(lx), nrow, ncol, crows, nrows, rowsType, ccols, ncols, colsType, narm, hasna, 0, REAL(ans)); 
  }

  /* Argument 'useNames': */
  PROTECT(useNames = coerceVector(useNames, LGLSXP));
  if (asLogical(useNames)){

    if (!byrow){
      SEXP matrixDimnames = getAttrib(lx, R_DimNamesSymbol);
      /* We check whether the result has a natural naming by the dimnames of the
      * input and set the names of the result to these names if it is
      */
      if(matrixDimnames != R_NilValue){
        SEXP namesVector = VECTOR_ELT(matrixDimnames, 1);
        /* We may risk that even though the dimnames attribute is defined,
        * the names for our requested dimension is not available
        */
        if (namesVector != R_NilValue){
          /* The naming vector is available, so we can set the names of the result */
          setNames(ans, namesVector, ncols, ccols, colsType);
        }
      }      
    }

  }

  UNPROTECT(3); /* ans = PROTECT(...), PROTECT(... = coerceVector(...)) */

  return(ans);
} /* rowLogSumExps() */


/***************************************************************************
 HISTORY:
 2015-06-12 [DJ]
  o Supported subsetted computation.
 2013-05-02 [HB]
 o BUG FIX: Incorrectly used ISNAN() on an int variable as caught by the
   'cc' compiler on Solaris.  Reported by Brian Ripley upon CRAN submission.
 2013-04-30 [HB]
 o Created.
 **************************************************************************/
