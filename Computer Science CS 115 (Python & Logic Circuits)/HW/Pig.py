#**********************************
# *  Name  : Maxwell Metzner
# * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
# *        :
#**********************************

'''
4-Dice Pig

Adapted from Java to Python by Justin Barish,  11/2018
Modified nov '19 by Toby Dalton

~ ~ ~

To exercise your looping ability, we're going to be filling in a bunch
of blanks. yay!

Pig is a game where players take turns rolling dice.
Traditionally, it's only 2, but this is a variant.

The goal is to have their total score reach a certain # of points.
Players take turns earning points by rolling dice.
Each roll adds that sum onto a round score, which my or may not be added
to their total score, dictated as below:

A person's turn lasts until they want to stop rolling or roll some 1s.

If at any point during the player's turn they roll one 1:
their round ends and their round score is added to their total score.

If they roll two 1s:
they lose all points for the round, and their turn is over.

Three 1s:
they lose all of their points in the game, and their turn is over.

If they recieve the luck of four 1s (four-eyed snake ::S):
they immediately lose the game.

Whenever the player decide to stop their turn, their round points are 
added to their total points.

When a player's total points reach 100 (controllable below), they win.
'''
import random

POINTS_TO_WIN = 100
AI_ROUND_TARGET = 20

'''
This Homework has 2 parts:

Part 1 (100 pts): Complete the game for two human players.
That is, fill in all of the methods below

Part 2 (15 pts Extra Credit):
Add in an "AI" as the second player, so you will play against the computer.
The AI takes the place of player 2, and will continue rolling until
it reaches its AI_ROUND_TARGET. NOTE: You *will* need to change some of the
function paramaters (I.E. pass in additional values) and other parts of
functions.
'''

#**   
#**   General Game Stuff
#**

def main(alreadyPlayed = 0):
  '''This is the main function for the pig game'''
  if alreadyPlayed == 1:
    if not wantsPlayAgain():
      print('Bye!')
      exit()
    else:
      main()
  welcome()
  while True:
    playGame()
    return

# TODO
def playGame():
  '''Play one game of pig
  Alternates between players, and at the end of a player's turn, 
  prints the overall game score for both players'''

  player = 1
  scores = initScores()
  while not gameOver(scores):
    print()
    print('Current Scores:')
    printScore(scores)
    getMove(scores, player)
    player = 2
    while not gameOver(scores) and player == 2:
      print()
      print('Current Scores:')
      printScore(scores)
      getMove(scores, player)
      player = 1
       

# TODO DONE
def initScores():
  '''initialize the scores to 0'''
  clearScores = [0,0]
  return clearScores

# TODO DONE
def gameOver(scores):
  '''checks if the game is over
  game is over when either player reaches >= POINTS_TO_WIN.
  [ or 4 ones are rolled :3]
  Prints the win message for the player who won
  If no one won, just returns false'''
  if scores[0] > 100:
    printWinMessage(1, scores)
    main(1)
    return True
  elif scores[1] > 100:
    printWinMessage(2, scores)
    main(1)
    return True
  return False

# TODO DONE
def getMove(scores, player, roundScore = 0):
  '''gets a player's move.
  Before every move, prints the current round score and the game score for the player
  Checks if the player wants to continue, and if they do, rolls dice and appropriately changes scores
  '''
  printPlayerMessage(player)
  while gameOver(scores) == False:

    printCurrentPlayerScore(scores, player, roundScore)

    if(not wantsRollAgain(player)):
      scores[player-1] = scores[player-1] + roundScore
      printScore(scores)
      if player == 2:
        player = 1
      else:
        player = 2
      getMove(scores, player)
    roll = rollDice()
    showRoll(roll)
    amountOfOnes = roll.count(1)
    roundScore = roundScore + sum(roll)
    if amountOfOnes == 4:
      print("Rolled four 1's... Game over")
      printWinMessage(otherPlayer(player), scores)
      # TODO DONE?- How to best do this is for you to figure out !
      # You'll likely have to modify some of structure of this code.
      break
    elif amountOfOnes == 3:
      print("Rolled three 1's. Score reset!")
      scores[player-1] = 0
      printScore(scores)
      getMove(scores, otherPlayer(player))
      break
    elif amountOfOnes == 2:
      print("Rolled two 1's! Round ended, no score added")
      scores[player-1] = scores[player-1] + 0
      printScore(scores)
      getMove(scores, otherPlayer(player))
      break
    elif amountOfOnes == 1:
      print("Rolled one 1! Round ended, score added")
      scores[player-1] = scores[player-1] + roundScore
      printScore(scores)
      getMove(scores, otherPlayer(player))
      break
    else:
      roundScore = roundScore + sum(roll)
      printScore(scores)
      getMove(scores, player, roundScore)

def rollDie():
  '''rolls a single die (wow)'''
  return random.randint(1,6)

# TODO DONE
def rollDice():
    counter = 0
    rolls = [[0],[0],[0],[0]]
    while counter < 4:
        rolls[counter] = rollDie()
        counter = counter + 1
    return rolls

#**   
#**   Checking if we want to [X] again
#**

# TODO DONE?
def wantsContinue(response):
  '''Checks if the response a user gives indicates they want to continue.
  assume the user has to give a Y to mean yes and N to mean no'''
  if response == "y" or "Y":
    return True
  else:
    return False

# TODO DONE?
def wantsPlayAgain():
  '''Asks a player if they want to play the game again (use wantsContinue()!)'''
  print("Would you want to play the game again? Answer with Y or N.")
  x = input()
  if x == "Y":
    return True
  else:
    return False

# TODO DONE
def wantsRollAgain(player):
  '''Asks a player if they want to roll again
  For Part 2, also handle the Computer's decision'''
  print("Would you like to roll? Y for yes, N for no:")
  answer = input()
  if answer == "Y":
    return True
  else:
    return False

#**   
#**   Printing Things
#**

def welcome():
  '''Prints the welcome message for the game.
  We might also print the rules for the game and any other
  information that the user might need to know.'''
  print('Welcome to Pig!')

# TODO DONE
def printScore(scores):
  '''prints the current game score for each player'''
  print()
  print("Current scores are:")
  print("player 1:" + str(scores[0]) + " & player 2:" + str(scores[1]))

def printWinMessage(winningPlayer, scores):
  print()
  print('***********************Player ' + str(winningPlayer) + ' Won!************************')
  print('***********************Final Score:*************************')
  printScore(scores)

# TODO
def showRoll(roll):
  ''' prints out the roll'''
  print("Roll: " + str(roll))

def printPlayerMessage(player):
  print()
  print('--------------------------------------------------------------')
  print('-------------------Player ' + str(player) + '\'s turn----------------------------')
  print('--------------------------------------------------------------')
  print()

# TODO DONE
def printCurrentPlayerScore(scores, player, roundScore):
  '''print the score for a specific player. Prints their round score 
  and their overall game score not including their current round score'''
  print("Player " + str(player) + " has a round score of " + \
        str(roundScore) + " and an overall score of " + str(scores[player-1]))

def otherPlayer(player):
  if player == 1:
    return 2
  else:
    return 1
  
if __name__ == '__main__':
  main()






  
