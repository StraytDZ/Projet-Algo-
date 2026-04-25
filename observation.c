#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "observation.h"
#include "structure.h"

//==================================================================================================================================
//============================================================CHIHAB================================================================
Lit *CreateLit(ListeLit* ListeL) { // Fonciton juste pour cree le ' noeud ', ici on ne l'ajoute pas encore vers notre 'lsite de noeud' (ListeLit)
    if(ListeL->indispo >= ListeL->total ) {  // Si on depasse le nombre de lit disponible dans l'hopitale, tel que ListeL->total est donner dans le main,
        printf("Erreur : plus de lit disponible !\n");
        return NULL; 
    }

    Lit *lit =(Lit*)malloc(sizeof(Lit)); // on crée le lit
        if(lit == NULL) {
            printf("Erreur : Impossible de donner un lit");
            return lit;
        }
        lit->num = ListeL->indispo+1; // on inisitalise ici nos informations sur le lit
        lit->etat = NOCCUPE;
        lit->patient = NULL;
        lit->suivant = NULL;
        if(ListeL->tete == NULL) {
            ListeL->tete = lit;
            ListeL->indispo++;
            return lit;
        }
        Lit *courant = ListeL->tete;
        while(courant->suivant != NULL) 
            courant = courant->suivant;
        
        courant->suivant = lit;
        ListeL->indispo++;
        return lit;
}
Lit *AddLit(ListeObservation *patientOB, ListeLit *ListeL) {

    Lit *lit = ListeL->tete; // Juste pour ne pas ecrire a chaque fois ListeL->tete
    while(lit != NULL && lit->etat == OCCUPE) { // si aucun lit n'est libre + n'est pas NULL
        lit = lit->suivant;
    }
    if(lit == NULL) { // si aucun lit libre n'as été trouver, on cree un nouveau lit
        lit = CreateLit(ListeL);
        if(lit == NULL) return NULL;  
    }
    lit->patient = patientOB;
    lit->etat = OCCUPE; // le lit a été donner, on change son etat

    return lit;
    
}

ListeObservation *AddObservation(Patient *patientEnConsultation, ListeObservation *tete, ListeLit *ListeL) {

    Observation *patientOB = (Observation*)malloc(sizeof(Observation));
        if(patientOB == NULL) {
            printf("Erreur : Impossible d'enregister une observation.\n");
            return tete;
        }
    printf("Veuillez indiquer la duree de l'observation : (En jour)");
    scanf("%d",&patientOB->duree);
    printf("Veuillez indiquer le traitement a suivre : ");
    scanf(" %[^\n]", patientOB->traitment);
    patientOB->lit = AddLit(patientOB,ListeL);
    if( patientOB->lit == NULL ) {
        printf("Erreur : Impossible d'atribuer une lit, Hopitale complet !"); // plus de lit dispo, on peut plus recevoir de patient pour les observer
        free(patientOB);
        return tete;
    }
    printf("Le patient est transeferer au lit %d.",patientOB->lit->num);

    patientOB->suivant = NULL; // onl l'ajoute a notre liste chainer de patient en observation
    if(tete == NULL) return patientOB;

    Observation *courant = tete;
    while(courant->suivant != NULL) 
        courant = courant->suivant;
    courant->suivant = patientOB;
    return tete;
}





//==================================================================================================================================
//============================================================JUBA==================================================================

void choixlit(Patient *patientEnConsult,ListeObservation ** liste, Observation ** lits){

    int temp;
    printf("veillez choisir un lit pour le patient %s %s : ", patientEnConsult->prenom, patientEnConsult->nom);
    scanf("%d", &temp);
    while (temp<1 || temp>100){
        printf("Numéro de lit invalide. Veuillez choisir un numéro entre 1 et 100.\n");
        scanf("%d", &temp);
    } 
    Observation *tempObservation=*lits;
    while (tempObservation!=NULL && tempObservation->numlit!=temp){
        tempObservation=tempObservation->suivant;
    }
    if (tempObservation != NULL){
        printf("Ce lit est déjà occupé. Veuillez choisir un autre lit.\n");
        choixlit(patientEnConsult,liste, lits);
    }
    else{
        *lits=donnerlit(patientEnConsult, *lits, temp);
        (*liste)->compteur=(*liste)->compteur+1;
        printf("Le patient %s %s a été placé en observation dans le lit %d.\n", patientEnConsult->prenom, patientEnConsult->nom, temp);
    }
}

void afficherObservation(Observation *lits){
    Observation *temp=lits;
    if (temp==NULL){
        printf("Aucun patient en observation.\n");
        return;
    }
    printf("Patients en observation :\n");
    while (temp!=NULL){
        printf("Lit %d : %s %s\n", temp->numlit, temp->patient->prenom, temp->patient->nom);
        temp=temp->suivant;
    }
}

Observation * donnerlit(Patient *patientEnConsult, Observation *lits, int numerolit){
    Observation *lit=malloc(sizeof(Observation));
    if (lit == NULL) {
        printf("Erreur : plus de mémoire pour les lits.\n");
        return lits;
    } 
    
    lit->suivant=NULL;
    lit->numlit=numerolit;
    lit->patient=patientEnConsult;
    Observation *temp=lits;
    if (temp==NULL){
        return lit;    
    }
    else{
        while (temp->suivant!=NULL){
            temp=temp->suivant;
        }
        temp->suivant=lit;     
    }
    return lits;   
}

Observation * supprimerObservation(Observation *lits, int numlit){
    Observation *lit = lits;
    if (lit->numlit==numlit){
        Observation *temp=lit;
        lit=lit->suivant;
        temp->patient->etat=SORTI;
        temp->suivant=NULL;
        free(temp);
        return lit;
    }
    while( lit->suivant!=NULL && lit->suivant->numlit!=numlit) {
         lit=lit->suivant;
    }
    Observation *temp=lit->suivant;
    lit->suivant=lit->suivant->suivant;
    temp->suivant=NULL;
    temp->patient->etat=SORTI;
    free(temp);
    return lits;     
}

void transferer(Patient *patientEnConsult){
    printf("Saisi du nom du département de transfert : ");
    scanf(" %[\n]",patientEnConsult->departement);
    patientEnConsult->etat=TRANSFERER;
    printf("Le patient %s %s a été transféré vers un departement de %s\n",patientEnConsult->prenom,patientEnConsult->nom, patientEnConsult->departement);
}

void saisirduree(Patient *patientEnConsult){
    int duree;
    printf("Saisi de la durée d'observation (en jours) : ");
    scanf("%d",&duree);
    time_t currentTime = time(NULL);
    patientEnConsult->heure.arrive = currentTime;
    patientEnConsult->heure.sorti = currentTime+duree*24*3600; 
}

void  modifierdiagnostique(Patient *patientEnConsult){
    printf("Saisi du nouveau diagnostique : ");
    scanf(" %[\n]",patientEnConsult->diagnostique);
}

void  modifiertraitement(Patient *patientEnConsult){
    printf("Saisi du nouveau traitement : ");
    scanf(" %[\n]",patientEnConsult->traitement);
}

void  modifierordonnance(Patient *patientEnConsult){
     printf("Saisi de la nouvelle ordonnance : ");
     scanf(" %[\n]",patientEnConsult->ordonnance);
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

