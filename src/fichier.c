#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fichier.h"
#include "reception.h"
#include "menu.h"
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
    time_t debutConsultation;
    time_t dureeConsultation;
    char departement[30];
    char diagnostique[100];
    char ordonnance[100];
    int index;
} PatientData;

typedef struct {    
    int lit;
    char traitement[100];
    time_t finObservation;
    time_t debutObservation;
    int index;
}ObservationData;

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
    char ordonnance[100];
    int lit;
    char traitement[100];
    Medicament medicament;
    time_t finObservation;
    time_t debutObservation;
    time_t debutConsultation;
    time_t dureeConsultation;
    int index;
}Data;

    /*
    SAUVEGARDER PATIENTS
    - "wb" = write binary : ouvre en ecriture binaire
    - Parcourt la liste et ecrit chaque patient
     */
void sauvegarderPatients(Patient *patient) {
    FILE *f = fopen("data/patients.bin","r+b");
    if (f == NULL) {
        f = fopen("data/patients.bin","wb"); // Si le fichiers n'existe pas , on le crée
        if(f == NULL) {
        printf("Erreur : Impossible d'ouvrir historique.bin\n");
        return;
        }
    }
   /*Patient *courant = liste->tete;//tban dayi acu 3elegh 
    while (courant != NULL) { */ 
        PatientData data;
        long position = (long)(patient->index - 1)*sizeof(PatientData);
        fseek(f,position,SEEK_SET);
        strcpy(data.nom,          patient->nom);
        strcpy(data.prenom,       patient->prenom);
        strcpy(data.id,           patient->id);
        strcpy(data.sexe,         patient->sexe);
        strcpy(data.departement,  patient->departement);
        strcpy(data.diagnostique, patient->diagnostique);
        strcpy(data.ordonnance,   patient->ordonnance);
        data.age          = patient->age;
        data.etat         = patient->etat;
        data.heure        = patient->heure;
        data.dureeConsultation = patient->dureeConsultation;
        data.index = patient->index;
        data.numeroTicket = patient->ticket ? patient->ticket->numero : 0; /*C'est un opérateur ternaire — c'est une façon courte d'écrire un if/else en une ligne :
            Version longue
        if (courant->ticket != NULL)
            data.numeroTicket = courant->ticket->numero;
        else
            data.numeroTicket = 0; on la pas etudié, mais pourquoi ce limiter*/
        if(patient->etat == CONSULTATION) data.debutConsultation = patient->debutConsulation;
        fwrite(&data, sizeof(PatientData), 1, f);
        /*  suntaxe is fwrite(adresse, taille d'un element, nombre, fichier) */ 

    fclose(f);
    printf("Patients sauvegarder dans patients.bin\n");
}

/* charger patients
   - "rb" = read binary : 
   - Relit chaque PatientData et recree le Patient en memoire
   - Recrée aussi le Ticket avec le bon numero
   */
void chargerPatients(ListePatient *liste, ListeTicket *listeT) {
    FILE *f = fopen("data/patients.bin", "rb");
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
        p->suivant = NULL;
        p->index             = data.index;
        p->debutConsulation  = data.debutConsultation;
        p->dureeConsultation = data.dureeConsultation;
        Ticket *t = malloc(sizeof(Ticket));
        t->numero  = data.numeroTicket;
        t->client  = p;
        t->suivant = NULL;
        p->ticket  = t;
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

void sauvegarderHistorique() {
    FILE *h = fopen("data/historique.bin", "r+b");
    if (h == NULL) {
        h = fopen("data/historique.bin","wb"); // Si le fichiers n'existe pas , on le crée
        if(h == NULL) {
        printf("Erreur : Impossible d'ouvrir historique.bin\n");
        return;
        }
    }
    FILE *p = fopen("data/patients.bin", "r+b");
    if (p == NULL) {
        printf("Erreur : Impossible d'ouvrir patients.bin\n");
        fclose(h);
        return;
        }
    FILE *o = fopen("data/observations.bin", "r+b");
    if (o == NULL) {
        printf("Erreur : Impossible d'ouvrir observations.bin\n");
        fclose(p);
        fclose(h);
        return;
        }

    Data data;
    PatientData dataP;
    while(fread(&dataP, sizeof(PatientData),1,p) == 1){
        strcpy(data.nom,dataP.nom);
        strcpy(data.prenom,dataP.prenom);
        strcpy(data.id,dataP.id);
        strcpy(data.sexe,dataP.sexe);
        strcpy(data.departement,dataP.departement);
        strcpy(data.diagnostique,dataP.diagnostique);
        strcpy(data.ordonnance,dataP.ordonnance);
        data.age = dataP.age;
        data.etat = dataP.etat;
        data.numeroTicket = dataP.numeroTicket;
        data.heure = dataP.heure;
        data.dureeConsultation = dataP.dureeConsultation;
        data.index = dataP.index;
        if(dataP.etat == OBSERVATION){
            ObservationData dataO;
            while(fread(&dataO,sizeof(ObservationData),1,o) == 1) {
                if(dataO.index == dataP.index) break;
            }
            strcpy(data.traitement, dataO.traitement);
            data.debutObservation = dataO.debutObservation;
            data.finObservation = dataO.finObservation;
            data.lit = dataO.lit;
        }
        else {
            data.lit = 0;
            data.finObservation   = 0;
            data.debutObservation = 0;
            strcpy(data.traitement, "");
        }
        long position = (long)(data.index - 1)*sizeof(Data);
        fseek(h,position,SEEK_SET);
        fwrite(&data,sizeof(Data),1,h);
        rewind(o);
    }
    fclose(h);
    fclose(p);
    fclose(o);
}

void afficherHistorique() {
    FILE *f = fopen("data/historique.bin", "r+b");
    if (f == NULL) {
        f = fopen("data/historique.bin","wb");
        printf("Aucun historique disponible.\n");
        return;
    }

    Data data;
    int i = 1;
    printf("\n========== HISTORIQUE DES PATIENTS ==========\n");
    while (fread(&data, sizeof(Data), 1, f) == 1) {
        char *etatStr;
        if      (data.etat == SORTI)     etatStr = "SORTI";
        else if (data.etat == TRANSFERER) etatStr = "TRANSFERE";
        else if (data.etat == CONSULTATION) etatStr = "CONSULTION";
        else if (data.etat == ATTENTE ) etatStr = "ATTENTE";
        else if (data.etat == OBSERVATION) etatStr = "OBSERVATION";
        else if (data.etat == URGENCE)     etatStr = "URGENCE";

        /* Convertir time_t en date lisible */
        char heureArrive[30];
        strftime(heureArrive, 30, "%d/%m/%Y %H:%M", localtime(&data.heure.arrive));
        printf("[%d] - %s  %s | %d Ans | %s | %s | %s | Arrive : %s\n", i, data.nom, data.prenom, data.age, data.sexe, data.id,etatStr,heureArrive);
        i++;
        }
        int choix;
        printf("----Choix : ");
        scanf("%d",&choix);
        long position = (long)(choix - 1) * sizeof(Data);
        fseek(f, position, SEEK_SET);

        char *etatStr;
        if      (data.etat == SORTI)     etatStr = "SORTI";
        else if (data.etat == TRANSFERER) etatStr = "TRANSFERE";
        else if (data.etat == CONSULTATION) etatStr = "CONSULTION";
        else if (data.etat == ATTENTE ) etatStr = "ATTENTE";
        else if (data.etat == OBSERVATION) etatStr = "OBSERVATION";
        else if (data.etat == URGENCE)     etatStr = "URGENCE";

        
        char heureArrive[30];
        strftime(heureArrive, 30, "%d/%m/%Y %H:%M", localtime(&data.heure.arrive));
        printf("+==== Patient %d ====\n", i++);
        printf("|--Nom      : %s %s\n",      data.prenom, data.nom);
        printf("|--ID       : %s | Age : %d | Sexe : %s\n", data.id, data.age, data.sexe);
        if (data.numeroTicket != 0) 
            printf("|--Ticket   : %d\n",       data.numeroTicket);
        printf("|--Etat     : %s\n",          etatStr);
        printf("|--Arrivee  : %s\n",          heureArrive);
        if (data.heure.sorti != 0) {
            char heureSortie[30];
            strftime(heureSortie, 30, "%d/%m/%Y %H:%M", localtime(&data.heure.sorti));
            printf("|--Sortie   : %s\n", heureSortie);
        }
        if(data.dureeConsultation != 0 || data.etat == CONSULTATION) { 
            printf("____CONSULTATION____");
        if (strlen(data.diagnostique) > 0)
            printf("|--Diagnostic  : %s\n",  data.diagnostique);
        if (strlen(data.ordonnance) > 0)
            printf("|--Ordonnance  : %s\n",  data.ordonnance);
        if (strlen(data.departement) > 0)
            printf("|--Departement : %s\n",  data.departement);
        if (data.dureeConsultation != 0) {
            char dureConsultation[30];
            strftime(dureConsultation, 30, "%M", localtime(&data.dureeConsultation));
            printf("|--Duree Consultation : %sMin", dureConsultation);
            }
        }   
        if(strlen(data.traitement) > 0 || data.etat == OBSERVATION) {
            printf("____OBSERVATION____");
        if(strlen(data.traitement) > 0) 
            printf("|--Traitement : %s", data.traitement);
        if(data.lit != 0)
            printf("|--Lit : %d", data.lit);
        }
        printf("=====================");
        printf("\n");
    
    fclose(f);
}

/* ============================================================
   SAUVEGARDER OBSERVATIONS
   - Sauvegarde : numero de lit + ID du patient
   - On sauvegarde l'ID car c'est l'identifiant unique
     qui permet de retrouver le patient au chargement
   ============================================================ */
void sauvegarderObservations(Observation *patientOB) {
    FILE *f = fopen("data/observations.bin", "r+b");
    if (f == NULL) {
        f = fopen("data/observations.bin", "wb"); 
        if (f == NULL) {
            printf("Erreur : Impossible d'ouvrir observations.bin\n");
        return;
        }
    }
    long position = (long)(patientOB->index - 1)*sizeof(ObservationData);
    ObservationData data;
    data.lit = patientOB->lit;
    data.debutObservation = patientOB->debutObservation;
    data.finObservation = patientOB->finObservation;
    data.index = patientOB->index;
    strcpy(data.traitement , patientOB->traitement);

    fseek(f, position, SEEK_SET);
    fwrite(&data, sizeof(ObservationData),1,f);

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
void chargerObservations(ListePatient *ListeP, ListeObservation *ListeO, ListeLit *ListeL) {
    FILE *f = fopen("data/observations.bin", "rb");
    if (f == NULL) return;
    ObservationData data;
    while (fread(&data, sizeof(ObservationData), 1, f) == 1) {

        // Retrouver le patient par son index
        Patient *p = ListeP->tete;
        while (p != NULL && p->index != data.index)
            p = p->suivant;

        if (p != NULL) {
            Observation *obs = malloc(sizeof(Observation));
            obs->lit              = data.lit;
            obs->patient          = p;
            obs->finObservation   = data.finObservation;
            obs->debutObservation = data.debutObservation;
            obs->index            = data.index;
            strcpy(obs->traitement, data.traitement);
            obs->suivant = NULL;

            // Retrouver et marquer le lit comme occupé
                ListeL->Tlit[obs->lit-1].etat    = OCCUPE;
                ListeL->Tlit[obs->lit-1].patient = p;
                ListeL->indispo++;
            

            // Ajouter à la liste
            if (ListeO->tete == NULL)
                ListeO->tete = obs;
            else {
                Observation *tmp = ListeO->tete;
                while (tmp->suivant != NULL) tmp = tmp->suivant;
                tmp->suivant = obs;
            }
            ListeO->compteur++;
        }
    }
    fclose(f);
}
