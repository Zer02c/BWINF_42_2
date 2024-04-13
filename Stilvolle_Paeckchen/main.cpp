#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <sstream>

using namespace std;

// Hash-Funktion für std::pair<int, int>
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1,T2>& p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

// Funktion zum Einlesen der Verbindungen
vector<pair<int, int>> inputConnections() {
    vector<pair<int, int>> connections;
    while (true) {
        cout << "Bitte geben Sie Ihre Verbindung ein (zwei Zahlen getrennt durch Leerzeichen, oder Eingabe zum Beenden): ";
        string line;
        getline(cin, line);
        if (line.empty()) break;
        int x, y;
        istringstream iss(line);
        if (!(iss >> x >> y)) {
            cout << "Ungültige Eingabe. Bitte geben Sie zwei Zahlen ein." << endl;
            continue;
        }
        connections.push_back({min(x, y), max(x, y)});
    }
    return connections;
}

// Funktion zum Sortieren der Elemente und Identifizieren gültiger Kombinationen
vector<tuple<int, int, int>> findValidCombinations(const vector<pair<int, int>>& connections) {
    // Set für schnellen Zugriff auf Verbindungen
    unordered_set<pair<int, int>, pair_hash> connectionSet(connections.begin(), connections.end());

    vector<tuple<int, int, int>> validCombinations;

    // Durchlaufe alle möglichen Kombinationen von drei Elementen (x < y < z)
    for (auto it1 = connectionSet.begin(); it1 != connectionSet.end(); ++it1) {
        int x = it1->first;
        int y = it1->second;
        for (auto it2 = next(it1); it2 != connectionSet.end(); ++it2) {
            int z = it2->second;
            // Überprüfe, ob die Kombination (x, y, z) gültig ist
            if (connectionSet.count({x, z}) && connectionSet.count({y, z})) {
                validCombinations.push_back({x, y, z});
            }
        }
    }

    return validCombinations;
}

// Hauptfunktion
int main() {
    // Verbindungen einlesen
    vector<pair<int, int>> connections = inputConnections();

    // Gültige Kombinationen finden
    vector<tuple<int, int, int>> validCombinations = findValidCombinations(connections);

    // Ausgabe der Verbindungen und gültigen Kombinationen
    cout << "Eingegebene Verbindungen:" << endl;
    for (const auto& conn : connections) {
        cout << "(" << conn.first << ", " << conn.second << ")" << endl;
    }

    cout << "Gültige Kombinationen von drei Elementen:" << endl;
    for (const auto& comb : validCombinations) {
        cout << "(" << get<0>(comb) << ", " << get<1>(comb) << ", " << get<2>(comb) << ")" << endl;
    }

    return 0;
}
