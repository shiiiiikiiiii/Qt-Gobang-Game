# Gobang Game

## Overview

This is a simple Gobang (Five in a Row) game implementation with AI opponent. The game rules are:

- It's played on a 19x19 grid. 
- Two players take turns placing stones of their color (black or white) on empty intersections.
- The first player to form an unbroken chain of 5 stones horizontally, vertically, or diagonally wins.

## Features

- Game board rendering and stone placement
- AI opponent with simple heuristic evaluation
- Undo moves
- Restart game
- Win/lose detection

## Technologies

- C++ 
- Qt 6.0

## Algorithms

- DFS to check for win condition
- Simple heuristic board evaluation for AI:
  - Score player's moves based on number of consecutive stones
  - Score AI's moves lower to allow wins
  - Add score to board positions to guide AI placement

## Usage

1. Compile and run the code in Qt Creator
2. Click intersections to place stones
3. Use the buttons to trigger AI move, undo, or restart
4. First to get 5 in a row wins

## Future Improvements

- More advanced AI algorithm like Monte Carlo Tree Search
- Multiplayer support over network
- Configurable board size and win condition
- Better graphics and animations
