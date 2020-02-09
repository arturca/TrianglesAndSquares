#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UI_triangles-and-squares.h"
#include <QtWidgets>
#include "algorithm.h"

class TrianglesAndSquares : public QMainWindow
{
	Q_OBJECT
public:
	TrianglesAndSquares(QWidget* parent = Q_NULLPTR);

public slots:
	void open();
	void saveClicked() const;
	bool TrianglesAndSquares::loadFile(const QString& fileName);
	void displayImage(const QImage& newImage, QImage& imageKeaper, QLabel* boxForImage);
	void startAlgorithm();
	void resizeEvent(QResizeEvent*);
	void startAndPause();


	void backgroundColorChooserSelected();
	void backgroundTransparentSelected();

private:
	Ui::TrianglesAndSquaresClass ui;

	std::unique_ptr<IAlgorithm> algorithm;


	int numberOfGenes = 0;
	int numberOfIndividualsInPopulation = 0;
	int image_width;
	int image_height;

	float currentFitness = -1;
	int i = 0;
	int benef = 0;

	QImage originalImage;
	QLabel* originalImageBox;
	QLabel* fittnesLabelNum;

	QLabel* generatedImageBox;
	QImage generatedImage;

	QSpinBox* genesisQuantitySpinBox;
	QSpinBox* populationQuantitySpinBox;

	bool timeForWork = false;
	QLabel* numerOfMutations;
	QLabel* timeOfWork;
	QPainter* paint = new QPainter(&generatedImage);
	QRadioButton* singleParent;
	QRadioButton* populationBased;
	QRadioButton* triangles;
	QRadioButton* circles;
	QRadioButton* both;
	QColor gen_img_back_color;
};
