#include <iostream>
#include <iomanip> // pour setprecision()
using namespace std;

int main()
{
  // Réduire le format d'affichage
  cout << setprecision(4);

  // Paramètres
  double taux_croissance_lapins(0.3);
  double taux_attaque(0.01);
  double taux_croissance_renards(0.008);
  double taux_mortalite(0.1);
  int duree(50);

  double renards_i(0.0);
  double lapins_i(0.0);

  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/

  // ===== PARTIE 1 =====
  // Saisie des populations initiales
  double renards, lapins;
  while (renards_i < 2) {
	cout << "Combien de renards au départ (>= 2) ? ";
	cin >> renards_i;
	renards = renards_i;
  }
  while (lapins_i < 5) {
	cout << "Combien de lapins au départ  (>= 5) ? ";
	cin >> lapins_i;
	lapins = lapins_i;
  }
  // ===== PARTIE 2 =====
  // Première simulation
  cout <<  endl << "***** Le taux d'attaque vaut "<< taux_attaque * 100 << "%" <<  endl;
  int m = 1;
  
  while (m <= duree) {
	double temp_lp = lapins_i;
	lapins_i *= (1.0 + taux_croissance_lapins - taux_attaque * renards_i );
	renards_i *= (1.0 + taux_attaque * temp_lp * taux_croissance_renards - taux_mortalite);
	if (lapins_i < 0) lapins_i = 0;
	if (renards_i < 0) renards_i = 0;
	cout << "Après " << m << " mois, il y a " 
		 << lapins_i << " lapins et " << renards_i << " renards"<< endl;
	m++;
  }
  // ===== PARTIE 3 =====
  // Variation du taux d'attaque
  double debut(0);
  double fin(0);
  
  cout << endl;
  while (debut < 0.5 || debut > 6) {
	cout << "taux d'attaque au départ en % (entre 0.5 et 6) ? ";
	cin >> debut;
  }
  while (fin < debut || fin > 6) {
	cout << "taux d'attaque à la fin  en % (entre " << debut;
	cout << " et 6) ? ";
	cin >> fin;
  }
  
  for (double i = debut; i < fin; i += 1) {
  renards_i = renards;
  lapins_i = lapins;
  cout << endl << "***** Le taux d'attaque vaut "<< i << "%" <<  endl;
  taux_attaque = i / 100;
  int m = 1;
  bool stop = 0;
  bool r_goextinct = 0;
  bool r_remontee = 0;
  bool r_disparu = 0;
  bool l_goextinct = 0;
  bool l_remontee = 0;
  bool l_disparu = 0;
  
  
  while (m <= duree && !stop) {
	double temp_lp = lapins_i;
	lapins_i *= (1.0 + taux_croissance_lapins - taux_attaque * renards_i );
	renards_i *= (1.0 + taux_attaque * temp_lp * taux_croissance_renards - taux_mortalite);
	/*cout << "Après " << m << " mois, il y a " 
		 << lapins_i << " lapins et " << renards_i << " renards"<< endl;*/
	if (lapins_i < 0) lapins_i = 0;
	if (renards_i < 0) renards_i = 0;
	if (renards_i < 0) renards_i = 0;
	if (renards_i < 5) r_goextinct = 1;
	if (lapins_i < 5) l_goextinct = 1;
	if (r_goextinct && renards_i > 5) r_remontee = 1;
	if (l_goextinct && lapins_i > 5) l_remontee = 1;
	if (renards_i < 2) {
		r_disparu = 1;
		renards_i = 0;
	}
	if (lapins_i < 2) {
		l_disparu = 1;
		lapins_i = 0;
	}
	if (r_disparu && l_disparu) stop = 1;
	m++;
  }
  cout << "Après " << m-1 << " mois, il y a " 
		 << lapins_i << " lapins et " << renards_i << " renards"<< endl;
  if (r_goextinct) {
	  cout << "Les renards ont été en voie d'extinction" << endl;
	  if (r_remontee) cout << "mais la population est remontée ! Ouf !" << endl;
      if (r_disparu) cout << "et les renards ont disparu :-(" << endl;
  }
  if (l_goextinct) {
	  cout << "Les lapins ont été en voie d'extinction" << endl;
      if (l_remontee) cout << "mais la population est remontée ! Ouf !" << endl;
	  if (l_disparu) cout << "et les lapins ont disparu :-(" << endl;
  }
  if (!r_disparu && !l_disparu) cout << "Les lapins et les renards ont des populations stables." << endl;
}	
  /*******************************************
   * Ne rien modifier après cette ligne.
   *******************************************/

  return 0;
}
