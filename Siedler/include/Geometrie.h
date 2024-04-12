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

			// Funktion um ein Punkt in das Polygon hinzuzufuegen
			void addPoint(double x, double y){
				points.push_back(Point(x,y));
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

					if((yi > p.getY()) != (yi1 > p.getY()) && p.getX() < (xi1 - xi) *
					 (p.getY() - yi) / (yi1 - yi) + xi){
						intersectioncount++;
					}
				}

				return intersectioncount % 2 == 1;
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
