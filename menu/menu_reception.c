#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#endif

#include "menu.h"
#include "menu_nav.h"
#include "reception.h"
#include "fichier.h"

#define RED    "\033[91m"
#define CYAN   "\033[96m"
#define GREEN  "\033[92m"
#define YELLOW "\033[93m"
#define RESET  "\033[0m"

#define REC_N 5

static void rec_show(int selected) {
    menu_nav_clear();
    printf(RED "+======================================+\n" RESET);
    printf(RED "|          MENU : RECEPTION            |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);

    printf(selected == 0 ? YELLOW "|  > Enregister un patient             |\n" RESET
                         : CYAN   "|    Enregister un patient             |\n" RESET);
    printf(selected == 1 ? YELLOW "|  > Enregister une urgence            |\n" RESET
                         : CYAN   "|    Enregister une urgence            |\n" RESET);
    printf(selected == 2 ? YELLOW "|  > Afficher la liste d'attente       |\n" RESET
                         : CYAN   "|    Afficher la liste d'attente       |\n" RESET);
    printf(selected == 3 ? YELLOW "|  > Afficher l'historique             |\n" RESET
                         : CYAN   "|    Afficher l'historique             |\n" RESET);
    printf(selected == 4 ? YELLOW "|  > QUITTER                           |\n" RESET
                         : CYAN   "|    " RED "QUITTER" CYAN "                           |\n" RESET);

    printf(CYAN "|______________________________________|\n" RESET);
    printf(GREEN "Selection (fleches + Entree) > " RESET);
}

void menuReception(ListePatient *patients, ListeTicket *tickets,
                   ListeUrgence *urgences) {
#ifdef _WIN32
    int selected = 0;
    int key;
    int running = 1;

    while (running) {
        rec_show(selected);
        key = _getch();

        if (key == MENU_NAV_ARROW_PREFIX) {
            key = _getch();
            if (key == MENU_NAV_KEY_UP)
                selected = (selected + REC_N - 1) % REC_N;
            else if (key == MENU_NAV_KEY_DOWN)
                selected = (selected + 1) % REC_N;

        } else if (key == MENU_NAV_KEY_ENTER) {
            switch (selected) {
            case 0:
                AddPatient(patients, tickets);
                menu_nav_pause();
                break;
            case 1:
                menuUrgence(urgences, tickets);
                break;
            case 2:
                afficherAttente(tickets);
                menu_nav_pause();
                break;
            case 3:
                sauvegarderHistorique();
                afficherHistorique();
                menu_nav_pause();
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
    printf("Menu reception interactif : Windows requis (_getch).\n");
#endif
}
