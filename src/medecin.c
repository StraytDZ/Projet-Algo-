#include <stdio.h>
#include <stdlib.h>
#include "medecin.h"

Patient *CallPatient(ListeTicket *ListT, ListeUrgence *ListU){
    if(ListU->tete != NULL) {
        Patient *patientUrgence = ListU->tete;
        patientUrgence->etat = CONSULTATION;
        ListU->tete = ListU->tete->suivant;
        return patientUrgence;
    }
    if(ListT->tete == NULL) {
        printf("Aucun patient en fille d'attente.\n");
        return NULL;
        }
    Patient *patient = ListT->tete->client;
    patient->etat = CONSULTATION;
    ListT->tete = ListT->tete->suivant;
    return patient;
}

void PatientDiagnostic(Patient *patientEnConsult) {
    printf("Saisir le diagnostique :\n");
    scanf(" %[^\n]",patientEnConsult->diagnostique);
}

void PatientOrdonnance(Patient *patientEnConsult) {
    if(strcmp(patientEnConsult->diagnostique, "") != 0) {
    printf("Inscrire l'ordonnance : \n");
    scanf(" %[^\n]",patientEnConsult->ordonnance);
    }
    else printf("Veuillez d'abord saisir un traitement.\n");
}
