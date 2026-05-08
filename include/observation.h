#ifndef OBSERVATION_H
#define OBSERVATION_H

#include "structure.h"

int AddLit(Patient *patientOB, ListeLit *ListeL);
void AfficherListeObservation(ListeObservation *ListeO);
void AddObservation(Patient *patientEnConsultation, ListeObservation *tete, ListeLit *ListeL,ListeTicket *ListeT,ListePatient *ListeP, ListeMedicament *ListeMedicament, ListeEquipement *ListeEquipement);
void SupprimerObservation(ListeObservation *ListeO, ListeLit *ListeL);
void ModifierObservation(ListeObservation *ListeO,ListeLit *ListeL);
void RechercheObservation(ListeObservation *ListeO);
#endif