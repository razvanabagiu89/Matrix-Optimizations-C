# Matrix Calculus Optimization in C using ATLAS and other techniques

## About

https://ocw.cs.pub.ro/courses/asc/teme/tema2

Given this matrix operation: C = B × A × At + Bt × B, where A is an upper triangular matrix,
find C with 3 methods explained at the sections below.

## How to run the tests

- run local bash script in skel folder provided by ASC team.

## Structure & Flow

### For solving the tasks I used the following modules:

- tema2_neopt

    The unoptimized solution was to take advantage of A being an upper triangular matrix,
    and find C with the operations order like this: C = (B × A) × At + (Bt × B) so we
    can take advantage of A's triangularity twice. For this, using the functions
    multiply_matrices which based on operation_no takes 3 cases where the second matrix
    is either a normal one, upper triangular or lower triangular and compute_transpose working
    the same as the one above, we were able to compute C, but unefficiently.


- tema2_opt_m

	For the optimized solution, it is almost the same code as above but with better modifications:
	- introducing registers for variables so they won't be located on the stack and their accessing
	will be done much faster
	- using pointers to save lines and columns to better access the memory


- tema2_blas

	Using ATLAS functions, first computation is Bt × B using the cblas_dgemm func and storing it in D array.
	Then, I calculated the first triangular multiplication with A: B × A using cblas_dtrmm and then (B × A) × At
	again using the same cblas_dtrmm.
 		

## Observations and comparing results

Comparing results for the 3 methods:

- tema2_neopt
400		1.466681					
480		2.591261
800		12.493057
880		15.401952
1200	40.986958
1320	55.462524

- tema2_opt_m
400		0.482528 
480		0.873473
800		3.855278
880		5.104302
1200	12.915595
1320	18.393248	

According to calculations: 67% faster than neopt that is almost x3 times better performance just by doing 
the performance optimizations described above.

- tema2_blas
400		0.044647	
480		0.078107
800		0.336842
880		0.455755
1200	1.118686
1320	1.489610

According to calculations: 97% faster than neopt and 90% faster than opt_m
This means the blas implementation is x33 times better than neopt and x10 times better than opt_m


The blas method is by far the best here and we can see this in graph_all.png that it is performing very well
All graphs are done with linear representation in for N = 400, 480, 800, 880, 1200 and 1320 with OX axis
representing N and OY axis representing the time on the cluster

## Cache inspection

First of all, looking at I cache reads we can clearly see that for neopt variant the number is significantly
higher and that is due to cache unoptimization. In opt variant where we used registers to cache the result
and pointers to forward store the values, we can see that the I cache reads is almost 50% lower than 
previously.

I   refs:      7,467,895,929 (neopt) vs 3,180,060,072 (opt)
This shows the difference between the number of instructions executed.
Also, on blas variant 290,532,026 we can see this goes a lot lower for its efficiency.

Then, by looking at D cache reads and comparing first two variants the percentage is at 66% more efficient in the
opt variant, meaning that memory reads are performing less times -> this is clear due to our performance tricks
D   refs:      3,798,273,918 (neopt) vs 975,546,446 (opt)
Again on blas: 107,627,173 very low compared to others  


Predictive caches use a history of recent cache misses to predict future misses, and to reduce the overall cache miss rate.
For this, looking at the branches on first two variants vs blas we have:
Branches:        709,035,793 (neopt) vs 709,516,156 (opt) vs blas (4,345,874) is showing that blas is the master here.


## Graphs:
![p1](graph_all.png)
![p2](graph_neopt.png)
![p3](graph_opt_m.png)
![p4](graph_blas.png)