# abcrf

<details>

* Version: 1.8.1
* GitHub: NA
* Source code: https://github.com/cran/abcrf
* Date/Publication: 2019-11-05 14:40:02 UTC
* Number of recursive dependencies: 33

Run `revdep_details(, "abcrf")` for more info

</details>

## Newly broken

*   checking installed package size ... NOTE
    ```
      installed size is  8.2Mb
      sub-directories of 1Mb or more:
        data   2.6Mb
        libs   5.4Mb
    ```

## Newly fixed

*   checking whether package ‘abcrf’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘/home/angelina/Documents/Github/matrixStats/revdep/checks/abcrf/old/abcrf.Rcheck/00install.out’ for details.
    ```

# DelayedMatrixStats

<details>

* Version: 1.14.0
* GitHub: https://github.com/PeteHaitch/DelayedMatrixStats
* Source code: https://github.com/cran/DelayedMatrixStats
* Date/Publication: 2021-05-19
* Number of recursive dependencies: 70

Run `revdep_details(, "DelayedMatrixStats")` for more info

</details>

## Newly broken

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
       1. └─base::Map(expect_equal, observeds, expecteds, check.attributes = check.attributes) test_row_and_col_functions.R:72:4
       2.   └─base::mapply(FUN = f, ..., SIMPLIFY = FALSE)
       3.     └─(function (object, expected, ..., tolerance = if (edition_get() >= ...
      ── Failure (test_row_and_col_functions.R:72:5): Non-NULL rows and cols ─────────
      c(R3 = 18, R2 = 18) not equal to c(18, 18).
      names for target but not for current
      Backtrace:
          █
       1. └─base::Map(expect_equal, observeds, expecteds, check.attributes = check.attributes) test_row_and_col_functions.R:72:4
       2.   └─base::mapply(FUN = f, ..., SIMPLIFY = FALSE)
       3.     └─(function (object, expected, ..., tolerance = if (edition_get() >= ...
      
      [ FAIL 552 | WARN 0 | SKIP 0 | PASS 14180 ]
      Error: Test failures
      Execution halted
    ```

*   checking dependencies in R code ... NOTE
    ```
    Missing object imported by a ':::' call: ‘DelayedArray:::.reduce_array_dimensions’
    Unexported objects imported by ':::' calls:
      ‘DelayedArray:::.get_ans_type’ ‘DelayedArray:::RleArraySeed’
      ‘DelayedArray:::get_Nindex_lengths’ ‘DelayedArray:::set_dim’
      ‘DelayedArray:::set_dimnames’ ‘DelayedArray:::subset_by_Nindex’
      ‘DelayedArray:::to_linear_index’
      See the note in ?`:::` about the use of this operator.
    ```

## Newly fixed

*   checking whether package ‘DelayedMatrixStats’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘/home/angelina/Documents/Github/matrixStats/revdep/checks/DelayedMatrixStats/old/DelayedMatrixStats.Rcheck/00install.out’ for details.
    ```

## In both

*   checking package dependencies ... WARNING
    ```
    Skipping vignette re-building
    Packages suggested but not available for checking:
      'knitr', 'rmarkdown', 'BiocStyle'
    
    VignetteBuilder package required for checking but not installed: ‘knitr’
    ```

# matrixTests

<details>

* Version: 0.1.9
* GitHub: https://github.com/KKPMW/matrixTests
* Source code: https://github.com/cran/matrixTests
* Date/Publication: 2020-05-01 06:50:12 UTC
* Number of recursive dependencies: 133

Run `revdep_details(, "matrixTests")` for more info

</details>

## Newly fixed

*   checking examples ... ERROR
    ```
    Running examples in ‘matrixTests-Ex.R’ failed
    The error most likely occurred in:
    
    > ### Name: bartlett
    > ### Title: Bartlett test
    > ### Aliases: bartlett row_bartlett col_bartlett
    > 
    > ### ** Examples
    > 
    > col_bartlett(iris[,1:4], iris$Species)
    Error: package ‘matrixStats’ was installed before R 4.0.0: please re-install it
    Execution halted
    ```

## In both

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      > test_check("matrixTests")
      ══ Failed tests ════════════════════════════════════════════════════════════════
      ── Error (test-correct-cosinor.R:45:3): monte-carlo random testing gives equal results ──
      Error: there is no package called 'cosinor2'
      Backtrace:
          █
       1. ├─matrixTests:::base_cosinor(X, T, 10) test-correct-cosinor.R:45:2
       2. └─base::loadNamespace(x) test-correct-cosinor.R:20:4
       3.   └─base::withRestarts(stop(cond), retry_loadNamespace = function() NULL)
       4.     └─base:::withOneRestart(expr, restarts[[1L]])
       5.       └─base:::doWithOneRestart(return(expr), restart)
      
      [ FAIL 1 | WARN 10 | SKIP 0 | PASS 2189 ]
      Error: Test failures
      Execution halted
    ```

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘cosinor2’
    ```

*   checking LazyData ... NOTE
    ```
      'LazyData' is specified without a 'data' directory
    ```

# sparseMatrixStats

<details>

* Version: 1.4.0
* GitHub: https://github.com/const-ae/sparseMatrixStats
* Source code: https://github.com/cran/sparseMatrixStats
* Date/Publication: 2021-05-19
* Number of recursive dependencies: 53

Run `revdep_details(, "sparseMatrixStats")` for more info

</details>

## Newly broken

*   checking installed package size ... NOTE
    ```
      installed size is  6.9Mb
      sub-directories of 1Mb or more:
        libs   5.2Mb
    ```

## Newly fixed

*   checking whether package ‘sparseMatrixStats’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘/home/angelina/Documents/Github/matrixStats/revdep/checks/sparseMatrixStats/old/sparseMatrixStats.Rcheck/00install.out’ for details.
    ```

## In both

*   checking package dependencies ... WARNING
    ```
    Skipping vignette re-building
    Packages suggested but not available for checking:
      'knitr', 'rmarkdown', 'BiocStyle'
    
    VignetteBuilder package required for checking but not installed: ‘knitr’
    ```

