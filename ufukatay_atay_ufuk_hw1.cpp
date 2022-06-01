#include <iostream>
#include "Stack.h"
#include "randgen.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

void print(vector<vector<bool>>& valid){
	for(int i=0; i< valid.size(); i++){
		for(int j=0; j<valid[0].size(); j++){				// printing valid elements to check how program goes
			cout << valid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}



int main(){

	int maze_count, m, n;

	cout << "Enter the number of mazes: ";
	cin >> maze_count;

	cout << "Enter the number of rows and columns (M and N): " ;
	cin >> m >> n;

	for (int k = 1; k <= maze_count; k++)
	{
		int knockdown = 0;
		int col = 0;
		int row = m-1;

		vector<vector<cell>> mat(m, vector<cell>(n));			
		vector<vector<bool>> valid(m+2, vector<bool>(n+2, true));  //to force to go unvisited cells

		for(int j=0; j < valid[0].size(); j++)
		{
			valid[0][j]=false;								// making false to borders in order to avoid moving beyond the matrix.
			valid[valid.size()-1][j]=false;
		}
	
		for(int j=0; j < valid.size(); j++)
		{
			valid[j][0]=false;
			valid[j][valid[0].size()-1]=false;
		}

		//print(valid);

		Stack<int> stk;
		RandGen rnd;

		valid[m][1] = false;

		//print(valid);

		while(knockdown < m*n-1)
		{

			int direction = rnd.RandInt(1,4);
			//print(valid);
			//cout << mat[row][col].x << mat[row][col].y << mat[row][col].l << mat[row][col].r << mat[row][col].u << mat[row][col].d << endl << endl;

			//generating a maze with random directions

			if(direction == LEFT && valid[row+1][col])
			{	
				mat[row][col].l = 0;
				mat[row][col-1].r = 0;
				mat[row][col-1].x = mat[row][col].x - 1;
				mat[row][col-1].y = mat[row][col].y;
				stk.push(LEFT);
				valid[row+1][col] = false;
				col--;
				knockdown++;
			}

			else if(direction == RIGHT && valid[row+1][col+2])
			{
				mat[row][col].r = 0;
				mat[row][col+1].l = 0;
				mat[row][col+1].x = mat[row][col].x + 1;
				mat[row][col+1].y = mat[row][col].y;
				stk.push(RIGHT);
				valid[row+1][col+2] = false;
				col++;
				knockdown++;
			}

			else if(direction == UP && valid[row][col+1])
			{
				mat[row][col].u = 0;
				mat[row-1][col].d = 0;
				mat[row-1][col].y = mat[row][col].y + 1;
				mat[row-1][col].x = mat[row][col].x;
				stk.push(UP);
				valid[row][col+1] = false;
				row--;
				knockdown++;
			}

			else if(direction == DOWN && valid[row+2][col+1])
			{
				mat[row][col].d = 0;
				mat[row+1][col].u = 0;
				mat[row+1][col].y = mat[row][col].y - 1;
				mat[row+1][col].x = mat[row][col].x;
				stk.push(DOWN);
				valid[row+2][col+1] = false;
				row++;
				knockdown++;
			}

			//if program cannot find anywhere to go, backtrack using the stack until you find a cell which has an unvisited neighbour cell

			else if((valid[row+1][col] || valid[row+1][col+2] || valid[row+2][col+1] || valid[row][col+1]) == false)
			{			
				int previous;
				stk.pop(previous);
				if(previous == LEFT)
					col++;
				else if(previous == RIGHT)
					col--;
				else if(previous == UP)
					row++;
				else if(previous == DOWN)
					row--;

			}
		}
		ofstream fout;
		string filename;
		filename = "maze_" + to_string(k) + ".txt"; 

		fout.open(filename);
	
		fout << m << " " << n << endl;

		for (int i = m-1; i >= 0 ; i--)
		{
			for (int j = 0; j < n; j++)
			{
				fout << "x=" << mat[i][j].x << " y=" << mat[i][j].y << " l=" << mat[i][j].l << " r=" << mat[i][j].r << " u=" << mat[i][j].u << " d=" << mat[i][j].d << endl;
			}
		}

		fout.close();
		
	}

	cout << "All mazes are generated." << endl << endl;

	int picked_maze_num, entryx, entryy, exitx, exity;

	cout << "Enter a maze ID between 1 to " << maze_count << " inclusive to find a path: ";
	cin >> picked_maze_num;
	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin >> entryx >> entryy;
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin >> exitx >> exity;
	
	ifstream fin;
	string picked_filename, line, gereksiz;

	picked_filename = "maze_" + to_string(picked_maze_num) + ".txt";
	fin.open(picked_filename.c_str());
	getline(fin,gereksiz);  //to get rid of the first row column line.
		
	vector<vector<cell>> mat(m, vector<cell>(n));
	vector<vector<bool>> valid(m+2, vector<bool>(n+2, true));

	for(int j=0; j < valid[0].size(); j++)
	{
		valid[0][j]=false;								// making false to borders in order to avoid moving beyond the matrix.
		valid[valid.size()-1][j]=false;
	}
	
	for(int j=0; j < valid.size(); j++)
	{
		valid[j][0]=false;
		valid[j][valid[0].size()-1]=false;
	}

	//getting data from the file which we have just generated. 

	for (int i = m-1; i >= 0 ; i--)
	{
		for (int j = 0; j < n; j++)
		{
			getline(fin,line);
			int idx = 0;
			while(line.find("=") != string::npos){
				idx = line.find("=");
				line.erase(idx-1, 2);
			}
			istringstream iss(line);
				
			iss >> mat[i][j].x >> mat[i][j].y >> mat[i][j].l >> mat[i][j].r >> mat[i][j].u >> mat[i][j].d;
		}
	}
	int gon = m-1-entryy;
	int ga = entryx;
	int count = 0;
	Stack<cell> steyk;
	steyk.push(mat[m-1-entryy][entryx]);
	valid[m-entryy][entryx+1] = false;
	ofstream output;
	string path_filename;
	path_filename = "maze_" + to_string(picked_maze_num) + "_path_" + to_string(entryx) + "_" + to_string(entryy) + "_" + to_string(exitx) + "_" + to_string(exity) + ".txt"; 

	output.open(path_filename);

	output << steyk.top().x << " " << steyk.top().y << endl; 

	//until stack finds the exit point, path is going to be generated.

	while(!(steyk.top().x == exitx && steyk.top().y == exity))
	{
		if (steyk.top().l == 0 && valid[gon+1][ga]) 
		{
			steyk.push(mat[gon][ga-1]);
			steyk.top().pre = LEFT;
			valid[gon+1][ga] = false;
			ga--;
			count++;

		}

		else if (steyk.top().r == 0 && valid[gon+1][ga+2])
		{
			steyk.push(mat[gon][ga+1]);
			steyk.top().pre = RIGHT;
			valid[gon+1][ga+2] = false;
			ga++;
			count++;
		}

		else if (steyk.top().u == 0 && valid[gon][ga+1])
		{
			steyk.push(mat[gon-1][ga]);
			steyk.top().pre = UP;
			valid[gon][ga+1] = false;
			gon--;
			count++;
		}

		else if (steyk.top().d == 0 && valid[gon+2][ga+1])
		{
			steyk.push(mat[gon+1][ga]);
			steyk.top().pre = DOWN;
			valid[gon+2][ga+1] = false;
			gon++;
			count++;
		}
		
		else
		{			
			cell hucre;
			steyk.pop(hucre);
			count--;
			if(hucre.pre == LEFT)
				ga++;
			else if(hucre.pre == RIGHT)
				ga--;
			else if(hucre.pre == UP)
				gon++;
			else if(hucre.pre == DOWN)
				gon--;
		}
	}

	//to get data with right order, one more stack is needed. 

	Stack<cell> tersten;
	
	for (int i = 0; i < count; i++)
	{
		cell hucre;
		tersten.push(steyk.top());
		steyk.pop(hucre);
	}

	for (int i = 0; i < count; i++)
	{
		cell hucre;
		output << tersten.top().x << " " << tersten.top().y << " " << endl;
		tersten.pop(hucre);
	}
		
	output.close();

	return 0;
}
//Ufuk Atay