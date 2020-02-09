#pragma once
#include "i-gene.h"
#include "helper-header.h"

class Triangle : public AGene {
public:
	Triangle() : AGene() {}
	Triangle(QColor& color, std::vector<Coordinates>& coordinates) :
		AGene(color, coordinates)
	{	}

	void mutateHard(int imageWidth, int imageHeight) override;
	void mutateSoft(int imageWidth, int imageHeight) override;
	int getRadius() const override { return -1; };
	void setRadius(int radius) override {  };
};
class Circle : public AGene {
public:
	Circle() :AGene() {}
	Circle(QColor color, std::vector<Coordinates> coordinates, int Radius) :
		AGene(color, coordinates), _radius(Radius) {}

	std::string getName() const {
		return std::string("I'm circle");
	}
	void mutateHard(int imageWidth, int imageHeight) override;
	void mutateSoft(int imageWidth, int imageHeight) override;
	int getRadius() const override { return _radius; };
	void setRadius(int radius) override { _radius = radius; };

private:
	int _radius;
};