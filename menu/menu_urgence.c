#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#endif

#include "menu.h"
#include "menu_nav.h"
#include "urgence.h"

#define RED    "\033[91m"
#define CYAN   "\033[96m"
#define GREEN  "\033[92m"
#define YELLOW "\033[93m"
#define RESET  "\033[0m"

#define URG_N 3

static void urg_show(int selected) {
    menu_nav_clear();
    printf(RED "+======================================+\n" RESET);
    printf(RED "|           MENU : URGENCE             |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);

    printf(selected == 0 ? YELLOW "|  > Enregister une urgence            |\n" RESET
                         : CYAN   "|    Enregister une urgence            |\n" RESET);
    printf(selected == 1 ? YELLOW "|  > Afficher la liste d'urgences      |\n" RESET
                         : CYAN   "|    Afficher la liste d'urgences      |\n" RESET);
    printf(selected == 2 ? YELLOW "|  > QUITTER                           |\n" RESET
                         : CYAN   "|    " RED "QUITTER" CYAN "                           |\n" RESET);

    printf(CYAN "|______________________________________|\n" RESET);
    printf(GREEN "Selection (fleches + Entree) > " RESET);
}

void menuUrgence(ListeUrgence *urgences, ListeTicket *tickets) {
#ifdef _WIN32
    int selected = 0;
    int key;
    int running = 1;

    while (running) {
        urg_show(selected);
        key = _getch();

        if (key == MENU_NAV_ARROW_PREFIX) {
            key = _getch();
            if (key == MENU_NAV_KEY_UP)
                selected = (selected + URG_N - 1) % URG_N;
            else if (key == MENU_NAV_KEY_DOWN)
                selected = (selected + 1) % URG_N;

        } else if (key == MENU_NAV_KEY_ENTER) {
            switch (selected) {
            case 0:
                AddUrgence(urgences, tickets);
                menu_nav_pause();
                break;
            case 1:
                afficherUrgence(urgences);
                menu_nav_pause();
                break;
            case 2:
                running = 0;
                break;
            default:
                break;
            }
        }
    }
#else
    menu_nav_clear();
    printf("Menu urgence interactif : Windows requis (_getch).\n");
#endif
}
