#include <stdio.h>
#include "structure.h"

void menuPrincipal() {
    printf("\t ++++URGENCE+++++\n");
    printf("\t=+=+=+=MENU=+=+=+=\n");
    printf("=======================================\n\n");
    printf("\t 1 - Medecin\n");
    printf("\t 2 - Reception\n");
    printf("\t 3 - Quitter\n\n");
    printf("=======================================\n");
    printf("                          Choix : ");
}
void menuMedecin() {
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

void menuReception() {
    printf("\n=======================================\n");
    printf("\t=+=+=+=MENU=+=+=+=\n");
    printf("\t*+*+*RECEPTION*+*+*\n");
    printf("=======================================\n\n");
    printf("\t 1 - Enregister un patient\n");
    printf("\t 2 - Afficher la liste d'attente\n");
    printf("\t 3 - Quitter\n\n");
    printf("=======================================\n");
    printf("                          Choix : ");
}

void menuConsultation(Patient *patientEnConsult) {
    printf("\n=======================================\n");
    printf("\tPatient %d : %s %s | %d | %s | %s \n",patientEnConsult->ticket->numero, patientEnConsult->nom,patientEnConsult->prenom, patientEnConsult->age,patientEnConsult->sexe,patientEnConsult->id);
    printf("=======================================\n\n");
    printf("\t 1 - Enregistrer le diagnostic\n");
    printf("\t 2 - Saisir le traitement\n");
    printf("\t 3 - Inscrire une ordonnance\n");
    printf("\t 4 - Mettre en observation\n");
    printf("\t 5 - Transferer a un autre departement\n");
    printf("\t 6 - Quitter\n\n");
    printf("=======================================\n");
    printf("                          Choix : ");

}
