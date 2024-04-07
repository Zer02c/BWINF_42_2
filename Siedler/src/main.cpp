#include <iostream>
#include <cmath>
#include <vector>

#include <Geometrie.h>
#include <matplotlibcpp.h>

namespace plt = matplotlibcpp;

Geometrie::Point end_point;

std::vector<Geometrie::Point> last_points(const Geometrie::Polygon& polygon){
	std::vector<Geometrie::Point> umfang_Punkte;

	for(int radius = 10; radius <= 85; radius += 10){
		double umfang = 2 * M_PI * radius;
		int anzahl_punkte = static_cast<int>(umfang/distance);

		for(int i = 0; i < anzahl_punkte; ++i){
			double winkel = (2*M_PI*i)/anzahl_punkte;
			double x = centroid_circle.getX() + radius * std::cos(winkel);
			double y = centroid_circle.getY() + radius * std::sin(winkel);
			if(polygon.isInsidePolygon(Geometrie::Point(x,y))){
				umfang_Punkte.push_back(Geometrie::Point(x, y));
			}
		}


	}
	return umfang_Punkte;
}

// Funktion zum berechen der Punkte auf dem Umkreis eines Kreises in 10 radius abstaenden bis 85
std::vector<Geometrie::Point> circle_Points(int distance, Geometrie::Point centroid_circle,const Geometrie::Polygon& polygon){
	std::vector<Geometrie::Point> umfang_Punkte;

	for(int radius = 10; radius <= 85; radius += 10){
		double umfang = 2 * M_PI * radius;
		int anzahl_punkte = static_cast<int>(umfang/distance);

		for(int i = 0; i < anzahl_punkte; ++i){
			double winkel = (2*M_PI*i)/anzahl_punkte;
			double x = centroid_circle.getX() + radius * std::cos(winkel);
			double y = centroid_circle.getY() + radius * std::sin(winkel);
			if(polygon.isInsidePolygon(Geometrie::Point(x,y))){
				umfang_Punkte.push_back(Geometrie::Point(x, y));
			}
		}


	}
	return umfang_Punkte;
}

std::vector<Geometrie::Point> search_algo(int distance, Geometrie::Point centroid_circle, const Geometrie::Polygon& polygon){
	std::vector<Geometrie::Point> points = circle_Points(distance, centroid_circle, polygon);
	int start_value = points.size();
	int end_value = 0;
	Geometrie::Point centroid = centroid_circle;
	do{
		for(const Geometrie::Point& p: points){
			std::cout << "jetzt" << std::endl;
			std::vector<Geometrie::Point> test_points = circle_Points(distance, p, polygon);
			if(test_points.size() > start_value){
				start_value = test_points.size();
				centroid = p;
				}
			if(start_value == end_value){
				end_point = p;
				return circle_Points(distance, centroid, polygon);
			}
			end_value = start_value;

		}
	}while(true);
}


int main() {
	// Erstellen eines Polygon Objektes
	Geometrie::Polygon polygon;

	// Punkte aus einer .txt file einlesen
	polygon.readPointsFromFile("../inputs/siedler1.txt");

	// bestimmen des centroid
	Geometrie::Point centroid = polygon.centroid();

	std::vector<Geometrie::Point> end_points = search_algo(10, centroid, polygon);
	std::cout << "size algo: " << end_points.size() << std::endl;
	std::cout << "size normal: " << circle_Points(10, centroid, polygon).size() << std::endl;
	std::cout << end_point.getX() << std::endl;





	//std::cout << "groesse ohne algo: " << test.size() << std::endl;
	std::vector<double>x_werte;
	std::vector<double>y_werte;
	for(Geometrie::Point p : end_points){
		x_werte.push_back(p.getX());
		y_werte.push_back(p.getY());
	}

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
	plt::plot(x_points, y_points, "r-", x_werte, y_werte,"bo");
	plt::plot(x_points, y_points, "r-", x_werte, y_werte,"bo");

	// Optional: Fülle das Polygon
	plt::xlabel("X-Achse");
	plt::ylabel("Y-Achse");

	// Titel des Plots
	plt::title("Polygon mit matplotlibcpp");

	// Plot anzeigen
	plt::show();

	return 0;
}
