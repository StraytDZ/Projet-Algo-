#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reception.h"

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
ListePatient *AddPatient(ListePatient *ListeP,ListeTicket *ListeT) {
    char Nom[30],Prenom[30],ID[20],Sexe[4];
    int Age;
    Patient *P = (Patient*)malloc(sizeof(Patient));
        if(P == NULL){
            printf("Erreur : Impossible d'enregister le patient.");
            exit(1);
        }
    printf("Veuiller fournir les informations suivante du patient :");
    printf("\t\nNom : ");
    scanf(" %[^\n]",Nom);
    printf("\t\nPrenom : ");
    scanf(" %[^\n]",Prenom);
    printf("\t\nID : ");
    scanf(" %[^\n]",ID);
    printf("\t\nAge : ");
    scanf("%d",&Age);
    printf("\t\nSexe(H/F): ");
    scanf("%s",Sexe);
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
    strcpy(P->traitement,"");
    strcpy(P->ordonnance,"");
    if(ListeT->tete == NULL) {
       ListeP->tete = P;
        ListeP->attente++;
        ListeP->total++;
    return ListeP;  
}
    Patient *courant = ListeP->tete;
    while(courant->suivant != NULL)
        courant = courant->suivant;
    courant->suivant = P;
    ListeP->attente++;
    ListeP->total++;
    return ListeP;
}
void DisplayQueue(ListePatient *ListeP) {
    Patient *courant = ListeP->tete;
    
    int i = 1;
    while(courant != NULL) {
        printf("Patient %d \n",i);
        printf("\tNom : %s\n",courant->nom);
        printf("\tPrenom : %s\n",courant->prenom);
        printf("\tID : %s\n",courant->id);
        printf("\tAge : %d\n",courant->age);
        printf("\tSexe(H/F): %s\n",courant->sexe);
        courant = courant->suivant;
        i++;
    }
}
