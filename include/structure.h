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
typedef enum { // 
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
    time_t debutConsulation;
    time_t dureeConsultation;
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
typedef struct Medicament {
    char nom[30];
    int quantite;
} Medicament;

#define MAX_MEDICAMENTS 100

typedef struct ListeMedicament {
    Medicament medicaments[MAX_MEDICAMENTS];
    int total;
} ListeMedicament;

typedef struct Equipement {
    char nom[30];
    int quantite;
} Equipement;

#define MAX_EQUIPEMENTS 100

typedef struct ListeEquipement {
    Equipement equipements[MAX_EQUIPEMENTS];
    int total;
} ListeEquipement;
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
    int index;
    char medicamentsUtilises[10][30]; // max 10 médicaments, 30 chars chacun
    int nbMedicaments;
    struct Observation *suivant;
    Equipement *equipements[10];
    int compteurEquipements;
}Observation;
typedef struct ListeObservation { // Liste de tout les noeuds Observation
    Observation *tete;
    int compteur;
}ListeObservation;

typedef struct Urgence{
    Patient *patient;  
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
 

#define RED    "\033[91m"
#define CYAN   "\033[96m"
#define GREEN  "\033[92m"
#define YELLOW "\033[93m"
#define RESET  "\033[0m"


#endif