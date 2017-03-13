# Ackermann-function

The Ackermann function has historical significance because it went against the common belief that every computable function was also primative recursive. The Ackermann function is one of the fastest growing functions. The value of `A(0,0)` is 1, `A(3,3)` is 61, however the value of `A(4,2)` is over 19,000 digits long!

This C++14 program calculates the result of the Ackermann–Péter function. It provides **optional** protection against stack overflow and segmentation fault. It also detects common input errors, like non-numbers, non-integers, and non-natural numbers.

This program is *by far* not optimal.

## Example output

	Warning: If large values are entered, stack overflow and segmentation fault will occur!
	Enable stack overflow protection? Y/N: y

	m = 3

	n = 12

	CALCULATING

	A(3,12) = 32765

	RUN SUCCESSFUL (total time: 13s)
