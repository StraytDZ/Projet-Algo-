#ifndef MENU_H
#define MENU_H

#include "structure.h"

void menuMedecin(ListeTicket *tickets, ListeUrgence *urgences,
                 ListePatient *patients, ListeObservation *observations,
                 ListeLit *lit);

void menuConsultation(Patient *patientEnConsult, ListeObservation *observations,
                      ListeLit *lit, ListeTicket *tickets, ListePatient *patients);

void menuObservation(ListeObservation *observations, ListeLit *lit,
                     ListePatient *patients);

void menuModifierObservation(Observation *patientEnObservation,
                             ListeLit *lit);

void menuReception(ListePatient *patients, ListeTicket *tickets,
                   ListeUrgence *urgences);

void menuUrgence(ListeUrgence *urgences, ListeTicket *tickets);

void menuAdmin(ListePatient *patients, ListeLit *lit,
               ListeUrgence *urgences, ListeMedicament *medicaments,
               ListeEquipement *equipements);

#endif
