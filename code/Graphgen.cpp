#include <iostream>
#include <string>
using namespace std;

int main (int argc, char* argv []) {
    int size, mode,count;
    cout << "Geben Sie die Anzahl der Graphen an: " << endl; // Type a number and press enter
    cin >> count; // Get user input from the keyboard
    cout << "Geben Sie eine Groesse an: " << endl; // Type a number and press enter
    cin >> size; // Get user input from the keyboard
    int ranarr[size][size];
    cout << "Geben Sie eine Modus an: " << endl; // Type a number and press enter
    cout << "1 fuer ger. ungew., 2 fuer ger. gew., 3 fuer unger. gew., 4 fuer unger. ungew., 5 fuer ger. gew. und ohne neg Gewichte (Dijkstra)" << endl;
    cin >> mode; // Get user input from the keyboard
    for (int f = 0; f < count; ++f) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if ((rand() % 4 + 1) == 4) {
                    ranarr[i][j] = ((rand() % size) - (size/4));
                } else ranarr[i][j] = 0;
            }
        }
        // Ausgabe als lesbares Format:
        bool first;
        switch (mode) {
            case 1:
                cout << "new Graph<string>({" << endl;
                for (int i = 0; i < size; ++i) {
                    first = true;
                    cout << "\t{\"" << i << "\",{";
                    for (int j = 0; j < size; ++j) {
                        if (ranarr[i][j] != 0 && i!=j) {
                            if (first) {
                                cout << "\"" << j << "\"";
                                first = false;
                            } else cout << ",\"" << j << "\"";
                        } else ranarr[i][j] = 0;
                    }
                    cout << "}}," << endl;
                }
                cout << "})," << endl;
                break;
            case 2:
                cout << "new WeightedGraph<string>({" << endl;
                for (int i = 0; i < size; ++i) {
                    first = true;
                    cout << "\t{\"" << i << "\",{";
                    for (int j = 0; j < size; ++j) {
                        if (ranarr[i][j] != 0 && i!=j) {
                            if (first) {
                                cout << "{\"" << j << "\"," << ranarr[i][j] << "}";
                                first = false;
                            } else cout << ",{\"" << j << "\"," << ranarr[i][j] << "}";
                        } else ranarr[i][j] = 0;
                    }
                    cout << "}}," << endl;
                }
                cout << "})," << endl;
                break;
            case 3:
                for (int i = 0; i < size; ++i) {
                    for (int j = 0; j < size; ++j) {
                        if (ranarr[i][j] != ranarr[j][i]) ranarr[j][i] = ranarr[i][j];
                    }
                }
                cout << "new WeightedGraph<string>({" << endl;
                for (int i = 0; i < size; ++i) {
                    first = true;
                    cout << "\t{\"" << i << "\",{";
                    for (int j = 0; j < size; ++j) {
                        if (ranarr[i][j] != 0 && i!=j) {
                            if (first) {
                                cout << "{\"" << j << "\"," << ranarr[i][j] << "}";
                                first = false;
                            } else cout << ",{\"" << j << "\"," << ranarr[i][j] << "}";
                        } else ranarr[i][j] = 0;
                    }
                    cout << "}}," << endl;
                }
                cout << "})," << endl;
                break;
            case 4:
                for (int i = 0; i < size; ++i) {
                    for (int j = 0; j < size; ++j) {
                        if (ranarr[i][j] != ranarr[j][i]) ranarr[j][i] = ranarr[i][j];
                    }
                }
                cout << "new Graph<string>({" << endl;
                for (int i = 0; i < size; ++i) {
                    first = true;
                    cout << "\t{\"" << i << "\",{";
                    for (int j = 0; j < size; ++j) {
                        if (ranarr[i][j] != 0 && i!=j) {
                            if (first) {
                                cout << "\"" << j << "\"";
                                first = false;
                            } else cout << ",\"" << j << "\"";
                        } else ranarr[i][j] = 0;
                    }
                    cout << "}}," << endl;
                }
                cout << "})," << endl;
                break;
            case 5:
                for (int i = 0; i < size; ++i) {
                    for (int j = 0; j < size; ++j) {
                        if (ranarr[i][j] < 0) ranarr[i][j] = ranarr[i][j] * (-1);
                    }
                }
                cout << "new WeightedGraph<string>({" << endl;
                for (int i = 0; i < size; ++i) {
                    first = true;
                    cout << "\t{\"" << i << "\",{";
                    for (int j = 0; j < size; ++j) {
                        if (ranarr[i][j] != 0 && i!=j) {
                            if (first) {
                                cout << "{\"" << j << "\"," << ranarr[i][j] << "}";
                                first = false;
                            } else cout << ",{\"" << j << "\"," << ranarr[i][j] << "}";
                        } else ranarr[i][j] = 0;
                    }
                    cout << "}}," << endl;
                }
                cout << "})," << endl;
                break;
        }
    }
}