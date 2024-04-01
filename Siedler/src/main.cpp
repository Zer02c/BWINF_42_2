#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>

#include <Geometrie.h>
#include <matplotlibcpp.h>

namespace plt = matplotlibcpp;

// Funktion um auf einem kreisumfang punkte zu platzieren

int main() {
	// Erstellen eines Polygon Objektes
	Geometrie::Polygon polygon;

	// Punkte aus einer .txt file einlesen
	polygon.readPointsFromFile("../inputs/siedler1.txt");

	// bestimmen des centroid
	Geometrie::Point centroid = polygon.centroid();
	std::cout << centroid.getX() << "||" << centroid.getY();

	return 0;
}
