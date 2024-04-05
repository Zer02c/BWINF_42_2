#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <fstream>

namespace Geometrie{

	// klasse point um ein punkt darzustellen
	class Point{
		private:
			double x,y;
		public:
		        Point() : x(0.0), y(0.0){}
			Point(double _x, double _y) : x(_x), y(_y){}

			// funktionen zum returnen der x und y koordinaten
			double getX() const {return x;}
			double getY() const  {return y;}

	};

	// klasse Polygon
	class Polygon{
		private:
			std::vector<Point> points;
		public:
			Polygon(){}

			std::vector<Point> getPoints() const{
				return points;
			}
			
			const Point& getPoint(int index) const{
				return points[index];
			}

			// Funktion um ein Punkt in das Polygon hinzuzufuegen
			void addPoint(double x, double y){
				points.push_back(Point(x,y));
			}

			void addPointsFromVector(const std::vector<Point>& vec) {
				points.insert(points.end(), vec.begin(), vec.end());
			}

			// Funktion zum Bestimmen des Schwerpunktes oder auch Centroid des Polygons
			Point centroid() const {
		         double cx = 0.0, cy = 0.0;
		         double area = 0.0;

		         for (int i = 0; i < points.size(); ++i) {
		             double xi = points[i].getX();
		             double yi = points[i].getY();

		             double xi1 = points[(i + 1) % points.size()].getX();
		             double yi1 = points[(i + 1) % points.size()].getY();

		             double common = xi * yi1 - xi1 * yi;
		             cx += (xi + xi1) * common;
		             cy += (yi + yi1) * common;
		             area += common;
		         }

		         area /= 2.0;
		         cx /= (6 * area);
		         cy /= (6 * area);

		         return Point(cx, cy);
			}

		// Funktion zum schauen ob der punkt innerhalb des polygons liegt oder nicht
			bool isInsidePolygon(const Point& p) const {
				int intersectioncount = 0;

				for(int i = 0; i < points.size(); ++i){
					double xi = points[i].getX();
					double yi = points[i].getY();
					double xi1 = points[(i + 1) % points.size()].getX();
					double yi1 = points[(i + 1) % points.size()].getY();

					if((yi > p.getY()) != (yi1 > p.getY()) && p.getX() < (xi1 - xi) * (p.getY() - yi) / (yi1 - yi) + xi){
						intersectioncount++;
					}
				}

				return intersectioncount % 2 == 1;
			}
		// Funktion zum schauen ob ein kreis das Polygon schneidet oder nicht
		bool intersectsCircle(const Point& center, double radius) const {
			 // Überprüfen, ob das Zentrum des Kreises innerhalb des Polygons liegt
			 if (isInsidePolygon(center)) {
					 return true;
			 }

			 // Überprüfen, ob irgendein Teil des Kreises mit den Polygonkanten schneidet
			 for (int i = 0; i < points.size(); ++i) {
					 double xi = points[i].getX();
					 double yi = points[i].getY();
					 double xi1 = points[(i + 1) % points.size()].getX();
					 double yi1 = points[(i + 1) % points.size()].getY();

					 double dx = xi1 - xi;
					 double dy = yi1 - yi;
					 double len = std::sqrt(dx * dx + dy * dy);
					 double dot = ((center.getX() - xi) * dx + (center.getY() - yi) * dy) / (len * len);

					 double closestX, closestY;

					 if (dot < 0) {
							 closestX = xi;
							 closestY = yi;
					 } else if (dot > 1) {
							 closestX = xi1;
							 closestY = yi1;
					 } else {
							 closestX = xi + dot * dx;
							 closestY = yi + dot * dy;
					 }

					 double distance = std::sqrt((center.getX() - closestX) * (center.getX() - closestX) +
																	(center.getY() - closestY) * (center.getY() - closestY));
					 if (distance <= radius) {
							 return true;
					 }
			 }

			 return false;
	 }
	 // Funktion zum einlesen des Polygons von der file .txt
	 void readPointsFromFile(const std::string& filename) {
		 std::ifstream file(filename);
		if (!file.is_open()) {
			std::cerr << "Fehler beim Öffnen der Datei: " << filename << std::endl;
				return;
		}

		std::string line;
		while (std::getline(file, line)) {
			std::stringstream ss(line);
				double x, y;
				if (ss >> x >> y) {
						addPoint(x, y);
				}
		}

		file.close();
}
	};
};
