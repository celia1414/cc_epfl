#include <iostream>
#include <vector>
using namespace std;

int somme_consecutifs_max(vector<int> tab);
vector<size_t> lignes_max(vector<vector<int>> tab2);
vector<vector<int>> tranches_max(vector<vector<int>> tab2);

int somme_consecutifs_max(vector<int> tab) {
	size_t i(0);
	int somme(0);
	int max(0);

	for(i = 0; i < tab.size(); i++) {
		if (tab[i] != 0) {
			somme += tab[i];
		} else somme = 0;
		if (somme > max) max = somme;
	}
	return max;
}

vector<size_t> lignes_max(vector<vector<int>> tab2) {
	size_t i(0);
	int max(0);
	vector<size_t> rows;

	for (i = 0; i < tab2.size(); i++) {
		int somme = somme_consecutifs_max(tab2[i]);
		if (max < somme) {
			max = somme;
			rows.clear();
			rows.push_back(i);
		} else if (somme == max) rows.push_back(i);
	}
	return rows;
}

vector<vector<int>> tranches_max(vector<vector<int>> tab2) {
	vector<vector<int>> new_tab;
	vector<size_t> max_tab;
	size_t i(0);

	max_tab = lignes_max(tab2);
	for (i = 0; i < max_tab.size(); i++) {
		new_tab.push_back(tab2[max_tab[i]]);
	}
	return new_tab;
}

int main(void) {
/*	vector<int> tab0({6, 3, 1, 5, 0, 0, 0, 1, 4});
	vector<vector<int>> tab1( {{1, 1, 0, 1}, // 3
							   {1, 3, 2, 0}, // 6
							   {1, 2, 3, 0},
							   {2, 0, 0, 1}} // 2
							);
	vector<vector<int>> tab3( {} );
	vector<vector<int>> tab4( {
		{2, 1, 0, 2, 0, 3, 2},
		{0, 1, 0, 7, 0},
		{1, 0, 1, 3, 2, 0, 3, 0, 4},
		{5, 0, 5},
		{1, 1, 1, 1, 1, 1, 1}
	}
	);
	vector<size_t> tab_val = lignes_max(tab3);
	for (auto elt : tab_val) {
		cout << elt << ' ';
	}
	cout << endl;
	vector<vector<int>> tab_final = tranches_max(tab3);
	for (auto ligne : tab_final) {
		for (auto elt : ligne) {
			cout << elt << " ";
		}
		cout << endl;
	}
	return 0;
*/
}

