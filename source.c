//
// Created by Jordan on 10/8/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

#define PRINT_RULES 1
#define START_GAME 2
#define EXIT 3

#define SUM_OF_ONES 1
#define SUM_OF_TWOS 2
#define SUM_OF_THREES 3
#define SUM_OF_FOURS 4
#define SUM_OF_FIVES 5
#define SUM_OF_SIXES 6
#define THREE_OF_A_KIND 7
#define FOUR_OF_A_KIND 8
#define FULL_HOUSE 9
#define SMALL_STRAIGHT 10
#define LARGE_STRAIGHT 11
#define YAHTZEE 12
#define CHANCE 13

void startUpMenu() {
    srand(time(NULL));
    int choice = 0;

    do {
        printMenu();
        scanf("%d", &choice);
        switch (choice) {
            case PRINT_RULES:
                printRules();
                break;
            case START_GAME:
                startGame();
                break;
        }

    } while (choice != EXIT);

    printGoodbye();
}

void printMenu() {
    printf("1. Print game rules\n");
    printf("2. Start a game of Yahtzee\n");
    printf("3. Exit\n");
}

void printRules() {

}

void printGoodbye() {
    printf("Thank you for playing! Goodbye :)\n");
}

void printScoresheet(Player player[2],int which) {
    printf("------ Your Scoresheet ------\n");
    printf("1. Sum of 1's : %d\n", player[which].scoresheet.ones);
    printf("2. Sum of 2's : %d\n", player[which].scoresheet.twos);
    printf("3. Sum of 3's : %d\n", player[which].scoresheet.threes);
    printf("4.Sum of 4's : %d\n", player[which].scoresheet.fours);
    printf("5.Sum of 5's : %d\n", player[which].scoresheet.fives);
    printf("6.Sum of 6's : %d\n", player[which].scoresheet.sixes);
    printf("-----------------------------\n");
    printf("7. Three of a Kind : %d\n", player[which].scoresheet.threeOfAKind);
    printf("8. Four of a Kind : %d\n", player[which].scoresheet.fourOfAKind);
    printf("9. Full house : %d\n", player[which].scoresheet.fullHouse);
    printf("10. Small straight : %d\n", player[which].scoresheet.smallStraight);
    printf("11. Large straight : %d\n", player[which].scoresheet.largeStraight);
    printf("12. Yahtzee : %d\n", player[which].scoresheet.yahtzee);
    printf("13. Chance : %d\n", player[which].scoresheet.chance);
}

int askIfTheyWantToUseScore(Player player[2],int which) {
    displayDice(player,which);
    printScoresheet(player,which);

    return askYesNoQuestion("Would you like to use your current dice on your scoresheet?");
}

void startGame() {
    int round = 1;



    Player p1 = {{0}};
    Player p2 = {{0}};

    Player players[2] = {p1,p2};

    printf("%p, %p", &p1,&p2);

    while (round < 14) {
        playTurn(players,0);
        printf("Before player two roll\n");
        playTurn(players,1);
        round++;
    }

}

void playTurn(Player player[2],int which){

    int rolls = 0;
    int toRoll[5] = {0, 1, 2, 3, 4};

    while (rolls < 3) {
        pressAnyKeyToRoll();
        rollCertainDice(player,which, toRoll);
        rolls++;

        int choice = askIfTheyWantToUseScore(player,which);

        if (choice == 1) {
            applyDiceToScoresheet(player,which);
            break;
        } //Ask what dice they want to reroll
        else continue;
    }

}

void playRound(Player *one, Player *two) {

}

void rollCertainDice(Player player[2],int which, int spots[5]) {

    int written[5] = {-1, -1, -1, -1, -1};
    for (int i = 0; i < 5; ++i) {
        int potential = spots[i];
        if (potential >= 0 && potential < 5) {
            if (doesArrayContainInt(potential, written) == 1)continue;
            written[i] = potential;
        }
    }

    for (int i = 0; i < 5; ++i) {
        int die = written[i];
        if (die < 0)continue;
        int roll = rollDie();
        player[which].dice[die] = roll;
    }
}

int doesArrayContainInt(int value, int array[5]) {
    for (int i = 0; i < 5; ++i) {
        if (array[i] == value)return 1;
    }
    return -1;
}

void applyDiceToScoresheet(Player player[2],int which) {
    int choice = 0;
    int used = 1;
    while ((choice < 1 || choice > 13) || used == 1) {
        printf("Which score would you like to apply your dice to? [1-13]?\n");
        scanf("%d", &choice);
        if (choice < 1 || choice > 13)continue;
        int currentScoreAtChoice = getScoreFromScoresheet(player,which, choice);
        used = isScoreUsed(currentScoreAtChoice);

        if (used == 1) {
            printf("That score is either scratched or you have already used it\n");
            continue;
        }


        switch (choice) {
            case SUM_OF_ONES:
                player[which].scoresheet.ones = getScoreFromDice(choice, player[which].dice);
                break;
            case SUM_OF_TWOS:
                printf("%d\n", player[which].scoresheet.twos);
                player[which].scoresheet.twos = getScoreFromDice(choice, player[which].dice);
                printf("%d",player[which].scoresheet.twos);
                break;
            case SUM_OF_THREES:
                player[which].scoresheet.threes = getScoreFromDice(choice, player[which].dice);
                break;
            case SUM_OF_FOURS:
                player[which].scoresheet.fours = getScoreFromDice(choice, player[which].dice);
                break;
            case SUM_OF_FIVES:
                player[which].scoresheet.fives = getScoreFromDice(choice, player[which].dice);
                break;
            case SUM_OF_SIXES:
                player[which].scoresheet.sixes = getScoreFromDice(choice, player[which].dice);
                break;
            case THREE_OF_A_KIND:
                if (isThreeOfAKind(player[which].dice) == 1)
                    player[which].scoresheet.threeOfAKind = getScoreFromDice(choice, player[which].dice);
                break;
            case FOUR_OF_A_KIND:
                if (isFourOfAKind(player[which].dice) == 1)
                    player[which].scoresheet.fourOfAKind = getScoreFromDice(choice, player[which].dice);
                break;
            case FULL_HOUSE:
                if (isFullhouse(player[which].dice) == 1)
                    player[which].scoresheet.fullHouse = getScoreFromDice(choice, player[which].dice);
                break;
            case SMALL_STRAIGHT:
                if (isSmallStraight(player[which].dice) == 1)
                    player[which].scoresheet.smallStraight = getScoreFromDice(choice, player[which].dice);
                break;
            case LARGE_STRAIGHT:
                if (isLargeStraight(player[which].dice) == 1)
                    player[which].scoresheet.largeStraight = getScoreFromDice(choice, player[which].dice);
                break;
            case YAHTZEE:
                if (isYahtzee(player[which].dice) == 1)player[which].scoresheet.yahtzee = getScoreFromDice(choice, player[which].dice);
                break;
            case CHANCE:
                player[which].scoresheet.chance = getScoreFromDice(choice, player[which].dice);
                break;
        }

    }
}

int getScoreFromDice(int spot, int dice[5]) {
    switch (spot) {

        case SUM_OF_ONES:
        case SUM_OF_TWOS:
        case SUM_OF_THREES:
        case SUM_OF_FOURS:
        case SUM_OF_FIVES:
        case SUM_OF_SIXES:
            return calculateSumOf(spot, dice);

        case FULL_HOUSE:
            return 25;
        case SMALL_STRAIGHT:
            return 30;
        case LARGE_STRAIGHT:
            return 40;
        case YAHTZEE:
            return 50;

        case THREE_OF_A_KIND:
        case FOUR_OF_A_KIND:
        case CHANCE:
            return dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
    }
}

int getScoreFromScoresheet(Player player[2],int which, int spot) {
    switch (spot) {
        case SUM_OF_ONES:
            return player[which].scoresheet.ones;
        case SUM_OF_TWOS:
            return player[which].scoresheet.twos;
        case SUM_OF_THREES:
            return player[which].scoresheet.threes;
        case SUM_OF_FOURS:
            return player[which].scoresheet.fours;
        case SUM_OF_FIVES:
            return player[which].scoresheet.fives;
        case SUM_OF_SIXES:
            return player[which].scoresheet.sixes;
        case THREE_OF_A_KIND:
            return player[which].scoresheet.threeOfAKind;
        case FOUR_OF_A_KIND:
            return player[which].scoresheet.fourOfAKind;
        case FULL_HOUSE:
            return player[which].scoresheet.fullHouse;
        case SMALL_STRAIGHT:
            return player[which].scoresheet.smallStraight;
        case LARGE_STRAIGHT:
            return player[which].scoresheet.largeStraight;
        case YAHTZEE:
            return player[which].scoresheet.yahtzee;
        case CHANCE:
            return player[which].scoresheet.chance;
    }
    return -2;
}

int isScoreUsed(int score) {
    return score == 0 ? -1 : 1;
}

void pressAnyKeyToRoll() {
    printf("-- Enter Any Key to Roll --\n");
    scanf(" %c");
}

void displayDice(Player player[2],int which) {
    
    printf("------ Your Roll ------\n");
    for (int i = 0; i < 5; ++i) {
        printf("Dice %d. %d\n", (i + 1), player[which].dice[i]);
    }
}


int rollDie() {
    return (rand() % 6) + 1;
}


int askYesNoQuestion(char question[]) {
    printf("%s[y/n]\n", question);
    char c = 'a';
    while (c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
        scanf(" %c", &c);
    }

    return c == 'y' || c == 'Y' ? 1 : -1;

}

int calculateSumOf(int number, int dice[5]) {
    int amount = 0;
    for (int i = 0; i < 5; ++i) {
        int found = dice[i];
        if (found == number)amount += number;
    }
    return amount == 0 ? -1 : amount;
}

int isYahtzee(int dice[5]) {
    int first = dice[0];
    for (int i = 1; i < 5; ++i) {
        if (dice[i] == first)continue;
        return -1;
    }
    return 1;
}

int isSmallStraight(int dice[5]) {
    if (doesArrayContainInt(1, dice) + doesArrayContainInt(2, dice) + doesArrayContainInt(3, dice) +
        doesArrayContainInt(4, dice) == 4)
        return 1;
    if (doesArrayContainInt(2, dice) + doesArrayContainInt(3, dice) + doesArrayContainInt(4, dice) +
        doesArrayContainInt(5, dice) == 4)
        return 1;
    if (doesArrayContainInt(3, dice) + doesArrayContainInt(4, dice) + doesArrayContainInt(5, dice) +
        doesArrayContainInt(6, dice) == 4)
        return 1;
    return -1;
}

int isLargeStraight(int dice[5]) {
    if (doesArrayContainInt(1, dice) + doesArrayContainInt(2, dice) + doesArrayContainInt(3, dice) +
        doesArrayContainInt(4, dice) + doesArrayContainInt(5, dice) == 5)
        return 1;
    if (doesArrayContainInt(2, dice) + doesArrayContainInt(3, dice) + doesArrayContainInt(4, dice) +
        doesArrayContainInt(5, dice) + doesArrayContainInt(6, dice) == 5)
        return 1;
    return -1;
}

int isFullhouse(int dice[5]) {
    int first = dice[0];
    int second = 0;
    for (int i = 1; i < 5; ++i) {
        int new = dice[i];
        if (new == first && second == 0)continue;
        if (new != first && second == 0)second = new;
        if (new != first && new != second)return -1;
    }
    return 1;
}

int isThreeOfAKind(int dice[5]) {
    for (int i = 0; i < 5; ++i) {
        int die = dice[i];
        int count = 0;
        for (int j = 0; j < 5; ++j) {
            if (dice[j] == die)count++;
        }
        if (count == 3)return 1;
    }
    return -1;
}

int isFourOfAKind(int dice[5]) {
    for (int i = 0; i < 5; ++i) {
        int die = dice[i];
        int count = 0;
        for (int j = 0; j < 5; ++j) {
            if (dice[j] == die)count++;
        }
        if (count == 4)return 1;
    }
    return -1;
}
