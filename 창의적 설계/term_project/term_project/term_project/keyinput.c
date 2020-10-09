#include <Windows.h>
#include "rule.h"

void getkey_input_move(int *tmpx, int *tmpy, int size, int gmod) {
	//-1~19������ ���ڵ�� nowx, nowy�� Ű���� �Է¿� ���� �ٲٴ� �Լ�
	//mod0�� ��� x�� 0~18�� y��0~18�� ����
	//mod1�� ��� x�� 0~18�� y��0~19�� ����
	//mod2�� ��� x�� 0~18�� y�� -1~19�� ����
	//mod3�� ��� x�� -1~19�� y�� -1~19�� ����
	int x, y;
	x = (*tmpx);
	y = (*tmpy);
	if (GetAsyncKeyState(VK_UP) < 0) (*tmpy) -= (*tmpy) > -1 ? 1 : 0;
	if (GetAsyncKeyState(VK_DOWN) < 0) (*tmpy) += (*tmpy) < size ? 1 : 0;
	if (GetAsyncKeyState(VK_LEFT) < 0) (*tmpx) -= (*tmpx) > -1 ? 1 : 0;
	if (GetAsyncKeyState(VK_RIGHT) < 0) (*tmpx) += (*tmpx) < size ? 1 : 0;
	if (gmod == 0) {
		if ((*tmpx) == -1) (*tmpx)++;
		if ((*tmpx) == size) (*tmpx)--;
		if ((*tmpy) == -1) (*tmpy)++;
		if ((*tmpy) == size) (*tmpy)--;
	}
	if (gmod == 1) {
		if ((*tmpx) == -1) (*tmpx)++;
		if ((*tmpx) == size) (*tmpx)--;
		if ((*tmpy) == -1) (*tmpy)++;
	}
	if (gmod == 2) {
		if ((*tmpx) == -1) (*tmpx)++;
		if ((*tmpx) == size) (*tmpx)--;
	}
	if (gmod == 3) {
		if (((*tmpx) == -1 || (*tmpx) == size) && (*tmpx) != x) {
			if ((*tmpy) == -1) (*tmpy)++;
			if ((*tmpy) == size) (*tmpy)--;
		}
		if (((*tmpy) == -1 || (*tmpy) == size) && (*tmpy) != y) {
			if ((*tmpx) == -1) (*tmpx)++;
			if ((*tmpx) == size) (*tmpx)--;
		}
	}
}

int getkey_input_sel(int tmpx, int tmpy, int *board, int size, int *stone, int *win, int *end, int *change) {
	if (GetAsyncKeyState(VK_RETURN) < 0) {
		if (tmpx == -1 || tmpx == size || tmpy == -1 || tmpy == size) {
			if (tmpy == -1) gravity(board, size, 2);
			else if (tmpy == size) gravity(board, size, 1);
			else if (tmpx == -1) gravity(board, size, 3);
			else if (tmpx == size) gravity(board, size, 4);
			if ((*change) == 1) {
				(*change) = 4;
				(*stone) = 2;
			}
			else if ((*change) == 2 || (*change) == 4) (*change)--;
			else if ((*change) == 3) {
				(*change)--;
				(*stone) = 1;
			}
			//����Ȯ�� �ؾ���
			int w, b;
			w = b = 0;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if ((*(board + (j * size) + i))) {
						if (find_win(i, j, (*(board + (j * size) + i)), board, size)) {
							(*win) = (*(board + (j * size) + i));
							if ((*(board + (j * size) + i)) == 1) b = 1;
							else if ((*(board + (j * size) + i)) == 2) w = 1;
							//������ ����
							(*end) = 1;
							if (w&&b) break;
						}
					}
				}
			}
			//���º��� ��� �鵹�� �̱�� �Ǿ�����
			if (w&&b) (*win) = 2;
		}
		else if (!(*(board + (tmpy * size) + tmpx))) {
			(*(board + (tmpy * size) + tmpx)) = *stone;
			//���� ������ ���� �¸� ���θ� �Ǵ��ϰ� �¸��Ͽ��ٸ� ������ �����ϰ� �¸��� ���� ����Ѵ�.
			if (find_win(tmpx, tmpy, (*stone), board, size)) {
				(*win) = (*stone);
				//������ ����
				(*end) = 1;
			}
			if ((*change) == 1) {
				(*change) = 4;
				(*stone) = 2;
			}
			else if ((*change) == 2 || (*change) == 4) (*change)--;
			else if ((*change) == 3) {
				(*change)--;
				(*stone) = 1;
			}
		}
		return 1;
	}
	else return 0;
}
