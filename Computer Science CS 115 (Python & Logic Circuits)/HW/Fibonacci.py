def fib(x):#if the next number in the sequence is higher than x, it stops
    def recursiveStep(old, new, limit):
        count = new + old
        if limit < count:
            return
        print(count)
        return recursiveStep(new, count, limit)
    return recursiveStep(1,0,x)