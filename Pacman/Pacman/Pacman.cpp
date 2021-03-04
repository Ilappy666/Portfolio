// Pacman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>

using namespace std;

class pm_object {
public:
	pm_object();
	void draw();
protected:
	char skin;
private:
};

pm_object::pm_object() {
	skin = 0;
};

void pm_object::draw() {
	cout << skin;
}

class spot : public pm_object {
public:
	enum s_type {
		s_empty,
		s_wall
	};

	spot();
	spot(s_type);
private:
	s_type type;
};

spot::spot() {
	skin = ' ';
	type = s_empty;
};

spot::spot(s_type t) {
	switch (t) {
	case s_empty:
		skin = ' ';
		break;
	case s_wall:
		skin = 'W';
		break;
	}
	type = t;
};

class caracter : public pm_object {
private:
	char currentAction;
	bool isAlive;
public:
	caracter();
	void getAction();
	void applyAction();
	char getCurrentAction();
	bool getIsAlive();
};

caracter::caracter() {
	isAlive = true;
	currentAction = 0;
	skin = 'C';
};

void caracter::getAction() {
	currentAction = static_cast<char>(_getch());
}

bool caracter::getIsAlive() {
	return isAlive;
}

void caracter::applyAction() {
	cout << "Vous avez effectuer : " << currentAction << endl;
	if(currentAction == 27) {
		isAlive = false;
	}
}

char caracter::getCurrentAction() {
	return currentAction;
}

class board {
private:
	int gridSize;
	pm_object** grid;
	caracter car;
public:
	board(caracter);
	void update();
	void draw();
	~board();
	void build();
};

board::board(caracter c) {
	gridSize = 20;
	car = c;
	grid = new pm_object*[gridSize];
	for (int i = 0; i < gridSize; ++i) {
		grid[i] = new pm_object[gridSize];
	}
}

void board::update() {
	char actionToApply = car.getCurrentAction();

	switch (actionToApply) {
	case 'w':
	case 'W':
		// implement the movement and the incorporation of displacement in caracter and board
		break;
	}
};

board::~board() {
	for (int i = 0; i < gridSize; ++i) {
		delete[] grid[i];
	}
	delete[] grid;
};

void board::build() {
	for (int i = 0; i < gridSize; ++i) {
		for (int j = 0; j < gridSize; ++j) {
			if (i == 0 || j == 0 || i == gridSize - 1 || j == gridSize - 1) {
				grid[i][j] = spot(spot::s_wall);
			} else {
				grid[i][j] = spot(spot::s_empty);
			}
		}
	}
};

void board::draw() {
	for (int i = 0; i < gridSize; ++i) {
		for (int j = 0; j < gridSize; ++j) {
			grid[i][j].draw();
		}
		cout << endl;
	}
};


int main() {
	cout << "Pac man!" << endl;
	cout << "Press a enter to start." << endl;

	bool isEndGame = false;

	//int start;
	//cin >> start;
	
	caracter pac;
	board map(pac);
	map.build();
	
	while (!isEndGame) {
		pac.getAction();
		pac.applyAction();

		map.update();
		
		map.draw();

		isEndGame = !pac.getIsAlive();
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
