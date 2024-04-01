#pragma once

#include <iostream>
#include <vector>

namespace Geometrie{

	// klasse point um ein punkt darzustellen
	class Point{
		private:
			double x,y;
		public:
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
		// Funktion zum schauen ob ein kreis das Polygon schneidet oder nicht
	};
};
