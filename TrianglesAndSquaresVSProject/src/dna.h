#pragma once

#include "i-gene.h"
#include <QPainter>


class DNA {
public:
	//DNA(QColor& backColor):gen_img_back_color(backColor) {}
	DNA() {}
	//~DNA() { deleteObj(); }
	DNA(std::vector<AGene*>genes, QImage& originalImage, QColor& backColor) :
		genotype(genes),
		gen_img_back_color(backColor)
	{
		calcFitness(originalImage);
	}

	DNA(std::vector<AGene*>genes, QImage& originalImage) :
		genotype(genes)
	{
		calcFitness(originalImage);
	}

	std::vector<AGene*> getGenes() const { return genotype; }

	// this will mutate single gene in DNA
	void mutateGenotype(int imageWidth, int imageHeight, QImage& originalImage);

	//AGene* mutateThisGen(int imageWidth, int imageHeight, QImage& originalImage);

	QImage& retAnImage(int image_width, int image_height);

	void drawImageFromDNA(QImage& image) const;

	void setFitness(float newFitness) { fitness = newFitness; }

	float getFitness() const { return fitness; }

	void calcFitness(QImage& originalImage);

	void addGene(AGene* newGene) {
		genotype.push_back(newGene);
	}


private:
	std::vector<AGene*> genotype;
	float fitness = -1;
	QColor gen_img_back_color;
};