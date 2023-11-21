#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 typedef char Chaine[20];

typedef struct _Mot{

    Chaine francais;
    Chaine anglais;
    struct _Mot *gauche, *droite;
}Mot, *ABR;


ABR newMot(Chaine fr, Chaine ang){
        ABR mot = (ABR)malloc(sizeof(Mot));
        if (mot == NULL)
            exit(EXIT_FAILURE); //Erreur si l'allocation à échouée
        else{
            for (int i = 0;i<20;i++){
                mot->francais[i] = fr[i];
                mot->anglais[i] = ang[i];
            }
            mot->droite = NULL;
            mot->gauche = NULL;
        }
        return mot;
    }

ABR ajouterMotFR(ABR mot, ABR dico){
    if (dico == NULL)
        return(newMot(mot->francais,mot->anglais));
    else{

        if (strcmp(mot->francais,dico->francais)==0){
            printf("Le mot est déjà dans le dico \n");
            return dico;
        }

        if((strcmp(mot->francais,dico->francais)<0)){
            dico->gauche = ajouterMotFR(mot, dico->gauche);
        }

        else{
            dico->droite = ajouterMotFR(mot, dico->droite);

        }
    }
    return dico;
}

ABR ajouterMotEN(ABR mot, ABR dico){
    if (dico == NULL)
        return(newMot(mot->francais,mot->anglais));
    else{

        if (strcmp(mot->anglais,dico->anglais)==0){
            printf("Le mot est déjà dans le dico \n");
            return dico;
        }

        if((strcmp(mot->anglais,dico->anglais)<0)){
            dico->gauche = ajouterMotEN(mot, dico->gauche);
        }

        else{
            dico->droite = ajouterMotEN(mot, dico->droite);

        }
    }
    return dico;
}

void rechMot(Chaine fr, ABR dico){
    if (dico == NULL){
        printf("Le mot n'est pas dans le dictionnaire \n");
        return;}
    else{

        if (strcmp(fr,dico->francais)==0){
            printf("La traduction de %s est %s \n",fr,dico->anglais);
            return;
        }

        if((strcmp(fr,dico->francais)<0)){
            rechMot(fr, dico->gauche);
        }

        else{
            rechMot(fr, dico->droite);

        }
    }
}

void affordre(ABR dico){
    if (dico){
        affordre(dico->gauche);
        printf("Français : %s | Anglais : %s \n",dico->francais,dico->anglais);
        affordre(dico->droite);
    }
}

void affordreEn(ABR dico){
    if (dico){
        affordre(dico->gauche);
        printf("Anglais : %s | Français : %s \n",dico->anglais,dico->francais);
        affordre(dico->droite);
    }
}

ABR conversion(ABR dicofr,ABR dicoEN){
    if (dicofr){
        conversion(dicofr->gauche,dicoEN);
        ajouterMotEN(dicofr->francais,dicoEN);
        conversion(dicofr->droite,dicoEN);
    }
    return dicoEN;
}


int main()
{
    ABR base = newMot("bonjour","hello");
    ABR mot2 = newMot("aurevoir","bye");
    ABR mot3 = newMot("maison","house");
    ABR mot4 = newMot("oui","yes");

    ABR baseEn = NULL;



    printf("Le mot 1 est %s et sa traduction est %s \n",base->francais,base->anglais);

    ajouterMotFR(mot2,base);
    ajouterMotFR(mot3,base);

    rechMot(mot3->francais,base);
    rechMot(mot4->francais,base);

    printf("---------------------- \n");

    affordre(base);
    printf("---------------------- \n");

    baseEn = conversion(base,baseEn);
    affordreEn(baseEn);




    return 0;
}
