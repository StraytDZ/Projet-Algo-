#include <stdio.h>
#include <stdlib.h>
#include "medecin.h"
#include <string.h>
#include "menu.h"

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
    printf("L'ordonnance a bien été inscrite a %s %s", patientEnConsult->nom,patientEnConsult->prenom);
    }
    else printf("Veuillez d'abord saisir un diagnostique.\n");
}

void transferer(Patient *patientEnConsult){
    if(strcmp(patientEnConsult->diagnostique, "") != 0) {
    printf("Saisi du nom du departement de transfert : ");
    scanf(" %[^\n]",patientEnConsult->departement);
    patientEnConsult->etat=TRANSFERER;
    printf("Le patient %s %s a ete transfere vers un departement de %s.\n",patientEnConsult->prenom,patientEnConsult->nom, patientEnConsult->departement);
    }else printf("Veuillez d'abord saisir un diagnostique.\n");
}
void AfficherAttente(ListeTicket *ListeT) {
    if(ListeT->tete == NULL) {
        printf("Aucun patient en file d'attente.\n");
        return;
    }
    Ticket *courant = ListeT->tete;
    int i = 1;
    while(courant != NULL) {
        char buffer[30];
        strftime(buffer, 30, "%d/%m/%Y %H:%M:%S", localtime(&courant->client->heure.arrive));
        printf("[%d] - %s  %s | %d Ans | %s | %s | Ticket  %d | %s\n", i, courant->client->nom, courant->client->prenom, courant->client->age, courant->client->sexe, courant->client->id,courant->numero,buffer);
        i++;
        courant = courant->suivant;
    }

}
