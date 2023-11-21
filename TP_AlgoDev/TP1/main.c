#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//TP Algo_Dev VILAIN Yoran

typedef struct _Client {
int temps; // l ’ instant d’ arrivee en caisse represente de facon simplifiee
int volume; // volume de courses
int prio; // 0 si non prioritaire , 1 sinon
struct _Client * suiv, * prec;
} Client, * Liste ;  //Liste c'est un pointeur sur CLient, CLient c'est littéralement le CLient


typedef struct {
int no; // le numero de la caisse
Liste debut, fin ; // le debut et la fin de la file d’ attente de la caisse
} Caisse;

Client* creerClient(int tps, int vlm, int prior){ //Création du client, on renvoie un pointeur sur Client

    Client* client = NULL; //Création du pointeur
    client = (Client*)malloc(sizeof(Client)); //Réservation de la mémoire
    if (client == NULL)
        exit(EXIT_FAILURE); //Erreur si l'allocation à échouée
    else{
        client->temps = tps;
        client->prio = prior; //Attribution des paramètres du client
        client->volume = vlm;
        client->prec = NULL;
        client->suiv = NULL;
    }
    return client;
}

Caisse ajouterClientCaisse(Caisse c, Client* client){ //Fonction servant à ajouter un client dans la file
    if (c.debut == NULL){
        c.debut = client; //Si la file est vide, le client devient et le début et la fin.
        c.fin = client;
    }
    else{
        c.fin->suiv = client; //On change la fin, le client ajouté devient la nouvelle fin.
        client->prec = c.fin;
        c.fin = client;
        if (client->prio == 1){ //Cas ou notre client est prioritaire et doit passer devant
            while (client->prec != NULL && client->prec->prio != 1){ //On fait remonter le client tant qu'il n'y a pas d'autre personnes prioritaires ou qu'il arrive en premier (cas ou client->prec = NULL)

                    int tmp_vlm = client->volume; //On n'interchange pas vraiment les clients, on interchange les valeurs ce qui revient au même
                    int tmp_prio = client->prio;
                    int tmp_tps = client->temps; //Ces 3 variables servent de variables tampons, elles prenennt les paramètres du client actuel

                    client-> prio = client->prec->prio;
                    client ->volume = client->prec->volume;  //On remplace les paramètres du client actuel par ceux du client devant
                    client -> temps = client->prec->temps;

                    client->prec->prio = tmp_prio;
                    client->prec->temps = tmp_tps;      //On remplace les paramètres du clients devant par ceux du client actuel (mis dans les valeurs tampons)
                    client->prec->volume = tmp_vlm;

                    client = client->prec;   //Le client de devant devient notre client actuel (comme s'ils avaient échangés de place)


                }
            }
        }

    return c;

    }

void afficherFileCaisse(Caisse c){ //Fonction qui sert à afficher les clients présents dans une file de caisse
    if (c.debut == NULL)
        printf("La caisse %d est vide \n",c.no); //Cas d'une caisse vide
    else{

    Client* act = c.debut; //Création d'un pointeur sur Client qui va nous permettre de parcourir chaque client en poitant vers leur adresse
    int cpt = 1; //Compteur de clients, c'est juste pour le visuel

    printf("Caisse %d : \n",c.no);
    while (act != NULL){ //On tourne jusqu'à ce qu'on sorte de la file (Le client est alors NULL)
        printf("Client %d avec : tps = %d, prio = %d, volume = %d \n",cpt,act->temps,act->prio,act->volume);
        cpt = cpt+1;
        act = act->suiv; //On passe au client suivant
        }
    }
    printf("-------------------------------------------- \n");

}

void afficherToutesLesCaisses(Caisse* t[]){ //Fonction qui affiche les files de toutes les caisses : On appelle afficherFileCaisse pour chaque caisse du tableau.
    printf("ACTIVATION AFFICHAGE TOUTES LES CAISSES \n");
    for (int i=0;i<4;i++){
        afficherFileCaisse(*t[i]);  //Utilsiation de pointeur vu qu'il n'y a que des adresses dans notre tableau
    }
}

Caisse passerClientCaisse(Caisse c){ //Fonction qui simule le passage d'un client à la caisse
    Client* ancdeb = c.debut; //Pointeur sur le premier client, me servira pour libérer l'espace mémoire

    if (c.debut == NULL) //Cas d'une liste vide, auxun client de disponible
        return c;

    printf("Debut du passage en caisse %d \n",c.no);
    Sleep(10*c.debut->temps);                  //utilisation de la fonction sleep pour simuler l'attente
    printf("Paiement en caisse %d \n",c.no);

    if (c.debut == c.fin){
        c.debut = NULL;     //Cas ou il n'y a qu'un client : la caisse devient vide, on met le débuet et la fin à NULL
        c.fin = NULL;
    }
    else{
    c.debut = c.debut->suiv; //Sinon on place le début de la caisse au deuxième client

    c.debut->prec = NULL;} //On coupe le lien avec le premier

    free(ancdeb); //On libère l'espace réservé au premier, le deuxième client devient donc premier

    printf("-------------------------------------------- \n");


    return (c);

}

int nbClientsCaisse(Caisse c){ //Fonction qui renvoie le nb de clients d'une caisse
    Client* client = NULL;
    client = c.debut;
    int cpt=0;              //Cpt de clients
    if (client == NULL){    //Cas de caisse vide
        return 0;
    }
    while (client != NULL){ //On passe au suivant jsuqu'à ce qu'on sorte de la file (Le client sera NULL)
        cpt++;
        client = client->suiv;
    }
    return cpt;
}

void initCaisses(Caisse* t[]){ //Initialisation de toutes les caisses, ici on sait qu'il y en aura 4
    int i;
    for (i=0;i<4;i++){
        t[i]->debut=NULL; //Caisses passées par adresses donc on utilise ->
        t[i]->fin=NULL;
        t[i]->no = i+1;
    }

}

int choisirCaisse(Caisse* t[]){         //Fonction renvoyant le numérod e la caisse avec le moins de monde
    int mini = nbClientsCaisse(*t[0]);  //On définit la base de comparaison, ce sera la première caisse
    int valmini = 1;
    for (int i=1;i<4;i++){
        if (nbClientsCaisse(*t[i]) < mini){ //Comparaison du nb de clients de chaque caisser, et modification de mini/valmini en conséquence
            mini = nbClientsCaisse(*t[i]);
            valmini = i+1;
        }
    }

    printf("La caisse avec le moins de monde est la caisse %d \n",valmini);
    printf("-------------------------------------------- \n");

    return valmini;
}


int main()
{
    Caisse c1,c2,c3,c4;


    Caisse t[4] = {&c1,&c2,&c3,&c4}; // Tableaux de caisses, on les rentre par adresse pour que les modifications soient pas locales aux fonctions

    initCaisses(t);

    Client * client = creerClient(30,5,0); //Création des 10 Clients
    Client * client2 = creerClient(15,6,0);
    Client * client3 = creerClient(40,7,1);
    Client * client4 = creerClient(50,8,1);

    Client * client5 = creerClient(30,6,1);
    Client * client6 = creerClient(25,4,0);
    Client * client7 = creerClient(12,2,1);

    Client * client8 = creerClient(56,3,1);
    Client * client9 = creerClient(35,1,0);

    Client * client10 = creerClient(18,8,1);

    afficherFileCaisse(c1);

    c1 = ajouterClientCaisse(c1,client);
    c1 = ajouterClientCaisse(c1,client2);
    c1 = ajouterClientCaisse(c1,client3);
    c1 = ajouterClientCaisse(c1,client4);

    afficherFileCaisse(c1);

    c2 = ajouterClientCaisse(c2,client5);
    c2 = ajouterClientCaisse(c2,client6);
    c2 = ajouterClientCaisse(c2,client7);

    afficherFileCaisse(c2);

    c3 = ajouterClientCaisse(c3,client8);
    c3 = ajouterClientCaisse(c3,client9);


    afficherFileCaisse(c3);

    c4 = ajouterClientCaisse(c4,client10);

    afficherFileCaisse(c1);

    printf("Il y a %d clients dans la file %d \n",nbClientsCaisse(c1),c1.no);
    printf("-------------------------------------------- \n");


    c1 = passerClientCaisse(c1);

    afficherFileCaisse(c1);
    printf("Il y a %d clients dans la file %d \n",nbClientsCaisse(c1),c1.no);
    printf("-------------------------------------------- \n");

    choisirCaisse(t);

    afficherToutesLesCaisses(t);

    return 0;
}
