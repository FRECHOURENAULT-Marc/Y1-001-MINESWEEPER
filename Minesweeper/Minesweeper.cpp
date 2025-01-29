
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdlib.h>

/*	"\033[3;42;30mTexting\033[0m"	font style ; background ; font color				MEMO
Name            FG  BG
Black           30  40
Red             31  41
Green           32  42
Yellow          33  43
Blue            34  44
Magenta         35  45
Cyan            36  46
White           37  47
Bright Black    90  100
Bright Red      91  101
Bright Green    92  102
Bright Yellow   93  103
Bright Blue     94  104
Bright Magenta  95  105
Bright Cyan     96  106
Bright White    97  107
*/

//AMELIORER ALGO ALEATOIRE
//REGLER AFFICHAGE LVL 2 BAS
//REGLER PROB LVL 3
//Il y a beaucoup de fonctions...

struct Case
{
	int adjacentMine;
	bool mine;
	bool flag;
	bool hidden;
};

struct Grid 
{
	Case** ppCase;	//Tab à double co
	int width;	//X
	int height; //Y
};

Case* GetCase(Grid* pGrid, int x, int y)		//Retourne pointeur d'une case, pour éviter d'aller à des endroits non autorisés
{
	if (x < 0 || x >= pGrid->height)
		return nullptr;

	if (y < 0 || y >= pGrid->width)
		return nullptr;

	return &pGrid->ppCase[x][y];
}

void TopSeparator(Grid* pGrid)		//affiche le séparateur horizontal
{
	std::cout << "  \033[2;47;30m+";
	for (int k = 0; k < pGrid->width; k++)
	{
		std::cout << "\033[2;47;30m";
		std::cout << "---+";
		std::cout << "\033[0m";
	}
}
void DisplayMap(Grid* pGrid)			//Affiche la zone de jeu
{
	//"\033[2;42;30m A \033[0m" VERT = case 0
	//"\033[2;43;30m A \033[0m" JAUNE = case 1+
	//"\033[2;47;30m A \033[0m" BLANC = separator
	//"\033[2;105;30m A \033[0m" B MAGENTA = flag
	//"\033[2;41;30m A \033[0m" ROUGE = mine
	system("cls");

	std::cout << "   ";				//Affichache coordonnées X
	for (int k = 0; k < pGrid->width; k++)
	{
		if (k > 9)
			std::cout << " " << k << " ";
		else
			std::cout << " " << k << "  ";
	}
	std::cout << std::endl;

	for (int i = 0; i < pGrid->height; i++)
	{
		TopSeparator(pGrid);			//premier séparateur horizontal
		std::cout << std::endl;
		if (i > 9)						//Affichache coordonnées Y
			std::cout << i;
		else
			std::cout << i << " ";

		for (int j = 0; j < pGrid->width; j++)		//1er séparateur de la ligne
		{
			std::cout << "\033[2;47;30m";
			std::cout << "|";
			std::cout << "\033[0m";
			if (pGrid->ppCase[i][j].flag == true)		//drapeau
			{
				std::cout << "\033[2;105;30m";
				std::cout << " F ";
				std::cout << "\033[0m";
			}
			else if (pGrid->ppCase[i][j].hidden == false)		//sinon si visible
			{
				if (pGrid->ppCase[i][j].mine == true)			//si mine
				{
					std::cout << "\033[2;41;30m";
					std::cout << " * ";
					std::cout << "\033[0m";
				}
				else if (pGrid->ppCase[i][j].adjacentMine == 0)	//si adjacent mine 0
				{
					std::cout << "\033[2;42;30m";
					std::cout << " " << pGrid->ppCase[i][j].adjacentMine << " ";
					std::cout << "\033[0m";
				}
				else 		//si adjacent mine 1+
				{
					std::cout << "\033[2;43;30m";
					std::cout << " " << pGrid->ppCase[i][j].adjacentMine << " ";
					std::cout << "\033[0m";
				}
			}
			else if (pGrid->ppCase[i][j].hidden == true)		//si cachée
				std::cout << "   ";
		}
		std::cout << "\033[2;47;30m";			//dernier séparateur de la ligne
		std::cout << "|" << std::endl;
		std::cout << "\033[0m";
	}
	TopSeparator(pGrid);		//dernier séparateur horizontal
	std::cout << std::endl;
}
void ClearBuffer()		//Vide le buffer en cas d'entrée incorrecte (j'ai pas tout compris ce qu'est un buffer) 
{
	while (true)
	{
		char c = getchar();
		if (c == '\n')
			break;
	}
}

void CaseSetup(Grid* pGrid)		//Def toutes les valeurs d'origines des cases (avant le tirage aléatoire)
{
	for (int i = 0; i < pGrid->width; i++)
	{
		for (int j = 0; j < pGrid->height; j++)
		{
			pGrid->ppCase[i][j].mine = false;
			pGrid->ppCase[i][j].flag = 0;
			pGrid->ppCase[i][j].hidden = 1;
			pGrid->ppCase[i][j].adjacentMine = 0;
		}
	}
}
void GetRandomMineCase(Grid* pGrid)		//Def d'une case minée pseudo-aléatoirement (et vérif qu'elle l'était pas) -> méthode utilisée peu opti
{
	int rdmx = std::rand() % pGrid->width + 0;
	int rdmy = std::rand() % pGrid->height + 0;

	if (pGrid->ppCase[rdmx][rdmy].mine == true)
	{
		GetRandomMineCase(pGrid);
		//int rdmx = std::rand() % xlength + 0;
		//int rdmy = std::rand() % ylength + 0;
	}
	pGrid->ppCase[rdmx][rdmy].mine = true;
}
void SetDifficulty(Grid* pGrid)
{
	int diff = 1;
	std::cout << "Difficulte : 1 ou 2 ? (3 en travaux)" << std::endl;
	std::cin >> diff;

	if (diff < 1 || diff > 3 || std::cin.fail())
	{
		ClearBuffer();
		std::cin.clear();
		std::cout << "Entree non valide, verifier votre saisie." << std::endl;
		SetDifficulty(pGrid);
	}
	else
	{
		switch (diff)
		{
		case 1:
			pGrid->width = 9;
			pGrid->height = 9;
			break;
		case 2:
			pGrid->width = 16;
			pGrid->height = 16;
			break;
		case 3:
			pGrid->width = 30;
			pGrid->height = 16;
			break;
		}
	}
}

void GetMineAround(Grid* pGrid)		//Compte le nb de mines autour d'une case
{
	for (int i = 0; i < pGrid->width; i++)
	{
		for (int j = 0; j < pGrid->height; j++)
		{
			pGrid->ppCase[i][j].adjacentMine = 0;
			for (int k = 0; k < 8; k++)
			{
				int direction[8][2]		//Def cases à vérif autour
				{
					{-1,1},
					{0,1},
					{1,1},
					{-1,0},
					{1,0},
					{-1,-1},
					{0,-1},
					{1,-1},
				};
				int xn = i + direction[k][0];
				int yn = j + direction[k][1];
				Case* c = GetCase(pGrid, xn, yn);

				if (c != nullptr)		//Vérif cases existent
				{
					if (c->mine == true)
						pGrid->ppCase[i][j].adjacentMine++;
				}
			}

		}

	}
}
void RevealCase(Grid* pGrid, int x, int y)		//révèle la case cible, et les cases aux alentours ssi elles ont adjacenteMine = 0
{
	Case* c = GetCase(pGrid, x, y);
	if (c == nullptr)
		return;

	if (c->hidden == false)
		return;

	if (c->flag == true)
		return;

	c->hidden = false;

	if (c->adjacentMine > 0)
		return;

	int direction[8][2]		//Def cases à vérif autour
	{
		{-1,1},
		{0,1},
		{1,1},
		{-1,0},
		{1,0},
		{-1,-1},
		{0,-1},
		{1,-1},
	};

	for (int i = 0; i < 8; i++)
	{
		int xn = x + direction[i][0];
		int yn = y + direction[i][1];
		RevealCase(pGrid, xn, yn);
	}
}
void SetCaseToFlag(Grid* pGrid, int x, int y)		//vérif si case déjà révélée ou marquée et met le .flag en true
{
	if (pGrid->ppCase[x][y].hidden == true)
	{
		if (pGrid->ppCase[x][y].flag == true)
			pGrid->ppCase[x][y].flag = false;
		else
			pGrid->ppCase[x][y].flag = true;
	}
	else if (pGrid->ppCase[x][y].hidden == false)
	{
		std::cout << "Case deja revelee"<<std::endl;
		return;
	}


}

int GetUserCoordX(Grid* pGrid)
{
	int userCoX = NULL;
	std::cin >> userCoX;
	if (userCoX < 0 || userCoX > pGrid->width || std::cin.fail())
	{
		ClearBuffer();
		std::cin.clear();
		std::cout << "Entree non valide, verifier votre saisie." << std::endl;
		GetUserCoordX(pGrid);
	}
	else
		return userCoX;
}
int GetUserCoordY(Grid* pGrid)
{
	int userCoY = NULL;
	std::cin >> userCoY;
	if (userCoY < 0 || userCoY > pGrid->height || std::cin.fail())
	{
		ClearBuffer();
		std::cin.clear();
		std::cout << "Entree non valide, verifier votre saisie." << std::endl;
		GetUserCoordY(pGrid);
	}
	else
		return userCoY;
}

bool Victory(Grid* pGrid, int x, int y)		//vérifie les conditions pour donner la victoire
{
	int hiddenCase = 0;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (pGrid->ppCase[i][j].hidden == true)
				hiddenCase++;
		}
	}
	if (hiddenCase == 0.15 * pGrid->height * pGrid->width)		//0.15*size = nombre de mines
		return true;
	else
		return false;
}
void DefeatRevealMine(Grid* pGrid)		//révèle toute les mines à la fin d'une partie perdu
{
	for (int i = 0; i < pGrid->width; i++)
	{
		for (int j = 0; j < pGrid->height; j++)
		{
			if (pGrid->ppCase[i][j].mine == true)
				pGrid->ppCase[i][j].hidden = false;
		}
	}
	DisplayMap(pGrid);
}

void PlayGame(); //Proto pour relancer
void NewGame(Grid* pGrid)	//Demande à l'utilisateur si il veur relancer un partie ou arreter
{
	std::cout << "Veux tu rejouer ? ";
	int again = 0;
	std::cin >> again;
	if (std::cin.fail())
	{
		ClearBuffer();
		std::cin.clear();
		std::cout << "Entree non valide, verifier votre saisie." << std::endl;
		NewGame(pGrid);
	}
	else if (again == 1)
	{
		system("cls");
		PlayGame();
	}
	else if (again == 0)
		exit;
}
void PlayGame()		//Gère le déroulement de la partie
{
	Grid grid;		//Crée le tableau à 2 coordonnées
	SetDifficulty(&grid);

	grid.ppCase = (Case**)malloc(sizeof(Case) * grid.width); //initilisation du tableau à 2 coordonnées
	for (int i = 0; i < grid.width; i++)
		grid.ppCase[i] = (Case*)malloc(sizeof(Case) * grid.height);

	CaseSetup(&grid); //initilisation des valeurs de Case dans le tableau

	srand(time(NULL));		//initialisation de la seed du random (pour que ce soit plus aléatoire)
	for (int i = 0; i < (0.15 * grid.width * grid.height); i++)
		GetRandomMineCase(&grid);

	GetMineAround(&grid);		//Remplis les valeurs des adjacentMine
	DisplayMap(&grid);

	while (true)		//Boucle pour répéter les tours jusqu'à la victoire ou defaite
	{
		std::cout << "Quelle case veux tu selectionner ? (X puis Y)"<<std::endl;
		int xUser, yUser;		//j'y arrivais pas donc c pas ouf (x et y inversés)
		yUser = GetUserCoordX(&grid);	// vérif l'entrée correcte des valeur
		xUser = GetUserCoordX(&grid);
		
		std::cout << "Que veux tu faire ? (0 pour reveler, 1 pour marquer/demarquer)" << std::endl;
		int action = 0;
		std::cin >> action;
		if (std::cin.fail())
		{
			ClearBuffer();
			std::cin.clear();
			std::cout << "Entree non valide, verifier votre saisie." << std::endl;
		}

		if (action == 0)	//révèle les cases
		{
			RevealCase(&grid, xUser, yUser);
			if (grid.ppCase[xUser][yUser].mine == true)		//Vérif si case révélée est pas minée (si oui fin)
			{
				DefeatRevealMine(&grid);
				std::cout << "Tu as perdu, dommage." << std::endl;
				break;
			}
		}
		if (action == 1)	//met un drapeau
			SetCaseToFlag(&grid, xUser, yUser);
		DisplayMap(&grid);

		

		if (Victory(&grid, grid.width, grid.height) == true)	//si toutes les cases non minées sont révélées alors victoire
		{
			std::cout << "Tu as gagne, bravo !"<<std::endl;
			break;
		}
	}
	NewGame(&grid);
}
int main()		//le main qui permet de lancer la partie (possibilté de faire plusieurs petits jeux...)
{
	PlayGame();
}
