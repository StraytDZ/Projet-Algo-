#ifndef RECEPTION_H
#define RECEPTION_H

#include "structure.h"

Ticket *CreateTicket(Patient *, int num);
Ticket * AddTicket(ListeTicket *, Patient *);
ListePatient * AddPatient(ListePatient *,ListeTicket*);
void DisplayQueue(ListePatient *ListeP);
void SaveTicket(ListeTicket *listeT);
void chargerTicket(ListeTicket *listeT);
void verifierNouveauJour(ListeTicket *ListeT);

#endif