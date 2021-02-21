#include <iostream>
#include <ctime>

// pour les nombres aléatoires
#include <random>
#include <cstring> // strlen

using namespace std;

// ======================================================================
// Couleur au hasard
std::uniform_int_distribution<int> distribution;
std::default_random_engine generateur(time(NULL)); /* NOT using std::random_device since not
                                                    * all compilers seems to support it :-( */

char tirer_couleur()
{
  static const char* const couleurs = ".RGBCYM";
  static const int nb = strlen(couleurs) - 1;

  return couleurs[distribution(generateur,
                               std::uniform_int_distribution<int>::param_type {0, nb})];
}

// ======================================================================
char poser_question()
{
  char lu(' ');
  cout << "Entrez une couleur : ";
  cin >> lu;
  return lu;
}

// ---- prototype -------------------------------------------------------
bool couleur_valide(char c);

// ======================================================================
char lire_couleur()
{
  char lu(poser_question());
  while (not couleur_valide(lu)) {
    cout << "'" << lu << "' n'est pas une couleur valide." << endl;
    cout << "Les couleurs possibles sont : ., R, G, B, C, Y ou M." << endl;
    lu = poser_question();
  }
  return lu;
}

// ======================================================================
void afficher_couleurs(char c1, char c2, char c3, char c4)
{
  cout << ' ' << c1 << ' ' << c2 << ' ' << c3 << ' ' << c4;
}

// ======================================================================
void afficher(int nb, char c)
{
  while (nb-- > 0) {
    cout << c;
  }
}

// ---- prototype -------------------------------------------------------
void afficher_reponses(char c1, char c2, char c3, char c4,
                       char r1, char r2, char r3, char r4);

// ======================================================================
void afficher_coup(char c1, char c2, char c3, char c4,
                   char r1, char r2, char r3, char r4)
{
  afficher_couleurs(c1, c2, c3, c4);
  cout << " : ";
  afficher_reponses(c1, c2, c3, c4,
                    r1, r2, r3, r4);
  cout << endl;
}

// ======================================================================
void message_gagne(int nb_coups)
{
  cout << "Bravo ! Vous avez trouvé en " << nb_coups << " coups." << endl;
}

// ======================================================================
void message_perdu(char c1, char c2, char c3, char c4)
{
  cout << "Perdu :-(" << endl;
  cout << "La bonne combinaison était : ";
  afficher_couleurs(c1, c2, c3, c4);
  cout << endl;
}

/*****************************************************
 * Compléter le code à partir d'ici
 *****************************************************/

// ======================================================================
bool couleur_valide(char c)
{
	if (c != 'R' && c != 'G' && c != 'B' && c != 'C' && c != 'Y' && c != 'M' && c != '.')
		return false;
	else return true;
}

// ======================================================================
bool verifier(char c1, char& c2, int &score)
{
	if (c1 == c2) {
		score++;
		c2 = 'x';
		return true;
	} else {
		//c2 = 'x';
		return false;
	}
}

// ======================================================================
void apparier(char c_propose, char &c_r1, char &c_r2, char &c_r3, int& num)
{
	if (!verifier(c_propose, c_r1, num)) {
		if (!verifier(c_propose, c_r2, num)) {
			if (!verifier(c_propose, c_r3, num))
				return;
		}
	}
}

// ======================================================================
void afficher_reponses(char c1, char c2, char c3, char c4,
                       char r1, char r2, char r3, char r4)
{
	int num_1(0);
	int num_2(0);
	
	if (c1 == r1) {
		r1 = 'x';
		num_1++;
	}
	if (c2 == r2) {
		r2 = 'x';
		num_1++;
	}
	if (c3 == r3) {
		num_1++;
		r3 = 'x';
	}
	if (c4 == r4) {
		num_1++;
		r4 = 'x';
	}
	
	if (c1 != r1) {
		int num(0);
		
		apparier(c1, r2, r3, r4, num);
		if (num != 0) num_2++;
	}
	if (c1 != r1) {
		int num(0);
		
		apparier(c1, r2, r3, r4, num);
		if (num != 0) num_2++;
	}
	if (c2 != r2) {
		int num(0);
		
		apparier(c2, r1, r3, r4, num);
		if (num != 0) num_2++;
	}
	if (c3 != r3) {
		int num(0);
		
		apparier(c3, r1, r2, r4, num);
		if (num != 0) num_2++;
	}
	if (c4 != r4) {
		int num(0);
		
		apparier(c4, r1, r2, r3, num);
		if (num != 0) num_2++;
	}
	
	afficher(num_1, '#');
	afficher(num_2, '+');
	afficher(4 - num_1 - num_2, '-');
	
}

// ======================================================================
bool gagne(char c1, char c2, char c3, char c4,
           char r1, char r2, char r3, char r4)
{
	if (c1 == r1 && c2 == r2 && c3 == r3 && c4 == r4) return true;
	else return false;
}

// ======================================================================
void jouer(int max = 8)
{
	char c1, c2, c3, c4;
	char r1 = tirer_couleur();
	char r2 = tirer_couleur();
	char r3 = tirer_couleur();
	char r4 = tirer_couleur();
	int time(0);
	
	do {
		c1 = lire_couleur();
		c2 = lire_couleur();
		c3 = lire_couleur();
		c4 = lire_couleur();
		
		afficher_coup(c1, c2, c3, c4, r1, r2, r3, r4);
		time++;
	} while (time <= max && !gagne(c1, c2, c3, c4, r1, r2, r3, r4));
	if (time > max) message_perdu(r1, r2, r3, r4);
	else message_gagne(time);
	
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  jouer();
  return 0;
}
