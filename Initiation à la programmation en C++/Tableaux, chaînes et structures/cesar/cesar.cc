// b08901214, Célia
// 16, janvier, 2021
// Cryptage de Jules César

#include <iostream>
#include <string>
using namespace std;

char code(char c, int d);
char decale(char c, char debut, int decalage);
string code(string s, int d);
string decode(string s, int d);

char decale(char c, char debut, int decalage) {
	while (decalage < 0) decalage += 26;
	return debut + (((c - debut) + decalage) % 26);
}

char code(char c, int d) {
	if (c >= 'a' && c <= 'z') return decale(c, 'a', d);
	else if (c >= 'A' && c <= 'Z') return decale(c, 'A', d);
	else return c;
}

string code(string s, int d) {
	size_t i;
	string newstring = s;
	
	for (i = 0; i < s.size(); i++) {
		newstring[i] = code(s[i], d);
		cout << newstring[i];
	}
	return newstring;
}

string decode(string s, int d) {
	return code(s, -d);
}

int main(void) {
/*	string input;
	int decalage;
	
	cout << "enter phrase: ";
	getline(cin, input);
	cout << "enter decalage: ";
	cin >> decalage;
	
	cout << "result: " << decode(input, decalage) << endl;
	
	return 0;
*/
}
