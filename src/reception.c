#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reception.h"
#include "structure.h"


Ticket *CreateTicket(Patient *patient, int num) {
    Ticket *T = (Ticket*)malloc(sizeof(Ticket));
        if(T == NULL) {
            printf("Erreur : Impossible de cree un ticket.");
            exit(1);
        }
    T->client = patient;
    T->numero = num;
    T->suivant = NULL;
    return T;
}
Ticket *AddTicket(ListeTicket *ListeT, Patient *patient) {
    ListeT->compteur++;
    Ticket *nouveauTicket = CreateTicket(patient,ListeT->compteur);
    if(ListeT->tete == NULL) { 
        ListeT->tete = nouveauTicket;  
        return nouveauTicket;
         }
    Ticket *courant = ListeT->tete;
    while(courant->suivant != NULL) {
        courant = courant->suivant;
    }
    courant->suivant = nouveauTicket;

    return nouveauTicket;
}
    
void AddPatient(ListePatient *ListeP,ListeTicket *ListeT) {
    char Nom[30],Prenom[30],ID[20],Sexe[4];
    int Age;
    Patient *P = (Patient*)malloc(sizeof(Patient));
        if(P == NULL){
            printf("Erreur : Impossible d'enregister le patient.");
            exit(1);
        }
    printf("Veuiller fournir les informations suivante du patient :\n");
    printf("\tNom : ");
    scanf(" %[^\n]",Nom);
    printf("\tPrenom : ");
    scanf(" %[^\n]",Prenom);
    printf("\tID : ");
    scanf(" %[^\n]",ID);
    printf("\tAge : ");
    scanf("%d",&Age);
    while(getchar() != '\n');
    printf("\tSexe(H/F): ");
    scanf("%s", Sexe);
    strcpy(P->nom, Nom);
    strcpy(P->prenom, Prenom);
    strcpy(P->id, ID);
    strcpy(P->sexe, Sexe);
    P->age = Age;
    P->suivant = NULL;
    P->ticket = AddTicket(ListeT,P);
    P->etat = ATTENTE;
    strcpy(P->departement,""); // Pas encore transeferer, c'est le medecin qui en decidera
    P->heure.arrive = time(NULL); // Recuperer l'heure actuelle (De l'enregistrment du patient du coup)
    P->heure.sorti = 0; // Pas encore sortie, on initialise a 0
    strcpy(P->diagnostique,"");
    strcpy(P->ordonnance,"");
    if(ListeP->tete == NULL) {
       ListeP->tete = P;
        ListeP->attente++;
        ListeP->total++;
    return;  
}
    Patient *courant = ListeP->tete;
    while(courant->suivant != NULL)
        courant = courant->suivant;
    courant->suivant = P;
    ListeP->attente++;
    ListeP->total++;
    P->index = ListeP->total;
     sauvegarderHistorique(P);
}
void afficherAttente(ListeTicket *ListeT) {
    if(ListeT->tete == NULL) {
        printf("Aucun patient en fille d'attente.\n");
        return;
    }
    Ticket *courant = ListeT->tete;
    int i = 1;
    while(courant != NULL) {
        char buffer[20];
        strftime(buffer, 20, "%H:%M:%S", localtime(&courant->client->heure.arrive));
        printf("[%d] - %s  %s | %d Ans | %s | %s | Ticket  %d | Debut d'attente : %s\n", i, courant->client->nom, courant->client->prenom, courant->client->age, courant->client->sexe, courant->client->id,courant->numero,buffer);
        courant = courant->suivant;
        i++;
    }
}
void SaveTicket(ListeTicket *listeT) {
    FILE *f = fopen("data/tickets.bin", "wb");
    if (f == NULL) return;

    fwrite(&listeT->compteur,     sizeof(int),    1, f);
    fwrite(&listeT->dernierReset, sizeof(time_t), 1, f);
    fclose(f);
}

void chargerTickets(ListeTicket *listeT) {
    FILE *f = fopen("data/tickets.bin", "rb");
    if (f == NULL) return;

    fread(&listeT->compteur,     sizeof(int),    1, f);
    fread(&listeT->dernierReset, sizeof(time_t), 1, f);

    fclose(f);
}
void verifierNouveauJour(ListeTicket *ListeT) {
    time_t maintenant = time(NULL);
    struct tm *tmMaintenant = localtime(&maintenant);
    struct tm *tmDernier    = localtime(&ListeT->dernierReset);
    // Si le jour a changé alors on met le compteur a 0
    if (tmMaintenant->tm_mday != tmDernier->tm_mday ||
        tmMaintenant->tm_mon  != tmDernier->tm_mon  ||
        tmMaintenant->tm_year != tmDernier->tm_year) {
    
        ListeT->compteur     = 0;
        ListeT->dernierReset = maintenant;
        printf("Nouveau jour : compteur de tickets reinitialise.\n");
    }
}
