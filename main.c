#include <stdlib.h>
#include <stdio.h>
#include "reception.h"
#include "medecin.h"
#include "menu.h"

<<<<<<< HEAD
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
=======
>>>>>>> 8a79baef209f28cd8e6f0efd94e56fb6edb59753

int main() {
    int choix,choixReception,choixMedecin,choixConsult;
    ListePatient patient = {NULL, 0, 0, 0, 0, 0};
    ListeTicket ticket = {NULL, 0};
    Patient *PatientEnConsult;
    do {
        menuPrincipal();
        scanf("%d",&choix);
        switch(choix) {
            case 1 : 
                do {
                     menuMedecin();
                     scanf("%d",&choixMedecin);
                     switch(choixMedecin) {
                        case 1 : 
                            PatientEnConsult = CallPatient(&ticket);
                            do{
                                menuConsultation();
                                scanf("%d",&choixConsult);
                                switch(choixConsult) {
                                    case 1 : 
                                        PatientDiagnostic(PatientEnConsult);
                                    break;
                                    case 2 : 
                                        PatientTraitement(PatientEnConsult);
                                    break;
                                    case 3 :
                                        PatientOrdonnance(PatientEnConsult);
                                    break;
                                    case 4 : 

                                    break;
                                }
                            }while(choixConsult != 6);
                        break;
                     }
                }while(choixMedecin != 3);
            break;
            
            case 2 : 
                    do{
                        menuReception();
                        scanf("%d",&choixReception);
                        switch(choixReception) {
                            case 1:
                                patient.tete = AddPatient(&patient,&ticket);
                            break;
                            case 2 :
                                DisplayQueue(&patient);
                            break;
                        }
                    }while(choixReception != 3);
            break;
        }  
    }while(choix != 3);
    return 0;
}