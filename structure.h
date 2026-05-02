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
    struct Lit *suivant;
}Lit;
typedef struct ListeLit{ // // Liste de tout les noeuds Lit
    Lit *teteLit;
    int total;
    int indispo; // On peut pas connaitre combien de lit disponible car on a ici une lsite Chainer, faudra alors faire total - indispo
}ListeLit;
typedef struct Observation{ // Un noeud Observation
    Patient *patient;
    Lit *lit;
    char traitement[100];
    Heure duree;
    struct Observation *suivant;
}Observation;
typedef struct ListeObservation { // Liste de tout les noeuds Observation
    Observation *tete;
    int compteur;
}ListeObservation;

typedef enum {
    DISPONIBLE,
    EN_UTILISATION,
    EN_MAINTENANCE,
    HORS_SERVICE,
} EtatEquipement;

typedef enum {
    MEDICAL,        // Stethoscope, tensiometre...
    CHIRURGICAL,    // Scalpel, pince...
    INFORMATIQUE,   // Ordinateur, imprimante...
    MOBILIER,       // Lit, chaise... 
    AUTRE,
} TypeEquipement;
typedef struct Equipement{
    int id;
    char nom[50];
    TypeEquipement type;
    EtatEquipement etat;
    int quantite;
    int quantiteDisponible;
    char service[30];       // quel service l'utilise
    time_t dateAchat;
    float prix;

}Equipements;


typedef struct Urgence{
    char nom[30];
    char prenom[30];
    Urgence *suivant;
    char traitement[100];  
} Urgence;

typedef struct ListeUrgence {
    Patient *tete;
    int attente;
    int total;
} ListeUrgence;

#endif