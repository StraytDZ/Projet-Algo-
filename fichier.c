#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fichier.h"
#include "reception.h"

/*
ad 3edregh s te9baylit rapide dayi 3eleghed tayi structure sans pointeur car on ne peut pas sauvegarder des pointeurs dans un fishier
on sauvegarde uniquement les donne brutes
 */
typedef struct {
    char nom[30];
    char prenom[30];
    int  age;
    char id[20];
    char sexe[4];
    int  numeroTicket;   /* On sauvegarde le NUMERO, pas le pointeur */
    Etat etat;
    Heure heure;
    char departement[30];
    char diagnostique[100];
    char traitement[100];
    char ordonnance[100];
    int  lit;
} PatientData;

    /*
    SAUVEGARDER PATIENTS
    - "wb" = write binary : ouvre en ecriture binaire
    - Parcourt la liste et ecrit chaque patient
     */
void sauvegarderPatients(ListePatient *liste) {
    FILE *f = fopen("patients.bin", "wb");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir patients.bin\n");
        return;
    }

    Patient *courant = liste->tete;//tban dayi acu 3elegh 
    while (courant != NULL) {
        PatientData data;  
        strcpy(data.nom,          courant->nom);
        strcpy(data.prenom,       courant->prenom);
        strcpy(data.id,           courant->id);
        strcpy(data.sexe,         courant->sexe);
        strcpy(data.departement,  courant->departement);
        strcpy(data.diagnostique, courant->diagnostique);
        strcpy(data.ordonnance,   courant->ordonnance);
        data.age          = courant->age;
        data.etat         = courant->etat;
        data.heure        = courant->heure;
        data.lit          = courant->lit;
        data.numeroTicket = courant->ticket->numero;

        fwrite(&data, sizeof(PatientData), 1, f);
        /*  suntaxe is fwrite(adresse, taille d'un element, nombre, fichier) */

        courant = courant->suivant;
    }

    fclose(f);
    printf("Patients sauvegarder dans patients.bin\n");
}

/* charger patients
   - "rb" = read binary : 
   - Relit chaque PatientData et recree le Patient en memoire
   - Recrée aussi le Ticket avec le bon numero
   */
void chargerPatients(ListePatient *liste, ListeTicket *listeT) {
    FILE *f = fopen("patients.bin", "rb");
    if (f == NULL)
        return; /* Premiere execution, fichier inexistant : normal */

    PatientData data;
    /* fread retourne le nombre d'elements lus.
       Quand il retourne 0, on est a la fin du fichier. */
    while (fread(&data, sizeof(PatientData), 1, f) == 1) {

        Patient *p = (Patient*)malloc(sizeof(Patient));
        if (p == NULL) { fclose(f); return; }

        strcpy(p->nom,          data.nom);
        strcpy(p->prenom,       data.prenom);
        strcpy(p->id,           data.id);
        strcpy(p->sexe,         data.sexe);
        strcpy(p->departement,  data.departement);
        strcpy(p->diagnostique, data.diagnostique);
        strcpy(p->ordonnance,   data.ordonnance);
        p->age     = data.age;
        p->etat    = data.etat;
        p->heure   = data.heure;
        p->lit     = data.lit;
        p->suivant = NULL;

        /* Recreer le ticket avec le bon numero */
        Ticket *t  = (Ticket*)malloc(sizeof(Ticket));
        if (t == NULL) { free(p); fclose(f); return; }
        t->numero  = data.numeroTicket;
        t->client  = p;
        t->suivant = NULL;
        p->ticket  = t;

        /* Mettre a jour le compteur pour que les prochains tickets
           continuent depuis le bon numero */
        if (data.numeroTicket > listeT->compteur)
            listeT->compteur = data.numeroTicket;

        /* Ajouter a la fin de la liste */
        if (liste->tete == NULL) {
            liste->tete = p;
        } else {
            Patient *tmp = liste->tete;
            while (tmp->suivant != NULL) tmp = tmp->suivant;
            tmp->suivant = p;
        }

        /* Mettre a jour les compteurs */
        liste->total++;
        if      (p->etat == ATTENTE)     liste->attente++;
        else if (p->etat == OBSERVATION) liste->observation++;
        else if (p->etat == SORTI)       liste->sortis++;
        else if (p->etat == TRANSFERER)  liste->transferes++;
    }

    fclose(f);
    printf("Donnees chargees depuis patients.bin\n");
}

/*
   SAUVEGARDER HISTORIQUE
   - "ab" = append binary : ajoute a la fin sans ecraser
   - Appeler quand un patient est SORTI ou TRANSFERE
    */
void sauvegarderHistorique(Patient *p) {
    FILE *f = fopen("historique.bin", "ab");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir historique.bin\n");
        return;
    }

    PatientData data;
    strcpy(data.nom,          p->nom);
    strcpy(data.prenom,       p->prenom);
    strcpy(data.id,           p->id);
    strcpy(data.sexe,         p->sexe);
    strcpy(data.departement,  p->departement);
    strcpy(data.diagnostique, p->diagnostique);
    strcpy(data.ordonnance,   p->ordonnance);
    data.age          = p->age;
    data.etat         = p->etat;
    data.heure        = p->heure;
    data.lit          = p->lit;
    data.numeroTicket = p->ticket->numero;

    fwrite(&data, sizeof(PatientData), 1, f);
    fclose(f);
}

/* 
   AFFICHER HISTORIQUE
   - Lit historique.bin et affiche tous les patients sortis
    */
void afficherHistorique() {
    FILE *f = fopen("historique.bin", "rb");
    if (f == NULL) {
        printf("Aucun historique disponible.\n");
        return;
    }

    PatientData data;
    int i = 1;
    printf("\n========== HISTORIQUE DES PATIENTS ==========\n");
    while (fread(&data, sizeof(PatientData), 1, f) == 1) {
        char *etatStr;
        if      (data.etat == SORTI)     etatStr = "SORTI";
        else if (data.etat == TRANSFERER) etatStr = "TRANSFERE";
        else                              etatStr = "AUTRE";

        /* Convertir time_t en date lisible */
        char heureArrive[30], heureSorti[30];
        strftime(heureArrive, 30, "%d/%m/%Y %H:%M", localtime(&data.heure.arrive));
        strftime(heureSorti,  30, "%d/%m/%Y %H:%M", localtime(&data.heure.sorti));

        printf("--- Patient %d ---\n", i++);
        printf("  Nom      : %s %s\n",      data.prenom, data.nom);
        printf("  ID       : %s | Age : %d | Sexe : %s\n", data.id, data.age, data.sexe);
        printf("  Ticket   : n°%d\n",       data.numeroTicket);
        printf("  Etat     : %s\n",          etatStr);
        printf("  Arrivee  : %s\n",          heureArrive);
        printf("  Depart   : %s\n",          heureSorti);
        if (strlen(data.diagnostique) > 0)
            printf("  Diagnostic  : %s\n",  data.diagnostique);
        if (strlen(data.ordonnance) > 0)
            printf("  Ordonnance  : %s\n",  data.ordonnance);
        if (strlen(data.departement) > 0)
            printf("  Departement : %s\n",  data.departement);
        printf("\n");
    }
    fclose(f);
}

/* ============================================================
   SAUVEGARDER OBSERVATIONS
   - Sauvegarde : numero de lit + ID du patient
   - On sauvegarde l'ID car c'est l'identifiant unique
     qui permet de retrouver le patient au chargement
   ============================================================ */
void sauvegarderObservations(ListeObservation *ListeO) {
    FILE *f = fopen("observations.bin", "wb");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir observations.bin\n");
        return;
    }
    Observation *courant = ListeO->tete;
    while (courant != NULL) {
        int  numlit = courant->lit->num;
        char idPatient[20];
        strcpy(idPatient, courant->patient->id);

        fwrite(&numlit,   sizeof(int),  1,  f);
        fwrite(idPatient, sizeof(char), 20, f);

        courant = courant->suivant;
    }
    fclose(f);
    printf("Observations sauvegardees dans observations.bin\n");
}

/* ============================================================
   CHARGER OBSERVATIONS
   - Lit observations.bin
   - Pour chaque entree, retrouve le patient par son ID
     dans la liste deja chargee (donc appeler APRES chargerPatients)
   - Retourne la liste d'observations reconstruite
     (pas de ** : on retourne le pointeur directement)
   ============================================================ */
Observation *chargerObservations(ListePatient *liste, int *numeroPrecedent) {
    FILE *f = fopen("observations.bin", "rb");
    if (f == NULL)
        return NULL; /* Premiere execution : normal */

    Observation *lits = NULL;
    int  numlit;
    char idPatient[20];

    while (fread(&numlit, sizeof(int), 1, f) == 1) {
        fread(idPatient, sizeof(char), 20, f);

        /* Rechercher le patient par ID dans la liste */
        Patient *p = liste->tete;
        while (p != NULL && strcmp(p->id, idPatient) != 0)
            p = p->suivant;

        if (p != NULL) {
            Observation *obs = malloc(sizeof(Observation));
            if (obs == NULL) break;
            obs->lit->num  = numlit;
            obs->patient = p;
            obs->suivant = NULL;

            /* Ajouter a la fin */
            if (lits == NULL) {
                lits = obs;
            } else {
                Observation *tmp = lits;
                while (tmp->suivant != NULL) tmp = tmp->suivant;
                tmp->suivant = obs;
            }

            if (numlit > *numeroPrecedent)
                *numeroPrecedent = numlit;
        }
    }
    fclose(f);
    return lits; /* Retourner au lieu de ** */
}
