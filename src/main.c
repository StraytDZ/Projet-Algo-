#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "reception.h"
#include "medecin.h"
#include "menu.h"
#include "observation.h"
#include "urgence.h"
#include "fichier.h"
#include "admin.h"


int main() {
    int choix,choixReception,choixMedecin,choixConsult,choixObservation,ChoixUrgence,ChoixAdmin;
    char mdp[] = "admin123Algo", mdpdonner[20];
    ListePatient patients = {NULL, 0, 0, 0, 0, 0};
    ListeTicket tickets = {NULL, 0, 0};
    Patient *PatientEnConsult;
    ListeObservation observations = {NULL,0};
    ListeUrgence urgences = {NULL, 0, 0};
    ListeLit lit = {{0}, MAX_LIT , 0};
    chargerTickets(&tickets);
    chargerPatients(&patients,&tickets);
    chargerObservations(&patients,&observations,&lit);
    verifierNouveauJour(&tickets); // Pour réinitialiser le compteur de ticket a chaque minuit.

    do {
        menuPrincipal();
        menuMessage();
        scanf("%d",&choix);
        switch(choix) {
            case 1 : 
                do {
                     menuMedecin();
                     scanf("%d",&choixMedecin);
                     switch(choixMedecin) {
                        case 1 : 
                            PatientEnConsult = CallPatient(&tickets,&urgences,&patients);
                            if(PatientEnConsult == NULL){
                                pause();
                                break;
                            }
                            do{
                                menuConsultation(PatientEnConsult);
                                scanf("%d",&choixConsult);
                                switch(choixConsult) {
                                    case 1 : 
                                        PatientDiagnostic(PatientEnConsult);
                                        pause();
                                    break;
                                    case 2 :
                                        PatientOrdonnance(PatientEnConsult,&patients);
                                        if(strcmp(PatientEnConsult->diagnostique,"") !=0)choixConsult = 5;
                                        pause();
                                    break;
                                    case 3 : 
                                        AddObservation(PatientEnConsult,&observations,&lit,&tickets,&patients);
                                        if(strcmp(PatientEnConsult->diagnostique,"") !=0)choixConsult = 5;
                                        pause();
                                    break;
                                    case 4: 
                                        transferer(PatientEnConsult,&patients);
                                        if(strcmp(PatientEnConsult->diagnostique,"") !=0)choixConsult = 5;
                                        pause();
                                        continue;
                                    break;
                                }
                            }while(choixConsult != 5);
                        break;
                        case 2 : 
                            AfficherAttente(&tickets);
                            pause();
                        break;
                        case 3 : 
                            do {
                            menuObservation();
                            scanf("%d",&choixObservation);
                            switch(choixObservation) {
                                case 1 : 
                                    ModifierObservation(&observations,&lit);
                                    pause();
                                break;
                                case 2 : 
                                    AfficherListeObservation(&observations);
                                    pause();
                                break;
                                case 3 : 
                                    RechercheObservation(&observations);
                                    pause();
                                break;
                                case 4 : 
                                    SupprimerObservation(&observations,&lit);
                                    pause();
                                break;
                            }
                        }while(choixObservation != 5);
                        break;
                     }
                }while(choixMedecin != 4);
            break;
            
            case 2 : 
                    do{
                        menuReception();
                        scanf("%d",&choixReception);
                        switch(choixReception) {
                            case 1:
                                AddPatient(&patients,&tickets);
                                pause();
                            break;
                            case 2 :
                                do{ 
                                menuUrgence();
                                scanf("%d", &ChoixUrgence);
                                switch(ChoixUrgence) {
                                    case 1: 
                                        AddUrgence(&urgences,&tickets);
                                        pause();
                                    break;
                                    case 2 :
                                        afficherUrgence(&urgences);
                                        pause();
                                    break;
                                }
                                }while(ChoixUrgence != 3);
                            break;
                            case 3 : 
                                afficherAttente(&tickets);
                                pause();
                            break;
                            case 4 :
                                afficherHistorique();
                                pause();
                            break;
                              }   
                    }while(choixReception != 5);
            break;
            case 3 : 
                    printf("Veuiller saisir le mot de passe : ");
                    scanf("%s", mdpdonner);
                    if(strcmp(mdp, mdpdonner) != 0 ) {
                        printf("Mot de passe incorrect ! ");
                        pause();
                    }
                    else { 
                        do{
                            menuAdmin();
                            scanf("%d", &ChoixAdmin);
                            switch(ChoixAdmin) {
                                case 1 :
                                    gerer
                                break;
                            }
                        }while(ChoixAdmin != 5)
                    }   
            break;
            case 4 :
                sauvegarderHistorique();
                SaveTicket(&tickets);
                printf("Au revoir !\n");
            break;
        }  
    }while(choix != 4);
    return 0;
}