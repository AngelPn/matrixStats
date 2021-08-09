#ifndef NAMING_H
#define NAMING_H

#include <R.h>
#include <Rinternals.h>
#include "000.types.h"

void setNames(SEXP vec/* Answer vector*/, SEXP namesVec, R_xlen_t length, R_xlen_t *subscripts);

#endif /* NAMING_H */