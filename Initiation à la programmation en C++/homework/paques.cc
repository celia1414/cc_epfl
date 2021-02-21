// Lab04-2. Date de Paques

#include <iostream>
using namespace std;

int demander_annee(void);
void affiche_date(int year, int num);
int date_Paques(int year);

int main(void)
{
	int annee(0);
	
	annee = demander_annee();
	affiche_date(annee, date_Paques(annee));
	return 0;
}

int demander_annee(void) 
{
	int annee(0);
	
	while (annee < 1583 || annee > 4000) {
		cout << "Entrez une annee (1583-4000) : ";
		cin >> annee;
	}
	return annee;
}

void affiche_date(int year, int num)
{
	if (num <= 31) {
		cout << "Date de Paques en " << year << " : " 
				 << num << " mars" << endl;
	} else {
		cout << "Date de Paques en " << year << " : "
				 << num - 31 << " avril" << endl;
	}
	
	return;
}

int date_Paques(int year)
{
	int siecle = year / 100;
	int p = (13 + 8 * siecle) / 25;
	int q = siecle / 4;
	int M = (15 - p + siecle - q) % 30;
	int N = (4 + siecle - q) % 7;
	int d = (M + 19 * (year % 19)) % 30;
	int e = (2 * (year % 4) + 4 * (year % 7) + 6 * d + N) % 7;
	int num = e + d + 22;
	
	if (e == 6 && (d == 29 || (d == 28 && (11 * (M + 1)) % 30 < 19)))
		num -= 7;
	
	return num;
}
