#include <iostream>
#include <vector>	// container
#include <time.h>	// time
#include <conio.h>	// _getch
#include <Windows.h>// SetConsoleCursorPosition

using namespace std;

void play_game();
void gotoXY(int x, int y);
void make_problem(vector<int>& problemBuf, int level);
void display_game(vector<int>& problem, vector<int>& answer, int level);
void display_problem(vector<int>& problem, int level);
void display_answer(vector<int>& answer);

enum ArrowKey {
	UP = 72,
	RIGHT = 77,
	DOWN = 80,
	LEFT = 75
};


int main() {
	play_game();

	return 0;
}

void gotoXY(int x, int y) {
	COORD pos = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void make_problem(vector<int>& problemBuf, int level) {
	// 문제를 제작.
	// 난수 생성.
	int arrow;
	int numberOfArrow;

	problemBuf.clear();

	srand((unsigned int)time(NULL));

	if (1 <= level && level <= 3) {
		numberOfArrow = 5;
	} else if (3 < level && level <= 7) {
		numberOfArrow = 7;
	} else { // 7 < level <= 10
		numberOfArrow = 10;
	}

	for (int i = 0; i < numberOfArrow; i++) {
		arrow = rand() % 4;
		problemBuf.push_back(arrow);
	}
}

void play_game() {
	// 게임 시작.
	vector<int> problem, answer;
	string displayProblem, displayAnswer;
	int level = 1;
	char input;

	displayProblem = displayAnswer = "";
	make_problem(problem, level);

	while (level <= 10) {
		// Refrash Display
		display_game(problem, answer, level);

		input = _getch();

		switch (input) {
			case UP:
				answer.push_back(0);
				break;
			case RIGHT:
				answer.push_back(1);
				break;
			case DOWN:
				answer.push_back(2);
				break;
			case LEFT:
				answer.push_back(3);
				break;
			default:
				break;
		}

		if (problem == answer) {
			level++; // Level up

			answer.clear();
			make_problem(problem, level);
		} else if (answer.size() == problem.size()) {
			// Wrong answer
			answer.clear();
		} else {
			// None
		}
	}
}

void display_game(vector<int>& problem, vector<int>& answer, int level) {
	display_problem(problem, level);
	display_answer(answer);
}

void display_problem(vector<int>& problem, int level) {
	string displayProblem = "";
	system("cls");
	gotoXY(5, 4);
	cout << level;

	gotoXY(5, 5);
	for (auto k = problem.begin(); k != problem.end(); k++) {
		switch (*k) {
			case 0: // UP
				displayProblem += "↑";
				break;
			case 1: // RIGHT
				displayProblem += "→";
				break;
			case 2: // DOWN
				displayProblem += "↓";
				break;
			case 3: // LEFT
				displayProblem += "←";
				break;
			default:
				break;
		}
	}

	cout << displayProblem;
}

void display_answer(vector<int>& answer) {
	string displayAnswer = "";

	gotoXY(5, 6);
	for (auto k = answer.begin(); k != answer.end(); k++) {
		switch (*k) {
		case 0: // UP
			displayAnswer += "↑";
			break;
		case 1: // RIGHT
			displayAnswer += "→";
			break;
		case 2: // DOWN
			displayAnswer += "↓";
			break;
		case 3: // LEFT
			displayAnswer += "←";
			break;
		default:
			break;
		}
	}

	cout << displayAnswer;
}

void timer() {
	// 문제를 해결하기 위한 총 시간 (1 분)
}