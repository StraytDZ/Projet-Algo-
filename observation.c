#include <stdlib.h>
#include <stdio.h>
#include "reception.h"

void donnerlit(Patient *patientEnConsult, int lit){
    
   patientEnConsult->lit=lit+1;
   printf("Le patient %s %s a été assigné au lit %d\n",patientEnConsult->prenom,patientEnConsult->nom,patientEnConsult->lit);
}

void  saisirdiagnostique(Patient *patientEnConsult){
    printf("Saisi du diagnostique : ");
    scanf("%s",patientEnConsult->diagnostique);
}

void  saisirtraitement(Patient *patientEnConsult){
    printf("Saisi du traitement : ");
    scanf("%s",patientEnConsult->traitement);
}

void  saisirordonnance(Patient *patientEnConsult){
     printf("Saisi de l'ordonnance : ");
     scanf("%s",patientEnConsult->ordonnance); 
}
void saisirduree(Patient *patientEnConsult){
    int duree;
    printf("Saisi de la durée d'observation (en jours) : ");
    scanf("%d",&duree);
    time_t currentTime = time(NULL);
    patientEnConsult->heure.arrive = currentTime;
    patientEnConsult->heure.sorti = currentTime + duree * 24 * 3600; 
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


