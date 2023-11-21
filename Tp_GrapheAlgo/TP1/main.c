#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 50

typedef struct {
    bool oriente;
    int n;              //nb de sommets
    int m;              //Nb d'arcs
    int **matrice;
} Graphe;


/*Question 1

int init_graphe(Graphe *G, bool oriente, int n) pour créer un graphe orienté ou non
(selon oriente) et ayant n sommets. La fonction initialise le graphe sans connexion mais initia1
lise la matrice d’adjacence avec des 0. La fonction retourne 1 en cas de succès, 0 en cas d’erreur
(problème mémoire par exemple).*/

int init_graphe(Graphe *G, bool oriente, int n) {
    G->oriente = oriente;
    G->n = n;
    G->m = 0;

    G->matrice = (int **)malloc(MAX * sizeof(int *));
    if (G->matrice == NULL) {
        return 0;
    }

    for (int i = 0; i < MAX; i++) {
        G->matrice[i] = (int *)malloc(MAX * sizeof(int));
        //S'il y a un problème dans la création de la matrice, on doit libérer toutes celles précédemment créées puis le tableau de tableaux
        if (G->matrice[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(G->matrice[j]);
            }
            free(G->matrice);
            return 0;
        }
        else{
            for (int j = 0; j < n; j++) {
                G->matrice[i][j] = 0;
            }
        }
    }

    return 1;
}

/*Question 2

int ajout_lien(Graphe *G, int id1, int id2) qui permet d’ajouter une connexion dans le
graphe G entre les deux sommets connus par leurs identifiants. Si le graphe est orienté la fonction
ajoute l’arc (id1, id2). Dans le cas non orienté elle ajoute l’arête entre les deux sommets. La
fonction retourne 1 en cas de succès, 0 en cas d’échec (si la connexion existait déjà par exemple).*/

int ajout_lien(Graphe *G, int id1, int id2){
    if (G->oriente == false){
        if ((G->matrice[id1-1][id2-1] == 1) &&(G->matrice[id2-1][id1-1] == 1))
            return 0;
        G->matrice[id1-1][id2-1] = 1;
        G->matrice[id2-1][id1-1] = 1;
        G->m = (G->m)+1;
        return 1;
    }
    else{
        if (G->matrice[id1-1][id2-1] == 1)
            return 0;
        G->matrice[id1-1][id2-1] = 1;
        G->m = (G->m)+1;
        return 1;
    }
}

/*Question 3

int supp_lien(Graphe *G, int id1, int id2) pour supprimer la connexion entre id1 et
id2, selon l’orientation du graphe. La fonction retourne 1 en cas de succès, 0 sinon (connexion
inexistante). */

int supp_lien(Graphe *G, int id1, int id2){

    if (G->oriente == false){
        if ((G->matrice[id1-1][id2-1] == 0) &&(G->matrice[id2-1][id1-1] == 0))
            return 0;
        G->matrice[id1-1][id2-1] = 0;
        G->matrice[id2-1][id1-1] = 0;
        G->m = (G->m)-1;
        return 1;
    }
    else{
        if (G->matrice[id1-1][id2-1] == 0)
            return 0;
        G->matrice[id1-1][id2-1] = 0;
        G->m = (G->m)-1;
        return 1;
    }

}

/*Question 4

int ajout_sommet(Graphe *G, int id) pour ajouter un nouveau sommet dont l’identifiant est
id. Ce sommet est initialement sans connexion. La fonction n’ajoute pas le sommet si l’identifiant
existe déjà et retourne 0. Elle retourne 1 en cas de succès */

int ajout_sommet(Graphe *G, int id){

    for (int i=G->n;i<id;i++){
        for (int j=0;j<id;j++){
                G->matrice[i][j] = 0;
        }
    }
    for (int i=G->n;i<id;i++){
        for (int j=0;j<G->n;j++){
                G->matrice[j][i] = 0;
        }
    }

    G->n = id;

    return 1;

}


/*Question 5

void affiche_simple(Graphe *G) qui affiche (très) simplement les informations du graphe :
nombre de sommets, nombre de connexions, type (orienté/non orienté), et contenu de la matrice
d’adjacence */

void affiche_simple(Graphe *G){
    printf("Nombre de sommets = %d \n",G->n);
    printf("Nombre de connexions = %d \n",G->m);

    if (G->oriente == true)
        printf("C'est un graphe orienté \n");
    else{
    printf("C'est un graphe non-orienté \n");}

    for (int i=0;i<G->n;i++){
    printf("\n");
    for (int j=0;j<G->n;j++){
        printf("%d ",G->matrice[i][j]);
    }
}

}

/*Question 6

int est_adjacent_direct(Graphe *G, int id1, int id2) qui retourne 1 si le sommet id2
est un successeur direct de id1 (cas orienté) ou un voisin direct de id1 (cas non orienté), 0 sinon */

int est_adjacent_direct(Graphe *G, int id1, int id2){
        if (G->matrice[id1-1][id2-1] == 1)
            printf("Le sommet %d est voisin direct (ou successif si orienté) de %d \n",id2,id1);
            return 1;
        return 0;

}

/*Question 7

void degres(Graphe *G, int *de, int *ds) qui calcule et retourne via les tableaux de et dg
les degrés entrant et sortant des sommets, respectivement. Dans le cas d’un graphe non orienté
la fonction retourne deux tableaux contenant les mêmes valeurs : le degré de chaque sommet. */

void degres(Graphe *G, int ds[], int de[]){
        if (G->oriente == false){
            for (int i=0;i<G->n;i++){

                for (int j=0;j<G->n;j++){

                    if (G->matrice[i][j] == 1){
                        de[i] = de[i] +1;
                        ds[i] = ds[i] +1;
                    }
                }
            }
        }
        else{
            for (int i=0;i<G->n;i++){

                for (int j=0;j<G->n;j++){
                    if (G->matrice[i][j] == 1){
                        de[j] = de[j] + 1;
                        ds[i] = ds[i] + 1;

                    }
                }
            }
        }
}

/* Question 8

void libere_graphe(Graphe *G) permettant de libérer l’intégralité de l’espace mémoire alloué
pour le graphe. */

void clearGraph(Graphe *G){

    for (int i = 0; i < MAX; i++) {
        free(G->matrice[i]);
            }
    free(G->matrice);
    }


void putInFichier(Graphe *G, char *fichier,int ds[], int de[]){
    int o;
    FILE* fich = NULL;
    fich = fopen(fichier,"w");
    if (fich == NULL){
        printf("ERROR FICHIER");
        return;}
    else{
        if (G->oriente == true)
            o=1;
        else{
            o=0;
        }

        fprintf(fich,"%d %d %d \n",o,G->n,G->m);

         if (G->oriente == false){
            for (int i=0;i<G->n;i++){

                for (int j=i;j<G->n;j++){

                    if (G->matrice[i][j] == 1){
                        fprintf(fich,"%d %d \n",i+1,j+1);
                    }
                }
            }
        }
        else{
            for (int i=0;i<G->n;i++){

                for (int j=0;j<G->n;j++){
                    if (G->matrice[i][j] == 1){
                        fprintf(fich,"%d %d \n",i+1,j+1);

                    }
                }
            }
        }

        fclose(fich);

    }


}

/* ***************************** EXERCICE 2 ***************************** */

 void PW(Graphe *G, int ds[], int de[]){
    int debis[G->n];
    int dsbis[G->n];
    int clr = 1;

    for (int i = 0; i<G->n;i++){
        debis[i] = de[i];
        dsbis[i] = ds[i];
    }





 }

void tri_deca(int t[],int t2[],int taille){
    int tmp;
    for (int i=0;i<taille-1;i++){
        for (int j=i+1;j<taille;j++){
            if (t[i]>=t[j]){
                deg_max = i;
            }
            else{
                deg_max=j;
            }
        }
        if (deg_max != i){
            tmp = t[j];
            t[j]=t[i];
            t[i] = tmp;

            tmp = t2[j];
            t2[j]=t2[i];
            t2[i] = tmp;
        }
    }
}
/* ******************************** MAIN ******************************** */
int main()
{

Graphe monGraphe;
init_graphe(&monGraphe, true, 5);

affiche_simple(&monGraphe);

printf("\n");
printf("---------------------------------- \n");

ajout_lien(&monGraphe,1,2);

ajout_lien(&monGraphe,3,4);


affiche_simple(&monGraphe);

printf("\n");
printf("----------------------------------  \n");

//supp_lien(&monGraphe,1,2);

affiche_simple(&monGraphe);

printf("\n");
printf("----------------------------------  \n");

ajout_sommet(&monGraphe,7);

affiche_simple(&monGraphe);

printf("\n");
printf("----------------------------------  \n");

est_adjacent_direct(&monGraphe,3,4);
est_adjacent_direct(&monGraphe,4,3);

printf("\n");
printf("----------------------------------  \n");

int ds[monGraphe.n];
int de[monGraphe.n];


for (int i=0;i<monGraphe.n;i++){
    de[i]=0;
    ds[i]=0;
}

degres(&monGraphe,ds,de);

for (int i=0;i<monGraphe.n;i++){
    printf("Le point %d à un degré sortant valant %d et un degré entrant valant %d \n",i+1,ds[i],de[i]);
}
printf("---------------------------------- \n");

putInFichier(&monGraphe,"text.txt",ds,de);

// *************** Exo 2 *************
int col[monGraphe.n];



}
