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