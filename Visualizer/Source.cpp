#include "Visualiser.h"


void _tmain(int argc, char *argv[])
{
	cout << "HELLO WORLD" << endl;

	/* Reading graph from a file*/
	/*Change the path in the input to the readGraph function below*/
	graph g = readGraph("C:\\Users\\ktayal\\Documents\\Solution_test.csv");
	printGraph(g, true);
	g.fileName = "graph1";
	/* Displaying the graph*/
	displayGraph(g, true);

	for (int i = 0; i < 5; i++){
		Sleep(1000);
		std::cout << "next " << i << std::endl;
	}

	/* Reading graph from a file*/
	/*Change the path in the input to the readGraph function below*/
	g = readGraph("C:\\Users\\ktayal\\Documents\\Solution_test1.csv");
	printGraph(g, false);
	g.fileName = "graph2";
	/* Displaying another graph*/
	displayGraph(g, false);

	for (int i = 0; i < 5; i++){
		Sleep(1000);
		std::cout << "next " << i << std::endl;
	}
	system("PAUSE");
}