#include "resource.h"
#include "display.h"

void draw_logo(int x, int y) {
	start_Render(599, 340);
	Render(0, 0, IDB_BITMAP18);
	Render_all(y, x, y + 600, x + 341);
	end_Render();
}

void draw_sel(int x, int y) {
	Render(x, y, IDB_BITMAP12);
	Render(x + 36, y, IDB_BITMAP13);
	Render(x + 36, y + 36, IDB_BITMAP14);
	Render(x, y + 36, IDB_BITMAP15);
}

void draw_board(int startx, int starty, int boardsize, int nowx, int nowy, int *board, int gmod) {
	start_Render(boardsize * 48 - 1, boardsize * 48 - 1);
	for (int i = 0; i < boardsize; i++) {
		for (int j = 0; j < boardsize; j++) {
			if (i == 0) {
				if (j == 0) Render(j * 48, i * 48, IDB_BITMAP1);
				else if (j == boardsize - 1) Render(j * 48, i * 48, IDB_BITMAP2);
				else Render(j * 48, i * 48, IDB_BITMAP8);
			}
			else if (i == boardsize - 1) {
				if (j == 0) Render(j * 48, i * 48, IDB_BITMAP4);
				else if (j == boardsize - 1) Render(j * 48, i * 48, IDB_BITMAP3);
				else Render(j * 48, i * 48, IDB_BITMAP9);
			}
			else {
				if (j == 0) Render(j * 48, i * 48, IDB_BITMAP10);
				else if (j == boardsize - 1) Render(j * 48, i * 48, IDB_BITMAP11);
				else Render(j * 48, i * 48, IDB_BITMAP7);
			}
			if (i == nowy && j == nowx) draw_sel(j * 48, i * 48);
			if ((*(board + (i * boardsize) + j)) == 1) Render(j * 48 + 4, i * 48 + 4, IDB_BITMAP17);
			else if ((*(board + (i * boardsize) + j))  == 2) Render(j * 48 + 4, i * 48 + 4, IDB_BITMAP16);
		}
	}
	Render_all(starty, startx, starty + boardsize * 48 - 1, startx + boardsize * 48 - 1);
	end_Render();
	//mod에 따라 화살표를 표시하는 부분
	if (gmod > 0) {
		start_Render(48, 48);
		Render(0, 0, IDB_BITMAP21);
		if (nowy == boardsize) draw_sel(0, 0);
		Render_all(492, 1014, 540, 1062);
		end_Render();
	}
	if (gmod > 1) {
		start_Render(48, 48);
		Render(0, 0, IDB_BITMAP19);
		if (nowy == -1) draw_sel(0, 0);
		Render_all(492, 18, 540, 66);
		end_Render();
	}
	if (gmod > 2) {
		start_Render(48, 48);
		Render(0, 0, IDB_BITMAP22);
		if (nowx == -1) draw_sel(0, 0);
		Render_all(18, 492, 66, 540);
		end_Render();
		start_Render(48, 48);
		Render(0, 0, IDB_BITMAP20);
		if (nowx == boardsize) draw_sel(0, 0);
		Render_all(1014, 492, 1062, 540);
		end_Render();
	}
	//돌이 놓이는 좌표를 출력하는걸 추가해야함

}

void draw_stone_state(int startx, int starty, int stone) {
	start_Render(48 - 1, 48 - 1);
	Render(0, 0, IDB_BITMAP7);
	if (stone == 1) draw_sel(0, 0);
	Render(4, 4, IDB_BITMAP17);
	Render_all(starty, startx, starty + 48 - 1, startx + 48 - 1);
	end_Render();
	starty += 48 * 3;
	start_Render(48 - 1, 48 - 1);
	Render(0, 0, IDB_BITMAP7);
	if (stone == 2) draw_sel(0, 0);
	Render(4, 4, IDB_BITMAP16);
	Render_all(starty, startx, starty + 48 - 1, startx + 48 - 1);
	end_Render();
}
