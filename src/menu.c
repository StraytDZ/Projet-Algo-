#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

#include "structure.h"

void pause() {
    printf("\nAppuyez sur Entree pour continuer...");
    while(getchar() != '\n');
}

void menuPrincipal() {
    pause();
    system("cls");
    printf("\t ++++URGENCE+++++\n");
    printf("\t=+=+=+=MENU=+=+=+=\n");
    printf("=======================================\n\n");
    printf("\t 1 - Medecin\n");
    printf("\t 2 - Reception\n");
    printf("\t 3 - Admin\n");
    printf("\t 4 - Quitter\n\n");
    printf("=======================================\n");
    printf("                          Choix : ");
}
void menuMedecin() {
    pause();
    system("cls");
    printf("\n=======================================\n");
    printf("\t=+=+=+=MENU=+=+=+=\n");
    printf("\t*+*+*MEDECIN*+*+*\n");
    printf("=======================================\n\n");
    printf("\t 1 - Appeler le patient suivant\n");
    printf("\t 2 - Afficher la liste d'attente\n");
    printf("\t 3 - Observation\n");
    printf("\t 4 - Quitter\n\n");
    printf("=======================================\n");
    printf("                          Choix : ");
}
void menuConsultation(Patient *patientEnConsult) {
    pause();
    system("cls");
    printf("\n=======================================\n");
    printf("\tPatient %d : %s %s | %d | %s | %s \n",patientEnConsult->ticket->numero, patientEnConsult->nom,patientEnConsult->prenom, patientEnConsult->age,patientEnConsult->sexe,patientEnConsult->id);
    printf("=======================================\n\n");
    printf("\t 1 - Enregistrer le diagnostic\n");
    printf("\t 2 - Inscrire une ordonnance\n");
    printf("\t 3 - Mettre en observation\n");
    printf("\t 4 - Transferer a un autre departement\n");
    printf("\t 5- Quitter\n\n");
    printf("=======================================\n");
    printf("                          Choix : ");
}
void menuObservation() {
    pause();
    system("cls");
    printf("\n=======================================\n");
    printf("\t=+=+=+=MENU=+=+=+=\n");
    printf("\t*+*+*OBSERVATION*+*+*\n");
    printf("=======================================\n\n");
    printf("\t 1 - Modifier une observation\n");
    printf("\t 2 - Afficher la liste d'observation\n");
    printf("\t 3 - Rechercher un patient\n");
    printf("\t 4 - Liberer un patient\n");
    printf("\t 5 - Quitter\n\n");
    printf("=======================================\n");
    printf("                          Choix : ");
}
void menuModifierObservation(Observation *patientEnObservation) {
    pause();
    char buffer[30];
    strftime(buffer, 30, "%d/%m/%Y", localtime(&patientEnObservation->finObservation));
    system("cls");
    printf("\n=======================================\n");
    printf("\t%s %s | Lit %d | Traitement : %s. | Fin Observation : %s\n", patientEnObservation->patient->nom, patientEnObservation->patient->prenom,patientEnObservation->lit,patientEnObservation->traitement,buffer);
    printf("=======================================\n\n");
    printf("\t 1 - Modifier le lit\n");
    printf("\t 2 - Modifier le traitement");
    printf("\t 3 - Modifier la durée de l'observation\n");
    printf("\t 4 - Quitter\n\n");
    printf("=======================================\n");
    printf("                          Choix : ");
}

void menuReception() {
    pause();
    system("cls");
    printf("\n=======================================\n");
    printf("\t=+=+=+=MENU=+=+=+=\n");
    printf("\t*+*+*RECEPTION*+*+*\n");
    printf("=======================================\n\n");
    printf("\t 1 - Enregister un patient\n");
    printf("\t 2 - Enregister une urgence\n");
    printf("\t 3 - Afficher la liste d'attente\n");
    printf("\t 4 - Afficher l'historique\n");    
    printf("\t 5 - Quitter\n\n");
    printf("=======================================\n");
    printf("                          Choix : ");
}

void menuUrgence() {
    pause();
    system("cls");
    printf("\n=======================================\n");
    printf("\t=+=+=+=MENU=+=+=+=\n");
    printf("\t*+*+*URGENEC*+*+*\n");
    printf("=======================================\n\n");
    printf("\t 1 - Enregister une urgence\n");
    printf("\t 2 - Afficher la liste d'urgenec\n"); 
    printf("\t 4 - Quitter\n\n");
    printf("=======================================\n");
    printf("                          Choix : ");
}

void menuAdmin() {
    pause();
    system("cls");
    printf("\n=======================================\n");
    printf("\t=+=+=+=MENU=+=+=+=\n");
    printf("\t*+*+*ADMIN*+*+*\n");
    printf("=======================================\n\n");
    printf("\t 1 - Gerer les equipements\n");
    printf("\t 2 - Gerer les medicaments\n");
    printf("\t 3 - Gerer les lits\n");
    printf("\t 4 - Statistiques\n");
    printf("\t 5 - Quitter\n\n");
    printf("=======================================\n");
    printf("                          Choix : ");
}


