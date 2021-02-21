#include <iostream>
#include <vector>
using namespace std;

/*******************************************
 * Complétez le programme à partir d'ici.
 *******************************************/
typedef vector<vector<int>> Carte;
struct Position
{
	int i;	// un indice de ligne
	int j;	// un indice de colonne
};
bool binaire(Carte const& carte);
void affiche(Carte const& carte);
bool verifie_et_modifie(Carte& carte);
double longueur_cloture(Carte const& carte, double echelle = 2.5);
void marque_composantes(Carte& carte);
void ajoute_unique(vector<int>& ensemble, int valeur);
bool convexite_lignes(Carte& carte, vector<int> const& labels_bords);
bool convexite_lignes(Carte& carte);

/* 3.4 Le code à produire */
bool binaire(Carte const& carte) 
{
	size_t  i, j;
	bool flag = 1;

	for (i = 0; flag && i < carte.size(); i++) {
		for (j = 0; flag && j < carte[i].size(); j++) {
			if (carte[i][j] != 0 && carte[i][j] != 1) 
				flag = 0;
		}
	}
	return flag;
}

void affiche(Carte const& carte) 
{
	size_t i, j;
	
	for (i = 0; i < carte.size(); i++) {
		for (j = 0; j < carte[i].size(); j++) {
			cout << carte[i][j];
		}
		cout << endl;
	}
	cout << endl << "----" << endl;
	return;
}

bool verifie_et_modifie(Carte& carte) 
{
	bool bin = binaire(carte);
	bool con = convexite_lignes(carte);
	
	if (bin && con) {
		return true;
	} else if (!bin) {
		cout << "Votre carte du terrain ne contient pas que des 0 et des 1." << endl;
		return false;
	} else {
		return con;
	}
}

double longueur_cloture(Carte const& carte, double echelle) 
{
	double total = 0;

	for (size_t i = 0; i < carte.size(); i++) {
		for (size_t j = 0; j < carte[i].size(); j++) {
			if (carte[i][j] == 1) {
				if (i > 0 && carte[i - 1][j] != 1) total++;
				if (i + 1 < carte.size() && carte[i + 1][j] != 1) total++;
				if (j > 0 && carte[i][j - 1] != 1) total++;
				if (j + 1 < carte[i].size() && carte[i][j + 1] != 1) total++;
				if (i == 0) total++;
				if (i == carte.size() - 1) total++;
				if (j == 0) total++;
				if (j == carte[i].size() - 1) total++;
			}
		}
	}
	return total * echelle;
}

/* 3.5 Vérification de la convexité par lignes */
void marque_composantes(Carte& carte) 
{
	vector<Position> tab;	// stocker les coordonées des pointes
	int composante(1);		// compter & étiqueter les différentes zone de 0
	
	for (size_t i = 0; i < carte.size(); i++) {
		for (size_t j = 0; j < carte[i].size(); j++) {
			if (carte[i][j] == 0) {
				composante++;
				Position point;
				point.i = i;
				point.j = j;
				tab.push_back(point);
				while (!tab.empty()) {
					Position point1;
					point1.i = tab.back().i;
					point1.j = tab.back().j;
					tab.pop_back();
					if (carte[point1.i][point1.j] == 0) {
						carte[point1.i][point1.j] = composante;
						if (point1.j - 1 > -1) {
							if (carte[point1.i][point1.j - 1] == 0) {
								Position point2;
								point2.i = point1.i;
								point2.j = point1.j - 1;
								tab.push_back(point2);
							}
						}
						if (point1.j + 1 < carte[i].size()) {
							if (carte[point1.i][point1.j + 1] == 0) {
								Position point2;
								point2.i = point1.i;
								point2.j = point1.j + 1;
								tab.push_back(point2);
							}
						}
						if (point1.i - 1 > -1) {
							if (carte[point1.i - 1][point1.j] == 0) {
								Position point2;
								point2.i = point1.i - 1;
								point2.j = point1.j;
								tab.push_back(point2);
							}
						}
						if (point1.i + 1 < carte.size()) {
							if (carte[point1.i + 1][point1.j] == 0) {
								Position point2;
								point2.i = point1.i + 1;
								point2.j = point1.j;
								tab.push_back(point2);
							}
						}
					}
				}
			}
		}
	}
}

void ajoute_unique(vector<int>& ensemble, int valeur)
{
	bool flag = 1;

	for (size_t i = 0; flag && i < ensemble.size(); i++) {
		if (ensemble[i] == valeur) flag = 0;
	}
	if (flag) ensemble.push_back(valeur);
	return;
}

bool convexite_lignes(Carte& carte, vector<int> const& labels_bords)
{
	for (size_t i = 0; i < carte.size(); i++) {
		for (size_t j = 0; j < carte[i].size(); j++) {
			if (carte[i][j] != 1) {
				bool flag = 1;
				for (size_t k = 0; flag && k < labels_bords.size(); k++) {
					if (labels_bords[k] == carte[i][j]) flag = 0;
				}
				if (flag) carte[i][j] = 1;
				else {
					if (carte[i][j - 1] == 1) {
						size_t jt = j;
						while (j + 1 < carte[i].size()) {
							if (carte[i][++j] == 1) {
								cout << "Votre carte du terrain n'est pas convexe par lignes :" << endl;
          						cout << "bord extérieur entrant trouvé en position [";
								cout << i << "][" << jt;
          						cout << "]" << endl;
								return false;
							}
						}
					}
				}
			}
		}
	}
	return true;
}

bool convexite_lignes(Carte& carte)
{
	vector<int> labels_bords;

	marque_composantes(carte);
	// affiche(carte);
	for (size_t i = 0; i < carte.size(); i++) 
		if (carte[i][0] != 1) ajoute_unique(labels_bords, carte[i][0]);
	for (size_t j = 0; j < carte[0].size(); j++) 
		if (carte[0][j] != 1) ajoute_unique(labels_bords, carte[0][j]);
	for (size_t i = 0; i < carte.size(); i++) 
		if (carte[i][carte[0].size() - 1] != 1) 
			ajoute_unique(labels_bords, carte[i][carte[0].size() - 1]);
	for (size_t j = 0; j < carte[0].size(); j++)
		if (carte[carte.size() - 1][j] != 1) 
			ajoute_unique(labels_bords, carte[carte.size() - 1][j]);
	return convexite_lignes(carte, labels_bords);
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Carte carte = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };

  cout << "Carte au départ :" << endl;
  affiche(carte);
  if (verifie_et_modifie(carte)) {
    cout << "Carte après modification :" << endl;
    affiche(carte);
    cout << "Il vous faut " << longueur_cloture(carte)
         << " mètres de clôture pour votre terrain."
         << endl;
  }

  return 0;
}
