#pragma once
#include "helper-header.h"
#include <qwidget.h>
#include <vector>

struct Coordinates
{
	int xpos;
	int ypos;
};

class AGene {
public:
	AGene() {}
	AGene(QColor color, std::vector<Coordinates>& coordinates) :
		colorOfGene(color),
		apexes(coordinates)
	{	}
	virtual void mutateHard(int imageWidth, int imageHeight) = 0;
	virtual void mutateSoft(int imageWidth, int imageHeight) = 0;
	virtual void setRadius(int radius) = 0;
	virtual int  getRadius() const = 0;

	QColor getColorOfGene() const { return colorOfGene; }
	void setColorOfGene(QColor& newColorOfGene) { colorOfGene = newColorOfGene; }

	std::vector<Coordinates> getApexes() const { return apexes; }
	void setApexes(std::vector<Coordinates> newApexes) { apexes = newApexes; }

	int recognizeGene();
	int getXApexesOf(int num) { return apexes[num].xpos; }
	int getYApexesOf(int num) { return apexes[num].ypos; }
	void setXApexesOf(int num, int value) { apexes[num].xpos = value; }
	void setYApexesOf(int num, int value) { apexes[num].ypos = value; }

private:
	QColor colorOfGene;
	std::vector<Coordinates> apexes;
};

