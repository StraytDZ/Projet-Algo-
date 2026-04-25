#ifndef OBSERVATION_H
#define OBSERVATION_H



Observation * donnerlit(Patient *patientEnConsult, Observation *lits, int *numeroprecedent);
Observation * supprimerObservation(Observation *lits, int numlit);
void transferer(Patient *patientEnConsult);
void saisirduree(Patient *patientEnConsult);
void  modifierdiagnostique(Patient *patientEnConsult);
void  modifiertraitement(Patient *patientEnConsult);
void  modifierordonnance(Patient *patientEnConsult);
void verifierStatut(Patient *patientEnConsult);

#endif