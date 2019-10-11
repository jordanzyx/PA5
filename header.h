//
// Created by Jordan on 10/8/2019.
//

typedef struct{
    int ones;
    int twos;
    int threes;
    int fours;
    int fives;
    int sixes;
    int threeOfAKind;
    int fourOfAKind;
    int fullHouse;
    int smallStraight;
    int largeStraight;
    int yahtzee;
    int chance;
}Scoresheet;

typedef struct {
    Scoresheet scoresheet;
    int dice[5];
} Player;

int askYesNoQuestion(char question[]);
void displayDice(Player player[2],int which);
void startUpMenu();
void printMenu();
void printRules();
void printGoodbye();
void printScoresheet(Player player[2],int which);
void startGame();
void playRound(Player *one,Player *two);
void playTurn(Player player[2],int which);
void pressAnyKeyToRoll();
void rollCertainDice(Player player[2],int which,int spots[5]);
int askIfTheyWantToUseScore(Player player[2],int which);
int getScoreFromScoresheet(Player player[2],int which,int spot);
int getScoreFromDice(int spot,int dice[5]);
int isScoreUsed(int score);
void applyDiceToScoresheet(Player player[2],int which);
void askWhichDiceToReRoll();
int doesArrayContainInt(int value,int array[5]);
int rollDie();
Player getCurrentPlayer(Player one,Player two,int turn);

//Scoring
int isYahtzee(int dice[5]);
int isSmallStraight(int dice[5]);
int isLargeStraight(int dice[5]);
int isFullhouse(int dice[5]);
int isThreeOfAKind(int dice[5]);
int isFourOfAKind(int dice[5]);
int calculateSumOf(int number,int dice[5]);