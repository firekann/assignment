#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <time.h>
#include "resource.h"
#include "all.h"

const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

int screenx = 0;
int screeny = 0;
int board[19][19];
int boardsize = 19;
int nowx = 0;
int nowy = 0;
//1은 흑돌 2는 백돌
int stone = 1;
int change_stone = 1;
int win_state = 0;
int end_game = 0;
//스크린 상태 0은 메뉴 1~는 게임 종류
int screen_state = 0;

void menu();
void connect6(int gmod);

int QHD;
/*QHD환경에서는 아래 주석표시를 지워주세요.*/
zQHD = 23;

int main() {
	system("title 중력 육목 게임");
	if(QHD) system("mode con cols=240 lines=68");
	else fullscreen();
	remove_scrollbar();
	system("color 0F");
	CursorView(0);
	
	while (1) {
		draw_logo(165, 660);
		gotoxy(79 + QHD, 35);
		printf("계속 하려면 Enter를 눌러주세요.");
		if (getkey_input_sel(nowx, nowy, board, boardsize, &stone, &win_state, &end_game, &change_stone)) break;
	}
	Sleep(100);
	system("cls");

	while (1) {
		if (screen_state == 0) menu();
		else if (screen_state == 1) connect6(0);
		else if (screen_state == 2) connect6(1);
		else if (screen_state == 3) connect6(2);
		else if (screen_state == 4) connect6(3);
	}
}

void menu() {
	nowy = 0;
	//1부터 시작해서 진행됨
	while (1) {
		draw_logo(165, 660);
		getkey_input_move(&nowx, &nowy, 5, 0);
		for (int i = 0; i < 5; i++) {
			gotoxy(84 + QHD, 35 + i);
			printf(" ");
			gotoxy(103 + QHD, 35 + i);
			printf(" ");
		}
		gotoxy(84 + QHD, 35 + nowy);
		printf(">");
		gotoxy(103 + QHD, 35 + nowy);
		printf("<");
		gotoxy(86 + QHD, 35);
		printf("   일반  육목   ");
		gotoxy(86 + QHD, 36);
		printf("중력  육목 mod 1");
		gotoxy(86 + QHD, 37);
		printf("중력  육목 mod 2");
		gotoxy(86 + QHD, 38);
		printf("중력  육목 mod 3");
		gotoxy(86 + QHD, 39);
		printf("      끄기      ");
		if (getkey_input_sel(nowx, nowy, board, 5, &stone, &win_state, &end_game, &change_stone)) break;
		Sleep(70);
	}
	screen_state = nowy + 1;
	if (screen_state == 5) exit(0);
	Sleep(100);
	system("cls");
}

void connect6(int gmod) {
	Sleep(300);
	boardsize = 19;
	for (int i = 0; i < boardsize; i++) for (int j = 0; j < boardsize; j++) board[i][j] = 0;
	end_game = 0;
	nowx = nowy = 0;
	stone = change_stone = 1;
	while (1) {
		if (end_game) break;
		//방향키 입력을 받아서 이동을 처리하는 함수
		getkey_input_move(&nowx, &nowy, boardsize, gmod);
		//엔터키 입력을 받아서 돌을 두는 함수
		getkey_input_sel(nowx, nowy, board, boardsize, &stone, &win_state, &end_game, &change_stone);
		//게임 판을 그리는 함수
		//인자로 시작 위치를 입력받음
		draw_board(84, 84, boardsize, nowx, nowy, board, gmod);
		//게임 상태를 표시하는 함수들
		draw_stone_state(108, 1164, stone);
		Sleep(70);
	}
	//승리한 쪽을 출력하고 현재 게임모드를 계속할지 메뉴로 갈지 게임을 끌지 고른다.
	Sleep(100);
	system("cls");
	nowy = 0;
	while (1) {
		start_Render(48, 48);
		Render(0, 0, IDB_BITMAP7);
		if (win_state == 1) Render(4, 4, IDB_BITMAP17);
		else if (win_state == 2) Render(4, 4, IDB_BITMAP16);
		Render_all(912, 500, 960, 548);
		end_Render();
		getkey_input_move(&nowx, &nowy, 3, 0);
		for (int i = 0; i < 3; i++) {
			gotoxy(84 + QHD, 35 + i);
			printf(" ");
			gotoxy(103 + QHD, 35 + i);
			printf(" ");
		}
		gotoxy(84 + QHD, 35 + nowy);
		printf(">");
		gotoxy(103 + QHD, 35 + nowy);
		printf("<");
		gotoxy(86 + QHD, 35);
		printf("  메뉴로  가기  ");
		gotoxy(86 + QHD, 36);
		printf("   계속  하기   ");
		gotoxy(86 + QHD, 37);
		printf("      끄기      ");
		if (getkey_input_sel(nowx, nowy, board, 3, &stone, &win_state, &end_game, &change_stone)) break;
		Sleep(70);
	}
	if (nowy == 0) screen_state = 0;
	if (nowy == 2) exit(0);
	Sleep(100);
	system("cls");
}
