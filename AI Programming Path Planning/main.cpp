#include <SDL.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Nodes.h"
#include "PathSearch.h"

SDL_Window* AIWindow = 0;
SDL_Renderer* AIRenderer = 0;

bool Initialise(const char*, int, int, int, int, int);
void Render(SDL_Rect);
void ReadingFile(std::ifstream &File);
void SetGridEdges(PathSearch);
void Update(bool, SDL_Rect);
bool ChangeNodes(bool, int);
void MenuText();
void Wipe();

// Function main
int main(int argc, char* argv[])
{

	bool AIRunLoop = false;

	//If statement used to check that initialisation has worked correctly, ending the program if something was incorrect
	if (Initialise("AI Path Planner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Node.GetGrid_x() * 40, Node.GetGrid_y() * 40, SDL_WINDOW_SHOWN))
	{
		AIRunLoop = true;
	}
	else
	{
		return 1;
	}

	const int TotalNodes = Node.GetTotalNodes();
	SDL_Rect Tile;

	for (int i = 0; i < Node.GetTotalNodes(); i++)
	{
		Grid.SetPath(i, Node.GetTotalNodes() + 1);
	};

	std::ifstream File("NodesFile.txt", std::ios::in);

	ReadingFile(File);

	Tile.h = 40;
	Tile.w = 40;

	SetGridEdges(Grid);

	Update(AIRunLoop, Tile);

	SDL_Quit();
	return 0;
};

// Function used to initialise SDL2
bool Initialise(const char* header, int x, int y, int h, int w, int flags)
{
	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		// if SDL initialises, the if statement is run and sets the variables for AIWindow
		AIWindow = SDL_CreateWindow(header, x, y,
			h, w, flags);
		// if the window creation succeeded create our renderer
			if (AIWindow != 0)
			{
				AIRenderer = SDL_CreateRenderer(AIWindow, -1, 0);
			}
	}
	else
	{
		//means SDL failed to initialise
		return false;
	}
	//means SDL initialised correctly
	return true;
};

// Function used to render the window
void Render(SDL_Rect Tile)
{
	Tile.x = 0;
	Tile.y = 0;

	// Clear the window to set Colour
	SDL_RenderClear(AIRenderer);
	
	for (int i = 0; i < Node.GetTotalNodes(); i++)
	{
		Node.SetNode_x(Tile.x, i);
		Node.SetNode_y(Tile.y, i);

		if (Node.GetNodeValues(i) == 1)
		{
			// Set Render Colour
			SDL_SetRenderDrawColor(AIRenderer, 0, 0, 0, 0);
			Node.SetClosedNodes(true, i);
		}
		else if(Node.GetNodeValues(i) == 0)
		{
			// Set Render Colour
			SDL_SetRenderDrawColor(AIRenderer, 255, 255, 255, 255);
			Node.SetClosedNodes(false, i);
		}

		// Check for Start Node
		else if (Node.GetNodeValues(i) == 2)
		{
			// Set Render Colour
			SDL_SetRenderDrawColor(AIRenderer, 0, 255, 0, 255);
			Node.SetStartNode(i);
		}
		else if (Node.GetNodeValues(i) == 3)
		{
			// Set Render Colour
			SDL_SetRenderDrawColor(AIRenderer, 255, 0, 0, 255);
			Node.SetEndNode(i);
		};
		if (i == Grid.GetPath(i))
		{
			SDL_SetRenderDrawColor(AIRenderer, 0, 0, 255, 255);
		}

		// Render the Tile
		SDL_RenderFillRect(AIRenderer, &Tile);

		Tile.x += 40;

		if (Tile.x >= Node.GetGrid_x() * 40)
		{
			Tile.x = 0;
			Tile.y += 40;
		};
	};

	// Set Render Colour
	SDL_SetRenderDrawColor(AIRenderer, 255, 255, 255, 255);

	// Display the Window
	SDL_RenderPresent(AIRenderer);
};

// Function used to read numbers from the file NodesFile.txt
void ReadingFile(std::ifstream &File)
{
	int FileNums;
	std::vector<int> NodeNums;

	while (File >> FileNums) {
		NodeNums.push_back(FileNums);
	};

	for (int i = 0; i < NodeNums.size(); i++)
	{
		Node.SetNodeValues(NodeNums[i], i);
	};

	File.close();
};

void SetGridEdges(PathSearch Grid)
{
		int count;

	for (int y = 0; y < Node.GetGrid_y(); y++)
	{

		for (int x = 0; x < Node.GetGrid_x(); x++)
		{
			count = x;

			if (y > 0)
			{
				count = count + Node.GetGrid_x() * (y);
			}
			if (count - Node.GetGrid_x() >= 0)
			{
				Grid.NodeEdge(count, count - Node.GetGrid_x());
			}
			if ((count + 1) % Node.GetGrid_x() != 0)
			{
				Grid.NodeEdge(count, count + 1);
			}
			if (count + Node.GetGrid_x() < Node.GetTotalNodes())
			{
				Grid.NodeEdge(count, count + Node.GetGrid_x());
			}
			if (((count - 1) % Node.GetGrid_x() != Node.GetGrid_x() - 1) && (count != 0))
			{
				Grid.NodeEdge(count, count - 1);
			}
		}
	}
}

void Update(bool AIRunLoop, SDL_Rect Tile)
{
	bool SearchDone = false;
	bool StartSet = false;
	bool EndSet = false;
	bool BlackandWhite = false;
	bool Black = false;
	bool White = false;

	MenuText();

	while (AIRunLoop)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				AIRunLoop = false;
			};
			if (event.type == SDL_KEYDOWN)
			{
				
				if (event.key.keysym.sym == SDLK_1)
				{
					BlackandWhite = false;
				};
				if (event.key.keysym.sym == SDLK_2)
				{
					BlackandWhite = true;
				};
				if (event.key.keysym.sym == SDLK_3)
				{
					if (Node.GetStartNode() != (Node.GetTotalNodes() + 1) && Node.GetEndNode() != (Node.GetTotalNodes() + 1))
					{
						if (SearchDone == false)
						{
							Grid.BreadthFirstSearch();
							SearchDone = true;
							Black = true;
							White = true;
						};
					};
				};
				if (event.key.keysym.sym == SDLK_4)
				{
					Wipe();
					StartSet = false;
					EndSet = false;
					Black = false;
					White = false;
					SearchDone = false;
					std::ifstream File("NodesFile.txt", std::ios::in);
					ReadingFile(File);
				};
				if (event.key.keysym.sym == SDLK_5)
				{
					Wipe();
					StartSet = false;
					EndSet = false;
					Black = false;
					White = false;
					SearchDone = false;
					std::ifstream File("NodesFile2.txt", std::ios::in);
					ReadingFile(File);
				};
				if (event.key.keysym.sym == SDLK_6)
				{
					Wipe();
					StartSet = false;
					EndSet = false;
					Black = false;
					White = false;
					SearchDone = false;
					std::ifstream File("NodesFile3.txt", std::ios::in);
					ReadingFile(File);
				};
				if (event.key.keysym.sym == SDLK_7)
				{
					Wipe();
					StartSet = false;
					EndSet = false;
					Black = false;
					White = false;
					SearchDone = false;
					std::ifstream File("NodesFile4.txt", std::ios::in);
					ReadingFile(File);
				};
				if (event.key.keysym.sym == SDLK_8)
				{
					for (int i = 0; i < Node.GetTotalNodes(); i++)
					{
						Grid.SetPath(i, Node.GetTotalNodes() + 1);				
					};
					Node.GetStartNode();
					Node.GetEndNode();
					SearchDone = false;
					Black = false;
					White = false;
					system("cls");
					MenuText();
				};
				if (event.key.keysym.sym == SDLK_9)
				{
					for (int i = 0; i < Node.GetTotalNodes(); i++)
					{
						Grid.SetPath(i, Node.GetTotalNodes() + 1);
						if (Node.GetNodeValues(i) == 2 || Node.GetNodeValues(i) == 3)
						{
							Node.SetNodeValues(0, i);
						};
					};
					Node.SetStartNode(Node.GetTotalNodes() + 1);
					Node.SetEndNode(Node.GetTotalNodes() + 1);
					StartSet = false;
					EndSet = false;
					Black = false;
					White = false;
					SearchDone = false;
					system("cls");
					MenuText();
				};
				if (event.key.keysym.sym == SDLK_0)
				{
					for (int i = 0; i < Node.GetTotalNodes(); i++)
					{
						Grid.SetPath(i, Node.GetTotalNodes() + 1);
						Node.SetNodeValues(0, i);
					};
					Node.SetStartNode(Node.GetTotalNodes() + 1);
					Node.SetEndNode(Node.GetTotalNodes() + 1);
					StartSet = false;
					EndSet = false;
					Black = false;
					White = false;
					SearchDone = false;
					system("cls");
					MenuText();
				};
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					AIRunLoop = false;
				};
			};

			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (BlackandWhite == false)
				{
					if (event.button.button == 1)
					{
						if (StartSet == false)
						{
							StartSet = ChangeNodes(StartSet, 2);
						};
					}
					if (event.button.button == 3)
					{
						if (EndSet == false)
						{
							EndSet = ChangeNodes(EndSet, 3);
						};

					};
				}
				if (BlackandWhite == true)
				{
					if (event.button.button == 1)
					{
						if (White == false)
						{
							White = ChangeNodes(false, 0);
						};
					}
					if (event.button.button == 3)
					{
						if (Black == false)
						{
							Black = ChangeNodes(false, 1);
						};
					};
				};
			};

			Render(Tile);

		};
	};
};

bool ChangeNodes(bool StateSet, int NodeValue)
{
	int x;
	int y;
	int arrayn;
	SDL_GetMouseState(&x, &y);

	for (int Gridy = 0; Gridy < Node.GetGrid_y(); Gridy++)
	{
		for (int Gridx = 0; Gridx < Node.GetGrid_x(); Gridx++)
		{
			if (x >= (Gridx * 40) && x < ((Gridx + 1) * 40) && y >= (Gridy * 40) && y < ((Gridy + 1) * 40))
			{
				if (y > 0)
				{
					arrayn = ((Node.GetGrid_x() * Gridy) + Gridx);
				}
				else
				{
					arrayn = Gridx;
				};
				//NodeValue for White
				if (NodeValue == 0)
				{
					if (Node.GetNodeValues(arrayn) != 2 && Node.GetNodeValues(arrayn) != 3)
					{
						Node.SetNodeValues(0, arrayn);
					};
				}
				//NodeValue for Black
				else if (NodeValue == 1)
				{
					if (Node.GetNodeValues(arrayn) != 2 && Node.GetNodeValues(arrayn) != 3)
					{
						Node.SetNodeValues(1, arrayn);
					};				
				}
				//NodeValue for StartNode
				else if (NodeValue == 2)
				{
					if (Node.GetNodeValues(arrayn) != 1)
					{
						Node.SetNodeValues(2, arrayn);
						StateSet = true;
					};
				}
				//NodeValue for EndNode
				else if (NodeValue == 3)
				{
					if (Node.GetNodeValues(arrayn) != 1)
					{
						Node.SetNodeValues(3, arrayn);
						StateSet = true;
					};
				}

			};

			if (StateSet == true)
			{
				break;
			};

		};

		if (StateSet == true)
		{
			break;
		};

	};
	return StateSet;
};

void MenuText()
{
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "Welcome to the AI Path Planning System" << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "1) Press 1 to place the Start/End node for searching using the mouse buttons" << std::endl;
	std::cout << "2) Press 2 to place blank spaces and collision walls using the mouse buttons" << std::endl;
	std::cout << "3) Press 3 to search for the shortest path between 2 nodes using Breadth First" << std::endl;
	std::cout << "4) Press 4, 5, 6 or 7 to choose different layouts" << std::endl;
	std::cout << "5) Press 8 to reset the path but keep the layout, start and end nodes" << std::endl;
	std::cout << "6) Press 9 to reset the start and end nodes" << std::endl;
	std::cout << "7) Press 0 to completely reset the whole grid to blank" << std::endl;
}

void Wipe()
{
	for (int i = 0; i < Node.GetTotalNodes(); i++)
	{
		Grid.SetPath(i, Node.GetTotalNodes() + 1);
		Node.SetNodeValues(0, i);
	};
	Node.SetStartNode(Node.GetTotalNodes() + 1);
	Node.SetEndNode(Node.GetTotalNodes() + 1);
	system("cls");
	MenuText();
}