/***************************************************************************
 Public methods:
 SEXP rowLogSumExps(SEXP lx, SEXP dim, SEXP rows, SEXP cols, SEXP naRm, SEXP hasNA, SEXP byRow, SEXP useNames)

 Authors: Henrik Bengtsson

 Copyright Henrik Bengtsson, 2013-2014
 **************************************************************************/
#include <Rdefines.h>
#include <R.h>
#include <Rinternals.h>
#include <stdio.h>
#include "000.types.h"
#include "rowLogSumExp_lowlevel.h"

void setNames(SEXP vec/* Answer vector*/,SEXP namesVec,R_xlen_t length,void *subscripts,int idxType);

SEXP rowLogSumExps(SEXP lx, SEXP dim, SEXP rows, SEXP cols, SEXP naRm, SEXP hasNA, SEXP byRow, SEXP useNames) {
  SEXP ans;
  int narm, hasna, byrow, usenames;
  R_xlen_t nrow, ncol;

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
  usenames = asLogical(useNames);  

  if (usenames){

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

          //namesgets(ans, getAttrib(namesVector, R_NamesSymbol));
          setAttrib(ans, R_NamesSymbol, getAttrib(namesVector, R_NamesSymbol));
          //setNames(ans, namesVector, ncols, ccols, colsType);
        }
      }      
    }

  }

  UNPROTECT(1); /* ans = PROTECT(...) */

  return(ans);
} /* rowLogSumExps() */



void setNames(SEXP vec/* Answer vector*/,SEXP namesVec, R_xlen_t length, void *subscripts, int idxType){

  if(length == 0){
    /* If the targets has length zero, we skip the entire process
    * which also is the behavior of base::rowSums
    */
    return;
  }

  SEXP ansNames;                                                                    
  ansNames = PROTECT(allocVector(STRSXP, length));

  if(idxType == SUBSETTED_ALL){                                                   
    ansNames = namesVec;                                                  
  }                                                                                 
  else if(idxType == SUBSETTED_INTEGER){
    Rprintf("Using integer mapping with %d indecies",length);

    int *typedIdx = subscripts;                                                          
    R_xlen_t thisIdx;           

    for(R_xlen_t i = 0; i < length; i++){
      thisIdx = (typedIdx[i] == NA_INTEGER) ? NA_R_XLEN_T : (R_xlen_t)typedIdx[i]-1;
      Rprintf("i=%d,Idx=%d",i,thisIdx);
      if(thisIdx == NA_R_XLEN_T){                                                   
        SET_STRING_ELT(ansNames, i, NA_STRING);                                       
      }                                                                             
      else{                                                                         
        SEXP eltElement = STRING_ELT(namesVec, thisIdx);                  
        SET_STRING_ELT(ansNames, i, eltElement);                                      
      }                                                                             
    }                                                                               
  }                                                                                 
  else if(idxType == SUBSETTED_REAL){
    Rprintf("Using floating point mapping");

    double *typedIdx = subscripts;                                                       
    R_xlen_t thisIdx;                      

    for(R_xlen_t i = 0; i < length; i++){
      Rprintf("index=%f",typedIdx);
      thisIdx = ISNAN(typedIdx[i]) ? NA_R_XLEN_T : (R_xlen_t)typedIdx[i]-1;
      Rprintf("i=%d,Idx=%d",i,thisIdx);
      if(thisIdx == NA_R_XLEN_T){                                                   
        SET_STRING_ELT(ansNames,i,NA_STRING);                                       
      }                                                                             
      else{                                                                         
        SEXP eltElement = STRING_ELT(namesVec, thisIdx);                  
        SET_STRING_ELT(ansNames,i,eltElement);                                      
      }                                                                             
    }                                                                               
  }                                                                                 
  else{                                                                             
    error("Invalid index type");                                                    
  }                                                                                 
  namesgets(vec, ansNames);                                                          
  UNPROTECT(1);
}


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
