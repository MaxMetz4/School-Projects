# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Name     : Maxwell Metzner
# Pledge   : I pledge my honor that I have abided by the Stevens Honor system.
# Purpose  : 
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Power:
#  - Write a RECURSIVE hmmm function that gets two numbers,
#   then prints (No.1 ^ No.2).
#  - Assumptions: No.1 is any integer, No.2 ≥ 0
#  - 0 ^ 0 can either be 0 or 1.
#  - Your function MUST be recursive.
#   No points will be given for solutions that
#   do not use the hmmm recursive/stack structure
#   See week9.pdf for more insight into that.
Power = """
00 read r1 
01 read r2 #take number and power
02 setn r10 1
03 setn r15 42
04 calln r14 8
05 nop
06 write r13
07 halt #this is end of recursion



08 jnezn r2 12
09 setn r13 1
10 nop
11 jumpr r14
12 pushr r2 r15
13 pushr r14 r15 #adding to stack



14 addn r2 -1
15 nop
16 calln r14 8
17 nop
18 popr r14 r15
19 popr r2 r15 #taking from stack
20 mul r13 r13 r1 #doing the power multiplication
21 jumpr r14 #recurse
"""



# ~~~~~ Running ~~~~~~
import hmmm
import importlib

runThis = Power  # Change to the function you want to run
doDebug = False # Change to turn debug mode on/off

# call main() from the command line to run the program again
def main(runArg = runThis, debugArg = doDebug):
    importlib.reload(hmmm)
    hmmm.main(runArg, debugArg)

if __name__ == "__main__" : 
    main()
