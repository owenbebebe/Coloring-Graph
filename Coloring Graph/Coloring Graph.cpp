// Coloring Graph.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <fstream>
#include <vector>
#include <iostream>
#include <map>


using namespace std;

//add color pushing a false onto every verticies
void addcolor(vector<int> &color) {
    int size = color.size();
    color.push_back(size);
}

int main()
{
	cout << "*****Welcome to Coloring Graph******" << endl;
    string filename;
    cout << "Please Enter the File Name: ";
    cin >> filename;
    ifstream infile;
    infile.open(filename);
    if (!infile.is_open()) {
        cout << "Can't open this file!" << endl << endl;
    }
    //at this point have successfully read the file
    //store it in a 2d vector
    int i, j, size;
    if (infile >> i) {
        size = i;
        infile >> i;
    }
    //create a vector that is size*size
    vector<vector<bool>> board(size, vector<bool> (size));
    while (infile >> i && infile >> j) {
        //i = first num
        //j = second num
        board[i][j] = true;
        board[j][i] = true;
        //vertex connects itself too
        board[i][i] = true;
        board[j][j] = true;
    }
    infile.close();
    //create a 2d vector that has all of the verticies with its color
    vector<int> color;
    vector<int> visited(size, -1);
    //add the first available color
    addcolor(color);
    //assign the first color to the first verticies
    addcolor(color);
    //go through the board of edges
    for (int i = 0; i < size; i++) {
        //check through its adjacency vertexes
        map<int, int> color_adj;
        for (int x : color) {
            color_adj[x] = 0;
        }
        for (int j = 0; j < size; j++) {
            //if there is an edge between them check for their colors
            if (board[i][j] == 1 && visited[j] != -1) {
                //assign the closest number
                color_adj[visited[j]] = 1;
            }
        }
        bool hit = false;
        for (auto it = color_adj.begin(); it != color_adj.end() && hit == false; it++) {
            if (it->second == 0) {
                hit = true;
                visited[i] = it->first;
            }
        }
        if (hit == false) {
            addcolor(color);
            visited[i] = color.size() - 1;
        }
    }
    ofstream output(filename + "_output");
    output << color.size() << endl;
    for (int i = 0; i < visited.size(); i++) {
        output << visited[i]  << " "; 
    }
    output.close();

}

