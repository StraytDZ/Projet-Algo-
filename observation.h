#ifndef OBSERVATION_H
#define OBSERVATION_H



ListeObservation * donnerlit(Patient *patientEnConsult, ListeObservation *lits, int *numeroprecedent);
void transferer(Patient *patientEnConsult);
void saisirduree(Patient *patientEnConsult);
void  modifierdiagnostique(Patient *patientEnConsult);
void  modifiertraitement(Patient *patientEnConsult);
void  modifierordonnance(Patient *patientEnConsult);
void verifierStatut(Patient *patientEnConsult);
void libererpatient(Patient *patientEnConsult);

#endif