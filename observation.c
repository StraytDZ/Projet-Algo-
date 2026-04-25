#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "observation.h"
#include "structure.h"




Observation * donnerlit(Patient *patientEnConsult, Observation *lits, int *numeroprecedent){
    Observation *lit=malloc(sizeof(Observation));
    if (lit == NULL) {
        printf("Erreur : plus de mémoire pour les lits.\n");
        return lits;
    } 
    (*numeroprecedent)++;
    lit->suivant=NULL;
    lit->numlit=*numeroprecedent;
    lit->patient=patientEnConsult;
    Observation *temp=lits;
    if (temp==NULL){
        return lit;    
    }
    else{
        while (temp->suivant!=NULL){
            temp=temp->suivant;
        }
        temp->suivant=lit;     
    }
    return lits;   
}

Observation * supprimerObservation(Observation *lits, int numlit){
    Observation *lit = lits;
    if (lit->numlit==numlit){
        Observation *temp=lit;
        lit=lit->suivant;
        temp->patient->etat=SORTI;
        temp->suivant=NULL;
        free(temp);
        return lit;
    }
    while( lit->suivant!=NULL && lit->suivant->numlit!=numlit) {
         lit=lit->suivant;
    }
    Observation *temp=lit->suivant;
    lit->suivant=lit->suivant->suivant;
    temp->suivant=NULL;
    temp->patient->etat=SORTI;
    free(temp);
    return lits;     
}

void transferer(Patient *patientEnConsult){
    printf("Saisi du nom du département de transfert : ");
    scanf("% [\n]s",patientEnConsult->traitement);
    patientEnConsult->etat=TRANSFERER;
    printf("Le patient %s %s a été transféré vers un departement de %s\n",patientEnConsult->prenom,patientEnConsult->nom, patientEnConsult->traitement);
}

void saisirduree(Patient *patientEnConsult){
    int duree;
    printf("Saisi de la durée d'observation (en jours) : ");
    scanf("%d",&duree);
    time_t currentTime = time(NULL);
    patientEnConsult->heure.arrive = currentTime;
    patientEnConsult->heure.sorti = currentTime+duree*24*3600; 
}

void  modifierdiagnostique(Patient *patientEnConsult){
    printf("Saisi du nouveau diagnostique : ");
    scanf(" [\n]%s",patientEnConsult->diagnostique);
}

void  modifiertraitement(Patient *patientEnConsult){
    printf("Saisi du nouveau traitement : ");
    scanf(" [\n]%s",patientEnConsult->traitement);
}

void  modifierordonnance(Patient *patientEnConsult){
     printf("Saisi de la nouvelle ordonnance : ");
     scanf(" [\n]%s",patientEnConsult->ordonnance);
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

