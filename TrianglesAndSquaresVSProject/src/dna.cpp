#include "dna.h"

void DNA::mutateGenotype(int imageWidth, int imageHeight, QImage& originalImage) {
	int numOfGeneToMutate = rand() % genotype.size();

	// this is copy of current values
	std::vector<Coordinates> tempCoor = genotype[numOfGeneToMutate]->getApexes();
	QColor tempColor = genotype[numOfGeneToMutate]->getColorOfGene();

	float old_fitness = fitness;
	//	TODO:: softMutate
	//	if (fitness < 0.65)
	genotype[numOfGeneToMutate]->mutateHard(imageWidth, imageHeight);
	//	else
	//		genotype[numOfGeneToMutate]->mutateSoft(imageWidth, imageHeight);

	calcFitness(originalImage);

	if (fitness < old_fitness) {
		fitness = old_fitness;
		genotype[numOfGeneToMutate]->setColorOfGene(tempColor);
		genotype[numOfGeneToMutate]->setApexes(tempCoor);
	}

}

QImage& DNA::retAnImage(int image_width, int image_height)
{
	QImage& newImage = QImage(image_width, image_height, QImage::Format_ARGB32);
	drawImageFromDNA(newImage);
	return newImage;
}

void DNA::drawImageFromDNA(QImage& image) const
{
	image.fill(gen_img_back_color);
	QPainter* paint = new QPainter(&image);
	for (std::size_t i = 0; i < genotype.size(); i++) {
		paint->setBrush(genotype[i]->getColorOfGene());
		paint->setPen(genotype[i]->getColorOfGene());
		if (genotype[i]->recognizeGene() == 1) {  //traingle
			QPolygon polygon;
			for (Coordinates cor : genotype[i]->getApexes())
				polygon << QPoint(cor.xpos, cor.ypos);
			paint->drawPolygon(polygon);
		}
		if (genotype[i]->recognizeGene() == 0) { //circle
			int r = genotype[i]->getRadius();
			paint->drawEllipse(QPoint(genotype[i]->getApexes()[0].xpos, genotype[i]->getApexes()[0].ypos), r, r);
		}
	}
	delete paint;
}

void DNA::calcFitness(QImage& originalImage)
{
	float fitnessOfDNA = 0;

	//QImage originalImage = orgIm.convertToFormat(QImage::Format_RGB32);
	int imageWidth = originalImage.width();
	int imageHeight = originalImage.height();

	// We should do sth if picture is too big
//int step = 1;

//	if (imageWidth > 1000 && imageHeight > 1000)
//		step = 10;

	QImage imageFromDNA(imageWidth, imageHeight, originalImage.format());
	drawImageFromDNA(imageFromDNA);

	const uchar* firstIm = originalImage.constBits();
	const uchar* seconIm = imageFromDNA.constBits();

	for (int i = 0; i < imageWidth * imageHeight * 4; i++) {
		fitnessOfDNA += abs((int)firstIm[i] - (int)seconIm[i]);
	}
	fitness = 1 - ((fitnessOfDNA / 4) / (imageWidth * imageHeight * (255)));

}

