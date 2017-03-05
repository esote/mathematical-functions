A cleaner version of this README will be linked here eventually.

---

The Lambert W function, also called the omega function or product logarithm, is the inverse of the function *f(W)=We^W*. It is used as the solution to many problems that cannot be solved using normal methods.

The Lambert W function can be approximated using Newton's method and Halley's method. These use successive approximation to converge towards the value of *W(x)*, meaning that given an infinite amount of approximations it will be completely accurate to all decimal places.

In my programs, I do not include imaginary results. I use the Boost multiprecision library to allow for theoretically unlimited precision. To change the precision, simply change the value of `const int PRECISION`.

# Lambert-W-function-v1

First, the program gets the value of *x* in the form of a string. It then checks if the string contains more than one decimal mark using the `string::find` function. Then, I check if the string is in the format of a decimal fraction (so not the letter "z" or something) by converting it to a double in a try-catch block. If the string is in the proper format, I convert it to the `arbFloat` data type. The number is checked to see if it is less than zero (which would return a complex number). I also put a bound of x <= 10^9 because there's an issue with larger values halting the program (fixed in later versions).

Inside of the for loop:

1. Convert initial value of `wnew` to a string, and set the string's precision.
2. Use the simplified Newton's method to approximate *W(x)*.
3. Convert the value of `wnew` after calculations to a string, and set the string's precision.
4. Compare the pre-calculation string post-calculation string, if they are the same it means the precision was exceeded.

## Example output

	0 <= x <= 1e9
	W(x), x = 1

	Convergence:
			1
			0.6839397205857211607977618850807304337229055655158839172539184008487307478724499016785736371729598219
			0.5774544771544497158879277307209708744246953720136943334618725831739970553254359545244940341535829055
			0.5672297377301170424199788873305659381989740529912345334258918256943726362413406459666277736815827773
			0.5671432965302959290104061393322652388244468110017561469052367139960666960291476041675058924102131759
			0.5671432904097839036821986273638501915396349920558000709178381348786164164929847042875694697488581049
			0.5671432904097838729999686622103563208086217342023287565768851248326011789240991181028762582526321268
			0.5671432904097838729999686622103555497538157871865125081351310792235327403215041862450323133272582057
			0.5671432904097838729999686622103555497538157871865125081351310792230457930866845666932194469617522946
			0.5671432904097838729999686622103555497538157871865125081351310792230457930866845666932194469617522946

	W(1) = 0.5671432904097838729999686622103555497538157871865125081351310792230457930866845666932194469617522946

	(rounded up to 100 digits, precise after 9 iterations)
	
# Lambert-W-function-v2

Changes from v1:

- Originally, I was using Newton's method, which converges quadratically (amount of precise digits doubles per iteration) for approximating *W(x)*. Now I am using Halley's method, which converges cubically (amount of precise digits triples per iteration). This is much faster, especially when finding larger values.
- I am now using `std::getline` instead of `std::cin`.
- In the Boolean function `isStringValid`, I am now checking the following things:
	1. Spaces in the string
	2. Multiple decimal marks in the string, optimized from the previous version.
	3. If, when converted to an `arbFloat`, it results in a runtime error (usually due to an extremely large value like 10^10^10, or an incorrect data type, like null).
	4. If, when converted to an `arbFloat`, it results in a non-runtime error (usually due to the input not being a number).
	5. If the user intentionally entered "NaN".
- In the Boolean function `isNumberValue`, I am now checking the following things:
	1. If the input is less than 0, which results in a complex number.
	2. If the input is infinity (or at least perceived as infinity), this is the result of inputs like 10^10^9 (which is smaller than the catch for parsing errors, but too large to be computed), or if the value "inf" is intentionally entered.
- Originally, it started computing at 0, but now it has a starting guess if the input is not equal to 0 or 1
- Replaced for loop with do-while loop, because the limit of 1 < 1e99 is unnecessary with other range checks.
- Originally, I used Boost `.convert_to<>()` for the string-to-`arbFloat` conversion, but now I use `static_cast`. The string-to-`arbFloat` has been abstracted to an inline function (`resizeArbtoString`).
- All of the functions now take constant referenced arguments, to avoid pointlessly copying the variable.

With these improvements, the value of *W(x)* within a computable range can be calculated in seconds with around 5 iterations.

## Example output

	0 <= x < inf
	W(x), x = 382903813902

	Initial Guess: 23.51058492712918919114582243355488790981166285829588560557376358648060096831120133580533938585632116
	Convergence:
			23.51058492712918919114582243355488790981166285829588560557376358648060096831120133580533938585632116
			23.51347595210448454142871835682176384958738553442394865049432759042578858344306346044132670280112569
			23.51347595429244717613280522620836780914305001935314712126885835149239110249930323970435009335473405
			23.51347595429244717613280522715678680545105184461531350781886276647715841787449182724224065575351117
			23.51347595429244717613280522715678680545105184461531350781886276647715841787449182731948759374067864

	W(382903813902) = 23.51347595429244717613280522715678680545105184461531350781886276647715841787449182731948759374067864
	(rounded up to 100 digits, precise after 5 iterations)

# Lambert-W-function-v3

Changes from v2:

- Moved declaration of `wnew` to its first usage.
- Switched if-else to the ternary operator `?:`.
- Moved the declaration of the `preComp` and `postComp` strings closer to their first usage.
- Replaced the do-while loop with a for loop, which is optimal compared to the original for loop and the previous do-while loop.

This should not improve performance too much, but it is cleaner than it was before.

## Example output

	0 <= x < inf
	W(x), x = 812938391290923992913

	Initial Guess: 44.35339134883215996973968716884070132445691959510133480762678367005160538324305405659125047252476026
	Convergence:
			44.35339134883215996973968716884070132445691959510133480762678367005160538324305405659125047252476026
			44.3549624063445606412268227676937814316982644538669196388950582583829684964816572864522199228692494
			44.35496240668242513973657868748029822161096853261157563622792382991592856784857054207453437390011557
			44.35496240668242513973657868748365863970197225075861669793254714385770220419310494747348654405936291
			44.35496240668242513973657868748365863970197225075861669793254714385770220419310494747348654736568818

	W(812938391290923992913) = 44.35496240668242513973657868748365863970197225075861669793254714385770220419310494747348654736568818
	(rounded up to 100 digits, precise after 5 iterations)
	
# Lambert-W-function-v4

Changes from v3:

- Clarified and removed a couple comments
- Switch from using `return 2` and `return 3` to `return returnID::invalidString` and `return returnID::invalidNumber` respectively. The use of an `enum` makes the intentions clearer.
