================================================================
        SYSTEME DE GESTION D'URGENCE HOSPITALIERE
         Documentation des fonctions par section
================================================================

----------------------------------------------------------------
                     SECTION : RECEPTION
----------------------------------------------------------------

  1 - Enregistrer un patient
        > Saisir : Nom, Prenom, ID, Age, Sexe (Etat par defaut : ATTENTE)
        > Creer un ticket numerote automatiquement
        > Ajouter le patient a la file d'attente

  2 - Rechercher un patient
        > Par Nom / Prenom
        > Par numero de ticket

  3 - Afficher la file d'attente
        > Lister tous les patients en attente
        > Afficher leur numero de ticket

  4 - Afficher la liste des patients en observation
        > Lister les patients actuellement en observation
        > Afficher : Nom, Lit, Traitement, Duree

  5 - Afficher l'historique des patients
        > Lister tous les patients ayant consulte
        > Afficher leur date de consultation

----------------------------------------------------------------
                      SECTION : MEDECIN
----------------------------------------------------------------

  1 - Appeler le prochain patient
        > Recuperer le premier patient de la file d'attente
        > Afficher ses informations

  2 - Enregistrer la consultation
        > Saisir le diagnostic
        > Saisir le traitement prescrit
        > Marquer le patient comme consulte (Etat : CONSULTATION)

  3 - Observation
        3.1 - Mettre en observation un patient
                > Assigner un lit
                > Saisir le traitement
                > Saisir la duree d'observation

        3.2 - Modifier l'observation d'un patient
                > Modifier le traitement
                > Modifier le lit
                > Modifier la duree

        3.3 - (A definir)

----------------------------------------------------------------
                    OBSERVATIONS A FAIRE
----------------------------------------------------------------

  - Gestion de la memoire (free) apres chaque liberation de patient
  - Verifier les cas limites : file vide, patient introuvable...ect
  - Sauvegarder les donnees dans un fichier

================================================================