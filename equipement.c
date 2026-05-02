#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "equipement.h"


void ajouterEquipement(ListeEquipement *listeE) {
    if(listeE->total >= NB_EQUIPEMENTS){
        printf("Erreur : Liste pleine !");
        return;
    }

    Equipement *e = &listeE->equipements[listeE->total + 1];
    printf("Preciser le nom du nouvel equipement :");
    scanf(" $[^\n]", e->nom);

    printf("Preciser le type : \n\t0 - Medicale \n\t1 - Chirurgical\n\t2 - Informatique\n\t3 - Mobilier\n\t4 - Autre\n");
    scanf("%d", &e->type);

    printf("Qauntite total :");
    scanf("%d",&e->quantite);
    e->quantiteDisponible = e->quantite;

    printf("Service : ");
    scanf(" %[^\n]", e->service);

    printf("Prix unitaire : ");
    scanf("%f", &e->prix);
 
    e->etat = DISPONIBLE;
    e->dateAchat = time(NULL);
    listeE->total++;
    printf("Equipement \"%s\" ajoutee avec succees.\n", e->nom);
    
}

void affichierEquipement(ListeEquipement *ListeE) {
    if(ListeE->total == 0) {
        printf("Aucun equipement enregister.\n");
        return;
    }
    

}

    int id;
    char nom[50];
    TypeEquipement type;
    EtatEquipement etat;
    int quantite;
    int quantiteDisponible;
    char service[30];       // quel service l'utilise
    time_t dateAchat;
    float prix;


}