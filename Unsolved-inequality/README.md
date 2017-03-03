# Unsolved-inequality

The following inequality resulted from [Waring's problem](https://en.wikipedia.org/wiki/Waring%27s_problem).

Paraphrased from [Wikipedia](https://en.wikipedia.org/wiki/Floor_and_ceiling_functions#Unsolved_problem):

> Are there any positive integers *k* ≥ 6 such that:

> ![`3^{k}-2^{k}\left\lfloor \left({\tfrac {3}{2}}\right)^{k}\right\rfloor >2^{k}-\left\lfloor \left({\tfrac {3}{2}}\right)^{k}\right\rfloor -2`](../equations/unsolved-inequality.png)

> Mahler proved there can only be a finite number of *k*; none are known.

From Wikipedia's page on Waring's problem, any solution to *k* would be larger than 471,600,600. It is conjectured, but not proven, that no such *k* exist.

I have been unable to find a name for this inequality. From what I have been able to find, it is **not** called Waring's problem, but is instead a result *of* Waring's problem. Further information: [MW Waring's Problem](http://mathworld.wolfram.com/WaringsProblem.html), and [MW Euler's conjecture](http://mathworld.wolfram.com/EulersConjecture.html).

---

## Code

Because this code handles extremely large values, a custom data type is required. I use Boost's `cpp_dec_float` library because it allows large, arbitrary-precision numbers. While *k* must be a positive integer, the calculation of dividing `3^k/2^k` (alternatively `(3/2)^k`) results in a decimal.

The cmath library is commented out because it is already included from `cpp_dec_float`. In this program, for simple demonstration of its usage, I set the value for `const int PRECISION` to 10000. This means that the program will handle numbers up to 10000 digits long. While the value for `k` only goes up to a relatively small number, the result of `3^k` is a humongous number.

Also for simple demonstration, the initial value for `k` is 6. If you use this program for legitimately searching for a solution (I don't recommend this), you will want to increase the value of `k` and `PRECISION` as you go along.

Inside of the loop, I continually increase the value of *k* whilst searching for a solution to the inequality. **If the precision of `arbFloat` is exceeded, it breaks the loop behaving as if it found a solution. This is why I re-check (**`if-else`**) if it is an actual solution.**

---

## Notes for compilation and performance

This program was tested using the `g++` compiler.

If you compile this code using `g++`, I recommend the following flags using the `-Ofast` flag. Below is a comparison of run-times using the different [optimization flags](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html). While my system will be different from others, the relative improvements will show performance costs.

Optimization flag | Run time
---|---|
None | `11m 40.775s`
`-O1` (`-O`) | `3m 59.017s`
`-O2` | `2m 47.888s`
`-O3` | `1m 50.419s`
`-Ofast` | `1m 47.860s`

So, use `-Ofast` or `-O3` unless you have time to kill.

	g++ -o Unsolved-inequality -Wall -std=c++14 -Ofast Unsolved-inequality.cpp
	real	1m47.860s
	user	1m47.856s

	g++ -o Unsolved-inequality -Wall -std=c++14 -O3 Unsolved-inequality.cpp
	real	1m50.419s
	user	1m50.316s

	g++ -o Unsolved-inequality -Wall -std=c++14 -O2 Unsolved-inequality.cpp
	real	2m47.888s
	user	2m47.840s

	g++ -o Unsolved-inequality -Wall -std=c++14 -O1 Unsolved-inequality.cpp
	real	3m59.017s
	user	3m59.000s

	g++ -o Unsolved-inequality -Wall -std=c++14 Unsolved-inequality.cpp
	real	11m40.775s
	user	11m40.576s
