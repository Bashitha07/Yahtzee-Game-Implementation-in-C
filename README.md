# Yahtzee-Game-Implementation-in-C
A two-player Yahtzee game in C featuring a strategic computer AI.

This repository contains a two-player, terminal-based implementation of the classic dice game Yahtzee, developed for the SE1012: Programming Methodology module. The game features a human player competing against a strategically programmed computer opponent over 13 rounds of gameplay.

## Project Overview
The objective of the game is to achieve the highest possible score by rolling five dice to create specific combinations across 13 unique scoring categories.

## Key Features
- **Core Mechanics:** Full implementation of rolling and rerolling dice (up to three times per turn).
- **Strategic AI:** A computer opponent that uses a priority-based system to make optimal decisions based on the current game state.
- **Human-Computer Interaction:** Simple terminal prompts for the human player to select which dice to keep (`1`) or reroll (`0`).
- **Scoring System:** Automatic calculation for all 13 standard Yahtzee categories.

## Scoring Categories
The game implements the following categories:

### Upper Section
- Ones
- Twos
- Threes
- Fours
- Fives
- Sixes

*(Sum of dice showing the chosen number.)*

### Lower Section
- **Three of a Kind:** Sum of all dice if 3+ are the same.
- **Four of a Kind:** Sum of all dice if 4+ are the same.
- **Full House:** 25 points for three of one number and two of another.
- **Small Straight:** 30 points for four consecutive numbers.
- **Large Straight:** 40 points for five consecutive numbers.
- **Yahtzee:** 50 points for five dice showing the same number.
- **Chance:** Sum of all five dice regardless of combination.

## Technical Implementation & AI Strategy

### Computer Player Logic
The computer's decision-making process is structured hierarchically to maximize its score:
- **High-Value Check:** It first checks for high-value opportunities like Yahtzee or Four of a Kind.
- **Sequence Detection:** It analyzes dice counts to detect potential sequences for Small or Large Straights.
- **Fallback Strategy:** If no high-value combinations are possible, it targets basic categories (Ones through Sixes) to build a steady score.
- **Category Management:** A Boolean array is used to ensure the AI never selects the same category more than once.

### Technical Details
- **Language:** C
- **Randomness:** Utilizes `rand() % 6 + 1` for dice rolls, seeded with `srand(time(NULL))` to ensure varied results across games.
- **Modular Design:** The code is organized into specific functions for rolling dice, calculating scores, and managing individual player turns.

## Getting Started

### Prerequisites
A C compiler (e.g., GCC).

### Compilation
To compile the game, run the following command in your terminal:

```bash
gcc yahtzee.c -o yahtzee
```

### Running the Game
```bash
./yahtzee
```

## Limitations & Known Issues
The following official rules were not implemented in this version due to project constraints:
- **Yahtzee Bonus:** Bonus points for subsequent Yahtzees after the first one is recorded.
- **Upper Section Bonus:** The 35-point bonus for achieving a score of 63 or higher in the Upper Section (categories 1–6).

## Author
- **Name:** Bashitha Sellapperuma
- **Student ID:** IT24103485
- **Institution:** SLIIT UNI
- **Year 1 Semester 1 Module:** SE1012 - Programming Methodology
