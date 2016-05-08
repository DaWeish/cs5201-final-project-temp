# CS5201 - Object-Oriented Numerical Modeling I
## Final Project - Connor Walsh
### Overview

This program uses two different solvers to calculate estimate points for the
Dirichlet method of solving the Poisson Equation. The two methods are 
Gaussian Elmination method and QR decomposition with back substitution

### Usage

You can compile the driver by running "make" with no commands at the top level
of the directory where the makefile resides. If you wish to compile the unit tests,
run "make tests" at the same directory location. To clean all temp files and 
executables, run "make clean".

To run the driver with default parameters, simply execute it with no arguments.
The default parameters will be printed at the top. This will run both of the
solvers on the standard Poisson problem using increasing number of divisions and
outputing the time required to perform the calculation.

To run the driver with different parameters, type "driver [start end increment]"
where start is an integer specifying the number of divisions to start at and end
is the number of divisions to end with and increment is the number to increment
by. Also you can append a 0 or 1 (or anything that evaluates to true) at the end
to specify whether you want a file friendly csv type output in order to graph
the results. ie "driver 5 35 1 1" will run from 5 to 35 divisions with an
increment of 1 and output the results in a csv type output at the command line.

## Questions

If you have any questions, please direct them to Connor Walsh at
    cwd8d@mst.edu
