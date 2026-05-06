#include <stdio.h>
#include <time.h>
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

#define MOBS_N 4

static void mobs_show(int selected, Observation *o, const char *dateStr) {
    menu_nav_clear();
    printf(RED "+======================================+\n" RESET);
    printf(RED "|      MENU : MODIFIER OBSERVATION     |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN " %s %s | Lit %d | Traitement : %s | Fin : %s\n" RESET,
           o->patient->nom, o->patient->prenom, o->lit, o->traitement, dateStr);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);

    printf(selected == 0 ? YELLOW "|  > Modifier le lit                   |\n" RESET
                         : CYAN   "|    Modifier le lit                   |\n" RESET);
    printf(selected == 1 ? YELLOW "|  > Modifier le traitement            |\n" RESET
                         : CYAN   "|    Modifier le traitement            |\n" RESET);
    printf(selected == 2 ? YELLOW "|  > Modifier duree observation        |\n" RESET
                         : CYAN   "|    Modifier duree observation        |\n" RESET);
    printf(selected == 3 ? YELLOW "|  > QUITTER                           |\n" RESET
                         : CYAN   "|    " RED "QUITTER" CYAN "                           |\n" RESET);

    printf(CYAN "|______________________________________|\n" RESET);
    printf(GREEN "Selection (fleches + Entree) > " RESET);
}

void menuModifierObservation(Observation *patientEnObservation, ListeLit *lit) {
    char buffer[30];

    if (patientEnObservation == NULL || patientEnObservation->patient == NULL) {
        menu_nav_clear();
        printf(RED "Erreur : observation ou patient invalide.\n" RESET);
        menu_nav_pause();
        return;
    }

    strftime(buffer, sizeof(buffer), "%d/%m/%Y",
             localtime(&patientEnObservation->finObservation));

#ifdef _WIN32
    int selected = 0;
    int key;
    int running = 1;

    while (running) {
        mobs_show(selected, patientEnObservation, buffer);
        key = _getch();

        if (key == MENU_NAV_ARROW_PREFIX) {
            key = _getch();
            if (key == MENU_NAV_KEY_UP)
                selected = (selected + MOBS_N - 1) % MOBS_N;
            else if (key == MENU_NAV_KEY_DOWN)
                selected = (selected + 1) % MOBS_N;

        } else if (key == MENU_NAV_KEY_ENTER) {
            switch (selected) {
            case 0: {
                int numlit;
                printf("Numero du nouveau lit : ");
                scanf("%d", &numlit);
                if (numlit < 1 || numlit > lit->total) {
                    printf(RED "Lit invalide.\n" RESET);
                } else if (lit->Tlit[numlit-1].etat == OCCUPE) {
                    printf(RED "Lit deja occupe.\n" RESET);
                } else {
                    lit->Tlit[patientEnObservation->lit-1].etat    = NOCCUPE;
                    lit->Tlit[patientEnObservation->lit-1].patient = NULL;
                    patientEnObservation->lit = numlit;
                    lit->Tlit[numlit-1].etat    = OCCUPE;
                    lit->Tlit[numlit-1].patient = patientEnObservation->patient;
                    sauvegarderObservations(patientEnObservation);
                    printf(GREEN "Lit modifie.\n" RESET);
                }
                menu_nav_pause();
                break;
            }
            case 1:
                printf("Nouveau traitement : ");
                scanf(" %[^\n]", patientEnObservation->traitement);
                sauvegarderObservations(patientEnObservation);
                menu_nav_pause();
                break;
            case 2: {
                int duree;
                printf("Ajouter/retirer des jours (ex: 2 ou -1) : ");
                scanf("%d", &duree);
                patientEnObservation->finObservation += (time_t)(duree * 24 * 60 * 60);
                strftime(buffer, sizeof(buffer), "%d/%m/%Y",
                         localtime(&patientEnObservation->finObservation));
                printf(GREEN "Nouvelle date de fin : %s\n" RESET, buffer);
                sauvegarderObservations(patientEnObservation);
                menu_nav_pause();
                break;
            }
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
    printf("Menu modifier observation interactif : Windows requis (_getch).\n");
#endif
}
