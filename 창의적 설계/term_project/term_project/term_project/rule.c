int find_win(int x, int y, int stone, int *board, int size) {
	int flag = 1, cnt, tmpx, tmpy;
	//x방향으로 판별
	tmpx = x, tmpy = y, cnt = 0;
	//(*(board + ((tmpy - 1) * size) + (tmpx - 1)));
	while ((*(board + ((tmpy)* size) + (tmpx - 1))) == stone && tmpx > 0) tmpx--;
	while ((*(board + ((tmpy)* size) + (tmpx++))) == stone && tmpx < size) cnt++;
	if (cnt == 6) flag = 0;
	//y방향으로 판별
	tmpx = x, tmpy = y, cnt = 0;
	while ((*(board + ((tmpy - 1) * size) + (tmpx))) == stone && tmpy > 0 && flag) tmpy--;
	while ((*(board + ((tmpy++) * size) + (tmpx))) == stone && tmpy < size && flag) cnt++;
	if (cnt == 6) flag = 0;
	//대각선 방향
	tmpx = x, tmpy = y, cnt = 0;
	while ((*(board + ((tmpy - 1) * size) + (tmpx - 1))) == stone && tmpx > 0 && tmpy > 0 && flag) tmpx--, tmpy--;
	while ((*(board + ((tmpy++) * size) + (tmpx++))) == stone && tmpx < size && tmpy < size && flag) cnt++;
	if (cnt == 6) flag = 0;
	//다른 대각선 방향
	tmpx = x, tmpy = y, cnt = 0;
	while ((*(board + ((tmpy - 1) * size) + (tmpx + 1))) == stone && tmpx < (size - 1) && tmpy > 0 && flag) tmpx++, tmpy--;
	while ((*(board + ((tmpy++) * size) + (tmpx--))) == stone && tmpx >= 0 && tmpy < size && flag) cnt++;
	if (cnt == 6) flag = 0;
	if (flag) return 0;
	else return 1;
}

void gravity(int *board, int size, int dir) {
	if (dir == 1) {
		for (int i = 0; i < size; i++) {
			for (int j = size - 1; j >= 0; j--) {
				if ((*(board + (j * size) + i)) == 0) {
					int save = 0;
					for (int k = j - 1; k >= 0; k--) {
						if ((*(board + (k * size) + i)) != 0) {
							save = (*(board + (k * size) + i));
							(*(board + (k * size) + i)) = 0;
							break;
						}
					}
					if (!save) break;
					else (*(board + (j * size) + i)) = save;
				}
			}
		}
	}
	if (dir == 2) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if ((*(board + (j * size) + i)) == 0) {
					int save = 0;
					for (int k = j + 1; k < size; k++) {
						if ((*(board + (k * size) + i)) != 0) {
							save = (*(board + (k * size) + i));
							(*(board + (k * size) + i)) = 0;
							break;
						}
					}
					if (!save) break;
					else (*(board + (j * size) + i)) = save;
				}
			}
		}
	}
	if (dir == 3) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if ((*(board + (i * size) + j)) == 0) {
					int save = 0;
					for (int k = j + 1; k < size; k++) {
						if ((*(board + (i * size) + k)) != 0) {
							save = (*(board + (i * size) + k));
							(*(board + (i * size) + k)) = 0;
							break;
						}
					}
					if (!save) break;
					else (*(board + (i * size) + j)) = save;
				}
			}
		}
	}
	if (dir == 4) {
		for (int i = 0; i < size; i++) {
			for (int j = size - 1; j >= 0; j--) {
				if ((*(board + (i * size) + j)) == 0) {
					int save = 0;
					for (int k = j - 1; k >= 0; k--) {
						if ((*(board + (i * size) + k)) != 0) {
							save = (*(board + (i * size) + k));
							(*(board + (i * size) + k)) = 0;
							break;
						}
					}
					if (!save) break;
					else (*(board + (i * size) + j)) = save;
				}
			}
		}
	}
}