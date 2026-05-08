#ifndef MEDECIN_H
#define MEDECIN_H

#include "structure.h"

Patient *CallPatient(ListeTicket *listT,ListeUrgence *ListeU,ListePatient *ListeP);
void PatientDiagnostic(Patient *patientEnConsult);
void PatientOrdonnance(Patient *patientEnConsult,ListePatient *ListeP, ListeTicket *ListeT);
void AfficherAttente(ListeTicket *ListeT);
void transferer(Patient *patientEnConsult,ListePatient *ListeP,ListeTicket *ListeT);
#endif