#ifndef RECEPTION_H
#define RECEPTION_H

#include "structure.h"

Ticket *CreateTicket(Patient *, int num);
Ticket * AddTicket(ListeTicket *, Patient *);
ListePatient * AddPatient(ListePatient *,ListeTicket*);
void afficherAttente(ListeTicket *ListeT);
void SaveTicket(ListeTicket *listeT);
void chargerTickets(ListeTicket *listeT);
void verifierNouveauJour(ListeTicket *ListeT);

#endif