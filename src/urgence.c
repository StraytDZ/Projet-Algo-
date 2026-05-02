#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "urgence.h"
#include "structure.h"
#include "reception.h"

ListeUrgence* AddUrgence(ListeUrgence *ListeU, ListeTicket *ListeT){
    Patient *patientEnUrgence = (Patient*)malloc(sizeof(Patient));
    patientEnUrgence->etat = URGENCE;
     ListeTicket *listeCible = ListeT;
    listeCible->compteur++;
    Ticket *nouveauTicket = CreateTicket(patientEnUrgence,listeCible->compteur);
    if(listeCible->tete == NULL) { 
        listeCible->tete = nouveauTicket;  
        patientEnUrgence->ticket = nouveauTicket;
    }
    else{    
        Ticket *courant = listeCible->tete;
        while(courant->suivant != NULL) {
        courant = courant->suivant;
    }
    courant->suivant = nouveauTicket;
   }
    patientEnUrgence->ticket = nouveauTicket;
    strcpy(patientEnUrgence->departement,"");
    strcpy(patientEnUrgence->diagnostique,"");
    strcpy(patientEnUrgence->ordonnance,"");
    patientEnUrgence->heure.arrive = time(NULL);
    patientEnUrgence->suivant = NULL;
    if(ListeU->tete == NULL) {
        ListeU->tete = patientEnUrgence;
        ListeU->attente++;
        ListeU->total++;
        return ListeU;  
    }
    Patient *courant = ListeU->tete;
    while(courant->suivant != NULL){
        courant = courant->suivant;
    }
    courant->suivant = patientEnUrgence;
    ListeU->attente++;
    ListeU->total++;
    return ListeU; 
}  
