#ifndef OBSERVATION_H
#define OBSERVATION_H

typedef struct ListeLit{

    int numlit;
    Patient *patient;
    struct ListeLit *suivant;
}ListeLit;

ListeLit * donnerlit(Patient *patientEnConsult, ListeLit *lits, int *numeroprecedent);
void transferer(Patient *patientEnConsult);
void saisirduree(Patient *patientEnConsult);
void  modifierdiagnostique(Patient *patientEnConsult);
void  modifiertraitement(Patient *patientEnConsult);
void  modifierordonnance(Patient *patientEnConsult);
void verifierStatut(Patient *patientEnConsult);
void libererpatient(Patient *patientEnConsult);

#endif