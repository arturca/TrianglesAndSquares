#pragma once
#include "helper-header.h"
//#include "triangles-and-squares.h"
#include "dna.h"


class IAlgorithm {
public:
	IAlgorithm(QImage& orgIm) :
		original_image(orgIm),
		image_width(orgIm.width()),
		image_height(orgIm.height())
	{	}

	virtual DNA getBestSolution() const = 0;
	virtual const DNA& getRefToBestSolutions() const = 0;
	virtual void turn() = 0;
	virtual float getFitness() const = 0;
	virtual std::string getDescription() const = 0;

protected:
	QImage& original_image;
	int image_width;
	int image_height;
};