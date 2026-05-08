#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "menu.h"
#include "reception.h"
#include "medecin.h"
#include "observation.h"
#include "urgence.h"
#include "fichier.h"
#include "admin.h"




int main() {
    int choix,choixReception,choixMedecin,choixConsult,choixObservation,ChoixUrgence, choixAdmin, choixMedoc, choixEquip;
    char mdp[] = "admin123", mdpdonner[10];
    ListePatient patients = {NULL, 0, 0, 0, 0, 0};
    ListeTicket tickets = {NULL, 0, 0};
    Patient *PatientEnConsult;
    ListeObservation observations = {NULL,0};
    ListeUrgence urgences = {NULL, 0, 0};
    ListeLit lit = {{{0}}, 0 , 0};
    ListeEquipement LE =  {0};
    ListeMedicament LM =  {0};
    Statistique stat = {0,0,0,0,0,0,0,0,0};
    chargerLit(&lit);
    chargerTickets(&tickets);
    chargerPatients(&patients,&tickets);
    chargerObservations(&patients,&observations,&lit);
    chargerUrgences(&urgences, &tickets); 
    verifierNouveauJour(&tickets); // Pour réinitialiser le compteur de ticket a chaque minuit.
    raffraichirequipement(&LE);
    raffraichirmedicament(&LM);
    do {
        menuPrincipal();
        choix = saisirChoix();
        switch(choix) {
            case 1 : 
                do {
                     menuMedecin();
                     choixMedecin = saisirChoix();
                     switch(choixMedecin) {
                        case 1 : 
                            PatientEnConsult = CallPatient(&tickets,&urgences,&patients);
                            if(PatientEnConsult == NULL){
                                pause();
                                break;
                            }
                            do{
                                menuConsultation(PatientEnConsult);
                                choixConsult = saisirChoix();
                                switch(choixConsult) {
                                    case 1 : 
                                        PatientDiagnostic(PatientEnConsult);
                                        pause();
                                    break;
                                    case 2 :
                                        PatientOrdonnance(PatientEnConsult,&patients,&tickets);
                                        if(strcmp(PatientEnConsult->diagnostique,"") !=0)choixConsult = 5;
                                        pause();
                                    break;
                                    case 3 :
                                        AddObservation(PatientEnConsult, &observations, &lit, &tickets, &patients, &LM, &LE);
                                        if(strcmp(PatientEnConsult->diagnostique,"") !=0)choixConsult = 5;
                                        pause();
                                    break;
                                    case 4: 
                                        transferer(PatientEnConsult,&patients,&tickets);
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
                            choixObservation = saisirChoix();
                            switch(choixObservation) {
                                case 1 : 
                                    ModifierObservation(&observations,&lit, &LM);
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
                        choixReception = saisirChoix();
                        switch(choixReception) {
                            case 1:
                                AddPatient(&patients,&tickets);
                                pause();
                            break;
                            case 2 :
                                do{ 
                                menuUrgence();
                                ChoixUrgence = saisirChoix();
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
                printf("Mot de passe : ");
                scanf("%s",mdpdonner);
                if(strcmp(mdp,mdpdonner) != 0) {
                    printf("Mot de passe incorrect !");
                    pause();
                    break;
                }
                    else {
                    do{
                        menuAdmin();
                        choixAdmin = saisirChoix();
                        switch(choixAdmin) {
                            case 1 : 
                            do{
                                menuequipement();
                                choixEquip = saisirChoix();
                                switch(choixEquip) {
                                    case 1 : 
                                        ajouterequipement(&LE); 
                                        pause();
                                    break;
                                    
                                    case 2 :
                                        afficherstockequipement(&LE);
                                        pause();
                                    break;
                                }  
                            }while(choixEquip != 3);
                            break;
                            case 2 : 
                            do{
                                menumedicament();
                                choixMedoc = saisirChoix();
                                switch(choixMedoc) {
                                    case 1 : 
                                        ajoutermedicament(&LM);
                                        pause();
                                    break;                                    
                                    case 2 :
                                        afficherstock(&LM);
                                        pause();
                                    break;
                                } 
                            }while(choixMedoc != 3);
                            break;
                            case 3 :
                                gererlit(&lit);
                                pause();
                            break;
                            case 4 :
                                afficherstatistique(&patients, &lit, &urgences, &stat);
                                pause();
                            break; 
                            }    
                    }while(choixAdmin != 5); 
                    break;
               }  

            case 4 : 
               printf(GREEN " Au revoir !\n" RESET);
               SaveTicket(&tickets);
               sauvegarderLit(&lit);
               sauvegarderUrgences(&urgences);
               NettoyerPatientsSortis(&patients);
            break;
           }
    }while(choix != 4);
return 0;
}
