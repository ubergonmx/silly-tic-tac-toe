# Silly Tic-Tac-Toe

Silly Tic-Tac-Toe is a 2-player console game made in C language. The game is played on a 5x5 grid, and each player can choose from a menu of special abilities at the beginning of the game, which they can use in lieu of their regular turn during the game.

## Installation

To install the game, simply clone this repository and compile the `sttt.c` file using a C compiler. For example, using gcc:

```bash
gcc -o main sttt.c
```

## How to Play

To play the game, run the `sttt` executable in your terminal. The game will ask each player to choose from a list of abilities, and then the game will proceed similarly to normal tic-tac-toe, where each player takes turns selecting an unoccupied space.

Each player can select a space by typing the label of the space they choose. If the chosen label is invalid (for example, it does not exist or it is already occupied), the player should choose another space until the player chooses a valid space.

The game ends when a player occupies all five spaces in a horizontal, vertical, or diagonal row, or all 25 spaces have been occupied.

## List of Abilities

1. Take 2 turns – Player gets two turns after using their normal turn to use this ability (so just a net gain of only one extra turn).
2. Flip a space – Player chooses a space occupied by an opponent, and then replaces the opponent’s symbol with their own.
3. Blank four corners and center – Removes all symbols from the four corners and center of the grid.
4. Free row – Player chooses 2 spaces they occupy that are within the same row, and then the computer removes all the symbols of the opponent within the same row.
5. Opponent chooses 3 for you – Lets the opponent choose three unoccupied spaces for the player (instead of the normal choice of only one space).
6. Even it out – Computer counts the number of spaces each player occupies, and if the opponent occupies more spaces than the player, the player can select spaces occupied by the opponent and those spaces become unoccupied and the opponent’s symbols removed from them, until they have equal number of spaces.
7. Delete ability – Player chooses and removes an unused ability from the opponent’s abilities so the opponent can no longer use it.
8. Counter – when an opponent plays an ability, the player with the counter ability will be asked by the computer if they would like to counter it, and if they agree, the opponent will not be able to use the ability, can no longer use that ability, and will instead take a normal turn. This ability can only be used during the opponent’s turn.

## Technical Requirements

- Each ability must be defined in its own function.
- There must be sufficient internal documentation.
- The code must be efficient.

## Future Improvements

- Add a graphical interface.
- Add the ability to play against an AI opponent.

## License

This project is licensed under the BSD 3-Clause License. See the [LICENSE](LICENSE) file for details.