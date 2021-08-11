#include "naming.h"

void setNames(SEXP vec/*Answer vector*/, SEXP namesVec, R_xlen_t length, R_xlen_t *subscripts) {

  if (length == 0) {
    /* Zero-length names attribute? Keep behavior same as base R function */
    return;
  }
  if (subscripts == NULL) { 
    namesgets(vec, namesVec);
  } else {
    SEXP ansNames = PROTECT(allocVector(STRSXP, length));
    R_xlen_t thisIdx;            
    for (R_xlen_t i = 0; i < length; i++) {
      thisIdx = subscripts[i];
      if (thisIdx == NA_R_XLEN_T) {                                                   
        SET_STRING_ELT(ansNames, i, NA_STRING);                                       
      }                                                                             
      else {                                                                         
        SEXP eltElement = STRING_ELT(namesVec, thisIdx);                  
        SET_STRING_ELT(ansNames, i, eltElement);                                      
      }                                                                             
    }
    namesgets(vec, ansNames);                                                          
    UNPROTECT(1);    
  }
}


void setDimnames(SEXP mat/*Answer matrix*/, SEXP rownames, SEXP colnames, R_xlen_t nrows, R_xlen_t *crows, R_xlen_t ncols, R_xlen_t *ccols) {

  SEXP ansDimnames = PROTECT(allocVector(VECSXP, 2));
  
  if (nrows == 0 || rownames == R_NilValue) {
    SET_VECTOR_ELT(ansDimnames, 0, R_NilValue);
  } else if (crows == NULL) {
    SET_VECTOR_ELT(ansDimnames, 0, rownames);
  } else {
    SEXP ansRownames = PROTECT(allocVector(STRSXP, nrows));
    R_xlen_t thisIdx;            
    for (R_xlen_t i = 0; i < nrows; i++) {
      thisIdx = crows[i];
      if (thisIdx == NA_R_XLEN_T) {                                                   
        SET_STRING_ELT(ansRownames, i, NA_STRING);                                
      }                                                                             
      else {                                                                         
        SEXP eltElement = STRING_ELT(rownames, thisIdx);                  
        SET_STRING_ELT(ansRownames, i, eltElement);                                      
      }                                                                             
    }
    SET_VECTOR_ELT(ansDimnames, 0, ansRownames);
    UNPROTECT(1);
  }
  
  if (ncols == 0 || colnames == R_NilValue) {
    SET_VECTOR_ELT(ansDimnames, 1, R_NilValue);
  } else if (ccols == NULL) {
    SET_VECTOR_ELT(ansDimnames, 1, colnames);
  } else {
    if (colnames != R_NilValue) {
      SEXP ansColnames = PROTECT(allocVector(STRSXP, ncols));
      R_xlen_t thisIdx;            
      for (R_xlen_t i = 0; i < ncols; i++) {
        thisIdx = ccols[i];
        if (thisIdx == NA_R_XLEN_T) {                                                   
          SET_STRING_ELT(ansColnames, i, NA_STRING);                                       
        }                                                                             
        else {                                                                  
          SEXP eltElement = STRING_ELT(colnames, thisIdx);                  
          SET_STRING_ELT(ansColnames, i, eltElement);                                      
        }                                                                             
      }
      SET_VECTOR_ELT(ansDimnames, 1, ansColnames);
      UNPROTECT(1);           
    }
  }
  
  dimnamesgets(mat, ansDimnames);
  UNPROTECT(1); 
}
