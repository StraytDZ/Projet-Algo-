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
typedef enum {
    OCCUPE,
    NOCCUPE,
}EtatLit;
typedef struct Lit{ // Un noeud Lit
    Patient *patient;
<<<<<<< HEAD
    EtatLit etat;
    int num;
    struct Lit *suivant;
}Lit;
typedef struct ListeLit{ // // Liste de tout les noeuds Lit
    Lit *tete;
    int total;
    int indispo; // On peut pas connaitre combien de lit disponible car on a ici une lsite Chainer, faudra alors faire total - indispo
}ListeLit;
typedef struct Observation{ // Un noeud Observation
    Patient *patient;
    Lit *lit;
    char traitment[100];
    int duree;
=======
    time_t duree;
    char traitement[100];
>>>>>>> 18942647839594ab316306a57306cf958eaa7fc6
    struct Observation *suivant;
}Observation;

typedef struct ListeObservation { // Liste de tout les noeuds Observation
    Observation *tete;
    int compteur;
}ListeObservation;

#endif