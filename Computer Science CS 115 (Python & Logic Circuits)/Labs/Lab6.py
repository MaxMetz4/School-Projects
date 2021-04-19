##Maxwell Metzner
##CS 115
##I pledge my honor that I have baided by the stevens honor system

def decimalToBinary(x):
    newList = [] #creates what is going to be the binary list
    def recursiveStep(x):
        if x == 1:
            return newList.append(1)#whenever there is a remainder of 1, add 1 to binary list
        elif x ==0:
            return newList.append(0)#otherwise add a 0
        else:
            remainder = x % 2
            newList.append(remainder)
            return recursiveStep(x//2)#recurse with he number divided by 2 without a remainder
    recursiveStep(x)
    return newList

def binaryToDecimal(x):
    newSum = 0
    power = 0#power keeps track of what power of 2 it is on
    if not x or x == [0]:
        return []
    def recursiveStep(x, power, newSum):
        if x == []:
            return newSum
        else:
            newSum = newSum + (x[0] * (2**power))#converts the binary digit to a power of 2 and adds it
            power = power + 1#keeps track of power of 2 from bnary list
            return recursiveStep(x[1:], power, newSum)
    return recursiveStep(x, power, newSum)

def incrementBinary(x):
    if x == []:
        return [1]
    def sublistBegone(x):#flattens list
        if not x:
            return x
        if isinstance(x[0], list):
            return sublistBegone(x[0]) + sublistBegone(x[1:])
        return x[:1] + sublistBegone(x[1:])
    def recursiveStep(x):#tries to add to list, if list already contains a 1 it moves on to the next in the list
        if x[0] == 0:
            x[0] = 1
            return x
        if x[0] == 1:
            x[0] = 0
            return [x[0]] + [incrementBinary(x[1:])]
        if x == []:
            return [1]
    return sublistBegone(recursiveStep(x))
        
def addBinary(num1, num2):
    c = []
    def sameLength(a, b):#makes sure the 2 lists are the same length, if not adds placeholder 0's
        if len(a)!= len(b):
            if len(a) < len(b):
                a.append(0)
                sameLength(a, b)
            else:
                b.append(0)
                sameLength(a,b)
        else:
            return a,b
    def recursiveStep(a,b,c):
        if a == []:
            return c
        c = c + [a[0] + b[0]]
        return recursiveStep(a[1:],b[1:],c)
    def carryTheOne(x,carry,final): #make sure to initiate with empty carry and final
        if x == []:
            final = final + [carry]
            return final
        x[0] = x[0] + carry
        if x[0] == 0:
            final = final + [0]
            return carryTheOne(x[1:],carry,final)
        if x[0] == 1:
            carry = 0
            final = final + [1]
            return carryTheOne(x[1:],carry,final)
        if x[0] == 2:
            x[0] = 0
            carry = 1
            final = final + [0]
            return carryTheOne(x[1:],carry,final)
        if x[0] == 3:
            x[0] = 1
            carry = 1
            final = final + [1]
            return carryTheOne(x[1:],carry,final)#depending on what the digit is, leave a 1 or 0 and carry the remainder
    sameLength(num1, num2)
    added = recursiveStep(num1, num2, [])
    result = carryTheOne(added,0,[])
    if result[-1] == 0:
        result = result[:-1]#cuts off the 0's on the end that don't contribute to the binary number
    return result


