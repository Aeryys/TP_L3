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
             if(T[i]!=0) printf("re�us %d signaux de num�ro %d et de nom %s\n",T[i], i, strsignal(i));
        }
    }


int main(int argc, char **argv)
{
    int i;
    for(i=0;i<NSIG;i++) //Remplissage du tableau de 0
        { T[i]=0;}
    for(i=1;i<NSIG;i++)
        { signal(i,f);}
    for(;;); // boucle infinie pour attendre l�arriv�e des signaux
    return 0 ;
}

//Fonction signal : d�finit le gestionnaire de signaux. Arg 1 -> num�ro du signal, Arg 2 -> fonction � appeler qui deviendra le gestionnaire
