/***************************************************************************
 Public methods:
 SEXP validate(SEXP idxs, SEXP maxIdx, SEXP allowOutOfBound)

 **************************************************************************/
#include <string.h>
#include "validateIndices_lowlevel.h"


/** idxs must not be NULL, which should be checked before calling this function. **/
R_xlen_t* validateIndices_lgl(int *idxs, R_xlen_t nidxs, R_xlen_t maxIdx, int allowOutOfBound, R_xlen_t *ansNidxs, int *subsettedType, int *hasna) {
  R_xlen_t ii, jj, kk;
  R_xlen_t count1 = 0, count2 = 0;

  // set default as no NA.
  *hasna = FALSE;
  // set default type as SUBSETTED_INTEGER
  *subsettedType = SUBSETTED_INTEGER;
  if (nidxs == 0) {
    *ansNidxs = 0;
    return NULL;
  }

  if (nidxs > maxIdx) {
    if (!allowOutOfBound) {
      error("logical subscript too long");
    }
    *hasna = TRUE; // out-of-bound index is NA

    // count how many idx items
    for (ii = 0; ii < maxIdx; ++ ii) {
      if (idxs[ii]) { // TRUE or NA
        ++ count1;
        if (ii + 1 > R_INT_MAX) *subsettedType = SUBSETTED_REAL;
      }
    }
    for (; ii < nidxs; ++ ii) {
      if (idxs[ii]) { // TRUE or NA
        ++ count2;
      }
    }
    *ansNidxs = count1 + count2;
    
    R_xlen_t *ans = (R_xlen_t *) R_alloc(*ansNidxs, sizeof(R_xlen_t));
    FILL_VALIDATED_ANS(maxIdx, idxs[ii], idxs[ii] == NA_LOGICAL ? NA_R_XLEN_T : ii);
    for (ii = count1; ii < *ansNidxs; ++ ii) {
      ans[ii] = NA_R_XLEN_T;
    }
    return ans;
  }
  // nidxs <= maxIdx
  R_xlen_t naCount = 0;
  R_xlen_t lastIndex = 0;
  R_xlen_t lastPartNum = maxIdx % nidxs;
  for (ii = 0; ii < lastPartNum; ++ ii) {
    if (idxs[ii]) { // TRUE or NA
      if (idxs[ii] == NA_LOGICAL) ++ naCount;
      else lastIndex = ii + 1;
      ++ count1;
    }
  }
  if (lastIndex > 0 && maxIdx - lastPartNum + lastIndex > R_INT_MAX)
    *subsettedType = SUBSETTED_REAL;

  lastIndex = 0;
  for (; ii < nidxs; ++ ii) {
    if (idxs[ii]) { // TRUE or NA
      if (idxs[ii] == NA_LOGICAL) ++ naCount;
      else lastIndex = ii + 1;
      ++ count2;
    }
  }
  R_xlen_t count = count1 + count2;
  if (lastIndex > 0 && maxIdx - lastPartNum - count + lastIndex > R_INT_MAX)
    *subsettedType = SUBSETTED_REAL;


  if (naCount == 0 && count == nidxs) { // All True
    *ansNidxs = maxIdx;
    *subsettedType = SUBSETTED_ALL;
    // return NULL;
    R_xlen_t *ans = (R_xlen_t *) R_alloc(maxIdx, sizeof(R_xlen_t));
    FILL_VALIDATED_ANS(maxIdx, 1, ii);
    return ans;
  }
  if (naCount) *hasna = TRUE;

  *ansNidxs = maxIdx / nidxs * count + count1;
  R_xlen_t *ans = (R_xlen_t *) R_alloc(*ansNidxs, sizeof(R_xlen_t));
  FILL_VALIDATED_ANS(nidxs, idxs[ii], idxs[ii] == NA_LOGICAL ? NA_R_XLEN_T : ii);
  
  for (ii = count, kk = nidxs; kk+nidxs <= maxIdx; kk += nidxs, ii += count) {
    for (jj = 0; jj < count; ++ jj) {
      ans[ii+jj] = ans[jj] == NA_R_XLEN_T ? NA_R_XLEN_T : ans[jj] + kk;
    }
  }
  for (jj = 0; jj < count1; ++ jj) {
    ans[ii+jj] = ans[jj] == NA_R_XLEN_T ? NA_R_XLEN_T : ans[jj] + kk;
  }
  return ans;
}


/*************************************************************
  * The most important function which is widely called.
  * If `idxs` is NULL, NULL will be returned, which indicates selecting.
  * the whole to-be-computed vector(matrix).
  * `maxIdx` is the to-be-computed vector(matrix)'s length (rows/cols).
  * `allowOutOfBound` indicates whether to allow positve out of bound indexing.
  * `ansNidxs` is used for returning the new idxs array's length.
  * `subsettedType` is used for returning the new idxs array's datatype.
  * `hasna` is TRUE, if NA is included in returned result.
  ************************************************************/
R_xlen_t *validateIndices(SEXP idxs, R_xlen_t maxIdx, int allowOutOfBound, R_xlen_t *ansNidxs, int *subsettedType) {
  int hasna;
  return validateIndicesCheckNA(idxs, maxIdx, allowOutOfBound, ansNidxs, subsettedType, &hasna);
}


R_xlen_t *validateIndicesCheckNA(SEXP idxs, R_xlen_t maxIdx, int allowOutOfBound, R_xlen_t *ansNidxs, int *subsettedType, int *hasna) {
  R_xlen_t nidxs = xlength(idxs);
  int mode = TYPEOF(idxs);
  // Set no NA as default.
  *hasna = FALSE;
  switch (mode) {
    case INTSXP:
      return validateIndices_int(INTEGER(idxs), nidxs, maxIdx, allowOutOfBound, ansNidxs, subsettedType, hasna);
    case REALSXP:
      return validateIndices_dbl(REAL(idxs), nidxs, maxIdx, allowOutOfBound, ansNidxs, subsettedType, hasna);
    case LGLSXP:
      return validateIndices_lgl(LOGICAL(idxs), nidxs, maxIdx, allowOutOfBound, ansNidxs, subsettedType, hasna);
    case NILSXP:
      *subsettedType = SUBSETTED_ALL;
      *ansNidxs = maxIdx;
      //return NULL;
      R_xlen_t *ans = (R_xlen_t *) R_alloc(maxIdx, sizeof(R_xlen_t));
      for (R_xlen_t ii = 0; ii < maxIdx; ii++) {
        ans[ii] = ii;
      }
      return ans;
    default:
      error("idxs can only be integer, numeric, or logical.");
  }
  return NULL; // useless sentence. won't be executed.
}



/*************************************************************
  * This function can be called by R.
  * If `idxs` is NULL, NULL will be returned, which indicates selecting.
  * the whole to-be-computed vector(matrix).
  * `maxIdx` is the to-be-computed vector(matrix)'s length (rows/cols).
  * `allowOutOfBound` indicates whether to allow positve out of bound indexing.
  ************************************************************/
SEXP validate(SEXP idxs, SEXP maxIdx, SEXP allowOutOfBound) {
  SEXP ans;
  R_xlen_t ansNidxs;
  int subsettedType;
  R_xlen_t cmaxIdx = asR_xlen_t(maxIdx, 0);
  R_xlen_t nidxs = xlength(idxs);
  int callowOutOfBound = asLogicalNoNA(allowOutOfBound, "allowOutOfBound");
  R_xlen_t *cidxs;

  // Set no NA as default.
  int hasna = FALSE;
  int mode = TYPEOF(idxs);
  switch (mode) {
    case INTSXP:
      cidxs = validateIndices_int(INTEGER(idxs), nidxs, cmaxIdx, callowOutOfBound, &ansNidxs, &subsettedType, &hasna);
      break;
    case REALSXP:
      cidxs = validateIndices_dbl(REAL(idxs), nidxs, cmaxIdx, callowOutOfBound, &ansNidxs, &subsettedType, &hasna);
      break;
    case LGLSXP:
      cidxs = validateIndices_lgl(LOGICAL(idxs), nidxs, cmaxIdx, callowOutOfBound, &ansNidxs, &subsettedType, &hasna);
      break;
    case NILSXP:
      return R_NilValue;
    default:
      error("idxs can only be integer, numeric, or logical.");
  }
  if (subsettedType == SUBSETTED_ALL) {
    return R_NilValue;
  }

  if (subsettedType == SUBSETTED_INTEGER) {
    ans = PROTECT(allocVector(INTSXP, ansNidxs));
    // Copy from cidxs to ans and coerce to int    
    int *ans_ptr = INTEGER(ans);
    for(R_xlen_t i = 0; i < cmaxIdx; i++) {
      ans_ptr[i] = cidxs[i] == NA_R_XLEN_T ? NA_INTEGER : (int) cidxs[i];
    }
    UNPROTECT(1);
    return ans;
  }
  // else: subsettedType == SUBSETTED_REAL
  ans = PROTECT(allocVector(REALSXP, ansNidxs));
  // Copy from cidxs to ans and coerce to double
  double *ans_ptr = REAL(ans);
  for(R_xlen_t i = 0; i < cmaxIdx; i++){
    ans_ptr[i] = cidxs[i] == NA_R_XLEN_T ? NA_REAL : (double) cidxs[i];
  }
  UNPROTECT(1);
  return ans;
}
