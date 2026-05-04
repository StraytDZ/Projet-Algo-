#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <time.h>  // Pour la structure de Heure, utile pour l'historique.
 
#define MAX_LIT 100
typedef struct Patient Patient;
typedef struct Ticket {
    int numero;
    Patient *client;
    struct Ticket *suivant;
}Ticket;
typedef struct ListeTicket {
    Ticket *tete;
    time_t dernierReset;
    int compteur;
}ListeTicket;
typedef enum {
    ATTENTE,
    CONSULTATION,
    OBSERVATION,
    TRANSFERER,
    URGENCE,
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
    int index;
    char diagnostique[100];
    char ordonnance[100];
    char departement[30];
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
    EtatLit etat;
    int num;
}Lit;
typedef struct ListeLit{ // // Liste de tout les noeuds Lit
    Lit Tlit[MAX_LIT];
    int total;
    int indispo; 
}ListeLit;
typedef struct Observation{ // Un noeud Observation
    Patient *patient;
    int lit;
    char traitement[100];
    time_t finObservation;
    time_t debutObservation;
    struct Observation *suivant;
}Observation;
typedef struct ListeObservation { // Liste de tout les noeuds Observation
    Observation *tete;
    int compteur;
}ListeObservation;

typedef struct Urgence{
    Patient *patient;
    char traitement[100];  
    struct Urgence *suivant;
} Urgence;

typedef struct ListeUrgence {
    Urgence *tete;
    int attente;
    int total;
} ListeUrgence;

typedef struct Statistique {
    int totalPatients;
    int totalAttente;
    int totalsortis;
    int totaltransferes;
    int totalObservation;
    int LitIndispo;
    int Littotal;
    int totalUrgence;
    int attenteUrgence;
} Statistique;  


#endif