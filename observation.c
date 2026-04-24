#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "reception.h"




ListeLit * donnerlit(Patient *patientEnConsult, ListeLit *lits, int *numeroprecedent){
    ListeLit *lit=malloc(sizeof(ListeLit));
    if (lit == NULL) {
        printf("Erreur : plus de mémoire pour les lits.\n");
        return lits;
        exit(1);
    } 
    (*numeroprecedent)++;
    lit->suivant=NULL;
    lit->numlit=*numeroprecedent;
    lit->patient=patientEnConsult;
    ListeLit *temp=lits;
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

void transferer(Patient *patientEnConsult){
    printf("Saisi du nom du département de transfert : ");
    scanf("%[\n]s",patientEnConsult->traitement);
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
    scanf("[\n]%s",patientEnConsult->diagnostique);
}

void  modifiertraitement(Patient *patientEnConsult){
    printf("Saisi du nouveau traitement : ");
    scanf("[\n]%s",patientEnConsult->traitement);
}

void  modifierordonnance(Patient *patientEnConsult){
     printf("Saisi de la nouvelle ordonnance : ");
     scanf("[\n]%s",patientEnConsult->ordonnance);
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

Patient* libererpatient(Patient *patientEnConsult){
    patientEnConsult->etat=SORTI;
    printf("Le patient %s %s a été libéré.\n",patientEnConsult->prenom,patientEnConsult->nom);
    return patientEnConsult;
}