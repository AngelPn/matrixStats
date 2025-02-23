library("matrixStats")

rowCumsums_R <- function(x, ..., useNames = NA) {
  suppressWarnings({
    y <- t(apply(x, MARGIN = 1L, FUN = cumsum))
  })
  
  # Preserve dimnames attribute?
  dim(y) <- dim(x)
  if (isTRUE(useNames)) {
    dimnames <- dimnames(x)
    if (!is.null(dimnames)) dimnames(y) <- dimnames      
  }
  
  y
}


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# With and without some NAs
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
dimnames = list(letters[1:20], LETTERS[1:5]) # to check dimnames attribute
for (mode in c("logical", "integer", "double")) {
  for (add_na in c(FALSE, TRUE)) {
    cat("add_na = ", add_na, "\n", sep = "")

    x <- matrix(1:100, nrow = 20, ncol = 5)
    if (add_na) {
      x[13:17, c(2, 4)] <- NA_real_
    }
    cat("mode: ", mode, "\n", sep = "")
    storage.mode(x) <- mode
    str(x)
    
    # Test with and without dimnames on x
    for (setDimnames in c(TRUE, FALSE)) {
      if (setDimnames) dimnames(x) <- dimnames
      else dimnames(x) <- NULL    
      # Check names attribute
      for (useNames in c(NA, TRUE, FALSE)) {
        # Row/column ranges
        r0 <- rowCumsums_R(x, useNames = useNames)
        r1 <- rowCumsums(x, useNames = useNames)
        r2 <- t(colCumsums(t(x), useNames = useNames))
        stopifnot(all.equal(r1, r2))
        stopifnot(all.equal(r1, r0))
        stopifnot(all.equal(r2, r0))
      } # for (useNames ...)
    } # for (setDimnames ...)
  } # for (add_na ...)
}


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# All NAs
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
for (mode in c("logical", "integer", "double")) {
  x <- matrix(NA_real_, nrow = 20, ncol = 5)
  cat("mode: ", mode, "\n", sep = "")
  storage.mode(x) <- mode
  str(x)
  
  # Test with and without dimnames on x
  for (setDimnames in c(TRUE, FALSE)) {
    if (setDimnames) dimnames(x) <- dimnames
    else dimnames(x) <- NULL    
    # Check names attribute
    for (useNames in c(NA, TRUE, FALSE)) {
      # Row/column ranges
      r0 <- rowCumsums_R(x, useNames = useNames)
      r1 <- rowCumsums(x, useNames = useNames)
      r2 <- t(colCumsums(t(x), useNames = useNames))
      stopifnot(all.equal(r1, r2))
      stopifnot(all.equal(r1, r0))
      stopifnot(all.equal(r2, r0))
    } # for (useNames ...)
  } # for (setDimnames ...)
} # for (mode ...)


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# A 1x1 matrix
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
dimnames = list("a", "A") # to check dimnames attribute
for (mode in c("logical", "integer", "double")) {
  x <- matrix(0, nrow = 1, ncol = 1)
  cat("mode: ", mode, "\n", sep = "")
  storage.mode(x) <- mode
  str(x)

  r0 <- rowCumsums_R(x)
  r1 <- rowCumsums(x)
  r2 <- t(colCumsums(t(x)))
  stopifnot(all.equal(r1, r2))
  stopifnot(all.equal(r1, r0))
  stopifnot(all.equal(r2, r0))
  
  # Check dimnames attribute
  dimnames(x) <- dimnames
  # r0 <- rowCumsums_R(x)
  # > r0
  #        a
  #   [1,] 0
  r1 <- rowCumsums(x, useNames = TRUE)
  r2 <- t(colCumsums(t(x), useNames = TRUE))
  stopifnot(identical(dimnames(r1), dimnames))
  stopifnot(identical(dimnames(r2), dimnames))    
  dimnames(x) <- NULL
}


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Corner cases
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
names <- LETTERS[1:5] # to check dimnames attribute
for (mode in c("logical", "integer", "double")) {
  cat("mode: ", mode, "\n", sep = "")
  value <- 0
  storage.mode(value) <- mode
  value2 <- value
  if (mode == "logical") value2 <- 0L
  
  # A 0x0 matrix
  x <- matrix(value, nrow = 0L, ncol = 0L)
  str(x)
  r0 <- matrix(value2, nrow = nrow(x), ncol = ncol(x))
  r1 <- rowCumsums(x)
  r2 <- t(colCumsums(t(x)))
  stopifnot(all.equal(r1, r2))
  stopifnot(all.equal(r1, r0))
  stopifnot(all.equal(r2, r0))

  # A 0xK matrix
  x <- matrix(value, nrow = 0L, ncol = 5L)
  str(x)
  colnames <- LETTERS[1:5]
  # Test with and without dimnames on x
  for (setDimnames in c(TRUE, FALSE)) {
    if (setDimnames) colnames(x) <- colnames
    else dimnames(x) <- NULL
    # Check names attribute
    for (useNames in c(NA, TRUE, FALSE)) {
      r0 <- rowCumsums_R(x, useNames = useNames)
      r1 <- rowCumsums(x, useNames = useNames)
      r2 <- t(rowCumsums(t(x), useNames = useNames))
      stopifnot(all.equal(r1, r2))
      stopifnot(all.equal(r1, r0))
      stopifnot(all.equal(r2, r0))
    } # for (useNames ...)
  } # for (setDimnames ...)

  # A Nx0 matrix
  x <- matrix(value, nrow = 5L, ncol = 0L)
  str(x)
  rownames <- LETTERS[1:5]
  # Test with and without dimnames on x
  for (setDimnames in c(TRUE, FALSE)) {
    if (setDimnames) rownames(x) <- rownames
    else dimnames(x) <- NULL
    # Check names attribute
    for (useNames in c(NA, TRUE, FALSE)) {
      r0 <- rowCumsums_R(x, useNames = useNames)
      r1 <- rowCumsums(x, useNames = useNames)
      r2 <- t(rowCumsums(t(x), useNames = useNames))
      stopifnot(all.equal(r1, r2))
      stopifnot(all.equal(r1, r0))
      stopifnot(all.equal(r2, r0))
    } # for (useNames ...)
  } # for (setDimnames ...)
} # for (mode ...)
