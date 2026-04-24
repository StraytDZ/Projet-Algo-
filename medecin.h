#ifndef MEDECIN_H
#define MEDECIN_H

#include "reception.h"

typedef struct PatientObservation {
    Patient *patient;
    int lit;
    char diagnostique[200];
    char traitement[100];
    struct PatientObservation *suivant;

}PatientObservation;


Patient *CallPatient(ListeTicket *listT);
void PatientDiagnostic(Patient *patientEnConsult);
void PatientTraitement(Patient *patientEnConsult);
void PatientOrdonnance(Patient *patientEnConsult);
#endif