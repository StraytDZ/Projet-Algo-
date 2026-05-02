#ifndef FICHIER_H
#define FICHIER_H

#include "structure.h"

/* wayi pour Sauvegarder */
void         sauvegarderPatients(ListePatient *liste);
void         sauvegarderObservations(ListeObservation *ListeO);
void         sauvegarderHistorique(Patient *p);

/* pour  Chargement */
void         chargerPatients(ListePatient *liste, ListeTicket *listeT);
Observation *chargerObservations(ListePatient *liste, int *numeroPrecedent);

/*pour  Historique */
void         afficherHistorique();

#endif