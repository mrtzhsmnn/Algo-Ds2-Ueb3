# Algo-Ds2-Ueb3
Übung 3 von Algorithmen und Datenstrukturen 2 im SoSe 2022 and der Hochschule Aalen.
Mit Nico Haisch, Friedrich Röntsch und Moritz Hausmann.
Abgabetermin ist der 30.06.2022.


## COMMIT-ETIQUETTE:
An folgende Commit-Etiquette ist sich zu halten.
https://www.conventionalcommits.org/en/v1.0.0/

Link zur weiteren Erklärung der Keywords am Beginn des Statements.
https://github.com/angular/angular/blob/22b96b9/CONTRIBUTING.md#-commit-message-guidelines

## Aufgabenverteilung:
**Deadline:** Montag ??.??.????
Pls update the checklist with 
- [x] `[x]` when done.
### Nico:
  
### Friedrich:
 
### Moritz:

# Grundlagen zu Graphen:
### Graph:
Ein Graph ist ein Paar `G = (V,E)` wobei `V` die endliche Menge von **Knoten** und `E` eine zugehörige Menge an **Kanten** ist.
Graphen können gerichtet oder ungerichtet sein. Diese unterscheiden sich in der Definition, dabei dass der gerichtete Graph ein Paar als Kante hat, 
wohingegen ein ungerichteter Graph eine Menge als Kante hat.
Ein ungerichteter Graph kann dem folgend auch als gerichteter Graph aufgefasst werden.
Führt eine Kante auf sich selbst zu, wird sie als eine **Schlinge** bezeichnet.
### Adjazenzlisten und -matrizen:
Wenn es in einem Graph eine Kante von einem Knoten ``u`` zu einem anderen Knoten ``v`` gibt, heisst diese Kante `(u,v)`, wobei `u` der *Vorgänger*
und `v` der _Nachfolger_ von `u` ist. Eine **Adjazenzliste** eines Knotens enthält alle seine Nachfolger, in beliebiger Reihenfolge.
Die **Adjazenzlistendarstellung** eines Graphen besteht aus einer **Adjazenzliste** für jeden Knoten.
Die **Adjazenzmatrizen** sind eine **Adjazenzliste** in Form einer **Matrix**.
Bei ungerichteten Graphen sind Adjazenzmatrizen symmetrisch, bei gerichteten Graphen nicht.
Die Adjazenzlistendarstellung eines Graphen `G = (V,E)` hat die Größe ``O(|V| + |E|)``, die zugehörige Adjazenzmatrix hat die Größe ``O(|V|^2)``.
### Weitere Begriffe:
- **(einfacher) Weg**: von einem Knoten `u` zu einem Knoten `v` ist eine Folge paarweise verschiedener Knoten.
- **Länge**: Die Länge eines Weges sind die Anzahl der Kanten.
- **Erreichbarkeit**: Ein Knoten ist erreichbar, wenn es einen Weg zu ihm gibt.
# Überlegungen Zu den Aufgaben 
**Algo Übung 3**  

# Container

Container Klasse aus der Standardbib. Testprogramm zum warm werden auf
Webseite.

## Beispiel Liste

Alle Funktionen sind bei leerer liste **UNDEFINIERT** also keine
abfangbare Exception\!\!

1.  Kann mit geschweiften klammern initialisiert konstruiert werden.

2.  push\_front: Fügt ein Element am **Anfang** der Liste an.

3.  push\_back: Fügt ein Element am **Ende** der Liste an.

4.  reverse: Dreht reihenfolge der Liste um.

5.  size: Liefert Größe als Int zurück.

6.  for loop: Ähnlich wie in python mit `for (string s : ls)`

7.  front **erstes** Element.

8.  back **letztes** Element.

9.  pop\_front/pop\_back: Entfernt erstes bzw. letztes Element aus
    Liste. RETURN TYP VOID

## Beispiel Map

Tabelle mit Schlüsselwert und Wert. Ähnlichkeit zu dictionary.

1.  Index: Schlüsselwert kann zum Schreiben, Lesen und Überschreiben
    verwendet werden, semantisch ähnlich zu einem Array.

2.  Undef. Index: Speichert und liefert den Wert des param. losen
    konstruktors des Wertdatentyps zurück, ist wohldefiniert, falls
    Parameterloser Konstr. existiert.

3.  kann auch mit geschweiften klammern initialisiert werden.

4.  For schleife: `for (pair<t1, t2> p : map)` wobei t1 der
    Schlüsseldatentyp und t2 der Wertdatentyp ist. Im For kann dann mit
    p.first der Schlüssel und mit p.second der Wert abgerufen werden.

## Containertypen verschachteln

Beispiel Liste von Listen von Int:  
  
Ausgabe mit zwei verschachtelten For-Schleifen. Bei einem "Bestimmung
starker Zusammenhangskomponenten" scheinbar nützlich.  
  
Man kann auch maps Verschachteln. Typedefs als vereinfachung als
Verschachtelung von Maps etc..  
  
Schlüsselwort `auto` ermittelt bsp. in für forschleife automatisch den
Datentyp. `for (auto p : mapmap)`. Kann auch an anderer stelle im
Programm verwendet werden.

# Aufgabe

Man erhält eine .h Datei zur Implementierung von
Vorrangwarteschlangen.  
  
Ein Graph ist ein beliebiger Typ G der allerdings zumindest die in der
Aufgabe erwähnten Funktionen unterstützen muss. Alle Container aus der
Standardbib unterstützen diese Funktionen.

    template <typename G, typename V>
    void bfs (G g, V s, BFS<V>& res) {
        for (V v: g.vertrices()) {
            if (v != s) {
                res.pred[v] = res.NIL;
                res.dist[v] = res.INF;
            }
        }
        res.dist[s] = 0;
        res.pred[s] = res.NIL;
        list<V> fifo;
        fifo.push_back(s);
        while (fifo.size() > 0) {
            V u = fifo.front();
            fifo.pop_front();
            for (V v: g.successors(u)) {
                if (res.dist[v] == res.INF) {
                    res.dist[v] = res.dist[u] + 1;
                    res.pred[v] = u;
                    fifo.push_back(v);
                }
            }
        }
    }

Die Funktionen `dfs` und `topsort` sollen sich an ursprünglicher
`dfs`-Funktion bedienen.

