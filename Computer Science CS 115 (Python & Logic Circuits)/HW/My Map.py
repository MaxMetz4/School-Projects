def myMap(f, L):
    baseVal = [] #adapt base case
    def recursiveStep(head,tail):
        return [f(head)] + myMap(f, tail) #adapt recursive step
    return baseVal if not L \
           else recursiveStep(L[0], L[1:])

def myReduce(f, L):
    baseVal = L[0]
    def recursiveStep(head, tail):
        #print("recursing on " + str(tail))
        return myReduce(f, [f(head, tail[0])] + tail[1:])
    return baseVal if 1 == len(L) \
           else recursiveStep(L[0], L[1:])
