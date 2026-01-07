# Minesweeper

## Description

The minesweeper game consists of a game where you have a grid. On this grid, you have some cells that are either empty or contain a bomb. The objective of the game is to either reveal all empty cells or to flag the position of all the bombs.

## Gameplay

To play the game, you follow the prompts that will be displayed at the console. At first, it will ask you for a width and a height for the grid, which will then be the dimensions you will be playing. These dimensions must be positive integers and smaller than 100 each. For each "move", you introduce your input in the form '($X, $Y, $A)', where $X is the horizontal position on the grid, $Y is the vertical position on the grid and $A is an action, which can be either R for reveal or F to flag, either lowercase or uppercase. Note that you substitute the values and that parenthesis are mandatory, so an example input would be '(3, 4, R)'. After you do your move, you will be able to see the status of the board, where for each cell in the grid there will be either an R for revealed, meaning that cell is revealed and there are no neighbors that are bombs, a number that states how many neighboring cells are bombs, an F for the cells which you decide to flag or finally an X if you end up revealing a bomb. Note that it is possible to reveal a cell that you flagged previously if you wish to do so, in case you reach the conclusion that there is no bomb there. After reaching game over condition, either by winning through revealing all empty cells or flagging all bombs, you will be invited to play another round.

## Compiling

The game is meant to and has only been tested being compiled on a environment that gives access to GNU tools such as GCC and Make. To compile, simply run the command make on the game folder and it will produce an executable with the name 'minesweeper'.