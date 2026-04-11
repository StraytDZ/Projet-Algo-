#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reception.h"

void menuReception() {
    system("cls");
    printf("\n=======================================\n");
    printf("\t=+=+=+=MENU=+=+=+=\n");
    printf("\t*+*+*RECEPTION*+*+*\n");
    printf("=======================================\n\n");
    printf("\t 1 - Enregister un patient\n");
    printf("\t 2 - Afficher la liste d'attente\n");
    printf("\t 3 - Quitter\n\n");
    printf("=======================================\n");
    printf("                          Choix : ");
}

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
Patient *AddPatient(Patient *ListeP,ListeTicket *ListeT, char Nom[],char Prenom[],char ID[],int Age, char Sexe[]) {
    Patient *P = (Patient*)malloc(sizeof(Patient));
    
        if(P == NULL){
            printf("Erreur : Impossible d'enregister le patient.");
            exit(1);
        }
    strcpy(P->nom, Nom);
    strcpy(P->prenom, Prenom);
    strcpy(P->id, ID);
    strcpy(P->sexe, Sexe);
    P->age = Age;
    P->suivant = NULL;
    P->numticket = AddTicket(ListeT,P);
    if(ListeP == NULL) return P;
    Patient *courant = ListeP;
    while(courant->suivant != NULL)
        courant = courant->suivant;
    courant->suivant = P;

    return ListeP;
}
void DisplayQueue(Patient *ListeP) {
    Patient *courant = ListeP;
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
