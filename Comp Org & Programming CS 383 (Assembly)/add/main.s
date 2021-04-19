/*
 * main.s
 *
 *  Created on: Oct 5, 2020
 *      Author: maxwe
 */

.text
.global main


main:

add x1, xzr, xzr /* Load value zero in x1 */
add x1, x1, #15  /* Add immediate value 15 to x1 */
br x30           /* return to the caller */

.end
