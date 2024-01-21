# Project-Minesweeper

<p>This project is a Minesweeper game, implemented in C++, made as part of the Introduction to Programming Practicum course in Sofia Univercity "St. Kliment Ohridski".</p>

<h5>The Game rules</h5>
<p>The Minesweeper game is simple. The game board is represented by a grid of squares, underneath which are hidden mines. The player must open squares to reveal what the squares contain. If a square contains a mine, the game is over. If a square does not contain a mine, a number is revealed indicating how many mines are in the adjacent squares. The player must use this information to deduce which squares contain mines and which do not. The game is won when all non-mine squares are cleared and all mine squares are marked.</p>

<h5>How to play</h5>
<p>1. Before the game begins, the user must input the desired dimentions of the game board. The allowed size is between **3x3** and **10x10**.</p>
<p>2. Next, the player must select how many mines to be hidden, ranging from **1** to **3 times the selected dimention**.</p>
<p>3. This is where the game begins. The player has the option to select an *action* and a *coordinate of the rows* and *coordinate of the colomns*.The player has 3 actions to choose from:</p>
<p>**open** a square, **mark** a square as a mine and **unmark** a square as a mine. Each action is represented by its first letter - **o**, **m** and **u**.</p>
<p>The player must input commands until the game is either won or lost.</p>
