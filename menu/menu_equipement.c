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
#include "admin.h"

#define RED    "\033[91m"
#define CYAN   "\033[96m"
#define GREEN  "\033[92m"
#define YELLOW "\033[93m"
#define RESET  "\033[0m"

#define EQ_N 4

static void eq_show(int selected) {
    menu_nav_clear();
    printf(RED "+======================================+\n" RESET);
    printf(RED "|         MENU : EQUIPEMENTS           |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);

    printf(selected == 0 ? YELLOW "|  > Nouvel equipement                 |\n" RESET
                         : CYAN   "|    Nouvel equipement                 |\n" RESET);
    printf(selected == 1 ? YELLOW "|  > Reapprovisionner stock            |\n" RESET
                         : CYAN   "|   Reapprovisionner stock            |\n" RESET);
    printf(selected == 2 ? YELLOW "|  > Afficher le stock                 |\n" RESET
                         : CYAN   "|    Afficher le stock                 |\n" RESET);
    printf(selected == 3 ? YELLOW "|  > QUITTER                           |\n" RESET
                         : CYAN   "|    " RED "QUITTER" CYAN "                           |\n" RESET);

    printf(CYAN "|______________________________________|\n" RESET);
    printf(GREEN "Selection (fleches + Entree) > \n" RESET);
}

void menuEquipement(ListeEquipement *equipements) {
#ifdef _WIN32
    int selected = 0;
    int key;
    int running = 1;

    while (running) {
        eq_show(selected);
        key = _getch();

        if (key == MENU_NAV_ARROW_PREFIX) {
            key = _getch();
            if (key == MENU_NAV_KEY_UP)
                selected = (selected + EQ_N - 1) % EQ_N;
            else if (key == MENU_NAV_KEY_DOWN)
                selected = (selected + 1) % EQ_N;

        } else if (key == MENU_NAV_KEY_ENTER) {
            switch (selected) {
            case 0:
                saisirequipement(equipements, "data/equipements.txt");
                menu_nav_pause();
                break;
            case 1:
                ajouterequipement(equipements, "data/equipements.txt");
                menu_nav_pause();
                break;
            case 2:
                afficherstockequipement(equipements);
                menu_nav_pause();
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
    printf("Menu equipement interactif : Windows requis.\n");
#endif
}