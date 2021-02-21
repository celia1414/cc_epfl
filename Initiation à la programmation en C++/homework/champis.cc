#include <iostream>
using namespace std;

int main() {
	bool ans1, ans2, ans3;
	
    cout << "Pensez à un champignon : amanite tue-mouches, pied bleu, girolle," << endl
         << "cèpe de Bordeaux, coprin chevelu ou agaric jaunissant." << endl << endl;
    cout << "Est-ce que votre champignon vit en forêt (1 : oui, 0 : non) ? ";
    cin >> ans1;
    cout << "Est-ce que votre champignon a un chapeau convexe (1 : oui, 0 : non) ? ";
    cin >> ans2;
    if (!ans1 && ans2) cout << "l'agaric jaunissant";
    else if (!ans1 && !ans2) cout << "==> Le champignon auquel vous pensez est le coprin chevelu";
    else if (ans1 && ans2) {
		cout << "Est-ce que votre champignon a un anneau (1 : oui, 0 : non) ? ";
		cin >> ans3;
		if (ans3) cout << "==> Le champignon auquel vous pensez est l'amanite tue-mouches";
		else cout << "==> Le champignon auquel vous pensez est le pied bleu";
	} else { // 10
		cout << "Est-ce que votre champignon a des lamelles (1 : oui, 0 : non) ? ";
		cin >> ans3;
		if (ans3)  cout << "==> Le champignon auquel vous pensez est la girolle";
		else cout << "==> Le champignon auquel vous pensez est le cèpe de Bordeaux";
	}

	return 0;
}
