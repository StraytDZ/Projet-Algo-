#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#endif

#include "menu.h"
#include "menu_nav.h"
#include "observation.h"
#include "fichier.h"

#define RED    "\033[91m"
#define CYAN   "\033[96m"
#define GREEN  "\033[92m"
#define YELLOW "\033[93m"
#define RESET  "\033[0m"

#define OBS_N 5

static void obs_show(int selected) {
    menu_nav_clear();
    printf(RED "+======================================+\n" RESET);
    printf(RED "|         MENU : OBSERVATION           |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);

    printf(selected == 0 ? YELLOW "|  > Modifier une observation          |\n" RESET
                         : CYAN   "|    Modifier une observation          |\n" RESET);
    printf(selected == 1 ? YELLOW "|  > Liste d'observation               |\n" RESET
                         : CYAN   "|    Liste d'observation               |\n" RESET);
    printf(selected == 2 ? YELLOW "|  > Rechercher un patient             |\n" RESET
                         : CYAN   "|    Rechercher un patient             |\n" RESET);
    printf(selected == 3 ? YELLOW "|  > Liberer un patient                |\n" RESET
                         : CYAN   "|    Liberer un patient                |\n" RESET);
    printf(selected == 4 ? YELLOW "|  > QUITTER                           |\n" RESET
                         : CYAN   "|    " RED "QUITTER" CYAN "                           |\n" RESET);

    printf(CYAN "|______________________________________|\n" RESET);
    printf(GREEN "Selection (fleches + Entree) > \n" RESET);
}

void menuObservation(ListeObservation *observations, ListeLit *lit,
                     ListePatient *patients) {
#ifdef _WIN32
    int selected = 0;
    int key;
    int running = 1;

    while (running) {
        obs_show(selected);
        key = _getch();

        if (key == MENU_NAV_ARROW_PREFIX) {
            key = _getch();
            if (key == MENU_NAV_KEY_UP)
                selected = (selected + OBS_N - 1) % OBS_N;
            else if (key == MENU_NAV_KEY_DOWN)
                selected = (selected + 1) % OBS_N;

        } else if (key == MENU_NAV_KEY_ENTER) {
            switch (selected) {
            case 0:
                ModifierObservation(observations, lit);
                menu_nav_pause();
                break;
            case 1:
                AfficherListeObservation(observations);
                menu_nav_pause();
                break;
            case 2:
                RechercheObservation(observations);
                menu_nav_pause();
                break;
            case 3:
                SupprimerObservation(observations, lit);
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
    printf("Menu observation interactif : Windows requis (_getch).\n");
#endif
}
