# Realize the game Pairs (Memory Tiles) in C# and WPF (<https://webgamesonline.com/memory/>)

### 1. Login

The game will have a "Sign in..." page window to choose a pre-existing user or create a new account.
This window also allows you to create a new user and associate him with an image; pre-existing jpg, png or gif images are used. This association will be saved in a file;
for simplicity, the username can be a single word; be careful with the paths you use, as problems will occur when moving
application to different locations - it is recommended not to use absolute paths.
The player can also choose an existing user to play the game.
The "Delete User" and "Play" buttons will initially be inactive, becoming active only when
a user is selected. The "Play" part is documented in section 2. The "Delete" part
is documented in section 4.

### 2. The Game

Clicking on Play will bring up a window with the following menu:

- New Game - start a new game;

- Open Game - opens a game for the current player, which he saved previously;
see section 3;

- Save Game - saves the current game; see section 3;

- Statistics - save statistics on games played and won by
users; see section 5;

- Exit - exit from the current window to the login window, from where you can
choose another user, delete user account, create new account or exit the application.

- Grid Size: -Standard (the game board will be 6x5);
-Custom (the game board will be the size specified by the user - MxN). (m or n must be even)

When the "New Game" button is clicked, a window will open where the following will be loaded
all the tokens that will have to be turned face up. If 2 tokens are clicked consecutively,
they will be turned face up. If the images on their face are identical, the chips will
disappear. Otherwise, when the third token is clicked, the previous 2 tokens are placed
backwards and the third chip remains face up, and so on until all the chips on the board disappear from the gameboard.
Consecutive selection of the same chip will not be allowed.
Each new game will have a different chip configuration. The algorithm for distributing the
images will be chosen conveniently so that the game configuration is random.
The images used for the tokens will be taken from a default set of images.
A game will have 3 levels. A game will be considered to be won only after winning 3
levels, at which point the player will count a new win and the levels will reset.
The user will see on the game window both his name and avatar, as well as the number of the level he is on.

### 3. Saving and opening the game

The player will be able to save his game (token configuration and the level of the current game) at any time
during the course of the game and then reopen it and continue from where he left off.
It will be up to you if a player overwrites the file each time,
save the game or if they can save multiple game files. In either situation, a
player will only be able to open one saved game.

### 4. Deleting an user

Deleting a user means deleting the user from the file, deleting the association with
image, deleting any game saved by him and deleting the statistics related to that player.

### 5. Saving and viewing statistics

Every time a player wins 3 consecutive levels (guesses 3 consecutive game boards in the specified time), add to the statistics a new game played and a new game won. If the player loses the game at the first, second or third level, then add to the statistics only a new game played by him.
Displaying the statistics will be done on a new window and will be in the form of: Username – Games Played – Games Won You will choose whether the current player can see the statistics related to all users or just his own statistics.
