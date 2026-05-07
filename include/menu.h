#ifndef MENU_H
#define MENU_H

#include "structure.h"

void pause();
void menuPrincipal();
void menuMedecin();
void menuConsultation(Patient *patientEnConsultation);
void menuReception();
void menuObservation();
void menuModifierObservation(Observation *patientEnObservation);
void menuUrgence();
void menuAdmin();
void menuMessage();
#endif