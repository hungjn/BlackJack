#include "blackjack.h"

// Function Definitions: ----------------------------------------

// Prompts user for name and stores string within the given input
void getName(char *string)
{
    char name[20];

    printf("Please Enter Your Name: ");
    fgets(name,20,stdin);
    printf("\n\n\n");

    // Remove newline from fgets
    for (int i = 0; i < 20; i++)
    {
        if (name[i] == '\n')
        {
            name[i] = '\0';
            break;
        }
    }

    strcpy(string,name);
}

// Welcome message and start
void welcomeUser(char *name)
{
    int start = 0;

    printf("==================================================\n");
    printf("Welcome to Hung's Black Jack Game %s!\n",name);
    printf("==================================================\n\n");
    printf("Instructions:\n");
    printf("\t- Start with $50 and try to win $1000 playing blackjack!\n");
    printf("\t- Try to get to 21 in your hand without busting\n\n\n\n");
    printf("Are you ready to start? Enter 1 to start: ");
    
    while (1)
    {
        scanf("%d", &start);

        switch (start)
        {
            case 1: return;
            default: printf("Take your time, press 1 to start.\n");
        }
    }
}

// Black Jack Game
void blackJack(char *name)
{
    int balance = 50, bet = 0, winnerCheck = 0, result, redo, stand;
    int *computerHand = calloc(MAX_CARDS,sizeof(int));
    int *playerHand = calloc(MAX_CARDS,sizeof(int));

    while (balance > 0)
    {
        // Checks if user won and has seen the winner message yet
        if (balance >= 1000 && winnerCheck == 0)
        {
            if (thousand() == 0)
            {
                printf("Thank you for playing!\n");
                return;
            }
            winnerCheck++;
        }

        redo = 1; // flag for continuing a round
        stand = 0; // flag for stands (determines round termination)
        resetHands(computerHand,playerHand);
        addHand(computerHand);
        addHand(playerHand);

        printf("\n========================");
        printf("\nCurrent Balance: $%d",balance);
        printf("\n========================");
        printf("\n\n\n");
        bet = betting(bet,balance);
        printf("\n\n");
        printHands(computerHand,playerHand);
        if (hitOrStand(computerHand,playerHand) == 0)
            stand = 1;

        while (redo == 1)
        {
            redo = 0;

            if (stand == 1)
            {
                result = computerPlay(computerHand,playerHand);
                printHands(computerHand,playerHand);
                
                switch(result)
                {
                    case 1: balance = winRound(name,balance,bet); break;
                    case -1: balance = loseRound(name,balance,bet); break;
                    case 0: balance = tieRound(balance); break;
                }
                break;
            }

            if (returnSum(playerHand) == 21)
                balance = winRound(name,balance,bet);
            else if (returnSum(playerHand) > 21)
            {
                if (aceOneSum(playerHand) == 21)
                    balance = winRound(name,balance,bet);
                else if (aceOneSum(playerHand) > 21)
                    balance = loseRound(name,balance,bet);
                else
                {
                    printHands(computerHand,playerHand);
                    if (hitOrStand(computerHand,playerHand) == 0)
                        stand = 1;
                    redo = 1;
                }
            }
            else
            {
                result = computerPlay(computerHand,playerHand);
                printHands(computerHand,playerHand);
                
                switch(result)
                {
                    case 1: balance = winRound(name,balance,bet); break;
                    case -1: balance = loseRound(name,balance,bet); break;
                    case 0: balance = tieRound(balance); break;
                }
                redo = 0;
            }
        }
    }
    printf("You went bankrupt, better luck next time!\n");
}

void printHands (int *cHand,int *pHand)
{
    int cCount = 0,pCount = 0;
    cCount = countCards(cHand);
    pCount = countCards(pHand);

    printf("Computer's Hand:\n");
    for (int i = 0; i < cCount; i++)
        printf("+-----+\t");
    printf("\n");
    for (int i = 0; i < cCount; i++)
        printf("|     |\t");
    printf("\n");
    for (int i = 0; i < MAX_CARDS; i++)
    {
        if (cHand[i] == 0)
            break;
        
        switch(cHand[i])
        {
            case 1: printf("| Ace |\t"); break;
            case 11: printf("|Jack |\t"); break;
            case 12: printf("|Queen|\t"); break;
            case 13: printf("|King |\t"); break;
            case 10: printf("| 10  |\t"); break;
            default: printf("|  %d  |\t",cHand[i]);
        }
    }
    printf("\n");
    for (int i = 0; i < cCount; i++)
        printf("|     |\t");
    printf("\n");
    for (int i = 0; i < cCount; i++)
        printf("+-----+\t");
    printf("\n\n");
    
    printf("Your Hand:\n");
    for (int i = 0; i < pCount; i++)
        printf("+-----+\t");
    printf("\n");
    for (int i = 0; i < pCount; i++)
        printf("|     |\t");
    printf("\n");
    for (int i = 0; i < MAX_CARDS; i++)
    {
        if (pHand[i] == 0)
            break;
        
        switch(pHand[i])
        {
            case 1: printf("| Ace |\t"); break;
            case 11: printf("|Jack |\t"); break;
            case 12: printf("|Queen|\t"); break;
            case 13: printf("|King |\t"); break;
            case 10: printf("| 10  |\t"); break;
            default: printf("|  %d  |\t",pHand[i]);
        }
    }
    printf("\n");
    for (int i = 0; i < pCount; i++)
        printf("|     |\t");
    printf("\n");
    for (int i = 0; i < pCount; i++)
        printf("+-----+\t");
    printf("\n\n");
}

// Generates a random num 1-13
int randomCard(void)
{
    int num = 0;

    while (num == 0) // prevents zero output
        num = rand() % 14;
    return num;
}

int hitOrStand (int *cHand,int *pHand)
{
    int hs, status = 0;

    while (status == 0)
    {
        printf("Hit or Stand? Enter 1 for Hit and 0 for Stand: ");
        scanf("%d",&hs);
        printf("\n");
        
        if (hs == 1)
        {
            addHand(pHand);
            printHands(cHand,pHand);
            status = checkHand(pHand);
        }
        else if (hs == 0)
        {
            status = 1;
            return 0;
        }
    }
    return 1;
}

// Insert a random num into hand (array)
void addHand(int *hand)
{
    for (int i = 0; i < MAX_CARDS; i++)
    {
        if (hand[i] == 0)
        {
            hand[i] = randomCard();
            return;
        }
    }
}

// Returns sum of given hand (array)
int returnSum(int *hand)
{
    int total = 0;
    for (int i = 0; i < MAX_CARDS; i++)
    {
        switch(hand[i])
        {
            case 11:
            case 12:
            case 13: total += 10; break;
            case 1:
                if (total + 11 > 21)
                    total += 1;
                else
                    total += 11;
                break;
            default: total += hand[i];
        }
    }
    return total;
}

// Returns sum of given hand (array) assuming all aces are set to 1
int aceOneSum(int *hand)
{
    int total = 0;
    for (int i = 0; i < MAX_CARDS; i++)
    {
        switch(hand[i])
        {
            case 11:
            case 12:
            case 13: total += 10; break;
            default: total += hand[i];
        }
    }
    return total;
}

int countCards(int *hand)
{
    int cardCount = 0;

    for (int i = 0; i < MAX_CARDS; i++)
    {
        if (hand[i] != 0)
            cardCount++;
    }
    return cardCount;
}

void resetHands(int *cHand,int *pHand)
{
    for (int i = 0; i < MAX_CARDS; i++)
    {
        cHand[i] = 0;
        pHand[i] = 0;
    }
}

int checkHand(int *hand)
{
    int sum = returnSum(hand);
    return sum >= 21 ? 1 : 0;
}

int winRound(char *name, int balance, int bet)
{
    printf("*Congratulations* %s, you have earned $%d\n\n",name,bet);
    return balance + bet;
}

int loseRound(char *name, int balance, int bet)
{
    printf("Sorry %s, you have lost $%d\n\n",name,bet);
    return balance - bet;
}

int tieRound(int balance)
{
    printf("You have tied, no money was gained or loss\n\n");
    return balance;
}

// Plays out the computer's run
int computerPlay(int *cHand,int *pHand)
{
    int playerSum = returnSum(pHand) > 21 ? aceOneSum(pHand) : returnSum(pHand);
    while (1)
    {
        while (playerSum > returnSum(cHand))
            addHand(cHand);
        
        if (returnSum(cHand) > 21)
        {
            if (aceOneSum(cHand) > 21)
                return 1;
            else if (aceOneSum(cHand) == 21)
                return -1;
            else
            {
                addHand(cHand);
                continue;
            }
        }
        else if (returnSum(cHand) > playerSum)
            return -1;
        else if (returnSum(cHand) == playerSum)
            return 0;

    }
}

// Winner message and replay option
int thousand(void)
{
    int cont;
    printf("Congratulations! You have beat the game!\n");
    printf("Would you like to continue playing? Enter 1 for yes, 0 for no: ");
    scanf("%d", &cont);
    return cont;
}

void lose(void)
{
    printf("Sorry, you have no more money :(\n");
}

// Prompt user for betting amount
int betting(int bet,int balance)
{
    int amount = 0;
    printf("How much would you like to bet from your balance? ");
    
    while (amount > balance || amount == 0)
    {
        scanf("%d", &amount);
        if (amount > balance || amount == 0)
            printf("Please Enter a Valid Amount of Money.\n");
    }
    return amount;
}

int playAgain(void)
{
    int yesno;
    printf("\n\nWould You Like to Play Again? Enter 1 for yes or 0 for no: ");
    scanf("%d",&yesno);
    return yesno;
}