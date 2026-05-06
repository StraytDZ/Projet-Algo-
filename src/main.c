#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <conio.h>
#endif

#include "menu.h"
#include "menu_nav.h"
#include "reception.h"
#include "medecin.h"
#include "observation.h"
#include "urgence.h"
#include "fichier.h"
#include "admin.h"

#define RED    "\033[91m"
#define CYAN   "\033[96m"
#define GREEN  "\033[92m"
#define YELLOW "\033[93m"
#define RESET  "\033[0m"

static void menu_principal(int selected) {
    menu_nav_clear();
    printf(RED "+======================================+\n" RESET);
    printf(RED "|           MENU : PRINCIPALE          |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);

    printf(selected == 0 ? YELLOW "|  > MEDECIN                           |\n" RESET
                         : CYAN   "|    MEDECIN                           |\n" RESET);
    printf(selected == 1 ? YELLOW "|  > RECEPTION                         |\n" RESET
                         : CYAN   "|    RECEPTION                         |\n" RESET);
    printf(selected == 2 ? YELLOW "|  > ADMIN                             |\n" RESET
                         : CYAN   "|    ADMIN                             |\n" RESET);
    printf(selected == 3 ? YELLOW "|  > QUITTER                           |\n" RESET
                         : CYAN   "|    " RED "QUITTER" CYAN "                           |\n" RESET);

    printf(CYAN "|______________________________________|\n" RESET);
    printf(GREEN "Selection (fleches + Entree) > " RESET);
}

int main(void) {
    /* ── Initialisation des listes ── */
    ListePatient     patients     = {NULL, 0, 0, 0, 0, 0};
    ListeTicket      tickets      = {NULL, 0, 0};
    ListeObservation observations = {NULL, 0};
    ListeUrgence     urgences     = {NULL, 0, 0};
    ListeMedicament  medicaments  = {{{{0}}}, 0};
    ListeEquipement  equipements  = {{{{0}}}, 0};
    ListeLit         lit;
    memset(&lit, 0, sizeof(ListeLit));
    lit.total = MAX_LIT;

    /* ── Chargement des données ── */
    chargerTickets(&tickets);
<<<<<<< HEAD
    chargerPatients(&patients, &tickets);
    chargerObservations(&patients, &observations, &lit);
    verifierNouveauJour(&tickets);

    /* ── Boucle principale ── */
    int select  = 0;
    int key;
    int running = 1;

    while (running) {
        verifierFinObservations(&observations, &lit, &patients);
        menu_principal(select);

#ifdef _WIN32
        key = _getch();

        if (key == MENU_NAV_ARROW_PREFIX) {
            key = _getch();
            if (key == MENU_NAV_KEY_UP)
                select = (select + 3) % 4;
            else if (key == MENU_NAV_KEY_DOWN)
                select = (select + 1) % 4;

        } else if (key == MENU_NAV_KEY_ENTER) {
            switch (select) {
            case 0:
                menuMedecin(&tickets, &urgences, &patients, &observations, &lit);
=======
    chargerPatients(&patients,&tickets);
    chargerObservations(&patients,&observations,&lit);
    verifierNouveauJour(&tickets); // Pour réinitialiser le compteur de ticket a chaque minuit.
    raffraichirequipement(&LE, "equipements.txt");
    raffraichirmedicament(&LM, "medicaments.txt");
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
                do{
                    menuAdmin();
                    scanf("%d",&choixAdmin);
                    switch(choixAdmin) {
                        case 1 : 
                            menuequipement();
                            scanf("%d",&choixEquip);
                            switch(choixEquip) {
                                case 1 : 
                                    saisirequipement(&LE, "equipements.txt");
                                    pause();
                                break;
                                case 2 : 
                                    ajouterequipement(&LE, "equipements.txt");
                                    pause();
                                    break;
                                case 3 :
                                    printf("Stock d'equipements :\n");
                                    afficherstockequipement(&LE);
                                    pause();
                                break;
                                case 4 : 
                                break; 
                            }  
                        break;
                        case 2 : 
                            menumedicament();
                            scanf("%d",&choixMedoc);
                            switch(choixMedoc) {
                                case 1 : 
                                    saisirmedicament(&LM, "medicaments.txt");
                                    pause();
                                break;
                                case 2 : 
                                    ajoutermedicament(&LM, "medicaments.txt");
                                    pause();
                                break;
                                case 3 :
                                    printf("Stock de medicaments :\n");
                                    afficherstock(&LM);
                                    pause();
                                break;
                                case 4 : 
                                break; 
                            }    
                        break;
                        case 3 :
                            gererlit(&lit);
                        break;
                        case 4 :
                            afficherstatistique(&patients, &lit, &urgences, &stat);
                        break; 
                        }    
                }while(choixAdmin != 5);
                
>>>>>>> parent of f6ebe7c (admin encore et toujours)
                break;
            case 1:
                menuReception(&patients, &tickets, &urgences);
                break;
            case 2:
                menuAdmin(&patients, &lit, &urgences, &medicaments, &equipements);
                break;
            case 3:
                sauvegarderHistorique();
                SaveTicket(&tickets);
                menu_nav_clear();
                printf(GREEN "Au revoir !\n" RESET);
                running = 0;
                break;
            default:
                break;
            }
        }
#else
        printf("\nCe mode interactif est configure pour Windows (_getch).\n");
        running = 0;
#endif
    }

    return 0;
}