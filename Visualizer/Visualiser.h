#ifndef VISUALISER_HPP
#define VISUALISER_HPP

#include <windows.h>
#include <iostream>
#include <string>
#include <atlbase.h>
#include <atlconv.h>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
#define nextLine std::getline(csvStream, csvCol, ',')

class graph{
public:
	vector<vector<int>> adj;
	int nodes;
	double ACC;
	double GCC;
	double DIAM;
	double APL;
	double CPL;
	string fileName;
};

/*
NOTE : DO NOT CHANGE THIS FUNCTION
This function returns the path of this file
*/
std::string ExePath() {
	CHAR szPath[MAX_PATH];
	GetModuleFileNameA(NULL, szPath, MAX_PATH);
	std::string::size_type pos = std::string(szPath).find_last_of("\\/");
	std::string path = std::string(szPath);
	return path.substr(0, pos);
}
/*
NOTE : DO NOT CHANGE THIS FUNCTION
This function exports the graph in a format which is readable by the visualiser.exe
*/
void exportGraph(string path, graph g){
	std::ofstream file(path, std::ios::out);
	for (int i = 0; i < g.adj.size(); i++){
		for (int j = 0; j < g.adj.size(); j++){
			file << g.adj[i][j] << ",";
		}
		file << endl;
	}
	file << "ACC" << "," << g.ACC << endl;
	file << "GCC" << "," << g.GCC << endl;
	file << "DIAM" << "," << g.DIAM << endl;
	file << "APL" << "," << g.APL << endl;
	file << "CPL" << "," << g.CPL << endl;
	file.close();
	return;
}

graph readGraph(string path){
	graph g;
	std::ifstream file;
	file.open(path);
	if (!file.is_open()) {
		cout << path << " - FILE NOT FOUND" << endl;
		system("PAUSE");
		exit(0);
	}
	std::string csvLine;
	int flag = true;
	int nodes = 0;
	int row = 0;
	while (std::getline(file, csvLine)){
		std::istringstream csvStream(csvLine);
		std::string csvCol;
		while (nextLine){
			if (flag){
				vector<int> vec;
				vec.push_back(std::stoi(csvCol));
				while (nextLine){
					nodes++;
					vec.push_back(std::stoi(csvCol));
				}
				g.adj.push_back(vec);
				row++;
				flag = false;
			}
			else if (nodes > 0){
				vector<int> vec;
				vec.push_back(std::stoi(csvCol));
				while (nextLine){
					vec.push_back(std::stoi(csvCol));
				}
				g.adj.push_back(vec);
				row++;
				nodes--;
			}
			else if (csvCol == "ACC"){ nextLine; g.ACC = std::stod(csvCol); }
			else if (csvCol == "GCC"){ nextLine; g.GCC = std::stod(csvCol); }
			else if (csvCol == "DIAM"){ nextLine; g.DIAM = std::stod(csvCol); }
			else if (csvCol == "APL"){ nextLine; g.APL = std::stod(csvCol); }
			else if (csvCol == "CPL"){ nextLine; g.CPL = std::stod(csvCol); }
		}
	}
	return g;
}

void printGraph(graph &g){
	for (int i = 0; i < g.adj.size(); i++){
		for (int j = 0; j < g.adj.size(); j++){
			cout << g.adj[i][j] << " ";
		}
		cout << "" << endl;
	}
	cout << "ACC" << g.ACC << endl;
	cout << "GCC" << g.GCC << endl;
	cout << "DIAM" << g.DIAM << endl;
	cout << "APL" << g.APL << endl;
	cout << "CPL" << g.CPL << endl;
}
/*
NOTE : DO NOT CHANGE THIS FUNCTION
*/
void exportFilePath(string path, string fileName){
	std::ofstream file(path + "filePath.txt", std::ios::out);
	file << path << endl;
	file << fileName << endl;
	file.close();
}
/*
NOTE : DO NOT CHANGE THIS FUNCTION
This function will take graph as an input and
1) create a csv file for the input graph
2) create a filePath.txt file which will help visualiser.exe to read in the csv file
3) display the graph using the visualiser.exe

*/
void displayGraph(graph &g){

	string excPath = ExePath();
	string fileName = g.fileName;
	string graphPath = excPath + "\\" + fileName + ".csv";
	exportGraph(graphPath, g);
	exportFilePath(excPath + "\\", fileName);
	std::string path = excPath + "\\visualiser.exe";

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	LPCTSTR;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	USES_CONVERSION;
	// Start the child process. 
	if (!CreateProcessW(NULL,   // No module name (use command line)
		A2W(path.c_str()),        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

#endif