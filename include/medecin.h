#ifndef MEDECIN_H
#define MEDECIN_H

#include "structure.h"

Patient *CallPatient(ListeTicket *listT,ListeUrgence *ListeU);
void PatientDiagnostic(Patient *patientEnConsult);
void PatientTraitement(Patient *patientEnConsult);
void PatientOrdonnance(Patient *patientEnConsult);
void AfficherAttente(ListeTicket *ListeT);
void transferer(Patient *patientEnConsult);
#endif