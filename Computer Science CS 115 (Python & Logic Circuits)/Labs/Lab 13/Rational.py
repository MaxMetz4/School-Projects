# **************
# * Name   : Maxwell Metzner
# * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
# **************

class Rational:
    def __init__(self, n=0, d=1):
        self.numerator = n
        self.denominator = d
        if not self.validate():
            print("Invalid inputs :(")

    def __repr__ (self):
        return "Rational(" + str(self.numerator) \
                + "," + str(self.denominator) + ")"

    def __str__ (self):
       return str(self.numerator) + "/" + str(self.denominator)

    def validate(self):
        return isinstance(self.numerator, int) \
               and isinstance(self.denominator, int) \
               and 0 != self.denominator

    def isZero(self):
        return 0 == self.numerator

    # TODO DONE
    def simplify(self):
        ''' Convert self into simplest form, i.e.
        2/4 becomes 1/2. Look into GCD!
        Make sure to add calls to simplify
        whenever you make a new rational throughout this code'''
        if self.numerator > self.denominator:
            largest = self.numerator
        else:
            largest = self.denominator
        i = largest
        while i <= largest and i > -1:
            if self.numerator % i == 0 and self.denominator % i == 0:
                self.numerator = int(self.numerator/i)
                self.denominator = int(self.denominator/i)
                break
            else:
                i = i - 1
        '''This finds GCD by dividing by the larger number
        (either numerator or denominator)and checking if it is
        in fact a gcd,if it is not a gcd, it will check if
        the next number below is a gcd, until a gcd is found.
        If the gcd is 1, simplify will just return self
        without modification'''

    # TODO DONE
    def invert(self):
        ''' Inverts self (makes it self^-1) '''
        temp = self.denominator#swaps numerator and denominator, using temp variable to hold numerator
        self.denominator = self.numerator
        self.numerator = temp 
        return 
    
    def __eq__(self, other):
       return self.numerator * other.denominator \
               == self.denominator * other.numerator

    def __ne__(self, other):
        return self.numerator * other.denominator \
               != self.denominator * other.numerator

    def __lt__(self, other):
        return self.numerator * other.denominator \
               < self.denominator * other.numerator
               
    def __le__(self, other):
        return self.numerator * other.denominator \
               <= self.denominator * other.numerator
               
    def __gt__(self, other):
        return self.numerator * other.denominator \
               > self.denominator * other.numerator
               
    def __ge__(self, other):
        return self.numerator * other.denominator \
               >= self.denominator * other.numerator
               
    def __add__(self, other):
        newDenominator = self.denominator*other.denominator
        newNumerator = self.numerator*other.denominator \
                       + self.denominator*other.numerator
        ret = Rational(newNumerator, newDenominator)
        return ret

    def __neg__(self):
        newDenominator = self.denominator
        newNumerator = - self.numerator

        return Rational(newNumerator, newDenominator)

    def __sub__(self, other):
        return self + (-other)

    # TODO DONE
    def __mul__(self, other):
        ''' Returns the product of self and other - SIMPLIFIED
        do not change self or other! '''
        newNumerator = self.numerator * other.numerator#numerator multiplication
        newDenominator = self.denominator * other.denominator#denominator multiplication
        newRational = Rational(newNumerator, newDenominator)#puts together values into Rational object
        newRational.simplify()
        return newRational

    # TODO DONE
    def __truediv__(self, other):
        ''' Returns the result of self/other - simplified
        do not modify self or other ! '''
        invertedOther = Rational(other.numerator,other.denominator)#make copy of other so other isnt modified
        invertedOther.invert()#invert it to be multiplied with self
        newFraction = self.__mul__(invertedOther)#do the multiplicaton, also not changing self
        newFraction.simplify()
        return newFraction

    # TODO DONE
    def __int__(self):
        ''' Returns the integer representation of this rational '''
        return int(self.numerator / self.denominator)#truncates simple division

    # Extra Credit: 5 pts
    def continuedFraction(self):#couldnt get this to work
        ''' Returns a string representation of the canonical continued fraction form of self.
        http://mathworld.wolfram.com/SimpleContinuedFraction.html
        5/4 -> [1;4] (since 5/4 = 1 + 1/4)
        33/5 -> [6;1,1,2] (since 33/5 = 6 + 3/5 = 6 + 1/(5/3) = 6 + 1/(1 + 2/3)
                                        = 6 + 1/(1 + 1/(3/2)) = 6 + 1/(1 + 1/(1 + 1/2))
        68/21 -> [3;4,5] (since 68/21 = 3 + 5/21 = 3 + 1/(21/5) = 3 + 1/(4 + 1/5)
        '''
        pass














        
