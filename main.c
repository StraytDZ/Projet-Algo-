#include <stdlib.h>
#include <stdio.h>
#include "reception.h"
#include "medecin.h"
#include "menu.h"


int main() {
    int choix,choixReception,choixMedecin,choixMedecinConsult;
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
                                scanf("%d",&choixMedecinConsult);
                                switch(choixMedecinConsult) {
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
                            }
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
                                patient = AddPatient(&patient,&ticket);
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