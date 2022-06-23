#include <limits>
#include <list>
#include <map>
#include <utility>	// pair#

/// TODO REMOVE
#include <stdio.h>
#include<iostream>

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
            for (V v: successors(u)){
                newadj[v].push_back(u);
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
struct DFS : Pred<V>, Dist<V, uint> {
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
void bfs (G g, V s, BFS<V>& res) {  //works
    for (V v: g.vertices()) {
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

template <typename V, typename G>
void dfsCheckSuccessors (G g, DFS<V>& res, int& zeitwert,V nodeName);

// Tiefensuche im Graphen g ausführen und das Ergebnis in res speichern.
// In der Hauptschleife des Algorithmus werden die Knoten in der
// Reihenfolge des Containers g.vertices() durchlaufen.
// ACHTUNG: ANFANGSZEIT WIRD in res.det und ABSCHLUSSZEIT in res.fin gespeichert. Index ist der Knoten
template <typename V, typename G>
void dfs (G g, DFS<V>& res){//works
    int zeitwert = 1;
    for(V u : g.vertices()){ // für jeden Knoten u
        if (!res.det.count(u)){ // weiß ? (Wenn noch keine Anfangszeit existiert)
            res.pred[u] = res.NIL; // Setze Vorgänger auf nil
            res.det[u] = zeitwert; // Anfangszeit auf zeitwert
            zeitwert++; // zeitwert Iterieren
            dfsCheckSuccessors(g,res,zeitwert,u);
            res.fin[u] = zeitwert;
            zeitwert++;
            res.seq.push_back(u);
        }
    }
}

template <typename V, typename G>
void dfsCheckSuccessors (G g, DFS<V>& res, int& zeitwert,V nodeName){
    for (V v: g.successors(nodeName)) {
        res.pred[v]=nodeName;
        if(!res.det.count(v)){
            res.det[v]=zeitwert++;
            dfsCheckSuccessors(g,res,zeitwert,v);
            res.fin[v]=zeitwert++;
            res.seq.push_back(v);
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
            res.det[u] = zeitwert; // Anfangszeit auf zeitwert
            zeitwert++; // zeitwert Iterieren
            for (V v: g.successors(u)) {
                if(!res.det.count(v)){
                    res.pred[v]=u;
                    dfs(g,g.successors(v),res);
                }
            }
            res.fin[u] = zeitwert;
            zeitwert++;
        }
    }
}



template <typename V, typename G>
bool extdfs (G g, list<V> vs, DFS<V>& res, list<V>& seq){
    int zeitwert = 1;
    for(V u : vs){ // für jeden Knoten u
        if (!res.det.count(u)){ // weiß ? (Wenn noch keine Anfangszeit existiert)
            res.pred[u] = res.NIL; // Setze Vorgänger auf nil
            res.det[u] = zeitwert; // Anfangszeit auf zeitwert
            zeitwert++; // zeitwert Iterieren
            for (V v: g.successors(u)) {
                if(!res.det.count(v)){
                    res.pred[v]=u;
                    dfsCheckSuccessors(g,res,zeitwert,v);
                } else if (!res.fin.count(v)) { // Zyklus!
                    return false;
                }
            }
            res.fin[u] = zeitwert;
            zeitwert++;
            seq.push_back(u);
        }
    }
    return true;
}

// Topologische Sortierung des Graphen g ausführen und das Ergebnis
// als Liste von Knoten in seq speichern.
// Resultatwert true, wenn dies möglich ist,
// false, wenn der Graph einen Zyklus enthält.
// (Im zweiten Fall darf der Inhalt von seq danach undefiniert sein.)
template <typename V, typename G>
bool topsort (G g, list<V>& seq){
    int zeitwert = 1;
    bool kreisfrei;
    DFS<V> mem;
    for(V u : g.vertices()){ // für jeden Knoten u
        if (!mem.det.count(u)){ // weiß ? (Wenn noch keine Anfangszeit existiert)
            mem.pred[u] = mem.NIL; // Setze Vorgänger auf nil
            mem.det[u] = zeitwert; // Anfangszeit auf zeitwert
            zeitwert++; // zeitwert Iterieren
            for (V v: g.successors(u)) {
                if(!mem.det.count(v)){
                    if (mem.det.count(u)&&!mem.fin.count(u)) mem.pred[v]=u;
                    kreisfrei = extdfs(g,g.successors(v),mem,seq);
                    if (!kreisfrei) return false;
                }
            }
            mem.fin[u] = zeitwert;
            zeitwert++;
            seq.push_back(u);
        }
    }
    return true;
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
    dfs(g,firstdfs);
    // Transsexuellen Graph erstellen
    Graph<V> transgraph = g.transpose();
    // Tiefensuchenliste umdrehen
    firstdfs.seq.reverse();
    // zweite Tiefensuche mit transgraph und umgedrehter tiefensuche liste aus erster dfs aufrufen.
    dfs(transgraph,firstdfs.seq,seconddfs);
    for (V u: seconddfs.seq){
        if (seconddfs.pred[u]==seconddfs.NIL){
            list<V> scc;
            scc.push_back(u);
            for(V v: g.successors(u)){
                if (seconddfs.fin[u]<seconddfs.det[v]){
                    scc.push_back(v);
                }
            }
            res.push_back(scc);
        }
    }
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
    Dist<V,uint> inf;
    // neue minimum-Vorrangwarteschlange Q erstellen
    PrioQueue<uint, V> Q;
    // für jeden Knoten v el. V:
    int c=0;
    for (V v: g.vertices()){
        if (v!=s){
            // v Objekt mit unendlicher prio einfügen
            inf.dist[v] = inf.INF;
            Q.insert(inf.dist[v],v);
            // Vorgänger von v auf NIL setzen
            res.pred[v] = res.NIL;
        }
        else{
            if(c>0) break;
            else c++;
        }

    }
    res.pred[s] = res.NIL;
    string u=s;
    // solange Q nicht leer ist:
    while (!Q.isEmpty()) {
        for (V v: g.successors(u)) {
            Entry<uint,V> *e;
            e = new Entry<uint, V>(inf.INF, v);
            if(Q.contains(e) && g.weight(u,v) < inf.dist[v]){
                inf.dist[v] = g.weight(u,v);
                res.pred[v] = u;
            }
        }
        Entry<uint ,V>* min;
        min = Q.extractMinimum();
        u = min->data;
        res.pred[u] = min->prio;
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
    for (V v: g.vertices()) {
        res.dist[v] = res.INF;
        res.pred[v] = res.NIL;
    }
    res.dist[s]=0;
    //Berechnung der Knotenanzahl
    int Knoten;
    for (pair<V, list<V>> p : g.adj) {
        Knoten++;
    }

    for(int i=0; i<Knoten; i++) {
        for (pair<V, list < V>> p : g.adj) {
            V u = p.first;
            for (V v: p.second) {
                res.dist[v] = res.dist[u] + g.weight(u, v);
                res.pred[v] = u;
            }
        }
    }

    for (pair<V, list<V>> p : g.adj) {
        V u = p.first;
        for (V v: p.second) {
            if(res.dist[u]+g.weight(u, v)){ //aka delta von u
                return false;
            }
        }
    }
    return true;
}

// Kürzeste Wege vom Startknoten s zu allen Knoten des Graphen g mit
// dem Algorithmus von Dijkstra ermitteln und das Ergebnis in res
// speichern.
// Die Kanten des Graphen dürfen keine negativen Gewichte besitzen.
// (Dies muss nicht überprüft werden.)
template <typename V, typename G> ///TODO: needs rework maybe one iteration missing?
void dijkstra (G g, V s, SP<V>& res){ ///... Error occurs when "dijk 4 A" is called.
    for (V v: g.vertices()) {
        res.dist[v]= res.INF;
        res.pred[v]=res.NIL;
    }
    res.dist[s]=0;
    PrioQueue<uint, V> Q;
    for (V v: g.vertices()){
        Q.insert(res.dist[v], v);
    }
    while(!Q.isEmpty()){
        Entry<uint,V>* min;
        min = Q.extractMinimum();
        V u = min->data;
        res.pred[u] = min->prio;
        int count=0;
        for(V v: g.successors(u)){
            int resmem = res.dist[v];
            res.dist[v] = res.dist[u] + g.weight(u, v);
            res.pred[v] = u;
            PrioQueue<uint,V> temp = Q;
            Entry<uint,V>* tempent;
            while (!temp.isEmpty()){
                tempent = temp.extractMinimum();
                if (tempent->data == v) break;
            }
            if(res.dist[v]<resmem){
                Q.changePrio(tempent,res.dist[v]);
            }
        }
    }
}
