#ifndef OBSERVATION_H
#define OBSERVATION_H

#include "structure.h"

int AddLit(Patient *patientOB, ListeLit *ListeL);
void AfficherListeObservation(ListeObservation *ListeO);
ListeObservation *AddObservation(Patient *patientEnConsultation, ListeObservation *tete, ListeLit *ListeL);
void SupprimerObservation(ListeObservation *ListeO, ListeLit *ListeL);
void ModifierObservation(ListeObservation *ListeO,ListeLit *ListeL);
void RechercheObservation(ListeObservation *ListeO);
#endif