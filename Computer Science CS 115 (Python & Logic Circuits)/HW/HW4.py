from importlib import reload as Rfrsh
import hmmm

# Fibonacci! You've already done it in Lab 9
# Now however, you are to do hmmmonacci with
# recursion, & you MUST do so for any credit
# The tests are still the same as from Lab 9
# Tests: f(2) = 1 ■■■ f(5) = 5 ■■■ f(9) = 34
RecFibSeq = """ # You may not need all lines

00 read r10 #get number of recursion
01 setn r1 0 
02 setn r15 42 #initialize stack
03 setn r2 0 # ^
04 setn r3 1 # ^
05 pushr r2 r15 #put stack first in stack first
06 pushr r3 r15 #put stack second in stack second
07 jumpn 11 #start recursion
08 nop 
09 write r9
10 halt 

11 popr r3 r15 
12 popr r2 r15 
13 add r4 r2 r3 #get next value
14 pushr r3 r15 #refill stack
15 copy r9 r2 #preliminary answer
16 pushr r4 r15 #refill stack
17 sub r6 r10 r1 
18 jeqzn r6 8 #check completion
19 setn r7 1 
20 add r1 r1 r7 
21 jumpn 7 #start over
"""

# Change doDebug to false to turn off debugs
runThis = RecFibSeq
doDebug = False

# Note: main() in the shell to easily reload
def main(runArg=runThis,  debugArg=doDebug):
    Rfrsh(hmmm); hmmm.main(runArg, debugArg)

if __name__ == "__main__" :
    main()
