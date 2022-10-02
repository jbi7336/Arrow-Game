/*
*	메이플에 있는거와 같은 같은 화살표 맞추기 게임.
*	키보드 입력을 받아 화면에 표시되며, 입력된 순서가 다르거나 입력된 길이가 길어지면 초기화
*	제한시간 내에 맞추지 못한다면 실패.
*/

#include <iostream>
#include <vector>	// container
#include <time.h>	// time
#include <conio.h>	// _getch
#include <Windows.h>// SetConsoleCursorPosition
#include <thread>	// thread

#define FIRSTLOW 6
#define SECONDLOW 8
#define TIMELIMIT 60

using namespace std;

void select_clear();
void timer(bool* flag);
void play_game(int select);
void gotoXY(int x, int y);
void make_problem(vector<int>& problemBuf, int level);
void display_menu(int y);
void display_menu_refrash(int& select);
void display_game(vector<int>& problem, vector<int>& answer, int level);
void display_answer(vector<int>& answer);
void display_arrow(vector<int>& temp);
void display_select(int select);
void display_complete();
void display_BOOM();

bool compare_vector(vector<int>& problem, vector<int>& answer);

enum ArrowKey {
	UP = 72,
	RIGHT = 77,
	DOWN = 80,
	LEFT = 75,
	ENTER = 13
};

int main() {
	int select;
	
	display_menu_refrash(select);
	play_game(select);

	return 0;
}

void gotoXY(int x, int y) {
	COORD pos = { x * 2, y };

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

void play_game(int select) {
	vector<int> problem, answer;
	thread timeCount;

	bool flag = true; // Time Out check
	int level = 1;
	char input;


	// 게임시작 선택 시 타이머 동작.
	if (select == FIRSTLOW) {
		timeCount = thread(timer, &flag);
		timeCount.detach(); // 쓰레드를 독립적으로 전환. 끝나는 걸 기다리지 않음. 안전한 종료 가능.
	} else {
		// None
	}

	make_problem(problem, level);
	display_game(problem, answer, level);

	while (level <= 10 && select == FIRSTLOW) {
		// Refrash Display
		display_answer(answer);

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
			display_game(problem, answer, level);
		} else if (!compare_vector(problem, answer)) {
			// Wrong answer
			answer.clear();
		} else {
			// None
		}

		if (!flag) {
			break;
		} else {
			// None
		}
	}

	timeCount.~thread();

	if (!flag) {
		display_BOOM();
	} else {
		display_complete();
	}
}

bool compare_vector(vector<int>& problem, vector<int>& answer) {
	int index = answer.size();

	if (index == 0) {
		return false;
	} else {
		// None
	}

	if (problem[index - 1] == answer[index - 1]) {
		return true;
	} else {
		// None
	}

	return false;
}

void display_menu(int select) {
	system("cls");

	gotoXY(10, 2);
	cout << "================================================================================";
	gotoXY(10, 10);
	cout << "================================================================================";

	display_select(select);
}

void display_select(int select) {
	switch (select) {
		case FIRSTLOW:
			select_clear();
			gotoXY(25, select);
			cout << "▶";
			break;
		case SECONDLOW:
			select_clear();
			gotoXY(25, select);
			cout << "▶";
			break;
		default:
			break;
	}
}

void select_clear() {
	gotoXY(27, FIRSTLOW);
	cout << "\33[2K" << "게임시작";

	gotoXY(27, SECONDLOW);
	cout << "\33[2K" << "게임종료";
}

void display_menu_refrash(int& select) {
	char input;
	bool flag = false;
	select = FIRSTLOW;

	display_menu(select);
	while (1) {
		display_select(select);
		input = _getch();

		switch (input) {
			case UP:
				select = select - 2;
				break;
			case DOWN:
				select = select + 2;
				break;
			case ENTER:
				flag = true;
				break;
			default:
				break;
		}

		if (select < FIRSTLOW) {
			select = FIRSTLOW;
		} else if (select > SECONDLOW) {
			select = SECONDLOW;
		} else {
			// None
		}

		if (flag) {
			return;
		} else {
			// None
		}
	}
}

void display_game(vector<int>& problem, vector<int>& answer, int level) {
	string displayProblem = "";
	system("cls");
	gotoXY(10, 2);
	cout << "================================================================================";
	gotoXY(10, 10);
	cout << "================================================================================";

	gotoXY(23, 5);
	cout << level;

	gotoXY(25, FIRSTLOW);
	display_arrow(problem);

	display_answer(answer);
}

void display_answer(vector<int>& answer) {
	gotoXY(25, SECONDLOW);
	cout << "\33[2K";
	display_arrow(answer);
}

void display_arrow(vector<int>& temp) {
	string arrow = "";

	for (auto k = temp.begin(); k != temp.end(); k++) {
		switch (*k) {
		case 0: // UP
			arrow += "↑";
			break;
		case 1: // RIGHT
			arrow += "→";
			break;
		case 2: // DOWN
			arrow += "↓";
			break;
		case 3: // LEFT
			arrow += "←";
			break;
		default:
			break;
		}

		arrow += " ";
	}

	cout << arrow;
}

void display_complete() {
	system("cls");
	
	gotoXY(10, 2);
	cout << "================================================================================\n\n";
	
	gotoXY(27, FIRSTLOW);
	cout << "COMPLETE\n\n\n";
	
	gotoXY(10, 10);
	cout << "================================================================================" << endl;
}

void display_BOOM() {
	system("cls");

	gotoXY(10, 2);
	cout << "================================================================================\n\n";

	gotoXY(27, FIRSTLOW);
	cout << "BOOM\n\n\n";

	gotoXY(10, 10);
	cout << "================================================================================" << endl;
}


void timer(bool* flag) {
	// 문제를 해결하기 위한 총 시간
    clock_t start, end;
    double preTime, curTime;

    start = end = clock();

    preTime = double(end - start) / CLOCKS_PER_SEC;
    while (1) {
        end = clock();
        curTime = double(end - start) / CLOCKS_PER_SEC;

		if ((TIMELIMIT - curTime) < 0) {
			*flag = false;
			return;
		}

        if ((curTime - preTime) >= 0.01) {
            preTime = curTime;
            
			gotoXY(0, 0);
			printf_s("\33[2K");
			gotoXY(27, 4);
			printf_s("\33[2K");

            printf_s("%.2f", TIMELIMIT - curTime);
        }
    }
}