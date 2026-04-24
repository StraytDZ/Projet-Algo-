#ifndef OBSERVATION_H
#define OBSERVATION_H

void donnerlit(Patient *patientEnConsult, int lit);
void  saisirdiagnostique(Patient *patientEnConsult);
void  saisirtraitement(Patient *patientEnConsult);
void  saisirordonnance(Patient *patientEnConsult);
void saisirduree(Patient *patientEnConsult);
void  modifierdiagnostique(Patient *patientEnConsult);
void  modifiertraitement(Patient *patientEnConsult);
void  modifierordonnance(Patient *patientEnConsult);


#endif