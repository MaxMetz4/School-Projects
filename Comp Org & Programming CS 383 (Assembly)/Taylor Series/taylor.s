/*
 * taylor.s
 *
 *  Created on: Dec 1, 2020
 *      Author: Maxwell Metzner
 */
.text
.global main
.extern printf

/*
	Register allocations:
	d0 = total, what is returned at the end of the function
	d1 = x
	d2 = result, used as the 1/factorial part of each term, eventually becomes value of entire term
	d3 = constant, used as intermediary in factorial and exponent

	x10 = i, how many terms there are, it remains the same
	x11 = j, used in how many terms there are, changes
	x12 = p, used in calculaing exponent x^j

	x13 = used to set d5 & d6 to 0 and 1
	d5 = 0
	d6 = 1, used in add, sub cbz

	x15 = constant but integer within factorial & loop

	x14 = register for data locations to be loaded in

*/

main:
	ldr x14, =in1			//Take in number of terms i
	ldr x10, [x14]			//set i to x10
	mov x11, x10			//initialize j to i
	mov x12, x10			//initialize p to i		(p/j/i are all loop counters)
	mov x13, #1
	SCVTF d6, x13			//initialize d6 to 1 (dedicated register)
	SCVTF d0, x13			//initialize total to 1
	ldr x14, =in2			//Take in x
	ldr d1, [x14]
	mov x13, #0
	SCVTF d2, x13			//initialize result to 0
	SCVTF d3, x13			//initialize constant to 0
	cbz x10, print			//if i=0 then print, no need to calculate any terms
	bl fact					//otherwise start the program

fact:
	cbz x11, print			//base case, if j = 0, print
	SCVTF d2, x11			//result = j (convert int -> double)
	FSUB d3, d2, d6			//constant = result - 1
	sub x15, x11, #1		//x15 is counter for factorial loop
	bl factloop				//move on to factorial loop

factloop:
	cbz x15, constant		//when loop is done head to constant
	FMUL d2, d2, d3			//result = result * constant
	FSUB d3, d3, d6			//decrement constant
	sub x15, x15, #1		//decrement loop counter
	bl factloop				//loop again

constant:
	FDIV d2, d6, d2			//result = 1/result (result is the factorial)
	sub x12, x11, #1			//initialize p to j-1
	mov x13, #1				//get ready to set constant to 1
	SCVTF d3, x13			//set constant to 1
	FMUL d3, d3, d1			//constant = x * 1 = x
	bl exponent				//now start computing x^i

exponent:
	cbz x12, finish			//both exponent and constants of term are done
	FMUL d3, d3, d1			//constant = constant * x
	sub x12, x12, #1		//p = p-1
	bl exponent

finish:
	FMUL d2, d2, d3			//complete the term into result
	FADD d0, d0, d2 		//add the term to the total
	sub x11, x11, #1		//decrement j
	bl fact					//start the loop over again at factorial

print:
	ldr x0, =string			//print the total
	bl printf
	br x30

.data
	in1:
		.dword 6     		//int input for value n
	in2:
		.double 5      		//double input for value x
	string:
		.ascii "The approximation is %f\n"
.end
