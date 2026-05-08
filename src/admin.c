#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "menu.h"

#define RED    "\033[91m" 
#define CYAN   "\033[96m"
#define GREEN  "\033[92m"
#define YELLOW "\033[93m"
#define RESET  "\033[0m"

void fichiermedicament(ListeMedicament *LM);
void fichierequipement(ListeEquipement *LE);

void gererlit(ListeLit *L) {
    do {
        printf("Nombre de lits (max %d) : ", MAX_LIT);
       L->total = saisirChoix();
    if(L->total == -1) L->total = MAX_LIT + 1; // force la revalidation
        if(L->total > MAX_LIT)
            printf("Erreur : maximum %d lits !\n", MAX_LIT);
    } while(L->total > MAX_LIT);
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

printf(RED "+======================================+\n" RESET);
printf(RED "|        STATISTIQUES HOPITAL          |\n" RESET);
printf(RED "+======================================+\n" RESET);

printf(YELLOW "| PATIENTS                             |\n" RESET);
printf(CYAN "|  Total         : " GREEN "%-20d" CYAN "|\n" RESET, stat->totalPatients);
printf(CYAN "|  En attente    : " GREEN "%-20d" CYAN "|\n" RESET, stat->totalAttente);
printf(CYAN "|  En observation: " GREEN "%-20d" CYAN "|\n" RESET, stat->totalObservation);
printf(CYAN "|  Sortis        : " GREEN "%-20d" CYAN "|\n" RESET, stat->totalsortis);
printf(CYAN "|  Transferes    : " GREEN "%-20d" CYAN "|\n" RESET, stat->totaltransferes);

printf(RED "+--------------------------------------+\n" RESET);

printf(YELLOW "| LITS                                 |\n" RESET);
printf(CYAN "|  Total         : " GREEN "%-20d" CYAN "|\n" RESET, stat->Littotal);
printf(CYAN "|  Occupes       : " RED    "%-20d" CYAN "|\n" RESET, stat->LitIndispo);
printf(CYAN "|  Disponibles   : " GREEN "%-20d" CYAN "|\n" RESET, stat->Littotal - stat->LitIndispo);

printf(RED "+--------------------------------------+\n" RESET);

printf(YELLOW "| URGENCES                             |\n" RESET);
printf(CYAN "|  Total urgences: " GREEN "%-20d" CYAN "|\n" RESET, stat->totalUrgence);
printf(CYAN "|  En attente    : " RED    "%-20d" CYAN "|\n" RESET, stat->attenteUrgence);

printf(RED "+======================================+\n" RESET);
}

void afficherstock(ListeMedicament *LM) {
    printf("Stock de medicaments :\n");
    for(int i = 0; i < LM->total; i++){
        printf("%s : %d\n", LM->medicaments[i].nom, LM->medicaments[i].quantite);
    }
}

void afficherstockequipement(ListeEquipement *LE) {
    printf("Stock d'equipements :\n");
    for(int i = 0; i < LE->total; i++){
        printf("%s : %d\n", LE->equipements[i].nom, LE->equipements[i].quantite);
    }
}

void verfierfindeStock(ListeMedicament *LM, ListeEquipement *LE){
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
    while(getchar() != '\n');   
    for(int i = 0; i < LM->total; i++){
        if(strcmp(LM->medicaments[i].nom, nom) == 0){
            LM->medicaments[i].quantite += quantite;
            fichiermedicament(LM);
            return;
        }
    }

    if(LM->total >= MAX_MEDICAMENTS) { 
        printf("Erreur : stock plein !\n");
        return;
    }
    strcpy(LM->medicaments[LM->total].nom, nom);
    LM->medicaments[LM->total].quantite = quantite;
    LM->total++;
    fichiermedicament(LM);
}

void ajouterequipement(ListeEquipement *LE){
    char nom[30];
    int quantite;
    printf("Veuillez entrer le nom d'equipement a ajouter et sa quantite : ");
    scanf("%s %d", nom, &quantite);
    while(getchar() != '\n');
    for(int i = 0; i < LE->total; i++){
        if(strcmp(LE->equipements[i].nom, nom) == 0){
            LE->equipements[i].quantite += quantite;
            fichierequipement(LE);
            return;
        }
    }
    if(LE->total >= MAX_EQUIPEMENTS) { 
        printf("Erreur : stock plein !\n");
        return;
    }

    strcpy(LE->equipements[LE->total].nom, nom);
    LE->equipements[LE->total].quantite = quantite;
    LE->total++;
    fichierequipement(LE);
}

void utilisermedicament(ListeMedicament *LM){
    char nom[30];
     printf("Veuillez entrer le nom du medicament a utiliser  : ");
    scanf("%s", nom);
    while(getchar() != '\n');
    for(int i = 0; i < LM->total; i++){
        if(strcmp(LM->medicaments[i].nom, nom) == 0){
            if(LM->medicaments[i].quantite >= 1){
                LM->medicaments[i].quantite -= 1;
                fichiermedicament(LM);
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
    while(getchar() != '\n');
    for(int i = 0; i < LE->total; i++){
        if(strcmp(LE->equipements[i].nom, nom) == 0){
            if(LE->equipements[i].quantite >= 1){
                LE->equipements[i].quantite -= 1;
                fichierequipement(LE);
            }else{
                printf("Quantite insuffisante pour l'equipement %s\n", nom);
            }
            return;
        }
    }
    
    printf("Equipement %s non trouve\n", nom);
}

void fichiermedicament(ListeMedicament *LM) {
    FILE *f = fopen("data/medicaments.bin", "wb");
    if (f == NULL) return;
    fwrite(&LM->total,sizeof(int),1,f);
    fwrite(LM->medicaments,sizeof(Medicament), LM->total, f);
    fclose(f);
}

void fichierequipement(ListeEquipement *LE) {
    FILE *f = fopen("data/equipements.bin", "wb");
    if (f == NULL) return;
    fwrite(&LE->total,       sizeof(int),        1,         f);
    fwrite(LE->equipements,  sizeof(Equipement),  LE->total, f);
    fclose(f);
}

void raffraichirmedicament(ListeMedicament *LM) {
    FILE *f = fopen("data/medicaments.bin", "rb");
    if (f == NULL) return;
    LM->total = 0;
    fread(&LM->total,       sizeof(int),       1,         f);
    fread(LM->medicaments,  sizeof(Medicament), LM->total, f);
    fclose(f);
}

void raffraichirequipement(ListeEquipement *LE) {
    FILE *f = fopen("data/equipements.bin", "rb");
    if (f == NULL) return;
    LE->total = 0;
    fread(&LE->total,       sizeof(int),        1,         f);
    fread(LE->equipements,  sizeof(Equipement),  LE->total, f);
    fclose(f);
}//utiliser cette derniere fonction a chaque lancement du programme pour raffraichir les stocks de medicaments et equipements a partir des fichiers de stockage.




