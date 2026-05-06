#ifndef ADMIN_H
#define ADMIN_H

#include "structure.h"

void gererlit(ListeLit *L);
void afficherstatistique(ListePatient *LP, ListeLit *LL, ListeUrgence *LU, Statistique *stat);
void saisirmedicament(ListeMedicament *LM, char fichiermedicaments[20]);
void afficherstock(ListeMedicament *LM);
void saisirequipement(ListeEquipement *LE, char fichierequipements[20]);
void afficherstockequipement(ListeEquipement *LE);
void verfierfindeMedoc(ListeMedicament *LM, ListeEquipement *LE);
void ajoutermedicament(ListeMedicament *LM, char fichiermedicaments[20]);
void ajouterequipement(ListeEquipement *LE, char fichierequipements[20]);
void utilisermedicament(ListeMedicament *LM, char fichiermedicaments[20]);
void utiliserequipement(ListeEquipement *LE, char fichierequipements[20]);
void fichiermedicament(ListeMedicament *LM, char fichiermedicaments[20]);
void fichierequipement(ListeEquipement *LE, char fichierequipements[20]);
void raffraichirmedicament(ListeMedicament *LM, char fichiermedicaments[20]);
void raffraichirequipement(ListeEquipement *LE, char fichierequipements[20]);
void menuequipement();
void menumedicament();

#endif