# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Name    : Maxwell Metzner
# Pledge  : I pledge my honor that I have abided by the Stevens Honor System
# Purpose : To learn how compiler logic works
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Max:
#  Write a hmmm function that gets two numbers,
#   then prints the larger of the two.
#  Assumptions: Both inputs are any integers
Max = """
00 read r1
01 read r2
02 sub r3 r1 r2
03 jltzn r3 6
04 write r1
05 halt
06 write r2
07 halt
"""


# Power:
#  Write a hmmm function that gets two numbers,
#   then prints (No.1 ^ No.2).
#  Assumptions: No.1 is any integer, No.2 ≥ 0
Power = """
00 read r1 #number
01 read r2 #counter of power
02 setn r3 1 #answer
03 jeqzn r2 7
04 mul r3 r3 r1
05 addn r2 -1
06 jumpn 3
07 write r3
08 halt
"""


# Fibonacci
#  Write a hmmm function that gets one numner,
#   then prints the No.1st fibonacci number.
#  Assumptions: No.1 ≥ 0
#  Hint: You really don't want to implement
#   recursion in hmmm, try to find an
#   iterative method to compute your goal.
#  Tests: f(2) = 1
#         f(5) = 5
#         f(9) = 34
Fibonacci = """
00 setn r1 0
01 setn r2 1
02 read r3
03 jeqzn r3 5
04 jumpn 7
05 write r1
06 halt
07 setn r4 0
08 setn r5 -1
09 add r4 r3 r5
10 jeqzn r4 12
11 jumpn 14
12 write r2
13 halt
14 add r4 r1 r2 #now we good
15 copy r1 r2
16 copy r2 r4
17 addn r3 -1
18 jeqzn r3 20
19 jumpn 14
20 write r1
21 halt
"""


# ~~~~~ Running ~~~~~~
RunThis = Max
doDebug = False

if __name__ == "__main__" : 
    import hmmm
    hmmm.main(RunThis, doDebug)


