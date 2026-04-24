#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "reception.h"

void donnerlit(Patient *patientEnConsult, int lit){
    
   patientEnConsult->lit=lit+1;
   printf("Le patient %s %s a été assigné au lit %d\n",patientEnConsult->prenom,patientEnConsult->nom,patientEnConsult->lit);
}

void transferer(Patient *patientEnConsult){
    patientEnConsult->etat=TRANSFERER;
    printf("Le patient %s %s a été transféré vers un autre service.\n9le nom du departement et dans le traitement\n",patientEnConsult->prenom,patientEnConsult->nom);
}

void saisirduree(Patient *patientEnConsult){
    int duree;
    printf("Saisi de la durée d'observation (en jours) : ");
    scanf("%d",&duree);
    time_t currentTime = time(NULL);
    patientEnConsult->heure.arrive = currentTime;
    patientEnConsult->heure.sorti = currentTime + duree*24*3600; 
}

void  modifierdiagnostique(Patient *patientEnConsult){
    printf("Saisi du nouveau diagnostique : ");
    scanf("%s",patientEnConsult->diagnostique);
}

void  modifiertraitement(Patient *patientEnConsult){
    printf("Saisi du nouveau traitement : ");
    scanf("%s",patientEnConsult->traitement);
}

void  modifierordonnance(Patient *patientEnConsult){
     printf("Saisi de la nouvelle ordonnance : ");
     scanf("%s",patientEnConsult->ordonnance);
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


