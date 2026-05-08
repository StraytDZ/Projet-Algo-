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
    char medicamentsUtilises[10][30];
    int nbMedicaments;
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
    time_t finObservation;
    time_t debutObservation;
    time_t debutConsultation;
    time_t dureeConsultation;
    char medicamentsUtilises[10][30];
    int nbMedicaments;
    int index;
}Data;

typedef struct {
    char   nom[30];
    char   prenom[30];
    int    age;
    char   id[20];
    char   sexe[4];
    Heure  heure;
    int    numeroTicket;
} UrgenceData;
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
    if (f == NULL) return;

    PatientData data;
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
        p->age               = data.age;
        p->etat              = data.etat;
        p->heure             = data.heure;
        p->index             = data.index;             
        p->dureeConsultation = data.dureeConsultation; 
        p->debutConsulation  = data.debutConsultation;
        p->suivant           = NULL;

        if (p->etat == ATTENTE) {
            Ticket *t = (Ticket*)malloc(sizeof(Ticket));
            if (t != NULL) {
                t->client  = p;
                t->numero  = data.numeroTicket;
                t->suivant = NULL;
                // Ajouter a la fin de la liste de tickets
                if (listeT->tete == NULL) {
                    listeT->tete = t;
                } else {
                    Ticket *tmp = listeT->tete;
                    while (tmp->suivant != NULL) tmp = tmp->suivant;
                    tmp->suivant = t;
                }
                p->ticket = t;
            }
        } else {
            p->ticket = NULL;
        }

        // Ajouter a la fin de la liste patients
        if (liste->tete == NULL) {
            liste->tete = p;
        } else {
            Patient *tmp = liste->tete;
            while (tmp->suivant != NULL) tmp = tmp->suivant;
            tmp->suivant = p;
        }

        liste->total++;
        if      (p->etat == ATTENTE)     liste->attente++;
        else if (p->etat == OBSERVATION) liste->observation++;
        else if (p->etat == SORTI)       liste->sortis++;
        else if (p->etat == TRANSFERER)  liste->transferes++;
    }

    fclose(f);
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
        return;
        }
    FILE *o = fopen("data/observations.bin", "r+b");
    if (o == NULL) {
        o = fopen("data/observations.bin", "wb");  // créer si inexistant
        if (o == NULL) {
            printf("Erreur : Impossible d'ouvrir observations.bin\n");
            fclose(p);
            fclose(h);
            return;
        }
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
            data.nbMedicaments = dataO.nbMedicaments; 
            memcpy(data.medicamentsUtilises, dataO.medicamentsUtilises, sizeof(dataO.medicamentsUtilises)); 
            data.lit = dataO.lit;
        }
        else {
            data.lit = 0;
            data.finObservation   = 0;
            data.debutObservation = 0;
            strcpy(data.traitement, "");
            data.nbMedicaments = 0;
            memset(data.medicamentsUtilises, 0, sizeof(data.medicamentsUtilises)); 
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
        f = fopen("data/historique.bin", "wb");
        system("cls");
        printf(RED  "+================================================+\n" RESET);
        printf(RED  "|           HISTORIQUE DES PATIENTS              |\n" RESET);
        printf(RED  "+================================================+\n" RESET);
        printf(CYAN "|    " YELLOW "Aucun historique disponible.              " CYAN "  |\n" RESET);
        printf(RED  "+================================================+\n" RESET);
        pause();
        return;
    }

    Data data;
    int total = 0;

    system("cls");
    printf(RED  "+================================================+\n" RESET);
    printf(RED  "|           HISTORIQUE DES PATIENTS              |\n" RESET);
    printf(RED  "+================================================+\n" RESET);

    while (fread(&data, sizeof(Data), 1, f) == 1) {
        char *etatStr;
        if      (data.etat == SORTI)        etatStr = "SORTI";
        else if (data.etat == TRANSFERER)   etatStr = "TRANSFERE";
        else if (data.etat == CONSULTATION) etatStr = "CONSULTATION";
        else if (data.etat == ATTENTE)      etatStr = "ATTENTE";
        else if (data.etat == OBSERVATION)  etatStr = "OBSERVATION";
        else if (data.etat == URGENCE)      etatStr = "URGENCE";
        else                                etatStr = "INCONNU";

        char heureArrive[30];
        strftime(heureArrive, 30, "%d/%m/%Y %H:%M", localtime(&data.heure.arrive));

        total++;
        printf(CYAN "| " YELLOW "[%2d]" CYAN " %-20s %-20s |\n" RESET,
               total, data.nom, data.prenom);
        printf(CYAN "|      ID     : %-33s|\n" RESET, data.id);
        printf(CYAN "|      Age    : %d ans | Sexe : %-1s | %-12s |\n" RESET,
               data.age, data.sexe, etatStr);
        printf(CYAN "|      Arrive : %-33s|\n" RESET, heureArrive);
        printf(RED  "+------------------------------------------------+\n" RESET);
    }

    if (total == 0) {
        printf(CYAN "|    Aucun patient dans l'historique.            |\n" RESET);
        printf(RED  "+================================================+\n" RESET);
        fclose(f);
        return;
    }

    printf(GREEN "                       Choix : " RESET);
    int choix;
    choix = saisirChoix();

    if (choix < 1 || choix > total) {
        printf(RED "+------------------------------------------------+\n" RESET);
        printf(CYAN "|  " YELLOW "Choix invalide.                             " CYAN "|\n" RESET);
        printf(RED "+================================================+\n" RESET);
        fclose(f);
        return;
    }

    long position = (long)(choix - 1) * sizeof(Data);
    fseek(f, position, SEEK_SET);
    fread(&data, sizeof(Data), 1, f);

    char *etatStr;
    if      (data.etat == SORTI)        etatStr = "SORTI";
    else if (data.etat == TRANSFERER)   etatStr = "TRANSFERE";
    else if (data.etat == CONSULTATION) etatStr = "CONSULTATION";
    else if (data.etat == ATTENTE)      etatStr = "ATTENTE";
    else if (data.etat == OBSERVATION)  etatStr = "OBSERVATION";
    else if (data.etat == URGENCE)      etatStr = "URGENCE";
    else                                etatStr = "INCONNU";

    char heureArrive[30];
    strftime(heureArrive, 30, "%d/%m/%Y %H:%M", localtime(&data.heure.arrive));

    system("cls");
    printf(RED  "+================================================+\n" RESET);
    printf(RED  "|             DETAIL DU PATIENT                  |\n" RESET);
    printf(RED  "+================================================+\n" RESET);
    printf(CYAN "| Nom         : %-33s|\n" RESET, data.nom);
    printf(CYAN "| Prenom      : %-33s|\n" RESET, data.prenom);
    printf(CYAN "| ID          : %-33s|\n" RESET, data.id);
    printf(CYAN "| Age         : %d ans                           |\n" RESET, data.age);
    printf(CYAN "| Sexe        : %-33s|\n" RESET, data.sexe);
    printf(CYAN "| Etat        : %-33s|\n" RESET, etatStr);
    printf(CYAN "| Arrivee     : %-33s|\n" RESET, heureArrive);

    if (data.heure.sorti != 0) {
        char heureSortie[30];
        strftime(heureSortie, 30, "%d/%m/%Y %H:%M", localtime(&data.heure.sorti));
        printf(CYAN "| Sortie      : %-33s|\n" RESET, heureSortie);
    }
    if (data.numeroTicket != 0)
        printf(CYAN "| Ticket      : %-33d|\n" RESET, data.numeroTicket);

    if (strcmp(data.diagnostique, "") != 0) {
        printf(RED  "+------------------------------------------------+\n" RESET);
        printf(CYAN "| Diagnostic  : %-33s|\n" RESET, data.diagnostique);
        if (strlen(data.ordonnance) > 0)
            printf(CYAN "| Ordonnance  : %-33s|\n" RESET, data.ordonnance);
        if (strlen(data.departement) > 0)
            printf(CYAN "| Departement : %-33s|\n" RESET, data.departement);
        if (data.dureeConsultation != 0) {
            char duree[10];
            strftime(duree, sizeof(duree), "%M", localtime(&data.dureeConsultation));
            printf(CYAN "| Duree       : %s min                           |\n" RESET, duree);
        }
    }

    if (data.lit != 0) {
        printf(RED  "+------------------------------------------------+\n" RESET);
        printf(CYAN "| Lit         : %-33d|\n" RESET, data.lit);
        if (strcmp(data.traitement, "") != 0)
            printf(CYAN "| Traitement  : %-33s|\n" RESET, data.traitement);
            if (data.nbMedicaments > 0) {
                printf(RED  "+------------------------------------------------+\n" RESET);
                printf(CYAN "| Medicaments pris :                             |\n" RESET);
                for(int i = 0; i < data.nbMedicaments; i++) {
                    printf(CYAN "|   - %-43s|\n" RESET, data.medicamentsUtilises[i]);
                 }   
            }
        if (data.debutObservation != 0) {
            char buffer[30];
            strftime(buffer, 30, "%d/%m/%Y %H:%M", localtime(&data.debutObservation));
            printf(CYAN "| Debut obs   : %-33s|\n" RESET, buffer);
        }
        if (data.finObservation != 0) {
            char buffer[30];
            strftime(buffer, 30, "%d/%m/%Y %H:%M", localtime(&data.finObservation));
            printf(CYAN "| Fin obs     : %-33s|\n" RESET, buffer);
        }
    }

    printf(RED "+================================================+\n" RESET);
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
    // dans sauvegarderPatients()
    data.nbMedicaments = patientOB->nbMedicaments;
    memcpy(data.medicamentsUtilises, patientOB->medicamentsUtilises, sizeof(data.medicamentsUtilises));
    
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
void chargerObservations(ListePatient *liste, ListeObservation *ListeO, ListeLit *ListeL) {
    FILE *f = fopen("data/observations.bin", "rb");
    if (f == NULL) return;

    ObservationData data;
    while (fread(&data, sizeof(ObservationData), 1, f) == 1) {
        // Retrouver le patient par index
        Patient *p = liste->tete;
        while (p != NULL && p->index != data.index)
            p = p->suivant;

        if (p != NULL) {
            Observation *obs = malloc(sizeof(Observation));
            if (obs == NULL) break;
            obs->lit              = data.lit;
            obs->patient          = p;
            obs->finObservation   = data.finObservation;
            obs->debutObservation = data.debutObservation;
            obs->index            = data.index;
            strcpy(obs->traitement, data.traitement);
            obs->nbMedicaments = data.nbMedicaments;
            memcpy(obs->medicamentsUtilises, data.medicamentsUtilises, sizeof(data.medicamentsUtilises));
            obs->suivant = NULL;

            if (data.lit >= 1 && data.lit <= ListeL->total) {
                ListeL->Tlit[data.lit-1].etat    = OCCUPE;
                ListeL->Tlit[data.lit-1].patient  = p;
                ListeL->indispo++;
            }

            if (ListeO->tete == NULL) ListeO->tete = obs;
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
void sauvegarderUrgences(ListeUrgence *ListeU) {
    FILE *f = fopen("data/urgences.bin", "wb");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir urgences.bin\n");
        return;
    }

    Urgence *courant = ListeU->tete;
    while (courant != NULL) {
        UrgenceData data;
        strcpy(data.nom,    courant->patient->nom);
        strcpy(data.prenom, courant->patient->prenom);
        strcpy(data.id,     courant->patient->id);
        strcpy(data.sexe,   courant->patient->sexe);
        data.age          = courant->patient->age;
        data.heure        = courant->patient->heure;
        data.numeroTicket = courant->patient->ticket
                            ? courant->patient->ticket->numero : 0;
        fwrite(&data, sizeof(UrgenceData), 1, f);
        courant = courant->suivant;
    }
    fclose(f);
}

void chargerUrgences(ListeUrgence *ListeU, ListeTicket *ListeT) {
    FILE *f = fopen("data/urgences.bin", "rb");
    if (f == NULL) return;

    UrgenceData data;
    while (fread(&data, sizeof(UrgenceData), 1, f) == 1) {

        // Reconstruire le patient
        Patient *p = (Patient*)malloc(sizeof(Patient));
        if (p == NULL) break;
        strcpy(p->nom,    data.nom);
        strcpy(p->prenom, data.prenom);
        strcpy(p->id,     data.id);
        strcpy(p->sexe,   data.sexe);
        p->age    = data.age;
        p->heure  = data.heure;
        p->etat   = URGENCE;
        p->suivant = NULL;
        strcpy(p->diagnostique, "");
        strcpy(p->ordonnance,   "");
        strcpy(p->departement,  "");

        // Reconstruire le ticket avec le numero sauvegarde
        Ticket *t = (Ticket*)malloc(sizeof(Ticket));
        if (t == NULL) { free(p); break; }
        t->client  = p;
        t->numero  = data.numeroTicket;
        t->suivant = NULL;
        // Ajouter a la fin de la liste de tickets
        if (ListeT->tete == NULL) {
            ListeT->tete = t;
        } else {
            Ticket *tmp = ListeT->tete;
            while (tmp->suivant != NULL) tmp = tmp->suivant;
            tmp->suivant = t;
        }
        p->ticket = t;

        // Reconstruire le noeud urgence
        Urgence *noeud = (Urgence*)malloc(sizeof(Urgence));
        if (noeud == NULL) { free(t); free(p); break; }
        noeud->patient  = p;
        noeud->suivant  = NULL;

        if (ListeU->tete == NULL) {
            ListeU->tete = noeud;
        } else {
            Urgence *tmp = ListeU->tete;
            while (tmp->suivant != NULL) tmp = tmp->suivant;
            tmp->suivant = noeud;
        }

        ListeU->total++;
        ListeU->attente++;
    }
    fclose(f);
}
void sauvegarderLit(ListeLit *L) {
    FILE *f = fopen("data/lit.bin", "wb");
    if (f == NULL) return;
    fwrite(&L->total, sizeof(int), 1, f);
    fclose(f);
}

void chargerLit(ListeLit *L) {
    FILE *f = fopen("data/lit.bin", "rb");
    if (f == NULL) return; 
    fread(&L->total, sizeof(int), 1, f);
    fclose(f);
}

void NettoyerPatientsSortis(ListePatient *ListeP) {
    if (ListeP == NULL || ListeP->tete == NULL) {
        return;
    }

    Patient *courant = ListeP->tete;
    Patient *precedent = NULL;
    int patientsNettoyes = 0; // Petit compteur pour le suivi

    while (courant != NULL) {
        // On vérifie si l'état est SORTI (tu pourrais aussi ajouter TRANSFERER si tu veux les nettoyer aussi)
        if (courant->etat == SORTI || courant->etat == TRANSFERER) {
            sauvegarderPatients(courant);

            Patient *aSupprimer = courant;
            if (precedent == NULL) {
                ListeP->tete = courant->suivant;
                courant = courant->suivant;
            } else {
                precedent->suivant = courant->suivant;
                courant = courant->suivant;
            }
            free(aSupprimer);
            patientsNettoyes++;

        } else {
            precedent = courant;
            courant = courant->suivant;
        }
    }

    if (patientsNettoyes > 0) {
        printf(GREEN "%d patient(s) SORTI(S) ont ete sauvegardes et liberes de la RAM.\\n" RESET, patientsNettoyes);
    }
}