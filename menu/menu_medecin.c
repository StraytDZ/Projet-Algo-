#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#endif

#include "menu_nav.h"
#include "medecin.h"
#include "reception.h"
#include "observation.h"
#include "fichier.h"
#include "menu.h" 

#define RED "\033[91m"
#define CYAN "\033[96m"
#define GREEN "\033[92m"
#define YELLOW "\033[93m"
#define RESET "\033[0m"

#define MED_N 4

static void med_show(int selected) {
    menu_nav_clear();

    printf(RED "+======================================+\n" RESET);
    printf(RED "|           MENU : MEDECIN             |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);

    printf(selected == 0 ? YELLOW "|  > Appeler le patient suivant        |\n" RESET
                         : CYAN "|    Appeler le patient suivant        |\n" RESET);
    printf(selected == 1 ? YELLOW "|  > Afficher la liste d'attente       |\n" RESET
                         : CYAN "|    Afficher la liste d'attente       |\n" RESET);
    printf(selected == 2 ? YELLOW "|  > Observation                       |\n" RESET
                         : CYAN "|    Observation                       |\n" RESET);
    printf(selected == 3 ? YELLOW "|  > QUITTER                           |\n" RESET
                         : CYAN "|    " RED "QUITTER" CYAN "                           |\n" RESET);

    printf(CYAN "|______________________________________|\n" RESET);
    printf(GREEN "Selection (fleches + Entree) > " RESET);
}

static void med_placeholder(const char *titre) {
    menu_nav_clear();
    printf(YELLOW "=== %s ===\n" RESET, titre);
    printf(CYAN "A implementer.\n" RESET);
    menu_nav_pause();
}

void menuMedecin(ListeTicket *tickets, ListeUrgence *urgences, ListePatient *patients, ListeObservation *observations, ListeLit *lit) {
#ifdef _WIN32
    int selected = 0;
    int key;
    int running = 1;
    Patient *PatientEnConsult = NULL;
    while (running) {
        med_show(selected);
        key = _getch();
        if (key == MENU_NAV_ARROW_PREFIX) {
            key = _getch();
            if (key == MENU_NAV_KEY_UP) {
                selected = (selected + MED_N - 1) % MED_N;
            } else if (key == MENU_NAV_KEY_DOWN) {
                selected = (selected + 1) % MED_N;
            }
        } else if (key == MENU_NAV_KEY_ENTER) {
            switch (selected) {
            case 0:
                PatientEnConsult = CallPatient(tickets, urgences, patients);
                if(PatientEnConsult != NULL)
                menuConsultation(PatientEnConsult, observations, lit, tickets, patients);
            break;
                break;
            case 1:
                med_placeholder("Liste d'attente");
                break;
            case 2:
                med_placeholder("Observation");
                break;
            case 3:
                running = 0;
                break;
            default:
                break;
            }
        }
    }
#else
    menu_nav_clear();
    printf("Menu medecin interactif : Windows requis (_getch).\n");
#endif
}
