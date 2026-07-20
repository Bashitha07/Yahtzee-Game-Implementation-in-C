/************************************************************
IT24103485 - SE1012 - Code of Yahtzee game in 'C' language 
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Print game instructions
void printInstructions() {
    printf("Welcome to 13 rounds Yahtzee Game!\n");
    printf("Roll the dice up to three times each turn, then pick a category to score in.\n");
}

// Roll random number from 1 to 6 for each die
void rollDice(int dice[]) {
    for (int i = 0; i < 5; i++) {
        dice[i] = rand() % 6 + 1; //(Random no) % 6 + 1 
    }
}

// Print rollDice or rerollDice values for all dice
void printDice(int dice[]) {
    printf("Dice: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", dice[i]); //ex:- 1 4 3 5 5
    }
    printf("\n"); //Break line
}

void rerollDice(int dice[], int player) {
// Reroll dice two times
int counts[6] = {0}; //Initial count as '0'
for (int rerollCount = 0; rerollCount < 2; rerollCount++) { //2 times
    if (player == 1) { //Human Player reroll
        int reroll[5];  //Initialize integer to input 1's and 0's for 5 inputs
        for (int i = 0; i < 5; i++) {
            printf("'0' for reroll or '1' for keep die %d : ", i + 1);
            scanf("%d", &reroll[i]);

            // Valid input (either '1' or '0')
            while (reroll[i] != 1 && reroll[i] != 0) {
                printf("Invalid input. 1 to keep and 0 to reroll: ");
                scanf("%d", &reroll[i]);
            }
        }

        for (int i = 0; i < 5; i++) { //Reroll if reroll[i] == 0
            if (reroll[i] == 0) {
                dice[i] = rand() % 6 + 1; //(Random no) % 6 + 1
            }
        }
        printDice(dice);  // Print dice after reroll
        
            
    } else { //Strategy of computer decisions : Use counts and sequences mostly
        /*  counts[0] = number of 1's
            counts[1] = number of 2's
            counts[2] = number of 3's
            ...
            counts[5] = number of 6's
        */
        if (counts[dice[0] - 1] >= 4) { //Try for Yahtzee Category
            for (int i = 0; i < 5; i++) {
                if (dice[i] != dice[0]) {
                    dice[i] = rand() % 6 + 1;
                }
            }
                
        } else if (counts[dice[0] - 1] >= 3) { //Try for four  of a kind
            for (int i = 0; i < 5; i++) {
                if (dice[i] != dice[0]) {
                    dice[i] = rand() % 6 + 1;
                }
            }
                
        } else if (counts[dice[0] - 1] >= 2) { //Try for three  of a kind
            for (int i = 0; i < 5; i++) {
                if (dice[i] != dice[0]) {
                    dice[i] = rand() % 6 + 1;
                }
            }
        } else { // Count occurrences of each die value (10 & 11) 
                int counts[6] = {0};
                    for (int i = 0; i < 5; i++) {
                        counts[dice[i] - 1]++;
                    }

            // Check for Large Straight (5 consecutive numbers)
            if ((counts[0] && counts[1] && counts[2] && counts[3] && counts[4]) || (counts[1] && counts[2] && counts[3] && counts[4] && counts[5])) 
                { //for Sequences: 1-2-3-4-5 & 2-3-4-5-6
                break;// No rerolls
                }
                
            // Check for Small Straight (4 consecutive numbers)
            // Sequences: 1-2-3-4 , 2-3-4-5 , 3-4-5-6
            else if ((counts[0] && counts[1] && counts[2] && counts[3]) || (counts[1] && counts[2] && counts[3] && counts[4]) || (counts[2] && counts[3] && counts[4] && counts[5])) 
            {
                // Reroll the dice not part of the small straight
                for (int i = 0; i < 5; i++) {
                    if (dice[i] < 2 || dice[i] > 4) { // Dice not in the straight sequence (1-4 or 2-5 or 3-6)
                        dice[i] = rand() % 6 + 1; // Reroll
                    }
                }
            } 
            //Check for three digit sequence to reroll
            //Sequences: 1-2-3, 2-3-4 , 3-4-5 , 4-5-6
            else if ((counts[0] && counts[1] && counts[2]) || (counts[1] && counts[2] && counts[3]) || (counts[2] && counts[3] && counts[4]) || (counts[3] && counts[4] && counts[5])) 
            {
                // Reroll the dice not in small straight
                for (int i = 0; i < 5; i++) {
                    // Check if the die is not part of the current small straight sequence
                    if (!(dice[i] >= 1 && dice[i] <= 4)) {  // Ex:-1-4 or 2-5 or 3-6
                    dice[i] = rand() % 6 + 1;  // Reroll dice not in sequence
                    }
                }
            } else if (counts[dice[0] - 1] >= 2) { //Reroll to select large value
                for (int i = 0; i < 5; i++) {
                    if (dice[i] <= 3) {
                        dice[i] = rand() % 6 + 1;
                    }
                }
            }
        }
    printDice(dice);
    }
} //End of reroll
}

int selectComputerCategory(int dice[], int usedCategories[]) {
    int counts[6] = {0}; // Initialize count as '0'
    int category = -1; //Initialize category as '-1'
    
    // Count occurrences of each die value
    for (int i = 0; i < 5; i++) { //ex: dice = {3, 4, 3, 1, 5} , i = 0
        counts[dice[i] - 1]++; //counts[(3 - 1)++] -> counts[2]++ -> counts[2] = 1 again i = 2 -> counts[3-1]++ -> counts[2] = 2
    }
    
    // Yahtzee condition - 12
    for (int i = 0; i < 6; i++) {
        if (counts[i] == 5 && !usedCategories[11]) { // Count 5 times
            category = 12; // Yahtzee
            break;
        }
    }
    
    // Four of a kind - 8
    if (category == -1) {
        for (int i = 0; i < 6; i++) {
            if (counts[i] >= 4 && !usedCategories[7]) { // check Category is already chosen
                category = 8; // Four of a kind
                break; // Break loop
            }    
        }
    }
    
    // Full House - 9
    if (category == -1) {
        int hasThree = 0, hasTwo = 0;
        for (int i = 0; i < 6; i++) {
            if (counts[i] == 3) { // 3 of a kind
                hasThree = 1;
            }
            if (counts[i] == 2) { // 2 of another kind
                hasTwo = 1;
            }
        }
        if (hasThree && hasTwo && !usedCategories[8]) { // Full House
            category = 9; // Full House
        }
    }
    
    // Three of a kind - 7
    if (category == -1) {
        for (int i = 0; i < 6; i++) {
            if (counts[i] >= 3 && !usedCategories[6]) { 
                category = 7; // Three of a kind
                break; // Break loop
            }    
        }
    }
    
    // Small straight - 10
    if (category == -1) { // for Sequences: 1-2-3-4 & 2-3-4-5 & 3-4-5-6
        if ((counts[0] && counts[1] && counts[2] && counts[3]) || 
            (counts[1] && counts[2] && counts[3] && counts[4]) || 
            (counts[2] && counts[3] && counts[4] && counts[5])) {
            
            if (!usedCategories[9]) { // Validity of category
                category = 10; // Small Straight
            }
        }
    }
    
    // Large straight - 11
    if (category == -1) { // for Sequences: 1-2-3-4-5 & 2-3-4-5-6
        if ((counts[0] && counts[1] && counts[2] && counts[3] && counts[4]) || 
            (counts[1] && counts[2] && counts[3] && counts[4] && counts[5])) {
            
            if (!usedCategories[10]) { // Validity of category
                category = 11; // Large Straight
            }
        }
    }
    
    // Chance as last option - 13
    if (category == -1 && !usedCategories[12]) { // Category Validity
        category = 13; // Chance
    }
    // No category was selected:
    if (category == -1) {
        for (int i = 0; i < 13; i++) {
            if (!usedCategories[i]) {
                category = i + 1; // Choose unused category from 1 to 13
                break;
            }
        }
    }
    
    return category;
}

void printAvailableCategories(const int usedCategories[]) { //Valid categories printing 
    const char *categoryNames[13] = {
        "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes",
        "Three of a Kind", "Four of a Kind", "Full House",
        "Small Straight", "Large Straight", "Yahtzee", "Chance"
    };

    printf("Available Categories:\n"); 
    for (int i = 0; i < 13; i++) {
        if (!usedCategories[i]) {
            printf("%d. %s\n", i + 1, categoryNames[i]); //Print valid categories only
        }
    }
}

int calculateScore(int category, int dice[]) {
    int score = 0; //Initialize score 
    int counts[6] = {0}; //Initial count as '0'

    for (int i = 0; i < 5; i++) {
        counts[dice[i] - 1]++;
    }

    switch (category) {
        case 1: case 2: case 3: case 4: case 5: case 6: // 1 - 6
            for (int i = 0; i < 5; i++) {
                if (dice[i] == category) {
                    score += category;
                }
            }
            break;
        case 7: // 3 of a kind
            for (int i = 0; i < 6; i++) { 
                if (counts[i] >= 3) {
                    for (int j = 0; j < 5; j++) {
                        score += dice[j];
                    }
                    break;
                }
            }
            break;
        case 8: // 4 of a kind
            for (int i = 0; i < 6; i++) { 
                if (counts[i] >= 4) {
                    for (int j = 0; j < 5; j++) {
                        score += dice[j];
                    }
                    break;
                }
            }
            break;
        case 9: { // Full House
            int hasThree = 0, hasTwo = 0;
            for (int i = 0; i < 6; i++) {
                if (counts[i] == 3) {
                    hasThree = 1;
                }
                if (counts[i] == 2) {
                    hasTwo = 1;
                }
            }
            if (hasThree == 1 && hasTwo == 1 ) {
                score = 25;
            }
            break;
        }
        case 10: // Small Straight : 1-2-3-4 , 2-3-4-5 , 3-4-5-6
            if ((counts[0] && counts[1] && counts[2] && counts[3]) || (counts[1] && counts[2] && counts[3] && counts[4]) || (counts[2] && counts[3] && counts[4] && counts[5])) 
            {
                score = 30;
            }
            break;
        case 11: // Large Straight : 1-2-3-4-5 , 2-3-4-5-6
            if ((counts[0] && counts[1] && counts[2] && counts[3] && counts[4]) || (counts[1] && counts[2] && counts[3] && counts[4] && counts[5])) 
            {
                score = 40;
            }
            break;
        case 12: //Yahtzee (5 of a kind)
            for (int i = 0; i < 6; i++) {
                if (counts[i] == 5) {
                    score = 50;
                }
            }
            break;
        case 13: //Chance : Add available dice values
            for (int i = 0; i < 5; i++) {
                score += dice[i];
            }
            break;
    }
    return score;
}

void HumanTurn(int dice[], int usedCategories[], int *humanScore) {
    int choice;
    rollDice(dice); //Initial roll of dice
    printDice(dice); //Print the dice values
    rerollDice(dice, 1); //2 rerolls
    printAvailableCategories(usedCategories); //Print un used categories
    printf("Select a category: ");
    scanf("%d", &choice);

    // Validity of category
    while (choice < 1 || choice > 13 || usedCategories[choice - 1]) { //from 1-13 and not used categories
        printf("Invalid category. Choose again: ");
        scanf("%d", &choice);
    }

    usedCategories[choice - 1] = 1; //Mark '1' for selected category

    int roundScore = calculateScore(choice, dice); // Calculate the score for category

    *humanScore += roundScore; // Update human score and print it in game round
    printf("You scored %d points in category %d. Total score: %d\n", roundScore, choice, *humanScore);
}

void ComputerTurn(int dice[], int usedCategories[], int *computerScore) {
    rollDice(dice);
    printDice(dice);
    rerollDice(dice, 2);

    int computerCategory = selectComputerCategory(dice, usedCategories); //from 1-13 and not used categories by computer

    usedCategories[computerCategory - 1] = 1; //Mark '1' for selected category for computer

    int roundScore = calculateScore(computerCategory, dice); // Calculate the computer score for category

    *computerScore += roundScore; // Update computer score and print it in game round
    printf("Computer scored %d points in category %d. Total score: %d\n", roundScore, computerCategory, *computerScore);
}

int main() {
    srand(time(NULL));

    int humanScore = 0, computerScore = 0; //Initialize scores for human and computer
    int usedCategoriesHuman[13] = {0}; //Initialize used categories for human
    int usedCategoriesComputer[13] = {0}; //Initialize used categories for computer
    int dice[5]; //Initialize array of 5 dice

    printInstructions(); //Print instructions

    // 13-Round loop
    for (int round = 1; round <= 13; round++) { //Loop for 13 rounds
        printf("\n--- Round %d ---\n", round);

        // Human's Turn
        printf("\nHuman's Turn:\n");
        HumanTurn(dice, usedCategoriesHuman, &humanScore); //Human turn

        // Computer's Turn
        printf("\nComputer's Turn:\n");
        ComputerTurn(dice, usedCategoriesComputer, &computerScore); //Computer turn 
    }

    printf("\n--- Game Over ---\n");   
    printf("Final Scores:\n"); //Print final scores
    printf("Human: %d\n", humanScore);
    printf("Computer: %d\n", computerScore);

    if (humanScore > computerScore) { //Winning condition
        printf("Congratulations! You won!\n");
    } else if (humanScore < computerScore) {
        printf("Computer wins. Better luck next time!\n");
    } else {
        printf("It's a tie!\n");
    }
    system("pause");  // Pause until a key is pressed for .exe file (terminal)
    return 0;
}
