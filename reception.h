#ifndef RECEPTION_H
#define RECEPTION_H

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
    Ticket *numticket;
    Etat etat;
    Heure heure;
    char departement[30];
    struct Patient *suivant;

};
void menuReception();
Ticket *CreateTicket(Patient *, int num);
Ticket * AddTicket(ListeTicket *, Patient *);
Patient * AddPatient(Patient *,ListeTicket*,char Nom[],char Prenom[],char ID[],int Age,char Sexe[]);
void DisplayQueue(Patient *);

#endif