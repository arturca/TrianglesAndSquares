#include "algorithm.h"
#include "helper-header.h"



void SingleParentAlgorithm::turn()
{
	solutions.mutateGenotype(image_width, image_height, original_image);
}


void PopulationBasedAlgorithm::turn()
{

	// TODO: user 
	// lets kill half of our solution...
	std::size_t size_of_sol = solutions.size();
	std::size_t num_of_genes = solutions[0].getGenes().size();


	for (std::size_t i = size_of_sol / 2; i < size_of_sol; i++) {
		int numToRand = rand() % num_of_genes;

		for (std::size_t numOfGene = 0; numOfGene < num_of_genes; numOfGene++) {
			if (solutions[i - size_of_sol / 2].getFitness() != solutions[(i - size_of_sol / 2) + 1].getFitness())
			{
				if (numToRand == numOfGene)
					solutions[i].getGenes()[numOfGene]->mutateHard(image_width, image_height);
				else {
					if (solutions[i].getGenes()[numOfGene]->recognizeGene() == solutions[(i - size_of_sol / 2) + numOfGene % 2].getGenes()[numOfGene]->recognizeGene()) {
						solutions[i].getGenes()[numOfGene]->setApexes(solutions[(i - size_of_sol / 2) + numOfGene % 2].getGenes()[numOfGene]->getApexes());
						solutions[i].getGenes()[numOfGene]->setColorOfGene(solutions[(i - size_of_sol / 2) + numOfGene % 2].getGenes()[numOfGene]->getColorOfGene());
					}
				}


			}
		}
		solutions[i].calcFitness(original_image);

	}
	std::sort(solutions.begin(), solutions.end(), [](DNA a, DNA b) {return a.getFitness() > b.getFitness(); });

}