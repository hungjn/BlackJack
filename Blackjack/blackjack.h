#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_CARDS 10

#ifndef BLACKJACK_H
#define BLACKJACK_H

void getName(char *string);
void welcomeUser(char *name);
void blackJack(char *name);
void printHands (int *cHand,int *pHand);
int randomCard(void);
int hitOrStand (int *cHand,int *pHand);
void addHand(int *hand);
int returnSum(int *hand);
int aceOneSum(int *hand);
int countCards(int *hand);
void resetHands(int *cHand,int *pHand);
int checkHand(int *hand);
int winRound(char *name, int balance, int bet);
int loseRound(char *name, int balance, int bet);
int tieRound(int balance);
int computerPlay(int *cHand,int *pHand);
int thousand(void);
void lose(void);
int betting(int bet,int balance);
int playAgain(void);

#endif