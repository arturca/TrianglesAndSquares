#pragma once

#include "helper-header.h"
#include "i-algorithm.h"

class SingleParentAlgorithm : public IAlgorithm {
public:

	SingleParentAlgorithm(QImage& orgIm, DNA sol, unsigned int solToKill) :
		IAlgorithm(orgIm),
		solutions(sol)
	{	}

	DNA getBestSolution()  const override { return solutions; } // /*return solutions[0];*/ 
	const DNA& getRefToBestSolutions() const override { return solutions; }
	float getFitness() const override { return solutions.getFitness(); }
	void turn() override;
	std::string getDescription() const override { return "Single parent"; };


private:
	DNA solutions;
};

class PopulationBasedAlgorithm : public IAlgorithm {
public:
	PopulationBasedAlgorithm(QImage& orgIm, std::vector<DNA> sols) :
		IAlgorithm(orgIm),
		solutions(sols)
	{
		size_of_population = sols.size();
	}

	DNA getBestSolution()  const override { return solutions[0]; }
	const DNA& getRefToBestSolutions() const override { return solutions[0]; }
	float getFitness() const override { return solutions[0].getFitness(); }
	void turn() override;
	std::string getDescription() const override { return "Population Based"; };
private:
	std::vector<DNA> solutions;
	std::size_t size_of_population;
};