#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

// Equipements
void ajouterEquipement(ListeEquipement *liste);
void afficherEquipements(ListeEquipement *liste);
void modifierEtatEquipement(ListeEquipement *liste, int index);

// Medicaments
void ajouterMedicament(ListeMedicament *liste);
void afficherMedicaments(ListeMedicament *liste);
void utiliserMedicament(ListeMedicament *liste, int index, int quantite);
void verifierStockBas(ListeMedicament *liste); // alerte si quantite < quantiteMin