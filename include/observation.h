#ifndef OBSERVATION_H
#define OBSERVATION_H

#include "structure.h"

Lit *AddLit(Observation *patientOB, ListeLit *ListeL);
void AfficherObservation(ListeObservation *patientO);
ListeObservation *AddObservation(Patient *patientEnConsultation, ListeObservation *tete, ListeLit *ListeL);
Observation * SupprimerObservation(Observation *lits, int numlit);
void transferer(Patient *patientEnConsult);
void saisirduree(Patient *patientEnConsult);
void modifiertraitement(Patient *patientEnConsult);
void verifierStatut(Patient *patientEnConsult);
void ModifierObservation(ListeObservation *ListeO);
void RechercheObservation(ListeObservation *ListeO);
#endif