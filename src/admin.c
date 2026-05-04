#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"



void gererlit(ListeLit *L){
    printf("veillez entrer le nombre maximal de lit dans l'hopital : ");
    scanf("%d",&L->total);
    if(L->total > MAX_LIT){
        printf("le nombre maximal de lit est %d\n",MAX_LIT);
        gererlit(L);
    }   
}

void afficherstatistique(ListePatient *LP, ListeLit *LL, ListeUrgence *LU, Statistique *stat){
    
    stat->totalPatients = LP->total;
    stat->totalAttente = LP->attente;
    stat->totalsortis = LP->sortis;
    stat->totaltransferes = LP->transferes;
    stat->totalObservation = LP->observation;
    stat->Littotal = LL->total;
    stat->LitIndispo = LL->indispo;
    stat->totalUrgence = LU->total;
    stat->attenteUrgence = LU->attente;
    printf("Statistiques de l'hopital :\n");
    printf("Nombre total de patients : %d\n", stat->totalPatients);
    printf("Nombre de patients en attente : %d\n", stat->totalAttente);
    printf("Nombre de patients en observation : %d\n", stat->totalObservation);
    printf("Nombre de patients sortis : %d\n", stat->totalsortis);
    printf("Nombre de patients transferes a un autre departement : %d\n", stat->totaltransferes);
    printf("Nombre total de lits : %d\n", stat->Littotal);
    printf("Nombre de lits occupes : %d\n", stat->LitIndispo);
    printf("Nombre de lits disponibles : %d\n", stat->Littotal - stat->LitIndispo);
    printf("Nombre de patients en totale passe en urgence : %d\n", stat->totalUrgence);
    printf("Nombre de patients en attente d'urgence : %d\n", stat->attenteUrgence);
}

void gerermedicament()