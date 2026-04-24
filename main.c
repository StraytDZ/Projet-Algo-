#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "reception.h"
#include "medecin.h"
#include "menu.h"
#include "observation.h"



int main() {
    int lit=0;
    int choix,choixReception,choixMedecin,choixConsult;
    ListePatient patient = {NULL, 0, 0, 0, 0, 0};
    ListeTicket ticket = {NULL, 0};
    Patient *PatientEnConsult;
    do {
        menuPrincipal();
        scanf("%d",&choix);
        switch(choix) {
            case 1 : 
                do {
                     menuMedecin();
                     scanf("%d",&choixMedecin);
                     switch(choixMedecin) {
                        case 1 : 
                            PatientEnConsult = CallPatient(&ticket);
                            do{
                                menuConsultation();
                                scanf("%d",&choixConsult);
                                switch(choixConsult) {
                                    case 1 : 
                                        PatientDiagnostic(PatientEnConsult);
                                    break;
                                    case 2 : 
                        }
                    }while(choixReception != 3);
            break;
        }  
    }while(choix != 3);
    return 0;
}
}
}