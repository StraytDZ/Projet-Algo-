#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "reception.h"
#include "medecin.h"
#include "menu.h"
#include "observation.h"



int main() {
    int choix,choixReception,choixMedecin,choixConsult,choixObservation;
    ListePatient patients = {NULL, 0, 0, 0, 0, 0};
    ListeTicket tickets = {NULL, 0};
    Patient *PatientEnConsult;
    ListeObservation observations = {NULL,0};
    ListeUrgence urgences = {NULL, 0, 0};
    ListeLit lit = {{0}, 0 , 0};
    chargerTicket(&tickets);
    chargerPatient(&patients);
    verifierNouveauJour(&tickets); // Pour réinitialiser le compteur de ticket a chaque minuit.

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
                            PatientEnConsult = CallPatient(&tickets,&urgences);
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
                                        AddObservation(PatientEnConsult,&observations,&lit);
                                    break;
                                }
                            }while(choixConsult != 6);
                        break;
                        case 2 : 
                            AfficherAttente(&tickets);
                        break;
                        case 3 : 
                            do {
                            menuObservation();
                            scanf("%d",&choixObservation);
                            switch(choixObservation) {
                                case 1 : 
                                    ModifierObservation(&observations,&lit);
                                break;
                                case 2 : 
                                    AfficherObservation(&observations);
                                break;
                                case 3 : 
                                    RechercheObservation(&observations);
                                break;
                            }
                        }while(choixObservation != 4);
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
                                AddPatient(&patients,&tickets);
                            break;
                            case 2 :
                                DisplayQueue(&patients);
                            break;
                            case 3 :
                                afficherHistorique();
                                break;
                        }
                    }while(choixReception != 3);
            break;
        }  
    }while(choix != 3);
    return 0;
}