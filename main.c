#include <stdlib.h>
#include <stdio.h>
#include "reception.h"

void menu(){
    system("cls");
    printf("\t+++++URGENCE+++++\n");
    printf("\t=+=+=+=MENU=+=+=+=\n");
    printf("=======================================\n\n");
    printf("\t 1 - Medecin\n");
    printf("\t 2 - Reception\n");
    printf("\t 3 - Quitter\n\n");
    printf("=======================================\n");
    printf("                          Choix : ");
}

int main() {
    int choix,choixReception,choixMedecin,Age;
    char Nom[30],Prenom[30],ID[20],Sexe[4];
    Patient *ListePatient = NULL;
    ListeTicket ticket = {NULL, 0};

    do {
        menu();
        scanf("%d",&choix);
        switch(choix) {
            case 1 : 
            break;
            
            case 2 : 
                    do{
                        menuReception();
                        scanf("%d",&choixReception);
                        switch(choixReception) {
                            case 1: 
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
                                ListePatient = AddPatient(ListePatient,&ticket,Nom,Prenom,ID,Age,Sexe);
                            break;
                            case 2 : 
                                DisplayQueue(ListePatient);
                            break;
                        }
                    }while(choixReception != 3);
            break;
        }  
    }while(choix != 3);
    return 0;
}