#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "reception.h"
#include "medecin.h"
#include "menu.h"
#include "observation.h"
#include "urgence.h"
#include "fichier.h"

int main() {
    int choix,choixReception,choixMedecin,choixConsult,choixObservation,ChoixUrgence;
    ListePatient patients = {NULL, 0, 0, 0, 0, 0};
    ListeTicket tickets = {NULL, 0};
    Patient *PatientEnConsult;
    ListeObservation observations = {NULL,0};
    ListeUrgence urgences = {NULL, 0, 0};
    ListeLit lit = {{0}, 0 , 0};
    chargerTickets(&tickets);
    chargerPatients(&patients,&tickets);
    chargerObservations(&patients,&observations,&lit);
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
                                    case 4: 
                                        transferer(PatientEnConsult);
                                    break;
                                }
                            }while(choixConsult != 5);
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
                                    AfficherListeObservation(&observations);
                                break;
                                case 3 : 
                                    RechercheObservation(&observations);
                                break;
                                case 4 : 
                                    AfficherListeObservation(&observations);
                                    int numlit;
                                    printf("Numero du lit a liberer : ");
                                    scanf("%d", &numlit);
                                    SupprimerObservation(&observations,&lit,numlit);
                                break;
                            }
                        }while(choixObservation != 5);
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
                                do{ 
                                menuUrgence();
                                scanf("%d", &ChoixUrgence);
                                switch(ChoixUrgence) {
                                    case 1: 
                                        AddUrgence(&urgences,&tickets);
                                    break;
                                    case 2 :
                                        afficherUrgence(&urgences);
                                    break;
                                }
                                }while(ChoixUrgence != 3);
                            break;
                            case 3 : 
                                afficherAttente(&tickets);
                            break;
                            case 4 :
                                afficherHistorique();
                            break;
                              }   
                    }while(choixReception != 5);
            break;

            case 4 :
                sauvegarderPatients(&patients);
                sauvegarderObservations(&observations);
                SaveTicket(&tickets);
                printf("Au revoir !\n");
            break;
        }  
    }while(choix != 4);
    return 0;
}