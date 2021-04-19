'''
Name: Maxwell Metzner

Date: 9/26/19

CS115 - HW 2 ~ Recursion

Pledge: I pledge my honor that I have abided by the Stevens honor system
'''
from functools import reduce
## Part 1 ~ Change
'''this is the program that we worked on in a previous lab, it returns the fewest number of coins
needed that add up to the desired value'''

def makeChange(val, coins):
    def recursiveStep(val, coins, used):#generator that gives out all possible permutations of coins to reach val
        if sum(used) == val:#these are my base cases
            yield used
        elif sum(used) > val:
            pass
        elif coins == []:
            pass
        else:
            for x in recursiveStep(val, coins[:], used + [coins[0]]):#useit
                yield x
            for x in recursiveStep(val, coins[1:], used):#loseit
                yield x
    permutations = [x for x in recursiveStep(val, coins, [])]#collects permutations from recursiveStep
    return [len(min(permutations, key=len)), min(permutations, key=len)]#returns shortest permutation and its length

## Part 2 ~ Least Common Substrings
def findSum(x, y):
    return x + y

def LCS(a,b):
    def helper(a,b):#helper inverses the output and puts individal characters together
        if not (a and b):
            return []
        if (a[0] == b[0]):#if they match,
            return helper(a[1:], b[1:]) + [a[0]]#move on and keep track of the match
        return (max(helper(a[1:], b), helper(a,b[1:])))
    if helper(a,b) == []:#for when one of the inputs are empty, it returns empty
        return ''
    else:
        return reduce(findSum, helper(a,b)[::-1])

def PLCS(a,b):
    str1 = LCS(a,b)
    str2 = LCS(a,b)#store it twice so one stays unedited

    def helper(s, substr, lst, count):
        if not s or not substr:#if one of the inputs are empty, return empty
            return lst
        if not substr:
            if  not lst:
                return [-1]
            else:
                return lst
        if(s[0] == substr[0]):
            lst.append(count)#adds list together
            substr = substr[1:]
        return helper(s[1:], substr, lst,count + 1)
    if helper(b, str2, [], 0) == [] or helper(a,str1,[],0) == []:#when one of the lists are empty, it returns -1
        return [[-1],[-1]]
    else:
        return [helper(b, str2, [], 0), helper(a,str1,[],0)]
