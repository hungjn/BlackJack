// Little Black Jack Game made by Hung Nguyen for fun (3-4 hours)

#include <time.h>
#include "blackjack.h"

int main(void)
{
    char name[20];
    srand(time(0));

    getName(name);
    while (1)
    {
        welcomeUser(name);
        blackJack(name);
        if (playAgain() == 0)
            break;
    }
    return 0;
}