# Ackermann-function

![`A(m,n) = \begin{cases}n+1 & \text{if } m=0\\ A(m-1,1) & \text{if } m>0 \text{ and } n=0\\ A(m-1,A(m,n-1)) & \text{if } m>0 \text{ and } n>0 \end{cases}`](../equations/Ackermann-Péter-function.png)

The Ackermann function has historical significance because it went against the common belief that every computable function was also primative recursive. The Ackermann function is one of the fastest growing functions. The value of `Ack(0,0)` is 1, `Ack(3,3)` is 61, however the value of `Ack(4,2)` is over 19,000 digits long!

This C++14 program calculates the result of the Ackermann–Péter function. It provides **optional** protection against stack overflow and segmentation fault. It also detects common input errors, like non-numbers, non-integers, and non-natural numbers.

This program is *by far* not optimal.

## Example output

	Warning: If large values are entered, stack overflow and segmentation fault will occur!
	Enable stack overflow protection? Y/N: y

	m = 3

	n = 12

	CALCULATING

	A(3,12) = 32765

# Ackermann-function-optimal

**This code is simply an adaptation of the code on [Rosetta Code](https://rosettacode.org/wiki/Ackermann_function#Efficient_version), I take no credit for this.** This code, in comparison with the Ackermann-function program, is optimal for both small arugments (`Ack(1,1)`) and large arguments (`Ack(4,2)`).

This adapation allows for user input.

	Ack(m,n)
	m = 4
	n = 1
	Ack(4,1) = 65533
