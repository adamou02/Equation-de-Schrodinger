/** Fonction principale
  * @author Romain DUJOL
  */

#include <gsl/gsl_errno.h>
#include <gsl/gsl_vector.h>
#include "consts.h"
#include "equadiff.h"
#include "tir.h"

int main() {
    double m = M_ELEC ;
    double l = 10.0 ; // nm
    int n = 1 ;

    /* Construction des parametres de l'equation differentielle */
    potentiel_params_type potentiel = {NUL, 0.0, 0.0, 0.0} ;
     equadiff_params_type equadiff  = {m, 0.0, &potentiel} ;
    /* Construction des parametres de la fonction de tir */
         ftir_params_type tir       = {l, &equadiff} ;

    /* Calcul de la solution theorique dans le cas du potentiel nul */
    gsl_vector *ez = theorique_potentielnul(n, l, m) ;
    int status = cherche_ez(100, ez, &tir) ;
    if (status == GSL_SUCCESS) {
         status = ecrire_gnuplot("schrodinger.dat", ez, l, 100, &equadiff) ;
      }
    else {
        printf("La resolution a echoue. Message d'erreur de GSL :\n") ;
        printf("   %s\n", gsl_strerror(status)) ;
      }

    return 0 ;
  }
