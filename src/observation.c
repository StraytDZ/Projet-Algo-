#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "observation.h"
#include "structure.h"



int AddLit(Observation *patientOB,ListeLit *ListeL) { // Fonciton juste pour cree le ' noeud ', ici on ne l'ajoute pas encore vers notre 'lsite de noeud' (ListeLit)
    if(ListeL->indispo >= ListeL->total ) {  // Si on depasse le nombre de lit disponible dans l'hopitale, tel que ListeL->total est donner dans le main,
        printf("Erreur : plus de lit disponible !\n");
        return -1; 
    }
        Lit lit;
        lit.num = ListeL->indispo+1;  // on inisitalise ici nos informations sur le lit
        lit.etat = OCCUPE;
        lit.patient = patientOB->patient;
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
    printf("Veuillez indiquer la duree de l'observation : (En jour)");
    scanf(" %d",&patientOB->finObservation);
    printf("Veuillez indiquer le traitement a suivre : ");
    scanf(" %[^\n]", patientOB->traitement);
    patientOB->lit = AddLit(patientOB,ListeL);
    if( ListeL->indispo >= ListeL->total) {
        printf("Erreur : Impossible d'atribuer un lit, Hopitale complet !"); // plus de lit dispo, on peut plus recevoir de patient pour les observer
        free(patientOB);
        return ListeO;
    }
    printf("Le patient est transeferer au lit %d.",patientOB->lit);

    patientOB->suivant = NULL; // onl l'ajoute a notre liste chainer de patient en observation
    if(ListeO == NULL) 
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

Observation * supprimerObservation(ListeObservation *ListeO,ListeLit *TLit[], int numlit){
    if( numlit < 0|| numlit > 100) {
        printf("Erreur : Numero invalide !");
        return NULL;
    }
    Observation *tete = ListeO->tete;
    Observation *temp=tete; // Pour pas perdre l'adresse a free
    if (tete->lit == 1){ // Enlever au debut de la liste chainer ListeObservation
        temp->patient->etat=SORTI;
        TLit[numlit] = NOCCUPE;
        tete=tete->suivant;
        free(temp); // On free de la liste chainer ListeObservation, Mais le patient est toujours present dans ListePatient
        return tete;
    }
    while( tete != NULL && tete->lit != numlit ) {
         tete=tete->suivant;
    }
    temp->patient->etat=SORTI;
    tete=tete->suivant;
    free(temp); // On free de la liste chainer ListeObservation, Mais le patient est toujours present dans ListePatient
    return tete;     
}


void verifierStatut(Patient *patientEnConsult){
    time_t maintenant = time(NULL);
    double secondesRestantes = difftime(patientEnConsult->heure.sorti, maintenant);

    printf("Patient : %s\n", patientEnConsult->nom);
    if (secondesRestantes > 0) {
        printf("Statut : En observation (Reste environ %d secondes)\n", secondesRestantes);
    } else {
        printf("Statut : Observation terminée. Le patient peut sortir.\n");
    }
}

void AfficherListeObservation(ListeObservation *ListeO) {
    if(ListeO == NULL) {    
        printf("Aucun patient en observations.\n");
        return;
    }
    int i = 1;
    Observation *courant = ListeO->tete;
    while(courant != NULL) {
        char buffer[30];
        strftime(buffer, 30, "%H:%M:%S", localtime(&courant->debutObservation));
        printf("[%d] - %s  %s | %d Ans | %s | %s | Lit  %d | Traitement : %s | Sortie : %s\n", i, courant->patient->nom, courant->patient->prenom, courant->patient->age, courant->patient->sexe, courant->patient->id,courant->lit,courant->traitement,buffer);
        i++;
        courant = courant->suivant;
    }
}

void ModifierObservation(ListeObservation *ListeO) {
    AfficherListeObservation(ListeO);
    int choix;
    int index = 1;
    int i = 1;
    do{
        if(index < 0 || index > ListeO->compteur) printf("Erreur : Numero invalide ! Reessayez.\n");
        printf("----Choix : ");
        scanf("%d",&index);
     }while(index < 0 || index > ListeO->compteur);
    Observation *courant = ListeO->tete;
    while(i < index) {
        courant = courant->suivant;
        i++;
    }
    Observation *patientCible = courant;
    do {
        menuModifierObservation(courant);
         canf("%d",&choix);
    switch(choix)  {
        case 1 : {
            int numlit;
            printf("Donner le num du nouveau lit : ");
            scanf("%d",&numlit);
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