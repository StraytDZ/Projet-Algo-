#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#endif

#include "menu.h"
#include "menu_nav.h"
#include "medecin.h"
#include "observation.h"
#include "fichier.h"

#define RED    "\033[91m"
#define CYAN   "\033[96m"
#define GREEN  "\033[92m"
#define YELLOW "\033[93m"
#define RESET  "\033[0m"

#define CONS_N 5

static void cons_show(int selected, Patient *p) {
    menu_nav_clear();
    printf(RED "+======================================+\n" RESET);
    printf(RED "|         MENU : CONSULTATION          |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN " Patient %d : %s %s | %d | %s | %s\n" RESET,
           p->ticket->numero, p->nom, p->prenom, p->age, p->sexe, p->id);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);

    printf(selected == 0 ? YELLOW "|  > Enregistrer le diagnostic         |\n" RESET
                         : CYAN   "|    Enregistrer le diagnostic         |\n" RESET);
    printf(selected == 1 ? YELLOW "|  > Inscrire une ordonnance           |\n" RESET
                         : CYAN   "|    Inscrire une ordonnance           |\n" RESET);
    printf(selected == 2 ? YELLOW "|  > Mettre en observation             |\n" RESET
                         : CYAN   "|    Mettre en observation             |\n" RESET);
    printf(selected == 3 ? YELLOW "|  > Transfert autre departement       |\n" RESET
                         : CYAN   "|    Transfert autre departement       |\n" RESET);
    printf(selected == 4 ? YELLOW "|  > QUITTER                           |\n" RESET
                         : CYAN   "|    " RED "QUITTER" CYAN "                           |\n" RESET);

    printf(CYAN "|______________________________________|\n" RESET);
    printf(GREEN "Selection (fleches + Entree) > " RESET);
}

void menuConsultation(Patient *patientEnConsult, ListeObservation *observations,
                      ListeLit *lit, ListeTicket *tickets, ListePatient *patients) {
    if (patientEnConsult == NULL || patientEnConsult->ticket == NULL) {
        menu_nav_clear();
        printf(RED "Erreur : patient ou ticket invalide.\n" RESET);
        menu_nav_pause();
        return;
    }

#ifdef _WIN32
    int selected = 0;
    int key;
    int running = 1;

    while (running) {
        cons_show(selected, patientEnConsult);
        key = _getch();

        if (key == MENU_NAV_ARROW_PREFIX) {
            key = _getch();
            if (key == MENU_NAV_KEY_UP)
                selected = (selected + CONS_N - 1) % CONS_N;
            else if (key == MENU_NAV_KEY_DOWN)
                selected = (selected + 1) % CONS_N;

        } else if (key == MENU_NAV_KEY_ENTER) {
            switch (selected) {
            case 0:
                PatientDiagnostic(patientEnConsult);
                menu_nav_pause();
                break;
            case 1:
                PatientOrdonnance(patientEnConsult, patients);
                if (patientEnConsult->etat == SORTI) running = 0;
                else menu_nav_pause();
                break;
            case 2:
                AddObservation(patientEnConsult, observations, lit, tickets, patients);
                if (patientEnConsult->etat == OBSERVATION) running = 0;
                else menu_nav_pause();
                break;
            case 3:
                transferer(patientEnConsult, patients);
                if (patientEnConsult->etat == TRANSFERER) running = 0;
                else menu_nav_pause();
                break;
            case 4:
                running = 0;
                break;
            default:
                break;
            }
        }
    }
#else
    menu_nav_clear();
    printf("Menu consultation interactif : Windows requis (_getch).\n");
#endif
}
