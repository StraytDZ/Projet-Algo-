#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "urgence.h"
#include "structure.h"
#include "reception.h"
#include "menu.h"

ListeUrgence *AddUrgence(ListeUrgence *ListeU, ListeTicket *ListeT)
{
    Patient *patientEnUrgence = (Patient *)malloc(sizeof(Patient));
    patientEnUrgence->etat = URGENCE;
    ListeT->compteur++;
    Ticket *nouveauTicket = CreateTicket(patientEnUrgence, ListeT->compteur);
    if (ListeT->tete == NULL)
    {
        ListeT->tete = nouveauTicket;
    }
    else
    {
        Ticket *courant = ListeT->tete;
        while (courant->suivant != NULL)
        {
            courant = courant->suivant;
        }
        courant->suivant = nouveauTicket;
    }
    int Age;
    char Sexe[4];
    patientEnUrgence->ticket = nouveauTicket;
    printf("Nom : ");
    scanf(" %[^\n]", patientEnUrgence->nom);
    printf("Prenom : ");
    scanf(" %[^\n]", patientEnUrgence->prenom);
    printf("ID : ");
    scanf(" %[^\n]", patientEnUrgence->id);
    do
    {
        printf("\tAge : ");
        Age = saisirChoix();
        if (Age <= 0 || Age > 150)
            printf(RED "\tAge invalide ! (1-150)\n" RESET);
    } while (Age <= 0 || Age > 150);
    do
    {
        printf("\tSexe (H/F) : ");
        scanf("%s", Sexe);
        while (getchar() != '\n')
            ;
        if (strcmp(Sexe, "H") != 0 && strcmp(Sexe, "F") != 0)
            printf(RED "\tSexe invalide ! (H ou F)\n" RESET);
    } while (strcmp(Sexe, "H") != 0 && strcmp(Sexe, "F") != 0);
    strcpy(patientEnUrgence->departement, "");
    strcpy(patientEnUrgence->diagnostique, "");
    strcpy(patientEnUrgence->ordonnance, "");
    strcpy(patientEnUrgence->sexe, Sexe);
    patientEnUrgence->age = Age;
    patientEnUrgence->heure.arrive = time(NULL);
    patientEnUrgence->suivant = NULL;

    Urgence *noeud = malloc(sizeof(Urgence));
    noeud->patient = patientEnUrgence;
    noeud->suivant = NULL;

    if (ListeU->tete == NULL)
        ListeU->tete = noeud;
    else
    {
        Urgence *courant = ListeU->tete;
        while (courant->suivant != NULL)
            courant = courant->suivant;
        courant->suivant = noeud;
    }
    ListeU->total++;
    ListeU->attente++;

    return ListeU;
}

void afficherUrgence(ListeUrgence *ListeU)
{
    if (ListeU->tete == NULL)
    {
        printf("Aucun patient en urgence.\n");
        return;
    }
    int i = 1;
    Urgence *courant = ListeU->tete;
    while (courant != NULL)
    {
        char buffer[20];
        strftime(buffer, 20, "%H:%M:%S", localtime(&courant->patient->heure.arrive));
        printf("[%d] - %s  %s | %d Ans | %s | %s | Ticket  %d | Debut d'attente : %s\n", i, courant->patient->nom, courant->patient->prenom, courant->patient->age, courant->patient->sexe, courant->patient->id, courant->patient->ticket->numero, buffer);
        i++;
        courant = courant->suivant;
    }
}