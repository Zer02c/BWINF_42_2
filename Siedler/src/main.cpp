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
	std::cout << centroid.getX() << "||" << centroid.getY() << std::endl;


	// Polygon plotten
	std::vector<double> x_points;
	std::vector<double> y_points;
	for(const Geometrie::Point point : polygon.getPoints()){
		x_points.push_back(point.getX());
		y_points.push_back(point.getY());
	}
	x_points.push_back(x_points[0]);
	y_points.push_back(y_points[0]);
	
	// Plot erstellen und Polygon plotten
	plt::plot(x_points, y_points, "r-");

	// Optional: Fülle das Polygon
	plt::xlabel("X-Achse");
	plt::ylabel("Y-Achse");

	// Titel des Plots
	plt::title("Polygon mit matplotlibcpp");

	// Plot anzeigen
	plt::show();


	return 0;
}
