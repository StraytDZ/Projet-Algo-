#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#endif

#include "menu.h"
#include "menu_nav.h"
#include "admin.h"

#define RED    "\033[91m"
#define CYAN   "\033[96m"
#define GREEN  "\033[92m"
#define YELLOW "\033[93m"
#define RESET  "\033[0m"

#define MED_N 4

static void med_show(int selected) {
    menu_nav_clear();
    printf(RED "+======================================+\n" RESET);
    printf(RED "|         MENU : MEDICAMENTS           |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);

    printf(selected == 0 ? YELLOW "|  > Ajouter un medicament             |\n" RESET
                         : CYAN   "|    Ajouter un medicament             |\n" RESET);
    printf(selected == 1 ? YELLOW "|  > Ajouter quantite                  |\n" RESET
                         : CYAN   "|    Ajouter quantite                  |\n" RESET);
    printf(selected == 2 ? YELLOW "|  > Afficher le stock                 |\n" RESET
                         : CYAN   "|    Afficher le stock                 |\n" RESET);
    printf(selected == 3 ? YELLOW "|  > QUITTER                           |\n" RESET
                         : CYAN   "|    " RED "QUITTER" CYAN "                           |\n" RESET);

    printf(CYAN "|______________________________________|\n" RESET);
    printf(GREEN "Selection (fleches + Entree) > \n" RESET);
}

void menuMedicament(ListeMedicament *medicaments) {
#ifdef _WIN32
    int selected = 0;
    int key;
    int running = 1;

    while (running) {
        med_show(selected);
        key = _getch();

        if (key == MENU_NAV_ARROW_PREFIX) {
            key = _getch();
            if (key == MENU_NAV_KEY_UP)
                selected = (selected + MED_N - 1) % MED_N;
            else if (key == MENU_NAV_KEY_DOWN)
                selected = (selected + 1) % MED_N;

        } else if (key == MENU_NAV_KEY_ENTER) {
            switch (selected) {
            case 0:
                saisirmedicament(medicaments, "data/medicaments.txt");
                menu_nav_pause();
                break;
            case 1:
                ajoutermedicament(medicaments, "data/medicaments.txt");
                menu_nav_pause();
                break;
            case 2:
                afficherstock(medicaments);
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
    printf("Menu medicament interactif : Windows requis.\n");
#endif
}
