#ifndef MEDECIN_H
#define MEDECIN_H

#include "reception.h"


Patient *CallPatient(ListeTicket *listT);
void PatientDiagnostic(Patient *patientEnConsult);
void PatientTraitement(Patient *patientEnConsult);
void PatientOrdonnance(Patient *patientEnConsult);
#endif