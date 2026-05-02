#ifndef OBSERVATION_H
#define OBSERVATION_H

#include "structure.h"

Lit *CreateLit(ListeLit* ListeL);
Lit *AddLit(ListeObservation *patientOB, ListeLit *ListeL);
void afficherObservation(ListeObservation *patientO);
ListeObservation *AddObservation(Patient *patientEnConsultation, ListeObservation *tete, ListeLit *ListeL);
Observation * supprimerObservation(Observation *lits, int numlit);
void transferer(Patient *patientEnConsult);
void saisirduree(Patient *patientEnConsult);
void modifiertraitement(Patient *patientEnConsult);
void verifierStatut(Patient *patientEnConsult);

#endif