#ifndef ADMIN_H
#define ADMIN_H

#include "structure.h"

void gererlit(ListeLit *L);
void afficherstatistique(ListePatient *LP, ListeLit *LL, ListeUrgence *LU);
void saisirmedicament(ListeMedicament *LM);
void afficherstock(ListeMedicament *LM);
void saisirequipement(ListeEquipement *LE);
void afficherstockequipement(ListeEquipement *LE);
void verfierfindeMedoc(ListeMedicament *LM, ListeEquipement *LE);
void ajoutermedicament(ListeMedicament *LM);
void ajouterequipement(ListeEquipement *LE);
void utilisermedicament(ListeMedicament *LM);
void utiliserequipement(ListeEquipement *LE);

#endif