#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "observation.h"
#include "structure.h"
#include "menu.h"
#include <string.h>


int AddLit(Patient *patientEnonsultation,ListeLit *ListeL) { // Fonciton juste pour cree le ' noeud ', ici on ne l'ajoute pas encore vers notre 'lsite de noeud' (ListeLit)
    if(ListeL->indispo >= ListeL->total ) {  // Si on depasse le nombre de lit disponible dans l'hopitale, tel que ListeL->total est donner dans le main,
        printf("Erreur : plus de lit disponible !\n");
        return -1; 
    }
        Lit lit;
        lit.num = ListeL->indispo+1;  // on inisitalise ici nos informations sur le lit
        lit.etat = OCCUPE;
        lit.patient = patientEnonsultation;
        ListeL->Tlit[ListeL->indispo] = lit; 
        int index = ListeL->indispo; 
        ListeL->indispo++;
        return ListeL->Tlit[index].num;
}


ListeObservation *AddObservation(Patient *patientEnConsultation, ListeObservation *ListeO, ListeLit *ListeL) {
    Observation *patientOB = (Observation*)malloc(sizeof(Observation));
        if(patientOB == NULL) {
            printf("Erreur : Impossible d'enregister une observation.\n");
            return ListeO;
        }
    int duree;
    printf("Duree de l'oservations :");
    scanf("%d",&duree);
    patientOB->debutObservation = time(NULL);  // initialiser d'abord
    patientOB->finObservation = patientOB->debutObservation + (duree * 24 * 60 * 60); // on ajoute par rapport a la date deja donnée
    char buffer[20];
    strftime(buffer, 20, "%d/%m/%Y", localtime(&patientOB->finObservation));
    printf("Date de fin : %s\n", buffer);
    printf("Veuillez indiquer le traitement a suivre : ");
    scanf(" %[^\n]", patientOB->traitement);
    int numLit = AddLit(patientEnConsultation, ListeL);
    if (numLit == -1) {
        printf("Hopital complet !\n");
        free(patientOB);
        return ListeO;
    }
    patientOB->lit = numLit;
    patientOB->patient = patientEnConsultation;
    patientEnConsultation->etat = OBSERVATION;
    printf("Le patient est transeferer au lit %d.",patientOB->lit);

    patientOB->suivant = NULL; // onl l'ajoute a notre liste chainer de patient en observation
    if(ListeO->tete == NULL) 
        ListeO->tete = patientOB;
    else {
    Observation *courant = ListeO->tete;
    while(courant->suivant != NULL) 
        courant = courant->suivant;
    courant->suivant = patientOB;
    }
    ListeO->compteur++;
    return ListeO;
}


void afficherObservation(ListeObservation *ListeO){
    Observation *tete=ListeO->tete;
    if (tete == NULL){
        printf("Aucun patient en observation.\n");
        return;
    }
    printf("Patients en observation :\n");
    while (tete != NULL){
        printf("Lit %d : %s %s\n", tete->lit, tete->patient->nom, tete->patient->prenom);
        tete=tete->suivant;
    }
}

void SupprimerObservation(ListeObservation *ListeO,ListeLit *ListeL){
     if(ListeO->tete == NULL) {
        printf("Aucun patient en observation.\n");
        return;
    }
    AfficherListeObservation(ListeO);
    int numlit;
    printf("Numero du lit a liberer : ");
    scanf("%d", &numlit);
    Observation *courant   = ListeO->tete;
    Observation *precedent = NULL;

    while (courant != NULL && courant->lit != numlit) {
        precedent = courant;
        courant   = courant->suivant;
    }
    if (courant == NULL) {
        printf("Observation introuvable.\n");
        return;
    }
    courant->patient->etat         = SORTI;
    ListeL->Tlit[numlit-1].etat    = NOCCUPE;
    ListeL->Tlit[numlit-1].patient = NULL;
    ListeL->indispo--;

    if (precedent == NULL)
        ListeO->tete = courant->suivant;
    else
        precedent->suivant = courant->suivant;

    free(courant);
    ListeO->compteur--;
}   



void AfficherListeObservation(ListeObservation *ListeO) {
    if(ListeO->tete == NULL) {    
        printf("Aucun patient en observations.\n");
        return;
    }
    int i = 1;
    Observation *courant = ListeO->tete;
    while(courant != NULL) {
        char buffer[20];
        strftime(buffer, 20, "%d/%m/%Y", localtime(&courant->finObservation));
        printf("[%d] - %s  %s | %d Ans | %s | %s | Lit  %d | Traitement : %s | Sortie : %s\n", i, courant->patient->nom, courant->patient->prenom, courant->patient->age, courant->patient->sexe, courant->patient->id,courant->lit,courant->traitement,buffer);
        i++;
        courant = courant->suivant;
    }
}

void ModifierObservation(ListeObservation *ListeO, ListeLit *ListeL) {
    if(ListeO->tete == NULL) {
        printf("Aucun patient en observation.\n");
        return;
    }
    AfficherListeObservation(ListeO);
    printf("----");
    int choix, index;
    int i = 1;
    do{
        printf("-Choix : ");
        scanf("%d",&index);
        if(index < 0 || index > ListeO->compteur)
            printf("Erreur : Numero invalide ! Reessayez.\n");
            
     }while(index < 0 || index > ListeO->compteur);
    Observation *courant = ListeO->tete;
    while(i < index) {
        courant = courant->suivant;
        i++;
    }
    Observation *patientCible = courant;
    do {
        menuModifierObservation(courant);
        scanf("%d",&choix);
    switch(choix)  {
        case 1 : {
            int numlit;
            printf("Donner le numero du nouveau lit : ");
            scanf("%d",&numlit);
            if (numlit < 1 || numlit > ListeL->total) {
                printf("Erreur : lit invalide.\n");
                break;
            }
            if (ListeL->Tlit[numlit-1].etat == OCCUPE) {
              printf("Erreur : lit %d deja occupe.\n", numlit);
              break;
            }
            ListeL->Tlit[patientCible->lit - 1].etat =  NOCCUPE;
            ListeL->Tlit[patientCible->lit - 1].patient =  NULL;
            patientCible->lit = numlit;
            ListeL->Tlit[numlit-1].etat =  OCCUPE;
            ListeL->Tlit[numlit-1].patient = patientCible->patient;
        break; }
        case 2 : {
            printf("Donner le nouveau traitement a suivre : ");
            scanf(" %[^\n]", patientCible->traitement);
        break; }
        case 3 : {
            int duree;
            printf("Ajouter une retier des jours (Exemple : 2 ou -1) :");
            scanf("%d",&duree);

            patientCible->finObservation = patientCible->finObservation + (duree * 24 * 60 * 60); // on ajoute ou reduire par rapport a la date deja donnée
            char buffer[20];
            strftime(buffer, 20, "%d/%m/%Y", localtime(&patientCible->finObservation));
            printf("Nouvelle date de fin : %s\n", buffer);
        break;}
        }
    }while(choix != 4);
}
void RechercheObservation(ListeObservation *ListeO) {
     if(ListeO->tete == NULL) {
        printf("Aucun patient en observation.\n");
        return;
    }
    int choix;
    do {
        printf("Rechercher par : \n");
        printf("\t 1 - ID\n");
        printf("\t 2 - Nom et Prenom\n");
        printf("\t 3 - Quitter\n");
        scanf("%d", &choix);
        switch(choix) {
        case 1 : {
            char IDcible[20];
            printf("ID :");
            scanf("%s", IDcible);
            int trouve = 0;
            Observation *courant = ListeO->tete;
            while(courant != NULL) {
                if(strcmp(courant->patient->id, IDcible) == 0) {
                    char buffer[30];
                    strftime(buffer, 30, "%d/%m/%Y", localtime(&courant->finObservation));
                    printf("%s  %s | %d Ans | %s | %s | Lit  %d | Traitement : %s | Sortie : %s\n",courant->patient->nom, courant->patient->prenom, courant->patient->age, courant->patient->sexe, courant->patient->id,courant->lit,courant->traitement,buffer);
                    trouve = 1;
                }
                courant = courant->suivant;
            }
            if(trouve == 0) printf("Patient introuvable.\n");
        break; }
        case 2 : {
            char nomCible[30],prenomCible[30];
            printf("Nom :");
            scanf(" %[^\n]", nomCible);
            printf("Prenom :");
            scanf(" %[^\n]", prenomCible);
            int trouve = 0;
            Observation *courant = ListeO->tete; 
            while(courant != NULL) {
                if((strcmp(courant->patient->nom, nomCible) == 0) && (strcmp(courant->patient->prenom, prenomCible) == 0)) {
                    char buffer[20];
                    strftime(buffer, 20, "%d/%m/%Y", localtime(&courant->finObservation));
                    printf("%s  %s | %d Ans | %s | %s | Lit  %d | Traitement : %s | Sortie : %s\n",courant->patient->nom, courant->patient->prenom, courant->patient->age, courant->patient->sexe, courant->patient->id,courant->lit,courant->traitement,buffer);
                    trouve = 1;
                }
                courant = courant->suivant;
            }
            if(trouve == 0) printf("Patient introuvable.\n");
        break; }
        }
    }while(choix != 3);
}