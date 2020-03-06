
#include <iostream>
#include <mutex>

#include "arbitre.h"

using namespace std;

int main()
{
    //initialise la graine du générateur aléatoire
    std::srand(20000);

    // création de l'Arbitre (graine , joueur 1, joueur 2 , nombre de parties)
    Arbitre a (9999, player::A_, player::RAND, 1);
    // commence le challenge
    a.challenge();
    return 0;
}
