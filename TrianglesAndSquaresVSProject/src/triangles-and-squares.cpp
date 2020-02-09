#include "triangles-and-squares.h"
#include "gene.h"
TrianglesAndSquares::TrianglesAndSquares(QWidget* parent)
	: QMainWindow(parent),
	gen_img_back_color(QColor(255, 255, 255, 0))
{
	ui.setupUi(this);
	// SETTER GROUP
	QGroupBox* setterGroup = new QGroupBox(this);
	setterGroup->setFixedWidth(200);
	setterGroup->setTitle(tr("Program Settings"));


	//
	QGroupBox* figureChooserGroup = new QGroupBox(setterGroup);
	figureChooserGroup->setTitle(tr("Figure"));
	triangles = new QRadioButton(figureChooserGroup);
	triangles->setChecked(true);
	circles = new QRadioButton(figureChooserGroup);
	circles->setCheckable(true);
	both = new QRadioButton(figureChooserGroup);
	both->setCheckable(true);
	triangles->setText(tr("Triangles"));
	circles->setText(tr("Circles"));
	both->setText(tr("Both"));

	triangles->setChecked(true);


	QVBoxLayout* figureChooserGroupLayout = new QVBoxLayout(figureChooserGroup);
	figureChooserGroupLayout->addWidget(triangles);
	figureChooserGroupLayout->addWidget(circles);
	figureChooserGroupLayout->addWidget(both);
	figureChooserGroupLayout->addSpacing(4);
	//
	QGroupBox* algorithmTypeChooserGroup = new QGroupBox(setterGroup);
	algorithmTypeChooserGroup->setTitle(tr("Type of Algorithm"));
	singleParent = new QRadioButton(algorithmTypeChooserGroup);
	singleParent->setChecked(true);
	populationBased = new QRadioButton(algorithmTypeChooserGroup);

	singleParent->setText(tr("Single parent"));
	populationBased->setText(tr("Population Based"));

	QVBoxLayout* algorithmTypeChooserGroupLayout = new QVBoxLayout(algorithmTypeChooserGroup);
	algorithmTypeChooserGroupLayout->addWidget(singleParent);
	algorithmTypeChooserGroupLayout->addWidget(populationBased);

	//

	QGroupBox* genesisQuantityGroup = new QGroupBox(setterGroup);
	genesisQuantitySpinBox = new QSpinBox(genesisQuantityGroup);
	genesisQuantitySpinBox->setSpecialValueText("Unset");
	genesisQuantitySpinBox->setMaximum(999);
	genesisQuantitySpinBox->setMaximumWidth(50);
	genesisQuantitySpinBox->setAlignment(Qt::AlignCenter);
	QLabel* textQuantity = new QLabel(QString("Genesis quantity:"), genesisQuantityGroup);

	QHBoxLayout* genesisQuantityGroupLayout = new QHBoxLayout(genesisQuantityGroup);
	genesisQuantityGroupLayout->addWidget(textQuantity);
	genesisQuantityGroupLayout->addWidget(genesisQuantitySpinBox);

	//
	QGroupBox* populationQuantityGroup = new QGroupBox(setterGroup);
	populationQuantitySpinBox = new QSpinBox(populationQuantityGroup);
	populationQuantitySpinBox->setSpecialValueText("Unset");
	populationQuantitySpinBox->setMaximumWidth(50);
	populationQuantitySpinBox->setAlignment(Qt::AlignCenter);


	QLabel* populationQuantity = new QLabel(QString("Population quantity:"), populationQuantityGroup);


	QHBoxLayout* populationQuantityGroupLayout = new QHBoxLayout(populationQuantityGroup);
	populationQuantityGroupLayout->addWidget(populationQuantity);
	populationQuantityGroupLayout->addWidget(populationQuantitySpinBox);

	//

	QGroupBox* backgroundTypeChooserGroup = new QGroupBox(setterGroup);
	backgroundTypeChooserGroup->setTitle(tr("Set Background"));
	QRadioButton* transparentBackgorund = new QRadioButton(backgroundTypeChooserGroup);
	transparentBackgorund->setText("Transparent");
	transparentBackgorund->setChecked(true);
	connect(transparentBackgorund, SIGNAL(clicked()), this, SLOT(backgroundTransparentSelected()));

	QRadioButton* colorBackgorund = new QRadioButton(backgroundTypeChooserGroup);
	colorBackgorund->setText("Color");

	connect(colorBackgorund, SIGNAL(clicked()), this, SLOT(backgroundColorChooserSelected()));

	QVBoxLayout* backgroundTypeChooserGroupLayout = new QVBoxLayout(backgroundTypeChooserGroup);
	backgroundTypeChooserGroupLayout->addWidget(transparentBackgorund);
	backgroundTypeChooserGroupLayout->addWidget(colorBackgorund);





	QPushButton* loadImage = new QPushButton(setterGroup);
	loadImage->setText(tr("&Load Image"));
	connect(loadImage, SIGNAL(clicked()), this, SLOT(open()));


	QPushButton* startPause = new QPushButton(setterGroup);
	startPause->setText(tr("S&tart/Pause"));

	connect(startPause, SIGNAL(clicked()), this, SLOT(startAndPause()));

	QPushButton* saveImage = new QPushButton(setterGroup);
	saveImage->setText(tr("&Save Image"));
	connect(saveImage, SIGNAL(clicked()), this, SLOT(saveClicked()));



	QVBoxLayout* setterGroupLayout = new QVBoxLayout(setterGroup);
	setterGroupLayout->addWidget(figureChooserGroup);
	setterGroupLayout->addWidget(algorithmTypeChooserGroup);
	setterGroupLayout->addWidget(genesisQuantityGroup);
	setterGroupLayout->addWidget(populationQuantityGroup);
	setterGroupLayout->addWidget(backgroundTypeChooserGroup);

	setterGroupLayout->addStretch(1);

	setterGroupLayout->addWidget(loadImage);
	setterGroupLayout->addWidget(startPause);
	setterGroupLayout->addWidget(saveImage);


	// ORIGINAL IMAGE VIEWER

	originalImageBox = new QLabel(this);

	originalImageBox->setStyleSheet("QLabel{ background-color: #e8e3e3}");

	originalImageBox->setMinimumSize(300, 400);

	originalImage = QImage();


	// GENERATED

	generatedImage = QImage();

	generatedImageBox = new QLabel(this);
	generatedImageBox->setStyleSheet("QLabel{ background-color: #e8e3e3}");
	generatedImageBox->setMinimumSize(300, 400);


	// RESULT
	QGroupBox* resultGroup = new QGroupBox(this);
	resultGroup->setFixedWidth(200);
	resultGroup->setTitle(tr("Results"));

	QGroupBox* numberOfMutationsGroup = new QGroupBox(resultGroup);
	QLabel* numerOfMutationsLabel = new QLabel(QString("Mutations:"), numberOfMutationsGroup);
	numerOfMutations = new QLabel(QString("0"), numberOfMutationsGroup);
	QHBoxLayout* numberOfMutationsGroupLayout = new QHBoxLayout(numberOfMutationsGroup);
	numberOfMutationsGroupLayout->addWidget(numerOfMutationsLabel);
	numberOfMutationsGroupLayout->addWidget(numerOfMutations);


	QGroupBox* timeOfWorkGroup = new QGroupBox(resultGroup);
	QLabel* timeOfWorkLabel = new QLabel(QString("Beneficial:"), timeOfWorkGroup);
	timeOfWork = new QLabel(QString("0"), timeOfWorkGroup);
	QHBoxLayout* timeOfWorkGroupLayout = new QHBoxLayout(timeOfWorkGroup);
	timeOfWorkGroupLayout->addWidget(timeOfWorkLabel);
	timeOfWorkGroupLayout->addWidget(timeOfWork);

	QGroupBox* fittnesGroup = new QGroupBox(resultGroup);
	QLabel* fittnesLabel = new QLabel(QString("Fitness:"), fittnesGroup);
	fittnesLabelNum = new QLabel(QString("0"), fittnesGroup);
	QHBoxLayout* fittnesGroupLayout = new QHBoxLayout(fittnesGroup);
	fittnesGroupLayout->addWidget(fittnesLabel);
	fittnesGroupLayout->addWidget(fittnesLabelNum);

	QVBoxLayout* resultGroupLayout = new  QVBoxLayout(resultGroup);
	resultGroupLayout->addWidget(numberOfMutationsGroup);
	resultGroupLayout->addWidget(timeOfWorkGroup);
	resultGroupLayout->addWidget(fittnesGroup);
	resultGroupLayout->addStretch(1);


	// ALL IN ALL
	QHBoxLayout* viewLayout = new QHBoxLayout(this);
	viewLayout->addWidget(setterGroup);
	//viewLayout->addStretch(1);
	viewLayout->addWidget(originalImageBox);
	//viewLayout->addStretch(1);
	viewLayout->addWidget(generatedImageBox);
	//viewLayout->addSt retch(1);
	viewLayout->addWidget(resultGroup);

	QFrame* setupFrame = new QFrame();
	setupFrame->setLayout(viewLayout);

	this->setCentralWidget(setupFrame);
}

void TrianglesAndSquares::startAndPause() {

	timeForWork = !timeForWork;
	if (singleParent->isChecked() && genesisQuantitySpinBox->text() == "Unset") {
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
			tr("Wrong value of genesis quantity spin box."));
		return;
	}
	else if (populationBased->isChecked() && (genesisQuantitySpinBox->text() == "Unset"
		|| genesisQuantitySpinBox->text() == "Unset"
		|| populationQuantitySpinBox->text() == "Unset"
		|| genesisQuantitySpinBox->value() < 2
		|| populationQuantitySpinBox->value() < 2)) {
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
			tr("Wrong value of genesis quantity spin box \n or population quantity spin box."));
		return;
	}
	if (timeForWork == TRUE)
		startAlgorithm();
}

void TrianglesAndSquares::startAlgorithm()
{
	if (originalImage.isNull())
	{
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
			tr("Specify image"));
		return;
	}
	numberOfGenes = genesisQuantitySpinBox->value();
	image_width = originalImage.width();
	image_height = originalImage.height();

	if (generatedImage.width() != originalImage.width())
		generatedImage = QImage(originalImage.width(), originalImage.height(), QImage::Format_ARGB32);


	// WORKING FOR SINGLE PARENT
	if (!algorithm.get()
		|| (singleParent->isChecked() && algorithm->getDescription() != "Single parent")
		|| (populationBased->isChecked() && algorithm->getDescription() != "Population Based"))
	{
		if (singleParent->isChecked()) {
			std::vector<AGene*> newGenotype;
			if (triangles->isChecked()) {
				for (int i = 0; i < numberOfGenes; i++) {
					newGenotype.push_back(new Triangle(QColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256), std::vector<Coordinates>{Coordinates{ rand() % (image_width + 1), rand() % (image_height + 1) },
						Coordinates{ rand() % (image_width + 1), rand() % (image_height + 1) }, Coordinates{ rand() % (image_width + 1), rand() % (image_height + 1) }}));
				}
			}
			else if (circles->isChecked()) {
				for (int i = 0; i < numberOfGenes; i++) {
					newGenotype.push_back(new Circle(QColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256), std::vector<Coordinates>{Coordinates{ rand() % (image_width + 1), rand() % (image_height + 1) } },
						rand() % image_width / 6));
				}
			}
			else if (both->isChecked()) {
				int pickTriangle = -1;
				for (int i = 0; i < numberOfGenes; i++) {
					pickTriangle = rand() % 3 % 2; //circle or triangle??
					if (pickTriangle == 1) {
						newGenotype.push_back(new Triangle(QColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256), std::vector<Coordinates>{Coordinates{ rand() % (image_width + 1), rand() % (image_height + 1) },
							Coordinates{ rand() % (image_width + 1), rand() % (image_height + 1) }, Coordinates{ rand() % (image_width + 1), rand() % (image_height + 1) }}));
					}
					else if (pickTriangle == 0) {
						newGenotype.push_back(new Circle(QColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256), std::vector<Coordinates>{Coordinates{ rand() % (image_width + 1), rand() % (image_height + 1) } },
							rand() % image_width / 6));
					}
				}
			}
			DNA new_Dna(newGenotype, originalImage, gen_img_back_color);

			algorithm = std::move(std::make_unique<SingleParentAlgorithm>(originalImage, new_Dna, 0));
		}
		else {
			numberOfIndividualsInPopulation = populationQuantitySpinBox->value();
			std::vector<DNA>sol;
			for (int i = 0; i < numberOfIndividualsInPopulation; i++) {
				std::vector<AGene*> newGenotype;
				if (triangles->isChecked()) {
					for (int i = 0; i < numberOfGenes; i++) {
						newGenotype.push_back(new Triangle(QColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256), std::vector<Coordinates>{Coordinates{ rand() % (image_width + 1), rand() % (image_height + 1) },
							Coordinates{ rand() % (image_width + 1), rand() % (image_height + 1) }, Coordinates{ rand() % (image_width + 1), rand() % (image_height + 1) }}));
					}
				}
				else if (circles->isChecked()) {
					for (int i = 0; i < numberOfGenes; i++) {
						newGenotype.push_back(new Circle(QColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256), std::vector<Coordinates>{Coordinates{ rand() % (image_width + 1), rand() % (image_height + 1) } },
							rand() % image_width / 6));
					}
				}
				else if (both->isChecked()) {
					int pickTriangle = -1;
					for (int i = 0; i < numberOfGenes; i++) {
						pickTriangle = rand() % 3 % 2; //circle or triangle??
						if (pickTriangle == 1) {
							newGenotype.push_back(new Triangle(QColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256), std::vector<Coordinates>{Coordinates{ rand() % (image_width + 1), rand() % (image_height + 1) },
								Coordinates{ rand() % (image_width + 1), rand() % (image_height + 1) }, Coordinates{ rand() % (image_width + 1), rand() % (image_height + 1) }}));
						}
						else if (pickTriangle == 0) {
							newGenotype.push_back(new Circle(QColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256), std::vector<Coordinates>{Coordinates{ rand() % (image_width + 1), rand() % (image_height + 1) } }, rand() % image_width / 6));
						}
					}
				}
				DNA new_Dna(newGenotype, originalImage, gen_img_back_color);

				sol.push_back(new_Dna);
			}
			std::sort(sol.begin(), sol.end(), [](DNA a, DNA b) {return a.getFitness() > b.getFitness(); });
			algorithm = std::move(std::make_unique<PopulationBasedAlgorithm>(originalImage, sol));
		}
		currentFitness = -1;
		i = 0;
		benef = 0;
	}


	while (currentFitness < 1) {
		if (timeForWork == false)
			break;
		i += 1;
		numerOfMutations->setText(QString::number(i));
		algorithm->turn();
		if (algorithm->getFitness() != currentFitness) {
			algorithm->getRefToBestSolutions().drawImageFromDNA(generatedImage);

			displayImage(generatedImage, generatedImage, generatedImageBox);

			currentFitness = algorithm->getFitness();
			fittnesLabelNum->setText(QString::number(currentFitness));

			benef++;
			timeOfWork->setText(QString::number(benef));
		}
		QCoreApplication::processEvents();

	}
}

void TrianglesAndSquares::resizeEvent(QResizeEvent* re)
{
	if (!originalImage.isNull())
		displayImage(originalImage, originalImage, originalImageBox);
	if (!generatedImage.isNull())
		displayImage(generatedImage, generatedImage, generatedImageBox);
}

void TrianglesAndSquares::backgroundColorChooserSelected()
{
	QColor backColor = QColorDialog::getColor(Qt::white, this, "Choose Color");
	if (backColor.isValid())
		gen_img_back_color = backColor;
}

void TrianglesAndSquares::backgroundTransparentSelected()
{
	gen_img_back_color = QColor(255, 255, 255, 0);
}

bool TrianglesAndSquares::loadFile(const QString& fileName)
{
	QImage newImage = QImage(fileName);
	newImage = newImage.convertToFormat(QImage::Format_ARGB32);

	if (newImage.isNull()) {
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
			tr("Cannot load file"));
		return false;
	}
	algorithm = nullptr;

	displayImage(newImage, originalImage, originalImageBox);

	setWindowFilePath(fileName);
	return true;
}

void TrianglesAndSquares::displayImage(const QImage& newImage, QImage& imageKeaper, QLabel* boxForImage)
{
	if (newImage != imageKeaper)
		imageKeaper = newImage;

	boxForImage->setPixmap(QPixmap::fromImage(newImage).scaled(boxForImage->width(), boxForImage->height(), Qt::KeepAspectRatio));
}

static void initializeImageFileDialog(QFileDialog& dialog, QFileDialog::AcceptMode acceptMode)
{
	static bool firstDialog = true;
	if (firstDialog) {
		firstDialog = false;
		const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
		dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
	}
	QStringList mimeTypeFilters;
	const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
		? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
	foreach(const QByteArray & mimeTypeName, supportedMimeTypes)
		mimeTypeFilters.append(mimeTypeName);
	mimeTypeFilters.sort();
	dialog.setMimeTypeFilters(mimeTypeFilters);
	dialog.selectMimeTypeFilter("image/png");
	if (acceptMode == QFileDialog::AcceptSave)
		dialog.setDefaultSuffix("PNG");
}

void TrianglesAndSquares::open()
{
	QFileDialog dialog(this, tr("Open File"));
	initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);
	dialog.setDirectory(QDir::currentPath());
	while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

void TrianglesAndSquares::saveClicked() const
{
	QString fileName = QFileDialog::getSaveFileName(new QWidget, tr("Save File"), QDir::currentPath(), tr("Images (*.png *.xpm *.jpg)"));
	if (fileName.isEmpty())
		return;
	else {
		generatedImage.save(fileName);

	}
}