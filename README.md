# CS 201 Portfolio Project (Connect-X)

This game is called Connect-X. It is essentially Connect Four, but the user can select any value between 3 and 10 for 'X'. This means that the user can play Connect Eight and Connect Five. Also, the user is able to choose any board size when loading up the program. The user then has options to play against an AI or multiplayer. The multiplayer allows for up to 10 opponents to play, but if you choose to use 10 opponents do not expect the games to be short. I have found that when using multiple oponents, it is best to change Connect Four to Connect Three under the settings option "Number of tokens in row to win". There is also an option to change the AI from the default mode (HARD) to the alternative mode (EASY). When the user is done playing a few games they are then able to check their stats under option 3 in the MAIN MENU. If the user wants to clear these stats for any reason, then they can clear them under option 4 in SETTINGS. After each game the user returns to the MAIN MENU where the user can then choose what they would like to do next.

* [Video Demonstration](https://youtu.be/9dL_LxoEqFw) - Check out my demonstration here!

## Getting Started

The following instructions will allow you to test the game that I developed for this project

### Prerequisites

You will have to clone the files from this repository to your machine as well as have with gcc installed in order to run this program

### Installing

The user must first type the command make once all the files are in the desired location

```
make
```

This makes an executeable that you can run called "connectx"

```
./connectx
```

## Playing Connect-X

### In-Game

The player going will be notified when they have to type the column that they would like to place their piece. The game will continue until someone wins or there is a tie.

### Main Menu

#### Play Against Computer

Play against the AI with the current difficulty that is set
	
#### Play Local Multiplayer

Play against however many players are currently active (default is 2)

#### Stats

Check the stats of each active player (removed players retain their stats) as well as the computers

#### Settings

#### Rules

Brief explanation of the rules for new users

### Settings

Some extra settings to make the game a little more interesting are provided here

#### Number of tokens in a row to win

Allows user to change the ammount of tokens needed to be in a row for a player to win

#### Number of players

Allows user to change ammount of active players

#### Choose player tokens

Allows the user to modify the tokens placed on the board for each player 

#### Clear win/loss record

Allows user to clear the win/loss record

#### Change AI difficulty

Allows user to choose AI difficulty between HARD and EASY


## Built With

* [Dr Lusth's Scanner Functions](https://github.com/hudsonators/CS201-Portfolio-Project/blob/master/scanner.c) - Scanner Functions Used
* [PurpleBooth](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2) - Template for README


## Authors

* **Hudson Nicholson** - *Initial work* - [Hudson's GitHub](https://github.com/hudsonators)


## Acknowledgments

* Big shout-out to Dr Anderson for assigning the project and giving the awesome option of Connect-4!
* Also, thank you Dr Lusth for preparing me for the course and letting us use your scanner functions!
* Shout out to this video which made me interested in Connect-4 in the first place (https://www.youtube.com/watch?v=yDWPi1pZ0Po)

## Warning

If a value is entered that is too close to the max int value for eaither columns or rows
there is a possibility that the value will not be read in properly. This should not be a problem 
because any values that large will yield run times to print the board far too large to play the game
within a week, month, or even year. 

  
