# I, Maxwell Metzner pledge my honor that I have abided by the Stevens Honor System.

def change(amount, coins):
    if amount == 0:
        return 0
    elif coins == []:
        return float("inf")
    elif coins[0] > amount:
        return change(amount,coins[1:])
    elif amount < 0:
        return float("inf")
    else:
        useIt = 1 + change((amount - coins[0]),coins)
        loseIt = change(amount, coins[1:])
    return min(useIt,loseIt)
        
