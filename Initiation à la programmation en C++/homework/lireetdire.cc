#include <iostream>
using namespace std;

int separer_chiffre_gauche(int& nombre)
{
  int dix(1);
  int temp(nombre);
  while (temp >= 10) {
    dix  *= 10;
    temp /= 10;
  }
  nombre %= dix;
  return temp;
}

/*****************************************************
 * Compléter le code à partir d'ici
 *****************************************************/

void ajouter_chiffre_droit(int& nombre, int chiffre)
{
	nombre = nombre * 10 + chiffre;
}

void dire_chiffre(int& nombre, int repetitions_chiffre, int chiffre)
{
	ajouter_chiffre_droit(nombre, repetitions_chiffre);
	ajouter_chiffre_droit(nombre, chiffre);
}

int lire_et_dire(int nombre)
{
	int repetitions_chiffre(1);
	int chiffre_1(0), chiffre_2(0);
	int return_nombre(0);
	//int i(0);
	// cout << "nombre: " << nombre << endl;
	chiffre_1 = separer_chiffre_gauche(nombre);
	while(nombre) {
		chiffre_2 = separer_chiffre_gauche(nombre);	
		if (chiffre_1 == chiffre_2) {
			repetitions_chiffre++;
		}
		else {
			dire_chiffre(return_nombre, repetitions_chiffre, chiffre_1);
			repetitions_chiffre = 1;
		}
		chiffre_1 = chiffre_2;
		// i++;
		// cout << "nombre: " << nombre << endl;
		// cout << "return_nombre: " << return_nombre << endl;
	}
	dire_chiffre(return_nombre, repetitions_chiffre, chiffre_1);
	return return_nombre;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void repeter_lire_et_dire(int& nombre, int fois)
{
  while (fois-- > 0) {
    nombre = lire_et_dire(nombre);
  }
}

int main()
{
  int nombre(1);
  int fois(1);
  cin >> nombre >> fois;
  repeter_lire_et_dire(nombre, fois);
  cout << nombre << endl;
  return 0;
}
