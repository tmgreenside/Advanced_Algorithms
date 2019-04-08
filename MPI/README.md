# MPI Programming

These are assignments I completed for a course in parallel computing. The 
MatrixMultiplication folder contains functions for dividing portions of a
square matrix between the different processes.

The ArraySorting folder contains code for sorting portions of an array
using the Odd-Even Sorting algorithm. It routinely shares portions of the
array between processes and sorts a portion and then exchanges it until
the array is completely sorted.
