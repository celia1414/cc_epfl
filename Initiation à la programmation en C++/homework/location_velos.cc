#include <iostream>
using namespace std;

int main()
{
  cout << "Donnez l'heure de début de la location (un entier) : ";
  int debut;
  cin >> debut;

  cout << "Donnez l'heure de fin de la location (un entier) : ";
  int fin;
  cin >> fin;

  /*****************************************************
   * Compl矇ter le code �� partir d'ici
   *****************************************************/
	if (debut < 0 || debut > 24 || fin < 0 || fin > 24)
		cout << "Les heures doivent être comprises entre 0 et 24 !" << endl;
    else if (debut == fin)
		cout << "Bizarre, vous n’avez pas loué votre vélo bien longtemps !" << endl;
    else if (debut > fin)
		cout << "Bizarre, le début de la location est après la fin ..." << endl;
	else {
		int temp1(0);
		int temp2(0);
		
		cout << "Vous avez loué votre vélo pendant" << endl;
		if (debut < 7) {
			if (fin <= 7) temp1 = fin - debut;
			else if (fin > 7 && fin <= 17) {
				temp1 = 7 - debut;
				temp2 = fin - 7;
			}
			else { /* if fin > 17 */
				temp1 = (7 - debut) + (fin - 17);
				temp2 = 10;
			}
		} else if (debut >= 7 && debut < 17) {
			if (fin <= 17) temp2 = fin - debut;
			else { /* if  fin > 17 */
				temp1 = fin - 17;
				temp2 = 17 - debut;
			}
		} else { /* if debut >= 17 */
			temp1 = fin - debut;
		}
	 int total = temp1 + temp2 * 2;
     if (temp1 > 0) {
		cout << temp1 << " heure(s) au tarif horaire de "
			 << "1 franc(s)" << endl;}
	 if (temp2 > 0) {
	    cout << temp2 << " heure(s) au tarif horaire de "
             << "2 franc(s)" << endl;}

     cout << "Le montant total à payer est de " 
          << total << " franc(s)." << endl;
	 }

  /*******************************************
   * Ne rien modifier apr癡s cette ligne.
   *******************************************/

  return 0;
}
