#ifndef ADMIN_H
#define ADMIN_H

#include "structure.h"

void gererlit(ListeLit *L);
void afficherstatistique(ListePatient *LP, ListeLit *LL, ListeUrgence *LU, Statistique *stat);
void afficherstock(ListeMedicament *LM);
void afficherstockequipement(ListeEquipement *LE);
void verfierfindeMedoc(ListeMedicament *LM, ListeEquipement *LE);
void ajoutermedicament(ListeMedicament *LM);
void ajouterequipement(ListeEquipement *LE);
void utilisermedicament(ListeMedicament *LM, char *nomUtilise);
void utiliserequipement(ListeEquipement *LE);
void fichiermedicament(ListeMedicament *LM);
void fichierequipement(ListeEquipement *LE);
void raffraichirmedicament(ListeMedicament *LM);
void raffraichirequipement(ListeEquipement *LE);

#endif