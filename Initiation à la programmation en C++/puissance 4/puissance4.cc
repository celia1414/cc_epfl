// Lab08. Puissance 4.
// Feb. 3, 2021
// b08901214 Célia

#include <stdio.h>
#include <array>
#include <iostream>
using namespace std;

enum Couleur { vide, rouge, jaune };
typedef array<array<Couleur, 7>, 6> Grille;

void initialise(Grille& grille);
void affiche(const Grille& grille);	// pour eviter la copie
bool joue(Grille& grille, size_t colonne, Couleur couleur);
void demande_et_joue(Grille& grille, Couleur couleur_joueur);
bool est_ce_gagne(const Grille& grille, Couleur couleur_joueur);
unsigned int compte(const Grille& grille, size_t ligne_depart,
					size_t colonne_depart, int dir_ligne, int dir_colonne);
bool plein(const Grille& grille);

void initialise(Grille& grille)
{
	for (auto& ligne : grille) {
		for (auto& kase : ligne) {
			kase = vide;
		}
	}
	return;
}

void affiche(const Grille& grille)
{
	for (auto ligne : grille) {
		cout << " |";
		for (auto kase : ligne) {
			switch(kase) {
				case  vide: cout << ' '; break;
				case rouge: cout << 'O'; break;
				case jaune: cout << 'X';
			}
			cout <<'|';
		}
		cout << endl;
	}
	printf("==");
	for (int i = 1; i <= 7; i++) printf("%d=", i);
	printf("=\n");
	return;
}

bool joue(Grille& grille, size_t colonne, Couleur couleur)
{
	size_t ligne = grille.size() - 1;

	if (colonne > grille[0].size()) return false;
	colonne--;
	if (grille[0][colonne] != vide) return false;
	while (grille[ligne][colonne] != vide) {
		ligne--;
	}
	grille[ligne][colonne] = couleur;
	return true;
}

void demande_et_joue(Grille& grille, Couleur couleur_joueur)
{
	bool valide;

	printf("\nJoueur ");
	if (couleur_joueur == rouge) printf("O");
	else printf("X");
	printf(" : entrez un numéro de colonne > ");
	do {
		size_t colonne;

		cin >> colonne;
		valide = joue(grille, colonne, couleur_joueur);
		if (!valide) printf("> Ce coup n'est pas valide\n");
	} while (!valide);
	return;
}

bool est_ce_gagne(const Grille& grille, Couleur couleur_joueur)
{
	for (size_t ligne(0); ligne < grille.size(); ligne++) {
		for (size_t colonne(0); colonne < grille[ligne].size(); colonne++) {
			Couleur couleur_case(grille[ligne][colonne]);

			if (couleur_case == couleur_joueur) {
				if (// en diagonale, vers le haut et la droite:
					compte(grille, ligne, colonne, -1, 1) >= 4 ||
					// horizontale, vers la droite:
					compte(grille, ligne, colonne,  0, 1) >= 4 ||
					// en diagonale, vers le bas et la droite:
					compte(grille, ligne, colonne,  1, 1) >= 4 ||
					// verticalement, vers le bas:
					compte(grille, ligne, colonne,  1, 0) >= 4
				) return true;
			}
		}
	}
	return false;
}

unsigned int compte(const Grille& grille, size_t ligne_depart,
					size_t colonne_depart, int dir_ligne, int dir_colonne)
{
	unsigned int compteur(0);
	size_t ligne(ligne_depart);
	size_t colonne(colonne_depart);
	bool valide = true;

	while (valide && (grille[ligne][colonne] == grille[ligne_depart][colonne_depart])) {

		compteur++;
		ligne   += dir_ligne;
		colonne += dir_colonne;
		valide = (ligne < grille.size()) && (colonne < grille[ligne].size());
	}
	//cout << "count: " << compteur << endl;
	return compteur;
}

bool plein(const Grille& grille)
{
	for (auto ligne: grille)
		for (auto kase: ligne) 
			if (kase != vide) return false;
	return true;
}

int main(void)
{
	Grille grille;
	Couleur couleur_joueur(jaune);
	bool gagne;

	initialise(grille);
	do {
		if (couleur_joueur == jaune) couleur_joueur = rouge;
		else couleur_joueur = jaune;
		demande_et_joue(grille, couleur_joueur);
		affiche(grille);
		gagne = est_ce_gagne(grille, couleur_joueur);
	} while (!gagne && !plein(grille));
	if (gagne) {
		if (couleur_joueur == rouge) 
			printf("Le joueur O a gagné !\n");
		else printf("Le joueur X a gagné !\n");
	} else printf("Match nul !\n");
	return 0;
}
