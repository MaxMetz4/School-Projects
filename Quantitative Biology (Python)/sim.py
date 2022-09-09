# EN 250 Evolutionary Algorithm
# I pledge my honor that I have abided by the Stevens Honor System.
# Coded by: Maxwell Metzner
# Partners: Ava, Akhilesh, Bailey

import math
import random
import matplotlib.pyplot as plt

# Each individual has attributes (power (initial velocity in m/s), angle (in degrees 0-180 left to right))
# Power ranges from 0 to 30 while angle ranges from 0 to 180

def print_list(list):
    print(*list, sep = "\n")
    
def distance_calc(pair):
    power = pair[0]
    angle = pair[1]
    direction = 1
    if angle < 90:
        direction = -1
    else:
        angle = angle-90
    return direction * ((power**2) * (math.sin(math.radians(2 * angle))))/9.8

def survive(gen):
    for i in range(0,10):
        gen[i] = (gen[i][0],gen[i][1],round(distance_calc(gen[i]),4))    
    gen = sorted(gen, key=lambda x: x[2])
    gen = gen[::-1]
    print('\nTop 5 survive:')
    print(*gen[0:5], sep = "\n")
    print('\nBottom 5 are killed:')
    print(*gen[5:10], sep = "\n")
    return gen[0:5]

def mutate_power(power, percent):
    # A number should be multiplied by the return of this to get a +- this percentage change
    power = power * (1-(0.01*percent)+(0.02*percent*random.random()))
    if power < 0:
        power = 0
    if power > 30:
        power = 30
    return power

def mutate_angle(angle, percent):
    # A number should be multiplied by the return of this to get a +- this percentage change
    angle = angle * (1-(0.01*percent)+(0.02*percent*random.random()))
    if angle < 0:
        angle = 0
    if angle > 180:
        angle = 180
    return angle

def reproduce(gen):
    newGen = []
    # Changes 10% UP OR DOWN
    # Fittest individual (3 children)
    newGen.append((round(mutate_power(gen[0][0], 5),2),round(mutate_angle(gen[0][1], 5),2)))
    newGen.append((round(mutate_power(gen[0][0], 5),2),round(mutate_angle(gen[0][1], 5),2)))
    newGen.append((round(mutate_power(gen[0][0], 5),2),round(mutate_angle(gen[0][1], 5),2)))
    # 2nd Fittest individual (2 children)
    newGen.append((round(mutate_power(gen[1][0], 10),2),round(mutate_angle(gen[1][1], 10),2)))
    newGen.append((round(mutate_power(gen[1][0], 10),2),round(mutate_angle(gen[1][1], 10),2)))
    # 3rd Fittest individual (2 children)
    newGen.append((round(mutate_power(gen[2][0], 15),2),round(mutate_angle(gen[2][1], 15),2)))
    newGen.append((round(mutate_power(gen[2][0], 15),2),round(mutate_angle(gen[2][1], 15),2)))
    # 4th Fittest individual (2 children)
    newGen.append((round(mutate_power(gen[3][0], 20),2),round(mutate_angle(gen[3][1], 20),2)))
    newGen.append((round(mutate_power(gen[3][0], 20),2),round(mutate_angle(gen[3][1], 20),2)))
    # 5th Fittest individual (1 child)
    newGen.append((round(mutate_power(gen[4][0], 25),2),round(mutate_angle(gen[4][1], 25),2)))
    return newGen

def main(generations=10):
    # Based on https://miro.medium.com/max/900/1*odW0CYMTeS-R5WW1hM0NUw.jpeg
    # Fittest are the best individuals in each generation, generation gets written over
    fittest = []
    # These variables are used for plotting graph of fittest individuals' performance
    x_values = []
    y_values = []
    # INITIALIZATION
    # Initial generation is started with a uniform distribution
    generation = [(5,9),(5,27),(5,45),(5,63),(5,81),(5,99),(5,117),(5,135),(5,153),(5,171)]
    
    print("START:")
    for i in range(1,generations+1):
        print("\n----------Generation " + str(i) + "----------")
        # SELECTION
        # Thin out the generation with survive
        generation = survive(generation)
        fittest.append(generation[0])
        # CROSSOVER (asexual) & MUTATION
        # Replenish generation to 10 members with reproduce
        generation = reproduce(generation)
        # Start over with next generation
    print("\nFittest of each generation:")
    for i in range(0,len(fittest)):
        fittest[i] = (fittest[i][0],fittest[i][1],round(distance_calc(fittest[i]),4))
        print("Generation " + str(i+1), end =": ")
        x_values.append(i+1)
        y_values.append(fittest[i][2])
        print(fittest[i])
    
    plt.plot(x_values,y_values)
    plt.xlabel('Generation')
    plt.ylabel('Distance travelled (meters)')
    plt.show()
        
if __name__ == '_main__':
    main()