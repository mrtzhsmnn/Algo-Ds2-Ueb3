// Beispiel zur Verwendung von Containern der C++-Standardbibliothek

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <utility>	// pair
using namespace std;

int main () {
    // Liste mit Elementen des Typs string.
    // Der parameterlose Konstruktor, der automatisch aufgerufen wird,
    // wenn es keine explizite Initialisierung gibt, erstellt eine
    // leere Liste.
    list<string> ls;

    // push_front bzw. push_back fügt ein Element am Anfang bzw.
    // am Ende der Liste ein.
    ls.push_back("zwei");
    ls.push_back("drei");
    ls.push_front("eins");

    // Alternativ kann eine Liste auch mit einer "initializer list"
    // in geschweiften Klammern initialisiert werden.
    ls = { "drei", "zwei", "eins" };

    // reverse dreht die Reihenfolge der Elemente um.
    ls.reverse();

    // size liefert die Anzahl der Elemente.
    cout << ls.size() << endl;

    // "range-based for loop" zum bequemen Durchlaufen aller Elemente.
    for (string s : ls) {
	cout << s << endl;
    }

    // front bzw. back liefert das erste bzw. letzte Element,
    // pop_front bzw. pop_back entfernt dieses Element.
    // (Für leere Listen ist das Verhalten dieser Funktionen undefiniert.)
    // Damit kann eine Liste auch als FIFO-Warteschlange verwendet werden.

    // Tabelle mit Schlüsseln des Typs string und zugehörigen Werten
    // des Typs int, die jedem String s einen int-Wert tab[s] zuordnet.
    // Der parameterlose Konstruktor, der automatisch aufgerufen wird,
    // wenn es keine explizite Initialisierung gibt, erstellt eine
    // leere Tabelle.
    map<string, int> tab;

    // Der Indexoperator kann sowohl zur Abfrage als auch zur Zuweisung
    // des Werts, der zu einem Schlüssel gehört, verwendet werden.
    tab["eins"] = 1; cout << tab["eins"] << endl;
    tab["zwei"] = 2; cout << tab["zwei"] << endl;
    tab["drei"] = 3; cout << tab["drei"] << endl;
    tab["zwei"] = -2; cout << tab["zwei"] << endl;

    // Wenn es zu einem Schlüssel noch keinen Wert gibt, wird vom
    // Indexoperator automatisch der Wert zugewiesen und geliefert,
    // den der parameterlose Konstruktor des Werttyps liefert.
    // (Für den Typ int ist dieser Wert 0.)
    cout << tab["vier"] << endl;

    // Alternativ kann eine Tabelle auch mit einer "initializer list"
    // initialisiert werden, die aus Schlüssel-Wert-Paaren besteht.
    tab = { { "eins", 11 }, { "zwei", 22 }, { "drei", 33 } };

    // "range-based for loop" zum Durchlaufen aller Schlüssel-Wert-Paare.
    // p.first bzw. p.second liefert den ersten bzw. zweiten Bestandteil
    // des Paars p.
    for (pair<string, int> p : tab) {
	cout << p.first << " -> " << p.second << endl;
    }

    // Containertypen können auch verschachtelt werden.
    // Zur Initialisierung können dann entsprechend verschachtelte
    // "initializer lists" verwendet werden.
    list<list<int>> ls2 = { { 1, 2 }, { }, { 3 } };

    // Oder schrittweise aufgebaut:
    ls2.clear();
    ls2.push_back(list<int>()); // list<int>() liefert eine leere Liste.
    ls2.back().push_back(1);
    ls2.back().push_back(2);
    ls2.push_back(list<int>());
    ls2.push_back(list<int>());
    ls2.back().push_back(3);

    // Ausgabe mit verschachtelten for-Schleifen.
    for (list<int> ls : ls2) {
	for (int x : ls) cout << x << " ";
	cout << endl;
    }

    // Containertypen können auch kombiniert werden.
    // friends speichert für jede Person, die durch ein Paar von
    // Strings (Vorname und Nachname) identifiziert wird, eine Liste
    // von Freunden, bei denen es sich ebenfalls um Paare von Strings
    // handelt.
    map<pair<string, string>, list<pair<string, string>>> friends = {
	{ { "Anton", "A." }, { { "Berta", "B." }, { "Hugo", "H." } } },
	{ { "Frieda", "F." }, { { "Gustav", "G." } } }
    };

    // Wenn der genaue Typ einer Variablen nicht bekannt oder umständlich
    // zu schreiben ist, kann man stattdessen häufig das Schlüsselwort
    // auto verwenden, damit der Compiler den Typ automatisch ermittelt.
    for (auto p : friends) {
	// Da friends eine Tabelle ist, ist p ein Paar.
	auto key = p.first;
	auto val = p.second;
	cout << key.first << " " << key.second;

	// val ist eine Liste von Paaren, deshalb ist q wieder ein Paar.
	string sep = " -> ";
	for (auto q : val) {
	    cout << sep << q.first << " " << q.second;
	    sep = " | ";
	}
	cout << endl;
    }
}
