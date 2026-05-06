#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <conio.h>
#endif

#include "menu_nav.h"

void menu_nav_clear(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void menu_nav_pause(void) {
#ifdef _WIN32
    printf("\n\033[96mAppuyez sur une touche pour continuer... \033[0m");
    (void)_getch();
#else
    printf("\nAppuyez sur Entree pour continuer... ");
    (void)getchar();
#endif
}
