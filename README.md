

<div id="badges"><!-- pkgdown markup -->
<a href="https://CRAN.R-project.org/web/checks/check_results_matrixStats.html"><img border="0" src="https://www.r-pkg.org/badges/version/matrixStats" alt="CRAN check status"></a></a>
<a href="https://github.com///github.com/AngelPn/matrixStats/actions?query=workflow%3AR-CMD-check"><img border="0" src="https://github.com///github.com/AngelPn/matrixStats/workflows/R-CMD-check/badge.svg?branch=develop" alt="Build status"></a></a>
<a href="https://travis-ci.org///github.com/AngelPn/matrixStats"><img border="0" src="https://travis-ci.org///github.com/AngelPn/matrixStats.svg" alt="Build status"></a></a>
<a href="https://ci.appveyor.com/project///github.com/AngelPn/matrixStats"><img border="0" src="https://ci.appveyor.com/api/projects/status/github///github.com/AngelPn/matrixStats?svg=true" alt="Build status"></a></a>
<a href="https://codecov.io/gh///github.com/AngelPn/matrixStats"><img border="0" src="https://codecov.io/gh///github.com/AngelPn/matrixStats/branch/develop/graph/badge.svg" alt="Coverage Status"></a></a>

</div>


# matrixStats: Functions that Apply to Rows and Columns of Matrices (and to Vectors)

## Skills Test

Task 1, 2, 3 completed

## Google Summer of Code (GSoC) 2021

If you are a student and interested in working on this project, please consider applying to work on it via GSoC 2021.  Google Summer of Code is an initiative to support students to learn about and contribute to open-source software projects, while getting payed.  The R community has been mentoring many GSoC projects over the years.  For more details, please see the GSoC 2021 proposal ['matrixStats: Consistent Support for Name Attributes'](https://github.com/rstats-gsoc/gsoc2021/wiki/matrixStats%3A-Consistent-Support-for-Name-Attributes).  **The deadline for student applications is on [April 13, 2021](https://github.com/rstats-gsoc/gsoc2021/wiki) with a soft deadline the week before.**

---

## Introduction

The matrixStats package provides highly optimized functions for
computing common summaries over rows and columns of matrices,
e.g. `rowQuantiles()`. There are also functions that operate on vectors,
e.g. `logSumExp()`. Their implementations strive to minimize both memory
usage and processing time. They are often remarkably faster compared
to good old `apply()` solutions. The calculations are mostly implemented
in C, which allow us to optimize beyond what is possible to do in
plain R. The package installs out-of-the-box on all common operating
systems, including Linux, macOS and Windows.

## Example
With a matrix
```r
> x <- matrix(rnorm(20 * 500), nrow = 20, ncol = 500)
```
it is [many times
faster](http://www.jottr.org/2015/01/matrixStats-0.13.1.html) to
calculate medians column by column using
```r
> mu <- matrixStats::colMedians(x)
```
than using
```r
> mu <- apply(x, MARGIN = 2, FUN = median)
```

Moreover, if performing calculations on a subset of rows and/or
columns, using
```r
> mu <- colMedians(x, rows = 33:158, cols = 1001:3000)
```
is much faster and more memory efficient than
```r
> mu <- apply(x[33:158, 1001:3000], MARGIN = 2, FUN = median)
```



## Benchmarks
For formal benchmarking of matrixStats functions relative to
alternatives, see the [Benchmark reports](https://github.com/HenrikBengtsson/matrixStats/wiki/Benchmark-reports).

## Installation
R package matrixStats is available on [CRAN](https://cran.r-project.org/package=matrixStats) and can be installed in R as:
```r
install.packages("matrixStats")
```


### Pre-release version

To install the pre-release version that is available in Git branch `develop` on GitHub, use:
```r
remotes::install_github("//github.com/AngelPn/matrixStats", ref="develop")
```
This will install the package from source.  Because of this and because this package also compiles native code, Windows users need to have [Rtools](https://cran.r-project.org/bin/windows/Rtools/) installed and macOS users need to have [Xcode](https://developer.apple.com/xcode/) installed.



<!-- pkgdown-drop-below -->

## Contributing

To contribute to this package, please see [CONTRIBUTING.md](CONTRIBUTING.md).
