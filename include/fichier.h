#ifndef FICHIER_H
#define FICHIER_H

#include "structure.h"

/* wayi pour Sauvegarder */
void         sauvegarderPatients(Patient *patient);
void         sauvegarderObservations(Observation *patient);
void         sauvegarderHistorique();
void         sauvegarderUrgences(ListeUrgence *ListeU);

/* pour  Chargement */
void         chargerPatients(ListePatient *liste, ListeTicket *listeT);
void chargerObservations(ListePatient *liste, ListeObservation *ListeO, ListeLit *ListeL); 
void chargerUrgences(ListeUrgence *ListeU, ListeTicket *ListeT);
/*pour  Historique */
void         afficherHistorique();

#endif