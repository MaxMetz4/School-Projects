def myLength(L):
    if not L:
        return 0
    else:
        head, tail = L[0], L[1:]
        headContribution = deepLegth(head) \
            if isinstance(L[0], list) \
            else 1        
    return headContribution + myLength(tail)
