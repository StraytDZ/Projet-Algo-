#include <stdio.h>
#include <stdlib.h>
#include "medecin.h"
#include <string.h>
#include "menu.h"
#include "fichier.h"

Patient *CallPatient(ListeTicket *ListeT, ListeUrgence *ListeU,ListePatient *ListeP){
    if(ListeU->tete != NULL) {
        Urgence *urgence = ListeU->tete;           
        Patient *patientUrgence = urgence->patient; 
        patientUrgence->etat = CONSULTATION;
        ListeU->tete = ListeU->tete->suivant;
        ListeP->attente--;
        patientUrgence->debutConsulation = time(NULL);
        sauvegarderPatients(patientUrgence);
        return patientUrgence;
    }
    if(ListeT->tete == NULL) {
        printf("Aucun patient en fille d'attente.\n");
        return NULL;
        }
    Patient *patient = ListeT->tete->client;
    patient->etat = CONSULTATION;
    patient->debutConsulation = time(NULL);
    ListeT->tete = ListeT->tete->suivant;
    ListeP->attente--;
    sauvegarderPatients(patient);
    return patient;
}

void PatientDiagnostic(Patient *patientEnConsult) {
    printf("Saisir le diagnostique :\n");
    scanf(" %[^\n]",patientEnConsult->diagnostique);
    sauvegarderPatients(patientEnConsult);
}

void PatientOrdonnance(Patient *patientEnConsult, ListePatient *ListeP) {
    if(strcmp(patientEnConsult->diagnostique, "") != 0) {
    printf("Inscrire l'ordonnance : \n");
    scanf(" %[^\n]",patientEnConsult->ordonnance);
    printf("L'ordonnance a bien ete inscrite a %s %s, le patient peut disposse.", patientEnConsult->nom,patientEnConsult->prenom);
    patientEnConsult->etat = SORTI;
    patientEnConsult->heure.sorti = time(NULL);
    patientEnConsult->dureeConsultation = time(NULL) - patientEnConsult->debutConsulation;
    ListeP->sortis++;
    sauvegarderPatients(patientEnConsult);
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
    sauvegarderPatients(patientEnConsult);
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
        printf("[%d] - %s  %s | %d Ans | %s | %s | Ticket  %d | Depuis : %s", i, courant->client->nom, courant->client->prenom, courant->client->age, courant->client->sexe, courant->client->id,courant->numero,buffer);
        if(courant->client->etat == URGENCE) printf(" | URGENCE !");
        printf("\n");
        i++;
        courant = courant->suivant;
    }

}
