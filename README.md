# Project-Minesweeper

<p>This project is a Minesweeper game, implemented in C++, made as part of the Introduction to Programming Practicum course in Sofia Univercity "St. Kliment Ohridski".</p>

<h5>The Game rules</h5>
<p>The Minesweeper game is simple. The game board is represented by a grid of squares, underneath which are hidden mines. The player must open squares to reveal what the squares contain. If a square contains a mine, the game is over. If a square does not contain a mine, a number is revealed indicating how many mines are in the adjacent squares. The player must use this information to deduce which squares contain mines and which do not. The game is won when all non-mine squares are cleared and all mine squares are marked.</p>

<h5>How to play</h5>
<p>1. Before the game begins, the user must input the desired dimentions of the game board. The allowed size is between <strong>3x3</strong> and <strong>10x10</strong>.</p>
<p>2. Next, the player must select how many mines to be hidden, ranging from <strong>1</strong> to <strong>3 times the selected dimention</strong>.</p>
<p>3. This is where the game begins. The player has the option to select an <em>action</em> and a <em>coordinate of the rows</em> and <em>coordinate of the colomns</em>.The player has 3 actions to choose from:</p>
<p><strong>Open</strong> a square, <strong>mark</strong> a square as a mine and <strong>unmark</strong> a square as a mine. Each action is represented by its first letter - <strong>o</strong>, <strong>m</strong> and <strong>u</strong>.</p>
<p>The player must input commands until the game is either won or lost.</p>
