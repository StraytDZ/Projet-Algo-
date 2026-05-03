#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "observation.h"
#include "structure.h"



Lit AddLit(Observation *patientOB,ListeLit* ListeL) { // Fonciton juste pour cree le ' noeud ', ici on ne l'ajoute pas encore vers notre 'lsite de noeud' (ListeLit)
    if(ListeL->indispo >= ListeL->total ) {  // Si on depasse le nombre de lit disponible dans l'hopitale, tel que ListeL->total est donner dans le main,
        printf("Erreur : plus de lit disponible !\n");
        return; 
    }
        Lit lit;
        lit.num = ListeL->indispo+1;  // on inisitalise ici nos informations sur le lit
        lit.etat = OCCUPE;
        lit.patient = patientOB;
        ListeL->Tlit[ListeL->indispo] = lit; 
        int index = ListeL->indispo; 
        ListeL->indispo++;
        return ListeL->Tlit[index];
}


ListeObservation *AddObservation(Patient *patientEnConsultation, ListeObservation *ListeO, ListeLit *ListeL) {

    Observation *patientOB = (Observation*)malloc(sizeof(Observation));
        if(patientOB == NULL) {
            printf("Erreur : Impossible d'enregister une observation.\n");
            return ListeO;
        }
    printf("Veuillez indiquer la duree de l'observation : (En jour)");
    scanf("%d",&patientOB->duree);
    printf("Veuillez indiquer le traitement a suivre : ");
    scanf(" %[^\n]", patientOB->traitement);
    patientOB->lit = AddLit(patientOB,ListeL);
    if( ListeL->indispo >= ListeL->total) {
        printf("Erreur : Impossible d'atribuer un lit, Hopitale complet !"); // plus de lit dispo, on peut plus recevoir de patient pour les observer
        free(patientOB);
        return ListeO;
    }
    printf("Le patient est transeferer au lit %d.",patientOB->lit.num);

    patientOB->suivant = NULL; // onl l'ajoute a notre liste chainer de patient en observation
    if(ListeO == NULL) 
        ListeO->tete = patientOB;
    else {
    Observation *courant = ListeO->tete;
    while(courant->suivant != NULL) 
        courant = courant->suivant;
    courant->suivant = patientOB;
    }
    ListeO->compteur++;
    return ListeO;
}


void afficherObservation(ListeObservation *ListeO){
    Observation *tete=ListeO->tete;
    if (tete == NULL){
        printf("Aucun patient en observation.\n");
        return;
    }
    printf("Patients en observation :\n");
    while (tete != NULL){
        printf("Lit %d : %s %s\n", tete->lit.num, tete->patient->nom, tete->patient->prenom);
        tete=tete->suivant;
    }
}

Observation * supprimerObservation(ListeObservation *ListeO, int numlit){
    if( numlit < 0|| numlit > 100) {
        printf("Erreur : Numero invaliDE !");
        return NULL;
    }
    Observation *tete = ListeO->tete;
    Observation *temp=tete; // Pour pas perdre l'adresse a free
    if (tete->lit.num == 1){ // Enlever au debut de la liste chainer ListeObservation
        temp->patient->etat=SORTI;
        temp->lit.etat = NOCCUPE;
        tete=tete->suivant;
        free(temp); // On free de la liste chainer ListeObservation, Mais le patient est toujours present dans ListePatient
        return tete;
    }
    while( tete != NULL && tete->lit.num != numlit ) {
         tete=tete->suivant;
    }
    temp->patient->etat=SORTI;
    tete=tete->suivant;
    free(temp); // On free de la liste chainer ListeObservation, Mais le patient est toujours present dans ListePatient
    return tete;     
}

void transferer(Patient *patientEnConsult){
    printf("Saisi du nom du département de transfert : ");
    scanf(" %[^\n]",patientEnConsult->departement);
    patientEnConsult->etat=TRANSFERER;
    printf("Le patient %s %s a été transféré vers un departement de %s\n",patientEnConsult->prenom,patientEnConsult->nom, patientEnConsult->departement);
}


void verifierStatut(Patient *patientEnConsult){
    time_t maintenant = time(NULL);
    double secondesRestantes = difftime(patientEnConsult->heure.sorti, maintenant);

    printf("Patient : %s\n", patientEnConsult->nom);
    if (secondesRestantes > 0) {
        printf("Statut : En observation (Reste environ %d secondes)\n", secondesRestantes);
    } else {
        printf("Statut : Observation terminée. Le patient peut sortir.\n");
    }
}

