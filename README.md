# Hudson Nicholson CS201 Portfolio Project (Connect 4)
This is Hudson Nicholson's CS201 Portfolio Project for Spring 2019.

  ______   ______   .__   __. .__   __.  _______   ______ .___________.          ___   ___    
 /      | /  __  \  |  \ |  | |  \ |  | |   ____| /      ||           |          \  \ /  /    
|  ,----'|  |  |  | |   \|  | |   \|  | |  |__   |  ,----'`---|  |----`______     \  V  /     
|  |     |  |  |  | |  . `  | |  . `  | |   __|  |  |         |  |    |______|     >   <      
|  `----.|  `--'  | |  |\   | |  |\   | |  |____ |  `----.    |  |                /  .  \     
 \______| \______/  |__| \__| |__| \__| |_______| \______|    |__|               /__/ \__\    
                                                                                              
                                                                                              
                             
This game is called Connect-X. It is essentially Connect Four, but the user can select any value 
between 3 and 10 for 'X'. This means that the user can play Connect Eight and Connect Five. Also,
the user is able to choose any board size when loading up the program. The user then has options
to play against an AI or multiplayer. The multiplayer allows for up to 10 opponents to play, but
if you choose to use 10 opponents do not expect the games to be short. I have found that when 
using multiple oponents, it is best to change Connect Four to Connect Three under the settings
option "Number of tokens in row to win". There is also an option to change the AI from the default
mode (HARD) to the alternative mode (EASY). When the user is done playing a few games they are then able
to check their stats under option 3 in the MAIN MENU. If the user wants to clear these stats for any 
reason, then they can clear them under option 4 in SETTINGS. After each game the user returns to the 
MAIN MENU where the user can then choose what they would like to do next.

IN-MATCH
-Type the column that you would like to place your piece
-The game will continue until someone wins or there is a tie

MAIN MENU
-Play Against Computer
  Play against the AI with the current difficulty that is set
-Play Local Multiplayer
  Play against however many players are currently active (default is 2)
-Stats
  Check the stats of each active player (removed players retain their stats) as well as the computers
-Settings
  1) Number of tokens in a row to win
    -Allows user to change the ammount of tokens needed to be in a row for a player to win
  2) Number of players
    -Allows user to change ammount of active players
  3) Choose player tokens
    -Allows the user to modify the tokens placed on the board for each player 
  4) Clear win/loss record
    -Allows user to clear the win/loss record
  5) Change AI difficulty
    -Allows user to choose AI difficulty between HARD and EASY
`-Rules
    Brief explanation of the rules for new users
    
To compile, type 'make' into the ubuntu system with gcc installed.
After the above step type ./connectx in order to run the executeable.

WARNING: If a value is entered that is too close to the max int value for eaither columns or rows
there is a possibility that the value will not be read in properly. This should not be a problem 
because any values that large will yield run times to print the board far too large to play the game
within a week, month, or even year. 

  
