#include <stdlib.h>
#include <stdio.h>
#include "reception.h"
#include "medecin.h"
#include "menu.h"
#include "observation.h"

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
    int lit=0
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
                        }
                    }while(choixReception != 3);
            break;
        }  
    }while(choix != 3);
    return 0;
}
}
}