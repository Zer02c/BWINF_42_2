#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>

#include <Geometrie.h>
#include <matplotlibcpp.h>

namespace plt = matplotlibcpp;

// Funktion um auf einem kreisumfang punkte zu platzieren
std::vector<Geometrie::Point> circle_algo(int distance, Geometrie::Point centroid_circle, const Geometrie::Polygon& polygon){
	std::vector<Geometrie::Point> points;

	for(int radius = 10; radius <= 85; radius += 10){
		double umfang = 2 * M_PI * radius;

		int anzahl_punkte = static_cast<int>(umfang/distance);

		for(int i = 0; i < anzahl_punkte; ++i){
			double winkel = (2 * M_PI * i) / anzahl_punkte;
			double x = centroid_circle.getX() + radius * std::cos(winkel);
			double y = centroid_circle.getY() + radius * std::sin(winkel);
			if(polygon.isInsidePolygon(Geometrie::Point(x,y))){
				points.push_back(Geometrie::Point(x,y));
			}
		}
	}
	return points;
}

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
