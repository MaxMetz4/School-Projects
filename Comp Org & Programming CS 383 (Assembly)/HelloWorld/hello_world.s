/*
	hello_world.s

	Created on: Oct. 24, 2020
	Author: Maxwell Metzner
*/


	.text
  	.global main
  	.extern printf

main:
  ldr x0, =hello_str
  bl printf
  br x30
  .data
hello_str:
  .ascii "Hello from Maxwell Metzner!\n\0"
  .end
