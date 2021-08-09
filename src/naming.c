#include "naming.h"

void setNames(SEXP vec/* Answer vector*/, SEXP namesVec, R_xlen_t length, R_xlen_t *subscripts) {

  if (length == 0) {
    /* If the targets has length zero, we skip the entire process
     * which also is the behavior of base::rowSums
     */
    return;
  }
  SEXP ansNames = PROTECT(allocVector(STRSXP, length));
  if (subscripts == NULL) { 
    ansNames = namesVec;                                                  
  }                                                                                 
  else {
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
  }
  namesgets(vec, ansNames);                                                          
  UNPROTECT(1);
}
