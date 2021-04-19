/*
 * fibonacci.s
 *
 *  Created on: Nov 3, 2020
 *      Author: Maxwell Metzner
 */
.text
.global main
.extern printf

/*
	Register allocations:
	current = x10
	previous = x11
	n = x12
	temp = x13 (used when transtitioning to new previous and current)

*/

main:
	mov x10, #1				//Initialize variable for current
	mov x11, #0				//Initialize variable for previous
	ldr x14, =in1			//Initialize variable for n
	ldr	x12, [x14]
	sub x12, x12, #1		//deincrement n so that it can be compared to 0 instead of 1
	mov x13, #0				//Initialize variable for temp
	bl fibonacci			//call the function

fibonacci:
	mov x30, x10			//get ready to return current
	cbz x12, print			//if n==0, go to print current
	sub x12, x12, #1		//else count down n by 1
	add x13, x10, x11		//temp holds future value current
	mov x11, x10			//replace previous with current
	mov x10, x13			//replace current with temp
	mov x13, #0				//reset temp
	bl fibonacci			//recursive call

print:
	ldr x0, =string			//print the return
	mov x1, x10
	bl printf
	br x30

.data
	in1:
		.dword 10      		//input for value n
	string:
		.asciz "%d\n"
.end
