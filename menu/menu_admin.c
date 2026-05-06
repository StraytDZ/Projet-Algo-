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

#define ADMIN_N 5

static void admin_show(int selected) {
    menu_nav_clear();
    printf(RED "+======================================+\n" RESET);
    printf(RED "|           MENU : ADMIN               |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);

    printf(selected == 0 ? YELLOW "|  > Gerer les equipements             |\n" RESET
                         : CYAN   "|    Gerer les equipements             |\n" RESET);
    printf(selected == 1 ? YELLOW "|  > Gerer les medicaments             |\n" RESET
                         : CYAN   "|    Gerer les medicaments             |\n" RESET);
    printf(selected == 2 ? YELLOW "|  > Gerer les lits                    |\n" RESET
                         : CYAN   "|    Gerer les lits                    |\n" RESET);
    printf(selected == 3 ? YELLOW "|  > Statistiques                      |\n" RESET
                         : CYAN   "|    Statistiques                      |\n" RESET);
    printf(selected == 4 ? YELLOW "|  > QUITTER                           |\n" RESET
                         : CYAN   "|    " RED "QUITTER" CYAN "                           |\n" RESET);

    printf(CYAN "|______________________________________|\n" RESET);
    printf(GREEN "Selection (fleches + Entree) > \n" RESET);
}

void menuAdmin(ListePatient *patients, ListeLit *lit,
               ListeUrgence *urgences, ListeMedicament *medicaments,
               ListeEquipement *equipements) {
#ifdef _WIN32
    int selected = 0;
    int key;
    int running = 1;
    Statistique stat;

    while (running) {
        admin_show(selected);
        key = _getch();

        if (key == MENU_NAV_ARROW_PREFIX) {
            key = _getch();
            if (key == MENU_NAV_KEY_UP)
                selected = (selected + ADMIN_N - 1) % ADMIN_N;
            else if (key == MENU_NAV_KEY_DOWN)
                selected = (selected + 1) % ADMIN_N;

        } else if (key == MENU_NAV_KEY_ENTER) {
            switch (selected) {
            case 0:
                menuEquipement(equipements);
                break;
            case 1:
                menuMedicament(medicaments);
                break;
            case 2:
                gererlit(lit);
                menu_nav_pause();
                break;
            case 3:
                afficherstatistique(patients, lit, urgences, &stat);
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
    printf("Menu admin interactif : Windows requis (_getch).\n");
#endif
}
