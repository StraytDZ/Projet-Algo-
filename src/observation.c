#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "observation.h"
#include "structure.h"
#include "menu.h"
#include "fichier.h"
#include "reception.h"
#include "admin.h"

int AddLit(Patient *patientEnonsultation, ListeLit *ListeL)
{ // Fonciton juste pour cree le ' noeud ', ici on ne l'ajoute pas encore vers notre 'lsite de noeud' (ListeLit)
    if (ListeL->indispo >= ListeL->total)
    { // Si on depasse le nombre de lit disponible dans l'hopitale, tel que ListeL->total est donner dans le main,
        printf("Erreur : plus de lit disponible !\n");
        return -1;
    }
    Lit lit;
    lit.num = ListeL->indispo + 1; // on inisitalise ici nos informations sur le lit
    lit.etat = OCCUPE;
    lit.patient = patientEnonsultation;
    ListeL->Tlit[ListeL->indispo] = lit;
    int index = ListeL->indispo;
    ListeL->indispo++;
    return ListeL->Tlit[index].num;
}

void AddObservation(Patient *patientEnConsultation, ListeObservation *ListeO, ListeLit *ListeL, ListeTicket *ListeT, ListePatient *ListeP, ListeMedicament *ListeMedicament, ListeEquipement *ListeEquipement)
{
    if (strcmp(patientEnConsultation->diagnostique, "") == 0)
    {
        printf("Veuilelz d'abord saisir un diagnostique.\n");
        return;
    }
    Observation *patientOB = (Observation *)malloc(sizeof(Observation));
    if (patientOB == NULL)
    {
        printf("Erreur : Impossible d'enregister une observation.\n");
        return;
    }
    int duree;
    patientOB->nbMedicaments = 0;
    memset(patientOB->medicamentsUtilises, 0, sizeof(patientOB->medicamentsUtilises));
    printf("Duree de l'oservations (Jours):");
    duree = saisirChoix();
    patientOB->debutObservation = time(NULL);                                         // initialiser d'abord
    patientOB->finObservation = patientOB->debutObservation + (duree * 24 * 60 * 60); // on ajoute par rapport a la date deja donnée
    char buffer[20];
    strftime(buffer, 20, "%d/%m/%Y", localtime(&patientOB->finObservation));
    printf("Date de fin : %s\n", buffer);
    printf("Veuillez indiquer le traitement a suivre : ");
    scanf(" %[^\n]", patientOB->traitement);
    char nomMed[30] = "";
    int choix;
    printf("Voulez vous lui donner un medicament ? (1 - oui / 0 - non) : ");
    scanf("%d", &choix);
    while (getchar() != '\n')
        ;
    if (choix == 1)
    {
        utilisermedicament(ListeMedicament, nomMed);
        if (strcmp(nomMed, "") != 0)
        { // si un médicament a bien été trouvé
            if (patientOB->nbMedicaments < 10)
            {
                strcpy(patientOB->medicamentsUtilises[patientOB->nbMedicaments], nomMed);
                patientOB->nbMedicaments++;
            }
            else
            {
                printf("Maximum de medicaments atteint pour ce patient.\n");
            }
        }
    }
    char nomequip[30] = "";
    printf("voulez vous lui donnez un equipement ? (1 - oui / 0 - non) : ");
    scanf("%d", &choix);
    int i = 0;
    do
    {
        if (choix == 1)
        {
            utiliserequipement(ListeEquipement, nomequip);
            for (int j = 0; j < ListeEquipement->total; j++)
            {
                if (strcmp(ListeEquipement->equipements[j].nom, nomequip) == 0)
                {
                    patientOB->equipements[i] = &ListeEquipement->equipements[j];
                }
            }
            printf("voullez vous saisir un autre equipement ? (1 - oui / 0 - non) : ");
            scanf("%d", &choix);
            i++;
        }
    } while (choix == 1);

    while (getchar() != '\n')
        ;
    int numLit = AddLit(patientEnConsultation, ListeL);
    if (numLit == -1)
    {
        printf("Hopital complet !\n");
        free(patientOB);
        return;
    }
    patientOB->lit = numLit;
    patientOB->patient = patientEnConsultation;
    patientOB->index = patientEnConsultation->index;
    patientEnConsultation->etat = OBSERVATION;
    printf("Le patient est transeferer au lit %d.", patientOB->lit);
    sauvegarderLit(ListeL);

    if (patientEnConsultation->ticket != NULL)
    {

        if (ListeT->tete != NULL && patientEnConsultation->ticket == ListeT->tete)
        {
            ListeT->tete = ListeT->tete->suivant;
            free(patientEnConsultation->ticket);
            patientEnConsultation->ticket = NULL;
        }
        else if (ListeT->tete != NULL)
        {
            Ticket *courant = ListeT->tete;
            Ticket *precedent = NULL;

            while (courant != NULL && courant != patientEnConsultation->ticket)
            {
                precedent = courant;
                courant = courant->suivant;
            }

            if (courant != NULL)
            {
                precedent->suivant = courant->suivant;
                free(courant);
            }
            patientEnConsultation->ticket = NULL;
        }
    }
    patientOB->suivant = NULL;
            if(ListeO->tete == NULL)
        ListeO->tete = patientOB;
    else {
    Observation *courant = ListeO->tete;
    while(courant->suivant != NULL) courant = courant->suivant;
    courant->suivant = patientOB;
    ListeO->compteur++;
    ListeP->observation++;
    ListeP->attente--;
}
}

void afficherObservation(ListeObservation *ListeO)
{
    Observation *tete = ListeO->tete;
    if (tete == NULL)
    {
        printf("Aucun patient en observation.\n");
        return;
    }
    printf("Patients en observation :\n");
    while (tete != NULL)
    {
        printf("Lit %d : %s %s\n", tete->lit, tete->patient->nom, tete->patient->prenom);
        tete = tete->suivant;
    }
}

void SupprimerObservation(ListeObservation *ListeO, ListeLit *ListeL)
{
    if (ListeO->tete == NULL)
    {
        printf("Aucun patient en observation.\n");
        return;
    }
    AfficherListeObservation(ListeO);
    int numlit = -1;
    printf("Numero du lit a liberer : ");
    numlit = saisirChoix();
    if (numlit == -1 || numlit <= 0 || numlit > ListeL->total)
    {
        do
        {
            printf(RED " Numero invalide.\n" RESET);
            printf("Numero du lit a liberer : ");
            numlit = saisirChoix();
        } while (numlit < 0 || numlit > ListeL->total || numlit == -1);
    }

    Observation *courant = ListeO->tete;
    Observation *precedent = NULL;

    while (courant != NULL && courant->lit != numlit)
    {
        precedent = courant;
        courant = courant->suivant;
    }
    if (courant == NULL)
    {
        printf("Observation introuvable.\n");
        return;
    }
    courant->patient->etat = SORTI;
    courant->patient->heure.sorti = time(NULL);
    ListeL->Tlit[numlit - 1].etat = NOCCUPE;
    ListeL->Tlit[numlit - 1].patient = NULL;
    ListeL->indispo--;
    sauvegarderLit(ListeL);
    sauvegarderObservations(courant);
    if (precedent == NULL)
        ListeO->tete = courant->suivant;
    else
        precedent->suivant = courant->suivant;

    free(courant);
    ListeO->compteur--;
}

void AfficherListeObservation(ListeObservation *ListeO)
{
    if (ListeO->tete == NULL)
    {
        printf("Aucun patient en observations.\n");
        return;
    }
    int i = 1;
    Observation *courant = ListeO->tete;
    while (courant != NULL)
    {
        char buffer[20];
        strftime(buffer, 20, "%d/%m/%Y", localtime(&courant->finObservation));
        printf("[%d] - %s  %s | %d Ans | %s | %s | Lit  %d | Traitement : %s | Sortie : %s\n", i, courant->patient->nom, courant->patient->prenom, courant->patient->age, courant->patient->sexe, courant->patient->id, courant->lit, courant->traitement, buffer);
        i++;
        courant = courant->suivant;
    }
}

void ModifierObservation(ListeObservation *ListeO, ListeLit *ListeL, ListeMedicament *ListeMedicament)
{
    if (ListeO->tete == NULL)
    {
        printf("Aucun patient en observation.\n");
        return;
    }
    AfficherListeObservation(ListeO);
    printf("----");
    int choix, index;
    int i = 1;
    do
    {
        printf("-Choix : ");
        index = saisirChoix();
        if (index < 0 || index > ListeO->compteur)
            printf("Erreur : Numero invalide ! Reessayez.\n");

    } while (index < 0 || index > ListeO->compteur);
    Observation *courant = ListeO->tete;
    while (i < index)
    {
        courant = courant->suivant;
        i++;
    }
    Observation *patientCible = courant;
    do
    {
        menuModifierObservation(courant);
        choix = saisirChoix();
        switch (choix)
        {
        case 1:
        {
            int numlit;
            printf("Donner le numero du nouveau lit : ");
            scanf("%d", &numlit);
            if (numlit < 1 || numlit > ListeL->total)
            {
                printf("Erreur : lit invalide.\n");
                pause();
                break;
            }
            if (ListeL->Tlit[numlit - 1].etat == OCCUPE)
            {
                printf("Erreur : lit %d deja occupe.\n", numlit);
                pause();
                break;
            }
            ListeL->Tlit[patientCible->lit - 1].etat = NOCCUPE;
            ListeL->Tlit[patientCible->lit - 1].patient = NULL;
            patientCible->lit = numlit;
            ListeL->Tlit[numlit - 1].etat = OCCUPE;
            ListeL->Tlit[numlit - 1].patient = patientCible->patient;
            sauvegarderObservations(patientCible);
            break;
        }
        case 2:
        {
            printf("Donner le nouveau traitement a suivre : ");
            scanf(" %[^\n]", patientCible->traitement);
            sauvegarderObservations(patientCible);
            break;
        }
        case 3:
        {
            int duree;
            printf("Ajouter une retier des jours (Exemple : 2 ou -1) :");
            scanf("%d", &duree);

            patientCible->finObservation = patientCible->finObservation + (duree * 24 * 60 * 60); // on ajoute ou reduire par rapport a la date deja donnée
            char buffer[20];
            strftime(buffer, 20, "%d/%m/%Y", localtime(&patientCible->finObservation));
            printf("Nouvelle date de fin : %s\n", buffer);
            sauvegarderObservations(patientCible);
            pause();
            break;
        }
        case 4:
        {
            int reponse;
            printf("voulez vous lui donnez un medicament ? (1 - oui / 0 - non) : ");
            scanf("%d", &reponse);
            while (reponse == 1)
            {

                char nomMed[30] = "";
                utilisermedicament(ListeMedicament, nomMed);
                if (strcmp(nomMed, "") != 0)
                { // si un médicament a bien été trouvé
                    if (patientCible->nbMedicaments < 10)
                    {
                        strcpy(patientCible->medicamentsUtilises[patientCible->nbMedicaments], nomMed);
                        patientCible->nbMedicaments++;
                    }
                    else
                    {
                        printf("Maximum de medicaments atteint pour ce patient.\n");
                    }
                }
                printf("voulez vous lui donnez un autre medicament ? (1 - oui / 0 - non) : ");
                scanf("%d", &reponse);
            }
            sauvegarderObservations(patientCible);
            break;
        }
        }
    } while (choix != 5);
}
void RechercheObservation(ListeObservation *ListeO)
{
    if (ListeO->tete == NULL)
    {
        printf("Aucun patient en observation.\n");
        return;
    }
    int choix;
    do
    {
        printf("Rechercher par : \n");
        printf("\t 1 - ID\n");
        printf("\t 2 - Nom et Prenom\n");
        printf("\t 3 - Quitter\n");
        choix = saisirChoix();
        switch (choix)
        {
        case 1:
        {
            char IDcible[20];
            printf("ID :");
            scanf("%s", IDcible);
            while (getchar() != '\n')
                ;
            int trouve = 0;
            Observation *courant = ListeO->tete;
            while (courant != NULL)
            {
                if (strcmp(courant->patient->id, IDcible) == 0)
                {
                    char buffer[30];
                    strftime(buffer, 30, "%d/%m/%Y", localtime(&courant->finObservation));
                    printf("%s  %s | %d Ans | %s | %s | Lit  %d | Traitement : %s | Sortie : %s\n", courant->patient->nom, courant->patient->prenom, courant->patient->age, courant->patient->sexe, courant->patient->id, courant->lit, courant->traitement, buffer);
                    trouve = 1;
                }
                courant = courant->suivant;
            }
            if (trouve == 0)
                printf("Patient introuvable.\n");
            break;
        }
        case 2:
        {
            char nomCible[30], prenomCible[30];
            printf("Nom :");
            scanf(" %[^\n]", nomCible);
            printf("Prenom :");
            scanf(" %[^\n]", prenomCible);
            while (getchar() != '\n')
                ;
            int trouve = 0;
            Observation *courant = ListeO->tete;
            while (courant != NULL)
            {
                if ((strcmp(courant->patient->nom, nomCible) == 0) && (strcmp(courant->patient->prenom, prenomCible) == 0))
                {
                    char buffer[20];
                    strftime(buffer, 20, "%d/%m/%Y", localtime(&courant->finObservation));
                    printf("%s  %s | %d Ans | %s | %s | Lit  %d | Traitement : %s | Sortie : %s\n", courant->patient->nom, courant->patient->prenom, courant->patient->age, courant->patient->sexe, courant->patient->id, courant->lit, courant->traitement, buffer);
                    trouve = 1;
                }
                courant = courant->suivant;
            }
            if (trouve == 0)
                printf("Patient introuvable.\n");
            break;
        }
        }
    } while (choix != 3);
}

void verifierFinObservations(ListeObservation *ListeO, ListeLit *ListeL, ListePatient *ListeP)
{
    time_t maintenant = time(NULL);
    Observation *courant = ListeO->tete;
    Observation *precedent = NULL;

    while (courant != NULL)
    {
        if (maintenant >= courant->finObservation)
        {
            printf("Observation terminee : %s %s (Lit %d) peut sortir.\n",
                   courant->patient->nom, courant->patient->prenom, courant->lit);

            courant->patient->etat = SORTI;
            courant->patient->heure.sorti = time(NULL);
            ListeP->sortis++;
            ListeP->observation--;

            ListeL->Tlit[courant->lit - 1].etat = NOCCUPE;
            ListeL->Tlit[courant->lit - 1].patient = NULL;
            ListeL->indispo--;

            sauvegarderPatients(courant->patient);

            Observation *aSupprimer = courant;
            if (precedent == NULL)
                ListeO->tete = courant->suivant;
            else
                precedent->suivant = courant->suivant;

            courant = courant->suivant;
            free(aSupprimer);
            ListeO->compteur--;
        }
        else
        {
            precedent = courant;
            courant = courant->suivant;
        }
    }
}