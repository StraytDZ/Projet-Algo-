#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <time.h>  // Pour la structure de Heure, utile pour l'historique.

typedef struct Patient Patient;
typedef struct Ticket {
    int numero;
    Patient *client;
    struct Ticket *suivant;
}Ticket;
typedef struct ListeTicket {
    Ticket *tete;
    int compteur;
}ListeTicket;
typedef enum {
    ATTENTE,
    CONSULTATION,
    OBSERVATION,
    TRANSFERER,
    SORTI,
}Etat;
typedef struct Heure {
    time_t arrive;
    time_t sorti;
}Heure;
struct Patient{
    char nom[30];
    char prenom[30];
    int age;
    char id[20];
    char sexe[4];
    Ticket *ticket;
    Etat etat;
    Heure heure;
    char departement[30];
    char diagnostique[100];
    char traitement[100];
    char ordonnance[100];
    int lit;
    struct Patient *suivant;

};
typedef struct ListePatient {
    Patient *tete;
    int total;
    int attente;
    int observation;
    int sortis;
    int transferes;
}ListePatient;

typedef struct Observation{

    int numlit;
    Patient *patient;
    time_t duree;
    char traitement[100];
    struct Observation *suivant;
}Observation;
typedef struct ListeObservation {
    Observation *tete;
    int compteur;
}ListeObservation;

#endif