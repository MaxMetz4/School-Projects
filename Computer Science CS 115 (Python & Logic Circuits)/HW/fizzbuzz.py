def fizzBuzz(x):#inspired by https://www.youtube.com/watch?v=QPZ0pIK_wsc
    def recursiveStep(num, maximum, fizz = 3, buzz = 5):
        if num > maximum:
            return
        elif (num % fizz == 0 and buzz % 5 == 0):
            print("FizzBuzz")
            recursiveStep(num + 1, maximum)
        elif num % fizz == 0:
            print("Fizz")
            recursiveStep(num + 1, maximum)
        elif num % fizz == 0:
            print("Buzz")
            recursiveStep(num + 1, maximum)
        else:
            print(num)
            recursiveStep(num + 1, maximum)
    recursiveStep(1,x)
    
        
