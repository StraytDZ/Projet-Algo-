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

void saisirmedicament(ListeMedicament *LM){
    printf("Veuillez entrer le nom de medicament a ajouter et ca quantite : ");
    scanf("%s %d", LM->medicaments[LM->total].nom, &LM->medicaments[LM->total].quantite);
    LM->total++;
}
void afficherstock(ListeMedicament *LM){
    printf("Stock de medicament :\n");
    for(int i = 0; i < LM->total; i++){
        printf("%s : %d\n", LM->medicaments[i].nom, LM->medicaments[i].quantite);
    }
}

void saisirequipement(ListeEquipement *LE){
    printf("Veuillez entrer le nom de equipement a ajouter et ca quantite : ");
    scanf("%s %d", LE->equipements[LE->total].nom, &LE->equipements[LE->total].quantite);
    LE->total++;
}

void afficherstockequipement(ListeEquipement *LE){
    printf("Stock de equipement :\n");
    for(int i = 0; i < LE->total; i++){
        printf("%s : %d\n", LE->equipements[i].nom, LE->equipements[i].quantite);
    }
}

void verfierfindeMedoc(ListeMedicament *LM, ListeEquipement *LE){
    printf("Medicaments en rupture de stock :\n");
    for(int i = 0; i < LM->total; i++){
        if(LM->medicaments[i].quantite == 0){
            printf("%s\n", LM->medicaments[i].nom);
        }
    }
    printf("Equipements en rupture de stock :\n");
    for(int i = 0; i < LE->total; i++){
        if(LE->equipements[i].quantite == 0){
            printf("%s\n", LE->equipements[i].nom);
        }
    }
}

void ajoutermedicament(ListeMedicament *LM){
    char nom[30];
    int quantite;
    printf("Veuillez entrer le nom du medicament a ajouter et sa quantite : ");
    scanf("%s %d", nom, &quantite);
    for(int i = 0; i < LM->total; i++){
        if(strcmp(LM->medicaments[i].nom, nom) == 0){
            LM->medicaments[i].quantite += quantite;
            return;
        }
    }
    strcpy(LM->medicaments[LM->total].nom, nom);
    LM->medicaments[LM->total].quantite = quantite;
    LM->total++;
}

void ajouterequipement(ListeEquipement *LE){
    char nom[30];
    int quantite;
    printf("Veuillez entrer le nom de equipement a ajouter et sa quantite : ");
    scanf("%s %d", nom, &quantite);
    for(int i = 0; i < LE->total; i++){
        if(strcmp(LE->equipements[i].nom, nom) == 0){
            LE->equipements[i].quantite += quantite;
            return;
        }
    }
    strcpy(LE->equipements[LE->total].nom, nom);
    LE->equipements[LE->total].quantite = quantite;
    LE->total++;
}

void utilisermedicament(ListeMedicament *LM){
    char nom[30];
     printf("Veuillez entrer le nom du medicament a utiliser  : ");
    scanf("%s", nom);
    for(int i = 0; i < LM->total; i++){
        if(strcmp(LM->medicaments[i].nom, nom) == 0){
            if(LM->medicaments[i].quantite >= 1){
                LM->medicaments[i].quantite -= 1;
            }else{
                printf("Quantite insuffisante pour le medicament %s\n", nom);
            }
            return;
        }
    }
    printf("Medicament %s non trouve\n", nom);
}


void utiliserequipement(ListeEquipement *LE){
    char nom[30];
     printf("Veuillez entrer le nom de l'equipement a utiliser  : ");
    scanf("%s", nom);
    for(int i = 0; i < LE->total; i++){
        if(strcmp(LE->equipements[i].nom, nom) == 0){
            if(LE->equipements[i].quantite >= 1){
                LE->equipements[i].quantite -= 1;
            }else{
                printf("Quantite insuffisante pour l'equipement %s\n", nom);
            }
            return;
        }
    }
    printf("Equipement %s non trouve\n", nom);
}



