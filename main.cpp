#include "graph.h"

int main(int argc, char* argv[])
{
	srand(time(NULL));
	bool done = false;
	std::string prompt = "";
	int nLignes = 0;
	int nColonnes = 0;
	int nInstances = 0;
	int nObstacles = 0;

	graph solver = graph();

	//solver.generateProblems(50, 50, 10, 300, "testGen");
	
	while(!done)
	{
		std::cout << "Veuillez entrer un nom de fichier, ou <g> pour générer des problèmes ,ou <q> pour quitter le programme : " << std::endl;
		getline(std::cin, prompt);
		if( ((prompt[0] == 'q') || (prompt[0] == 'Q')) && (prompt.size() == 1) )
		{
			done = true;
		}
		else if( ((prompt[0] == 'g') || (prompt[0] == 'G')) && (prompt.size() == 1) )
		{
			std::cout << "Veuillez entrer le nombre de lignes souhaitées : " << std::endl;
			std::cin >> nLignes;
			std::cout << "Veuillez entrer le nombre de colonnes souhaitées : " << std::endl;
			std::cin >> nColonnes;
			std::cout << "Veuillez entrer le nombre d'instances souhaitées : " << std::endl;
			std::cin >> nInstances;
			std::cout << "Veuillez entrer le nombre d'obstacles souhaités : " << std::endl;
			std::cin >> nObstacles;
			std::cout << "Veuillez entrer le nom du fichier où les problèmes seront sauvegardés : " << std::endl;
			std::cin.ignore();
			getline(std::cin, prompt);
			solver.generateProblems(nLignes, nColonnes, nInstances, nObstacles, prompt);
		}
		else if(solver.readProblems(prompt))
		{
			solver.solveAllProblems();
		}
		else
		{
			std::cout << "L'ouverture du fichier a echoue" << std::endl; 
		}
	}
	std::cout << "Bye bye !" << std::endl;
	return 0;
}
