#include "gene.h"

void Triangle::mutateHard(int imageWidth, int imageHeight)
{
	int n = imageWidth;
	int x = imageHeight;

	// change color of gene
	if (rand() % 1000 > 700) {
		QColor mutatedColor = getColorOfGene();

		int colorTochange = rand() % 4;

		if (colorTochange == 0) mutatedColor.setRed(rand() % 256);
		if (colorTochange == 1) mutatedColor.setGreen(rand() % 256);
		if (colorTochange == 2) mutatedColor.setBlue(rand() % 256);

		if (colorTochange == 3) mutatedColor.setAlpha(rand() % 256);

		setColorOfGene(mutatedColor);
	}
	else {
		int apexToMutate;
		if (getApexes().size() == 0)
			apexToMutate = 0;
		else
			apexToMutate = rand() % getApexes().size();

		while (true) {
			int x = rand() % imageWidth;
			if (x <= imageWidth && x >= 0) {
				setXApexesOf(apexToMutate, x);
				break;
			}
		}

		while (true) {
			int y = rand() % imageHeight;
			if (y <= imageHeight && y >= 0) {
				setYApexesOf(apexToMutate, y);
				break;
			}
		}
	}
}

void Triangle::mutateSoft(int imageWidth, int imageHeight)
{
	int n = imageWidth;
	int x = imageHeight;

	// change color of gene
	if (rand() % 1000 > 700) {
		QColor mutatedColor = getColorOfGene();

		int colorTochange = rand() % 4;

		if (colorTochange == 0) {
			int r = mutatedColor.red();
			do {
				r += rand() % 20 - 40;
			} while (r > -1 && r < 256);

			mutatedColor.setRed(r);
		}
		if (colorTochange == 1) {

			int g = mutatedColor.green();
			do {
				g += rand() % 20 - 40;
			} while (g > -1 && g < 256);

			mutatedColor.setGreen(g);
		}
		if (colorTochange == 2) {
			int b = -1;
			do {
				b = mutatedColor.blue();
				b += rand() % 20 - 40;
			} while (b > -1 && b < 256);

			mutatedColor.setBlue(b);

		}

		if (colorTochange == 3) {
			int a = -1;
			do {
				a = mutatedColor.alpha();
				a += rand() % 20 - 40;
			} while (a > -1 && a < 256);

			mutatedColor.setAlpha(a);

		}

		setColorOfGene(mutatedColor);
	}
	else {
		int apexToMutate;
		if (getApexes().size() == 0)
			apexToMutate = 0;
		else
			apexToMutate = rand() % getApexes().size();

		while (true) {
			int x = -1;
			while (x < 0 || x >imageWidth) {
				x = getXApexesOf(apexToMutate);
				x += rand() % (imageWidth / 5) - imageWidth / 10;
			}
			setXApexesOf(apexToMutate, x);
			break;
		}

		while (true) {
			int y = -1;
			while (y < 0 || y > imageHeight) {
				y = getYApexesOf(apexToMutate);
				y += rand() % (imageHeight / 5) - imageHeight / 10;
			}
			setYApexesOf(apexToMutate, y);
			break;
		}
	}
}

void Circle::mutateHard(int imageWidth, int imageHeight) {

	//change color of gene
	if (rand() % 1000 < 600) {
		QColor mutatedColor = QColor();

		int colorTochange = rand() % 4;

		if (colorTochange == 0) mutatedColor.setRed(rand() % 256);
		if (colorTochange == 1) mutatedColor.setBlue(rand() % 256);
		if (colorTochange == 2) mutatedColor.setGreen(rand() % 256);
		if (colorTochange == 3) mutatedColor.setAlpha(rand() % 256);

		setColorOfGene(mutatedColor);
	}

	//change location and size of gene
	else {
		int apexToMutate = rand() % 2;

		// mutate location of circle's center
		if (apexToMutate == 0)
		{
			while (true) {
				int x = rand() % imageWidth;
				if (x <= imageWidth - _radius && x >= 0 + _radius) {
					setXApexesOf(apexToMutate, x);
					break;
				}
			}

			while (true) {
				int y = rand() % imageHeight;
				if (y <= imageHeight - _radius && y >= 0 + _radius) {
					setYApexesOf(apexToMutate, y);
					break;
				}
			}
		}
		else
		{
			//mutate size of radius
			if (imageWidth <= imageHeight) {
				int newRad = (rand() % imageWidth) / 2;
				setRadius(newRad);
			}
			else {
				int newRad = (rand() % imageHeight) / 2;
				setRadius(newRad);
			}
		}
	}
}

void Circle::mutateSoft(int imageWidth, int imageHeight)
{
	int n = imageWidth;
	int x = imageHeight;
	// change color of gene
	if (rand() % 1000 < 600) {
		QColor mutatedColor = getColorOfGene();
		int colorTochange = rand() % 4;

		if (colorTochange == 0) {
			int r = mutatedColor.red();
			do {
				r += rand() % 20 - 40;
			} while (r > -1 && r < 256);

			mutatedColor.setRed(r);
		}
		if (colorTochange == 1) {

			int g = mutatedColor.green();
			do {
				g += rand() % 20 - 40;
			} while (g > -1 && g < 256);

			mutatedColor.setGreen(g);
		}
		if (colorTochange == 2) {
			int b = -1;
			do {
				b = mutatedColor.blue();
				b += rand() % 20 - 40;
			} while (b > -1 && b < 256);

			mutatedColor.setBlue(b);

		}

		if (colorTochange == 3) {
			int a = -1;
			do {
				a = mutatedColor.alpha();
				a += rand() % 20 - 40;
			} while (a > -1 && a < 256);

			mutatedColor.setAlpha(a);

		}

		setColorOfGene(mutatedColor);
	}
	else {
		int apexToMutate;
		if (getApexes().size() == 0)
			apexToMutate = 0;
		else
			apexToMutate = rand() % (getApexes().size() + 1);

		while (true) {
			// mutate center of Circle
			if (apexToMutate == 0) {
				int x = -1;
				while (x < 0 || x >imageWidth) {
					x = getXApexesOf(apexToMutate);
					x += (rand() % imageWidth) / 10 - (rand() % imageHeight) / 5;
				}
				setXApexesOf(apexToMutate, x);
				int y = -1;
				while (y < 0 || y > imageHeight) {
					y = getYApexesOf(apexToMutate);
					y += rand() % imageHeight / 10 - (rand() % imageWidth) / 5;
				}
				setYApexesOf(apexToMutate, y);
				break;
			}
			// mutate radius
			else {
				int r = 1;
				while (r < 2 || r >imageWidth / 5) {
					r = getRadius();
					r += (rand() / RAND_MAX - 0.5) * 10;
				}
				setRadius(r);
			}
		}
	}
}
