#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "structure.h"

void pause() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    printf(CYAN "\nAppuyez sur Entree pour continuer..." RESET);
}

int saisirChoix() { // Au cas ou l'utilisateurs donne un choix invalide, comme les caractere qui font out bug quand ils sont donner comme choix
    char buffer[20];
    int choix;
    char *end;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        return -1;

    choix = (int)strtol(buffer, &end, 10);

    if (end == buffer || (*end != '\n' && *end != '\0'))
        return -1;

    return choix;
}

void menuPrincipal() {
    system("cls");
    printf(RED "+======================================+\n" RESET);
    printf(RED "|         SYSTEME D'URGENCES           |\n" RESET);
    printf(RED "|           MENU PRINCIPAL             |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(CYAN "|           " YELLOW "1" CYAN " - Medecin                |\n" RESET);
    printf(CYAN "|           " YELLOW "2" CYAN " - Reception              |\n" RESET);
    printf(CYAN "|           " YELLOW "3" CYAN " - Admin                  |\n" RESET);
    printf(CYAN "|           " RED    "4" CYAN " - Quitter                |\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(GREEN "                       Choix : " RESET);
}

void menuMedecin() {
    system("cls");
    printf(RED "+======================================+\n" RESET);
    printf(RED "|           MENU : MEDECIN             |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(CYAN "|  " YELLOW "1" CYAN " - Appeler le patient suivant      |\n" RESET);
    printf(CYAN "|  " YELLOW "2" CYAN " - Afficher la liste d'attente     |\n" RESET);
    printf(CYAN "|  " YELLOW "3" CYAN " - Observation                     |\n" RESET);
    printf(CYAN "|  " RED    "4" CYAN " - Quitter                         |\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(GREEN "                       Choix : " RESET);
}

void menuConsultation(Patient *p) {
    system("cls");
    printf(RED "+======================================+\n" RESET);
    printf(RED "|         MENU : CONSULTATION          |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "| Ticket %-3d : %s %-15s|\n" RESET, p->ticket->numero, p->nom, p->prenom);
    printf(CYAN "| %d ans | %s | %-24s|\n" RESET, p->age, p->sexe, p->id);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(CYAN "|  " YELLOW "1" CYAN " - Enregistrer le diagnostic      |\n" RESET);
    printf(CYAN "|  " YELLOW "2" CYAN " - Inscrire une ordonnance        |\n" RESET);
    printf(CYAN "|  " YELLOW "3" CYAN " - Mettre en observation          |\n" RESET);
    printf(CYAN "|  " YELLOW "4" CYAN " - Transferer a un autre dpt      |\n" RESET);
    printf(CYAN "|  " RED    "5" CYAN " - Quitter                        |\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(GREEN "                       Choix : " RESET);
}

void menuObservation() {
    system("cls");
    printf(RED "+======================================+\n" RESET);
    printf(RED "|         MENU : OBSERVATION           |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(CYAN "|  " YELLOW "1" CYAN " - Modifier une observation        |\n" RESET);
    printf(CYAN "|  " YELLOW "2" CYAN " - Afficher la liste d'observation |\n" RESET);
    printf(CYAN "|  " YELLOW "3" CYAN " - Rechercher un patient           |\n" RESET); 
    printf(CYAN "|  " YELLOW "4" CYAN " - Liberer un patient              |\n" RESET);
    printf(CYAN "|  " RED    "5" CYAN " - Quitter                         |\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(GREEN "                       Choix : " RESET);
}

void menuModifierObservation(Observation *o) {
    char buffer[30];
    strftime(buffer, 30, "%d/%m/%Y", localtime(&o->finObservation));
    system("cls");
    printf(RED "+======================================+\n" RESET);
    printf(RED "|      MENU : MODIFIER OBSERVATION     |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "| Patient  : %-26s|\n" RESET, o->patient->nom); 
    printf(CYAN "| Lit      : %-26d|\n" RESET, o->lit);
    printf(CYAN "| Traitement : %-24s|\n" RESET, o->traitement);
    printf(CYAN "| Fin observation  : %-26s|\n" RESET, buffer);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(CYAN "|  " YELLOW "1" CYAN " - Modifier le lit                 |\n" RESET);
    printf(CYAN "|  " YELLOW "2" CYAN " - Modifier le traitement          |\n" RESET);
    printf(CYAN "|  " YELLOW "3" CYAN " - Modifier la duree               |\n" RESET);
    printf(CYAN "|  " RED    "4" CYAN " - Quitter                         |\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(GREEN "                       Choix : " RESET);
}

void menuReception() {
    system("cls");
    printf(RED "+======================================+\n" RESET);
    printf(RED "|          MENU : RECEPTION            |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(CYAN "|  " YELLOW "1" CYAN " - Enregistrer un patient          |\n" RESET);
    printf(CYAN "|  " YELLOW "2" CYAN " - Enregistrer une urgence         |\n" RESET);
    printf(CYAN "|  " YELLOW "3" CYAN " - Afficher la liste d'attente     |\n" RESET);
    printf(CYAN "|  " YELLOW "4" CYAN " - Afficher l'historique           |\n" RESET);
    printf(CYAN "|  " RED    "5" CYAN " - Quitter                         |\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(GREEN "                       Choix : " RESET);
}

void menuUrgence() {
    system("cls");
    printf(RED "+======================================+\n" RESET);
    printf(RED "|           MENU : URGENCE             |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(CYAN "|  " YELLOW "1" CYAN " - Enregistrer une urgence         |\n" RESET);
    printf(CYAN "|  " YELLOW "2" CYAN " - Afficher la liste d'urgences    |\n" RESET);
    printf(CYAN "|  " RED    "3" CYAN " - Quitter                         |\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(GREEN "                       Choix : " RESET);
}

void menuAdmin() {
    system("cls");
    printf(RED "+======================================+\n" RESET);
    printf(RED "|           MENU : ADMIN               |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(CYAN "|  " YELLOW "1" CYAN " - Gerer les equipements           |\n" RESET);
    printf(CYAN "|  " YELLOW "2" CYAN " - Gerer les medicaments           |\n" RESET);
    printf(CYAN "|  " YELLOW "3" CYAN " - Gerer les lits                  |\n" RESET);
    printf(CYAN "|  " YELLOW "4" CYAN " - Statistiques                    |\n" RESET);
    printf(CYAN "|  " RED    "5" CYAN " - Quitter                         |\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(GREEN "                       Choix : " RESET);
}

void menuequipement() {
    system("cls");
    printf(RED "+======================================+\n" RESET);
    printf(RED "|          MENU : EQUIPEMENTS          |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(CYAN "|  " YELLOW "1" CYAN " - Ajouter un equipement           |\n" RESET);
    printf(CYAN "|  " YELLOW "2" CYAN " - Ajouter quantite equipement     |\n" RESET);
    printf(CYAN "|  " YELLOW "3" CYAN " - Afficher stock equipements      |\n" RESET);
    printf(CYAN "|  " RED    "4" CYAN " - Quitter                         |\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(GREEN "                       Choix : " RESET);
}

void menumedicament() {
    system("cls");
    printf(RED "+======================================+\n" RESET);
    printf(RED "|          MENU : MEDICAMENTS          |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(CYAN "|  " YELLOW "1" CYAN " - Ajouter un medicament           |\n" RESET);
    printf(CYAN "|  " YELLOW "2" CYAN " - Ajouter quantite medicament     |\n" RESET);
    printf(CYAN "|  " YELLOW "3" CYAN " - Afficher stock medicaments      |\n" RESET);
    printf(CYAN "|  " RED    "4" CYAN " - Quitter                         |\n" RESET);
    printf(CYAN "|                                      |\n" RESET);
    printf(RED "+======================================+\n" RESET);
    printf(GREEN "                       Choix : " RESET);
}