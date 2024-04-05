#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>

#include <Geometrie.h>
#include <matplotlibcpp.h>

namespace plt = matplotlibcpp;

// finale funktion
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

/*
// Funktion um auf einem kreisumfang punkte zu platzieren
std::vector<Geometrie::Point> circle_algo(int distance, Geometrie::Point centroid_circle, const Geometrie::Polygon& polygon){
	std::vector<Geometrie::Point> finale_points;
	int counter = 0;
	int start = 0;

	for(int radius = 10; radius <= 85; radius += 10){
		std::vector<Geometrie::Point> points;
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

		// check mehr punkte in polygon
		for(int i = 0; i < points.size(); i++){
			counter = 0;
			int s = 10;
			do{
				double um = 2 * M_PI * s;
				int an_p = static_cast<int>(um/distance);
				for(int j = 0; j < an_p; ++j){
					double winkel = (2 * M_PI * j) / anzahl_punkte;
					double x_ = points[i].getX() + s * std::cos(winkel);
					double y_ = points[i].getY() + s * std::sin(winkel);

					if(polygon.isInsidePolygon(Geometrie::Point(x_,y_))){
						counter++;
					}else{std::cout << "not" << std::endl;}
					}
				s += 10;
				}while(s <= radius);

			if(counter > start){
				std::cout << "counter: " << counter << " start value: " << start << std::endl;
				std::cout << centroid_circle.getX() << "||" << centroid_circle.getY() << std::endl;
				centroid_circle = points[i];
				start = counter;
				}
			}
	}
	std::cout << "end point: " << centroid_circle.getX() << "||" << centroid_circle.getY() << std::endl;
	return circle_Points(distance, centroid_circle, polygon);
}*/


int main() {
	// Erstellen eines Polygon Objektes
	Geometrie::Polygon polygon;

	// Punkte aus einer .txt file einlesen
	polygon.readPointsFromFile("../inputs/siedler1.txt");

	// bestimmen des centroid
	Geometrie::Point centroid = polygon.centroid();
	//std::cout << centroid.getX() << "||" << centroid.getY() << std::endl;

	// test funktion
	//std::vector<Geometrie::Point> list = circle_algo(10, centroid, polygon);
	//std::cout << "groese mit algo: " << list.size() << std::endl;
	std::vector<Geometrie::Point> test = circle_Points(10, centroid, polygon);
	std::vector<Geometrie::Point> finale_points;
	int start = test.size();
	Geometrie::Point current_point;
	for(const Geometrie::Point p : test){
		std::vector<Geometrie::Point> ak = circle_Points(10,p,polygon);
		if(ak.size() > start){
			current_point = p;
			finale_points = ak;
		}
	}
	std::cout << "best place: " << "(" <<current_point.getX() << "|" << current_point.getY() << ")" << std::endl;
	std::cout << "anzahl der doerfer alt: " << test.size() << std::endl;
	std::cout << "anzahl der doerfer new: " << finale_points.size() << std::endl;
	//std::cout << "groesse ohne algo: " << test.size() << std::endl;
	std::vector<double>x_werte;
	std::vector<double>y_werte;
	for(Geometrie::Point p : test){
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
