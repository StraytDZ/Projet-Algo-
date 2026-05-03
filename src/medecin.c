#include <stdio.h>
#include <stdlib.h>
#include "medecin.h"
#include <string.h>
#include "menu.h"

Patient *CallPatient(ListeTicket *ListT, ListeUrgence *ListU,ListePatient *ListeP){
    if(ListU->tete != NULL) {
        Urgence *urgence = ListU->tete;           
        Patient *patientUrgence = urgence->patient; 
        patientUrgence->etat = CONSULTATION;
        ListU->tete = ListU->tete->suivant;
        ListeP->attente--;
         sauvegarderHistorique(patientUrgence);
        return patientUrgence;
    }
    if(ListT->tete == NULL) {
        printf("Aucun patient en fille d'attente.\n");
        return NULL;
        }
    Patient *patient = ListT->tete->client;
    patient->etat = CONSULTATION;
    ListT->tete = ListT->tete->suivant;
    ListeP->attente--;
    sauvegarderHistorique(patient);
    return patient;
}

void PatientDiagnostic(Patient *patientEnConsult) {
    printf("Saisir le diagnostique :\n");
    scanf(" %[^\n]",patientEnConsult->diagnostique);
    sauvegarderHistorique(patientEnConsult);
}

void PatientOrdonnance(Patient *patientEnConsult, ListePatient *ListeP) {
    if(strcmp(patientEnConsult->diagnostique, "") != 0) {
    printf("Inscrire l'ordonnance : \n");
    scanf(" %[^\n]",patientEnConsult->ordonnance);
    printf("L'ordonnance a bien ete inscrite a %s %s, le patient peut disposse.", patientEnConsult->nom,patientEnConsult->prenom);
    patientEnConsult->etat = SORTI;
    patientEnConsult->heure.sorti = time(NULL);
    ListeP->sortis++;
    }
    else printf("Veuillez d'abord saisir un diagnostique.\n");
}

void transferer(Patient *patientEnConsult,ListePatient *ListeP){
    if(strcmp(patientEnConsult->diagnostique, "") != 0) {
    printf("Saisi du nom du departement de transfert : ");
    scanf(" %[^\n]",patientEnConsult->departement);
     printf("Le patient %s %s a ete transfere vers un departement de %s.\n",patientEnConsult->prenom,patientEnConsult->nom, patientEnConsult->departement);
    patientEnConsult->etat=TRANSFERER;
    patientEnConsult->heure.sorti = time(NULL);
    ListeP->transferes++;
    sauvegarderHistorique(patientEnConsult);
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
        printf("[%d] - %s  %s | %d Ans | %s | %s | Ticket  %d | Depuis : %s\n", i, courant->client->nom, courant->client->prenom, courant->client->age, courant->client->sexe, courant->client->id,courant->numero,buffer);
        if(courant->client->etat == URGENCE) printf(" | URGENCE !");
        i++;
        courant = courant->suivant;
    }

}
