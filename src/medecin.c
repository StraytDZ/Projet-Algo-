#include <stdio.h>
#include <stdlib.h>
#include "medecin.h"
#include <string.h>

Patient *CallPatient(ListeTicket *ListT, ListeUrgence *ListU){
    if(ListU->tete != NULL) {
        Urgence *urgence = ListU->tete;           
        Patient *patientUrgence = urgence->patient; 
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

void transferer(Patient *patientEnConsult){
    printf("Saisi du nom du département de transfert : ");
    scanf(" %[^\n]",patientEnConsult->departement);
    patientEnConsult->etat=TRANSFERER;
    printf("Le patient %s %s a été transféré vers un departement de %s.\n",patientEnConsult->prenom,patientEnConsult->nom, patientEnConsult->departement);
}
void AfficherAttente(ListeTicket *ListeT) {
    Ticket *courant = ListeT->tete;
    if(courant == NULL) {
        printf("Aucun patient en file d'attente.\n");
        return;
    }
    int i = 1;
    while(courant != NULL) {
        char buffer[30];
        strftime(buffer, 30, "%d/%m/%Y %H:%M:%S", localtime(&courant->client->heure.arrive));
        printf("[%d] - %s  %s | %d Ans | %s | %s | Ticket  %d | %s\n", i, courant->client->nom, courant->client->prenom, courant->client->age, courant->client->sexe, courant->client->id,courant->numero,buffer);
        i++;
        courant = courant->suivant;
    }

}
