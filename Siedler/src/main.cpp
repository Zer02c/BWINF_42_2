#include <iostream>
#include <cmath>
#include <vector>

#include <Geometrie.h>
#include <matplotlibcpp.h>

namespace plt = matplotlibcpp;


// Funktion um die punkte eines umfangs Berechen
std::vector<Geometrie::Point> umfang_punkte_eins(const Geometrie::Polygon& polygon,
	Geometrie::Point centroid, int radius){
	std::vector<Geometrie::Point> umfang_Punkte;
	double umfang = 2 * M_PI * radius;
	int anzahl_punkte = static_cast<int>(umfang/20);

	for(int i = 0; i < anzahl_punkte; ++i){
		double winkel = (2*M_PI*i)/anzahl_punkte;
		double x = centroid.getX() + radius * std::cos(winkel);
		double y = centroid.getY() + radius * std::sin(winkel);
		if(polygon.isInsidePolygon(Geometrie::Point(x,y))){
			umfang_Punkte.push_back(Geometrie::Point(x, y));
		}
	}
	return umfang_Punkte;
}
// Funktion um die letzten punkte im polygon zu bestimmen
std::vector<Geometrie::Point> last_points(const Geometrie::Polygon& polygon,
	const Geometrie::Point& center_point) {
	int radius = 100;
	std::vector<Geometrie::Point> end_points;
	std::vector<Geometrie::Point> points = umfang_punkte_eins(polygon, center_point, radius);
	// endet wenn der kreis so gros ist das kein punkt mehr im polygon platziert werden kann
	while(points.size() > 0){
		end_points.insert(end_points.end(), points.begin(), points.end());
		radius += 20;
		points = umfang_punkte_eins(polygon, center_point, radius);
	}
	return end_points;
}

// Funktion zum berechen der Punkte auf dem Umkreis eines Kreises in 10 radius abstaenden bis 85
std::vector<Geometrie::Point> circle_Points(int distance, Geometrie::Point centroid_circle,
	const Geometrie::Polygon& polygon){
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
// Funktion zum bestimmen des Gesundheitszentrums
Geometrie::Point gesundheitszentrum (int distance, Geometrie::Point centroid_circle,
	const Geometrie::Polygon& polygon){
	std::vector<Geometrie::Point> points = circle_Points(distance, centroid_circle, polygon);
	Geometrie::Point end_point;
	int start_value = points.size();
	int end_value = 0;
	Geometrie::Point centroid = centroid_circle;
	// wir gehen gehen unsere 1 liste von punkten(doerfern) durch und schauen jeden punkt
	// durch ob er ein besserer centroid waere
	do{
		for(const Geometrie::Point& p: points){
			std::cout << "jetzt" << std::endl;
			std::vector<Geometrie::Point> test_points = circle_Points(distance, p, polygon);
			if(test_points.size() > start_value){
				start_value = test_points.size();
				centroid = p;
				}
				// wen der wert vom vorherigem durchlauf gleich dem 2 durchlauf ist returnen wir
				// den vector
			if(start_value == end_value){
				end_point = p;
				return p;
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

	// bester punkt fuer das gesundheitszentrum
	Geometrie::Point gesundheitszent = gesundheitszentrum(10, centroid, polygon);
	// vector mit den punkten innerhalb des radiuses von dem Gesundheitszentrum
	std::vector<Geometrie::Point> gesundheitszentrum_Points = circle_Points(10, gesundheitszent, polygon);
	// Restlichen punkte ausserhalb des radiuses des gesundheitszentrums
	std::vector<Geometrie::Point> end_points = last_points(polygon, gesundheitszent);

	//output
	std::cout << "Gesundheitszentrum: " << "(" << gesundheitszent.getX() <<"|" << gesundheitszent.getY() << ")"<< std::endl;
	std::cout << "Doerfer innerhalb des Radiuses von dem Gesundheitszentrum: " << std::endl;
	int counter = 1;
	for (const Geometrie::Point p : gesundheitszentrum_Points) {
		std::cout << "Das " << counter << "Dorf liegt bei den koordinaten: " << "(" << p.getX() << "|"
		<< p.getY() << ")" << std::endl;
		counter++;
	}
	std::cout << "Restliche doerfer ausserhalb des Radiuses des gesundheitszentrums: " << std::endl;
	for (const Geometrie::Point p : end_points) {
		std::cout << "Das " << counter << "Dorf liegt bei den koordinaten: " << "(" << p.getX() << "|"
		<< p.getY() << ")" << std::endl;
		counter++;
	}



	// Zustaz Plott erstellen mit matplotlibcpp
	std::vector<double> _x_werte;
	std::vector<double> _y_werte;
	for(const Geometrie::Point p : end_points){
		_x_werte.push_back(p.getX());
		_y_werte.push_back(p.getY());
	}

	//std::cout << "groesse ohne algo: " << test.size() << std::endl;
	std::vector<double>x_werte;
	std::vector<double>y_werte;
	for(Geometrie::Point p : gesundheitszentrum_Points){
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
	plt::plot(x_points, y_points, "r-", x_werte, y_werte
	,"bo", _x_werte, _y_werte, "ro");

	// Optional: Fülle das Polygon
	plt::xlabel("X-Achse");
	plt::ylabel("Y-Achse");

	// Titel des Plots
	plt::title("Polygon mit matplotlibcpp");

	// Plot anzeigen
	plt::show();

	return 0;
}
