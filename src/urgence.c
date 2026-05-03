#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "urgence.h"
#include "structure.h"
#include "reception.h"

ListeUrgence* AddUrgence(ListeUrgence *ListeU, ListeTicket *ListeT){
    Patient *patientEnUrgence = (Patient*)malloc(sizeof(Patient));
    patientEnUrgence->etat = URGENCE;
    ListeT->compteur++;
    Ticket *nouveauTicket = CreateTicket(patientEnUrgence,ListeT->compteur);
    if(ListeT->tete == NULL) { 
        ListeT->tete = nouveauTicket;  
    }
    else{    
        Ticket *courant = ListeT->tete;
        while(courant->suivant != NULL) {
        courant = courant->suivant;
    }
    courant->suivant = nouveauTicket;
   }
    patientEnUrgence->ticket = nouveauTicket;
    printf("Nom : ");    scanf(" %[^\n]", patientEnUrgence->nom);
    printf("Prenom : "); scanf(" %[^\n]", patientEnUrgence->prenom);
    printf("ID : ");     scanf(" %[^\n]", patientEnUrgence->id);
    printf("Age : ");    scanf("%d", &patientEnUrgence->age);
    printf("Sexe : ");   scanf("%s", patientEnUrgence->sexe);
    strcpy(patientEnUrgence->departement,"");
    strcpy(patientEnUrgence->diagnostique,"");
    strcpy(patientEnUrgence->ordonnance,"");
    patientEnUrgence->heure.arrive = time(NULL);
    patientEnUrgence->suivant = NULL;

    Urgence *noeud  = malloc(sizeof(Urgence));
    noeud->patient  = patientEnUrgence;
    noeud->suivant  = NULL;

    if (ListeU->tete == NULL)
        ListeU->tete = noeud;
    else {
        Urgence *courant = ListeU->tete;
        while (courant->suivant != NULL) courant = courant->suivant;
        courant->suivant = noeud;
    }
    ListeU->total++;
    ListeU->attente++;

    return ListeU; 
}  
