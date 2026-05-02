#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "reception.h"
#include "medecin.h"
#include "menu.h"
#include "observation.h"
#include "historique.h"



int main() {
    int choix,choixReception,choixMedecin,choixConsult;
    ListePatient patient = {NULL, 0, 0, 0, 0, 0};
    ListeTicket ticket = {NULL, 0};
    Patient *PatientEnConsult;
    ListeObservation observation = {NULL,0};
    ListeLit lit = {NULL, 0 , 0};
    chargerTicket(&ticket);
    chargerPatient(&patient);
    verifierNouveauJour(&ticket); // Pour réinitialiser le compteur de ticket a chaque minuit.

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
                                menuConsultation(PatientEnConsult);
                                scanf("%d",&choixConsult);
                                switch(choixConsult) {
                                    case 1 : 
                                        PatientDiagnostic(PatientEnConsult);
                                    break;
                                    case 2 :
                                        PatientOrdonnance(PatientEnConsult);
                                    break;
                                    case 3 : 
                                        AddObservation(PatientEnConsult,&observation,&lit);
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
                                AddPatient(&patient,&ticket);
                            break;
                            case 2 :
                                DisplayQueue(&patient);
                            break;
                            case 4 :
                                afficherHistorique(&patient,&observation);
                                break;
                        }
                    }while(choixReception != 3);
            break;
        }  
    }while(choix != 3);
    return 0;
}