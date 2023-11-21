#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>


int T[NSIG];

void f(int sig)
{
    int i;
    T[sig]++;
    for(i=1;i<NSIG;i++)
        {
             if(T[i]!=0) printf("reçus %d signaux de numéro %d et de nom %s\n",T[i], i, strsignal(i));
        }
    }


int main(int argc, char **argv)
{
    int i;
    for(i=0;i<NSIG;i++) //Remplissage du tableau de 0
        { T[i]=0;}
    for(i=1;i<NSIG;i++)
        { signal(i,f);}
    for(;;); // boucle infinie pour attendre l’arrivée des signaux
    return 0 ;
}

//Fonction signal : définit le gestionnaire de signaux. Arg 1 -> numéro du signal, Arg 2 -> fonction à appeler qui deviendra le gestionnaire
