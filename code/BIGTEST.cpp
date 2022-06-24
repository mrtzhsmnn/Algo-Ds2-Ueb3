#include <iostream>
#include <string>

using namespace std;

#include "graph.h"

// Knotentyp.
using V = string;

// Feld mit Testgraphen.
// (Für eigene Tests können beliebige weitere Graphen hinzugefügt werden.)
// Damit Graphen der Typen Graph<V> und WeightedGraph<V> im selben Feld
// gespeichert werden können, werden Zeiger auf den Basistyp Graph<V>
// gespeichert, die bei Bedarf in Zeiger auf WeightedGraph<V>
// umgewandelt werden.
Graph<V> *graphs[] = {
        // Beispiel eines ungewichteten Graphen.
        new Graph<string>({
                                  {"A", {"B", "C"}},    // Knoten A hat Nachfolger B und C.
                                  {"B", {}},        // Knoten B hat keine Nachfolger.
                                  {"C", {"C"}}    // Knoten C hat sich selbst als Nachfolger.
                          }),

        // Beispiel eines gewichteten Graphen.
        new WeightedGraph<string>({
                                          {"A", {{"B", 2}, {"C", 3}}},
                                          // Kanten A -> B mit Gewicht 2 und A -> C mit Gewicht 3.
                                          {"B", {}},        // Keine Kanten B -> ...
                                          {"C", {{"C", 4}}}    // Kante C -> C mit Gewicht 4.
                                  }),

        new Graph<string>({
                                  {"0", {"1", "4"}},
                                  {"1", {"0", "2", "5"}},
                                  {"2", {"4"}},
                                  {"3", {"1", "5"}},
                                  {"4", {"2"}},
                                  {"5", {}},
                                  {"6", {"2", "5"}},
                                  {"7", {"6"}},
                          }),
        //Gewichteter ungerichteter Graph
        new WeightedGraph<string>({
                                          {"A", {{"B", 2}, {"C", 3}}},
                                          {"B", {{"A", 2}}},        // Keine Kanten B -> ...
                                          {"C", {{"A", 3}, {"D", 5}}},    // Kante C -> C mit Gewicht 4.
                                          {"D", {{"C", 5}, {"E", 1}}},
                                          {"E", {{"D", 1}}}
                                  }),
        // Graph aus der Vorlesung
        new WeightedGraph<string>({
                                          {"A", {{"D", 4}}},
                                          {"B", {{"A", 3}}},
                                          {"C", {{"A", 6}, {"B", 2}}},
                                          {"D", {{"B", 5}, {"C", 1}}}
                                  }),
};

// Weg vom Startknoten s zum Knoten v anhand der Vorgängerinformation
// in res ausgeben.
void path(V s, V v, Pred<V> &res) {
    if (s != v && res.pred[v] != res.NIL) {
        path(s, res.pred[v], res);
        cout << " -> ";
    }
    cout << v;
}

template<typename V>
void testout(int mode, Graph<V> *g, int graphnr);

int main() {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 5; ++j) {
            testout(i, graphs[j], j);
        }
    }

}

template<typename V>
void testout(int mode, Graph<V> *g, int graphnr) {
    map<int, string> modestring;
    modestring[0] = "BFS";
    modestring[1] = "DFS";
    modestring[2] = "TOPSORT";
    modestring[3] = "SCC";
    modestring[4] = "PRIM";
    modestring[5] = "BELLMAN-FORD";
    modestring[6] = "DIJKSTRA";
    cout << "#################" << endl;
    cout << "###" << modestring[mode] << " - TESTS###" << endl;
    cout << "###GRAPHNR: " << graphnr << "###" << endl;
    cout << "#################" << endl;
    switch (mode) {
        case 0: {// BFS
            for (V s: g->vertices()) {
                cout << "----------------------------------------" << endl;
                cout << "Startknoten: " << s << endl;
                cout << "----------------------------------------" << endl;
                BFS<V> res;
                bfs(*g, s, res);
                for (V v: g->vertices()) {
                    path(s, v, res);
                    uint d = res.dist[v];
                    if (d == res.INF) cout << " inf" << endl;
                    else cout << " " << d << endl;
                }
            }
            break;
        }
        case 1: { // DFS
            DFS<V> res2;
            dfs(*g, res2);
            for (V v: res2.seq) {
                cout << v << " " << res2.det[v] << " " << res2.fin[v] << endl;
            }
            break;
        }
        case 2: { // TOPSORT
            list<V> res;
            if (topsort(*g, res)) {
                for (V v: res) cout << v << endl;
            } else {
                cout << "cycle" << endl;
            }
            break;
        }
        case 3: { // SCC
            list<list<V>> res;
            scc(*g, res);
            for (list<V> c: res) {
                c.sort();
                for (V v: c) cout << v << " ";
                cout << endl;
            }
            break;
        }
        case 4: { // PRIM
            Pred<V> res;
            for (V s: g->vertices()) {
                if (graphnr != 3) { // NUR GRAPH 3 ist unger. und gew.
                    cout << "Nur fuer unger. und gew. Graphen!" << endl;
                    break; // nur für gewichtete Graphen
                }
                cout << "----------------------------------------" << endl;
                cout << "Startknoten: " << s << endl;
                cout << "----------------------------------------" << endl;
                prim(*(WeightedGraph<V> *) g, s, res);
                for (V v: g->vertices()) {
                    path(s, v, res);
                    cout << endl;
                }
            }
            break;
        }
        case 5: { // BELLMAN-FORD
            SP<V> res;
            if (graphnr > 2) {
                cout << "Nur fuer gew. Graphen!" << endl;
                break; // nur für gewichtete Graphen
            }
            for (V s: g->vertices()) {
                cout << "----------------------------------------" << endl;
                cout << "Startknoten: " << s << endl;
                cout << "----------------------------------------" << endl;
                if (bellmanFord(*(WeightedGraph<V> *) g, s, res)) {
                    for (V v: g->vertices()) {
                        path(s, v, res);
                        cout << " " << res.dist[v] << endl;
                    }
                } else {
                    cout << "negative cycle" << endl;
                }
            }
            break;
        }
        case 6: { // DIJKSTRA
            SP<V> res;
            if (graphnr > 2) {
                cout << "Nur fuer gew. Graphen!" << endl;
                break; // nur für gewichtete Graphen
            }
            for (V s: g->vertices()) {
                cout << "----------------------------------------" << endl;
                cout << "Startknoten: " << s << endl;
                cout << "----------------------------------------" << endl;
                dijkstra(*(WeightedGraph<V> *) g, s, res);
                for (V v: g->vertices()) {
                    path("A", v, res);
                    cout << " " << res.dist[v] << endl;
                }
            }
            break;
        }
        default:
            cout << "Unknown mode" << endl;
            break;
    }
}

