#include <limits>
#include <list>
#include <map>
#include <utility>	// pair

#include "prioqueue.h"

// Vorzeichenlose ganze Zahl.
using uint = unsigned int;

/*
 *  Graphen
 */

// Gerichteter Graph mit Knoten des Typs V.
// (Ein ungerichteter Graph kann als gerichteter Graph repräsentiert
// werden, bei dem jede Kante in beiden Richtungen vorhanden ist.)
template <typename V>
struct Graph {
    // Adjazenzlistendarstellung des Graphen als Tabelle (map),
    // die zu jedem Knoten die Liste seiner Nachfolger enthält.
    map<V, list<V>> adj;

    // Initialisierung mit der Adjazenzlistendarstellung a.
    // Damit ist auch eine Initialisierung mit einer passenden
    // (verschachtelten) Initialisiererliste in geschweiften Klammern
    // möglich, zum Beispiel:
    // { { "A", { "B", "C" } }, { "B", { } }, { "C", { "C" } } }
    Graph (map<V, list<V>> a) : adj(a) {}

    // Container mit allen Knoten des Graphen liefern.
    list<V> vertices () {
        // Alle Paare p der Tabelle adj durchlaufen
        // und jeweils ihren ersten Bestandteil p.first
        // am Ende der Liste vs anfügen.
        list<V> vs;
        for (pair<V, list<V>> p : adj) vs.push_back(p.first);
        return vs;
    }

    // Container mit allen Nachfolgern des Knotens v liefern.
    list<V> successors (V v) {
        // Die zum Knoten v in der Tabelle adj gespeicherte
        // Liste von Nachfolgern liefern.
        return adj[v];
    }

    // Transponierten Graphen als neues, unabhängiges Objekt liefern.
    Graph<V> transpose () {
	// Idee: In einer äußeren Schleife alle Knoten u des Graphen
	// durchlaufen. In einer inneren Schleife alle Nachfolger v
	// von u durchlaufen und dabei jeweils u als Nachfolger von v
	// zu einer neuen Adjazenzlistendarstellung a des
	// transponierten Graphen hinzufügen.
	// Zum Schluss a an den Konstruktor von Graph<V> übergeben.
	// Hinweis: Wenn die Tabelle a noch keinen Eintrag für den
	// Knoten v enthält, erzeugt a[v] automatisch einen neuen
	// Eintrag mit einer leeren Liste von Nachfolgern, auf die
	// direkt push_back angewandt werden kann.
        map<V, list<V>> newadj;
        for (V u: vertices()) {
            newadj.insert(V(u));
            for (V v: successors(u)){
                newadj[u].push_back(v);
            }
        }
        return Graph<V>(newadj);
    }
};

// Gerichteter gewichteter Graph als Unterklasse von Graph<V>.
// (Ein ungerichteter gewichteter Graph kann als gerichteter gewichteter
// Graph repräsentiert werden, bei dem jede Kante in beiden Richtungen
// mit dem gleichen Gewicht vorhanden ist.)
template <typename V>
struct WeightedGraph : Graph<V> {
    // Tabelle mit Kantengewichten.
    map<pair<V, V>, double> wt;

    // Initialisierung mit der um Kantengewichte erweiterten
    // Adjazenzlistendarstellung a.
    // Damit ist auch eine Initialisierung mit einer passenden
    // (verschachtelten) Initialisiererliste in geschweiften Klammern
    // möglich, zum Beispiel:
    // { { "A", { { "B", 2 }, { "C", 3 } } }, { "B", { } },
    //					{ "C", { { "C", 4 } } } }
    WeightedGraph (map<V, list<pair<V, double>>> a) : Graph<V>({}) {
	// Die erweiterte Adjazenzlistendarstellung a durchlaufen und
	// mit der darin enthaltenen Information die (von Graph<V>
	// geerbte) einfache Adjazenzlistendarstellung adj und die
	// Gewichtstabelle wt passend füllen. 
        for (auto p : a) {
            V u = p.first;
            Graph<V>::adj[u];
            for (auto q : p.second) {
                V v = q.first;
                double w = q.second;
                Graph<V>::adj[u].push_back(v);
                wt[{ u, v }] = w;
            }
        }
    }

    // Gewicht der Kante (u, v) liefern.
    double weight (V u, V v) {
	    return wt[{ u, v }];
    }
};

/*
 *  Datenstrukturen zur Speicherung der Ergebnisse der Algorithmen
 */

// Ergebnis von Prim sowie Teil des Ergebnisses von Breitensuche,
// Bellman-Ford und Dijkstra.
template <typename V>
struct Pred {
    // Tabelle zur Speicherung des Vorgängers pred[v] eines Knotens v.
    map<V, V> pred;

    // Ersatzwert NIL, der in pred[v] gespeichert wird, wenn es zu
    // einem Knoten v keinen Vorgänger gibt.
    // Standardmäßig der Wert, den der parameterlose Konstruktor von V
    // liefert. Bei Bedarf kann vor der Ausführung eines Algorithmus
    // aber auch ein anderer Wert an NIL zugewiesen werden, der nicht
    // als echter Knotenwert vorkommt.
    V NIL = V();
};

// Teil des Ergebnisses von Breitensuche (mit N gleich uint)
// sowie Bellman-Ford und Dijkstra (mit N gleich double).
template <typename V, typename N>
struct Dist {
    // Tabelle zur Speicherung der Distanz dist[v] mit numerischem Typ N
    // zwischen dem Startknoten s und dem Knoten v.
    map<V, N> dist;

    // Ersatzwert INF, der in dist[v] gespeichert wird, wenn die Distanz
    // zwischen s und v unendlich ist.
    // Der Wert INF ist entweder "unendlich" (falls verfügbar) oder der
    // größtmögliche endliche Wert des Typs N.
    // (Gleitkommatypen sind üblicherweise gemäß IEEE 754 implementiert
    // und besitzen dann "unendlich" als Wert, ganzzahlige Typen jedoch
    // nicht.)
    static constexpr N INF = numeric_limits<N>::has_infinity ?
	    numeric_limits<N>::infinity() : numeric_limits<N>::max();
};

// Ergebnis einer Breitensuche:
// Durch Mehrfachvererbung gebildete Kombination von Pred<V> und
// Dist<V, uint> mit Elementvariablen pred, NIL, dist und INF.
template <typename V>
struct BFS : Pred<V>, Dist<V, uint> { //muss man das implementieren?

};

// Ergebnis einer Tiefensuche.
template <typename V>
struct DFS {
    // Tabellen zur Speicherung der Entdeckungszeit det[v] und der
    // Abschlusszeit fin[v] eines Knotens v.
    // Beide Zeitwerte liegen zwischen 1 und der doppelten Knotenzahl
    // des Graphen.
    map<V, uint> det, fin;

    // Liste zur Speicherung aller Knoten des Graphen nach aufsteigenden
    // Abschlusszeiten, die damit gleichzeitig das Ergebnis einer
    // erfolgreichen topologischen Sortierung ist.
    list<V> seq;
};

// Ergebnis der Shortest-path-Algorithmen Bellman-Ford und Dijkstra:
// Durch Mehrfachvererbung gebildete Kombination von Pred<V> und
// Dist<V, double> mit Elementvariablen pred, NIL, dist und INF.
template <typename V>
struct SP : Pred<V>, Dist<V, double> {};

/*
 *  Algorithmen
 */

// Breitensuche im Graphen g mit Startknoten s ausführen
// und das Ergebnis in res speichern.
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


// Tiefensuche im Graphen g ausführen und das Ergebnis in res speichern.
// In der Hauptschleife des Algorithmus werden die Knoten in der
// Reihenfolge des Containers g.vertices() durchlaufen.
// ACHTUNG: ANFANGSZEIT WIRD in res.det und ABSCHLUSSZEIT in res.fin gespeichert. Index ist der Knoten
template <typename V, typename G>
void dfs (G g, DFS<V>& res){
    int zeitwert = 1;
    for(V u : g.vertices){ // für jeden Knoten u
        if (!res.det.count(u)){ // weiß ? (Wenn noch keine Anfangszeit existiert)
            res.pred[u] = res.NIL; // Setze Vorgänger auf nil
            res.dist[u] = zeitwert; // Setze Distanz auf zeitwert ///TODO: Fraglich obsolet??
            res.det[u] = zeitwert; // Anfangszeit auf zeitwert
            zeitwert++; // zeitwert Iterieren
            for (V v: g.successors(u)) {
                if(!res.det.count(v)){
                    res.pred[v]=u;
                    dfs(v,res);
                }
            }
            res.fin[u] = zeitwert;
            zeitwert++;
        }
    }
}

// Tiefensuche im Graphen g ausführen und das Ergebnis in res speichern.
// In der Hauptschleife des Algorithmus werden die Knoten in der
// Reihenfolge der Liste vs durchlaufen.
template <typename V, typename G>
void dfs (G g, list<V> vs, DFS<V>& res){
    int zeitwert = 1;
    for(V u : vs){ // für jeden Knoten u
        if (!res.det.count(u)){ // weiß ? (Wenn noch keine Anfangszeit existiert)
            res.pred[u] = res.NIL; // Setze Vorgänger auf nil
            res.dist[u] = zeitwert; // Setze Distanz auf zeitwert ///TODO: Fraglich obsolet??
            res.det[u] = zeitwert; // Anfangszeit auf zeitwert
            zeitwert++; // zeitwert Iterieren
            for (V v: g.successors(u)) {
                if(!res.det.count(v)){
                    res.pred[v]=u;
                    dfs(v,res);
                }
            }
            res.fin[u] = zeitwert;
            zeitwert++;
        }
    }
}

// Topologische Sortierung des Graphen g ausführen und das Ergebnis
// als Liste von Knoten in seq speichern.
// Resultatwert true, wenn dies möglich ist,
// false, wenn der Graph einen Zyklus enthält.
// (Im zweiten Fall darf der Inhalt von seq danach undefiniert sein.)
template <typename V, typename G>
bool topsort (G g, list<V>& seq){
    int zeitwert = 1;
    for(V u : g.vertices){ // für jeden Knoten u
        if (!seq.det.count(u)){ // weiß ? (Wenn noch keine Anfangszeit existiert)
            seq.pred[u] = seq.NIL; // Setze Vorgänger auf nil
            seq.dist[u] = zeitwert; // Setze Distanz auf zeitwert ///TODO: Fraglich obsolet??
            seq.det[u] = zeitwert; // Anfangszeit auf zeitwert
            zeitwert++; // zeitwert Iterieren
            for (V v: g.successors(u)) {
                if(!seq.det.count(v)){
                    if (seq.det.count(u)&&!seq.fin.count(u))
                    seq.pred[v]=u;
                    dfs(v,seq);
                }
            }
            seq.fin[u] = zeitwert;
            zeitwert++;
            seq.push_back(u);
        }
    }
}

// Die starken Zusammenhangskomponenten des Graphen g ermitteln
// und das Ergebnis als Liste von Listen von Knoten in res speichern.
// (Jedes Element von res entspricht einer starken Zusammenhangskomponente.)
template <typename V, typename G>
void scc (G g, list<list<V>>& res){
    // Ergebnisdatenstruktur für die Erste u. zweite Tiefensuche erstellen.
    DFS<V> firstdfs;
    DFS<V> seconddfs;
    // erste DFS ausführen
    dfs(g,&firstdfs);
    // Transsexuellen Graph erstellen
    Graph<V> transgraph = g.transpose;
    // Tiefensuchenliste umdrehen
    firstdfs.seq.reverse();
    // zweite Tiefensuche mit transgraph und umgedrehter tiefensuche liste aus erster dfs aufrufen.
    dfs(transgraph,firstdfs.seq,&seconddfs);

    /// TIEFENSUCHENWALD???

}

// Minimalgerüst des Graphen g mit dem modifizierten Algorithmus von
// Prim mit Startknoten s bestimmen und das Ergebnis in res speichern.
// Der Graph muss ungerichtet sein, d. h. jede Kante muss in beiden
// Richtungen mit dem gleichen Gewicht vorhanden sein.
// (Dies muss nicht überprüft werden.)
// Achtung: res enthält keine Tabelle dist und damit auch keinen Wert
// INF, weil die dist-Werte nur während der Ausführung des Algorithmus
// benötigt werden, aber nicht für das Ergebnis.
// Trotzdem kann die Funktion intern natürlich ein entsprechendes
// Dist-Objekt verwenden.
template <typename V, typename G>
void prim (G g, V s, Pred<V>& res){
    // neue minimum-Vorrangwarteschlange Q erstellen
    PrioQueue<uint, V> Q;
    // für jeden Knoten v el. V:
    for (V v: g.vertices()){
        // v Objekt mit unendlicher prio einfügen
        Q.insert(res.INF,v);
        // Vorgänger von v auf NIL setzen
        g.pred[v] = res.NIL;
    }
    // solange Q nicht leer ist:
    while (!Q.isEmpty()) {
        Entry<uint,V> u;
        u = Q.minimum();
        /// Nachfolger von u??
    }
}

// Kürzeste Wege vom Startknoten s zu allen Knoten des Graphen g mit
// dem Algorithmus von Bellman-Ford ermitteln und das Ergebnis in res
// speichern.
// Resultatwert true, wenn es im Graphen keinen vom Startknoten aus
// erreichbaren Zyklus mit negativem Gewicht gibt, andernfalls false.
// (Im zweiten Fall darf der Inhalt von res danach undefiniert sein.)
template <typename V, typename G>
bool bellmanFord (G g, V s, SP<V>& res){
    for (V v: g.vertrices()) {
        res.dist[v]= res.INF;
        res.pred[v]=res.NIL;
    }
    res.dist[s]=0;
    for(int i=0; i < g.size() -1 ; ++i){
//        for(){
//                      //commented to remove error
//        }
    }
    res.dist[s]=0;
    for (int i = 0; i < g.size() -1; ++i) {
//        if(res.dist[u]+)   //commented to remove error
    }
}

// Kürzeste Wege vom Startknoten s zu allen Knoten des Graphen g mit
// dem Algorithmus von Dijkstra ermitteln und das Ergebnis in res
// speichern.
// Die Kanten des Graphen dürfen keine negativen Gewichte besitzen.
// (Dies muss nicht überprüft werden.)
template <typename V, typename G>
void dijkstra (G g, V s, SP<V>& res){
    for (V v: g.vertrices()) {
        res.dist[v]= res.INF;
        res.pred[v]=res.NIL;
    }
    res.dist[s]=0;
    for (V v: g.vertrices()){

    }
}
