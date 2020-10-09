#include <Windows.h>

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

static HWND hWnd;
static HINSTANCE hInst;

HDC hDC, hMemDC;
static HDC hBackDC;
HBITMAP hBitmap, hOldBitmap, hBackBitmap;
BITMAP Bitmap;
RECT WindowRect;

void start_Render(int x, int y) {
	hWnd = GetConsoleWindow();
	hInst = GetModuleHandle(NULL);
	GetWindowRect(hWnd, &WindowRect);
	hDC = GetDC(hWnd);
	hBackDC = CreateCompatibleDC(hDC);
	hBackBitmap = CreateCompatibleBitmap(hDC, x, y);
}

void Render_all(int sx, int sy, int ex, int ey) {
	BitBlt(hDC, sx, sy, ex, ey, hBackDC, 0, 0, SRCCOPY);
}

void end_Render() {
	DeleteObject(SelectObject(hBackDC, hBackBitmap));
	DeleteDC(hBackDC);
	ReleaseDC(hWnd, hDC);
}

void Render(int x, int y, int def) {
	hMemDC = CreateCompatibleDC(hDC);
	hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(def));
	GetObject(hBitmap, sizeof(BITMAP), &Bitmap); SelectObject(hMemDC, hBitmap);
	hOldBitmap = (HBITMAP)SelectObject(hBackDC, hBackBitmap);
	BitBlt(hBackDC, x, y, x + Bitmap.bmWidth, y + Bitmap.bmHeight, hMemDC, 0, 0, SRCCOPY);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
}

void remove_scrollbar() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size = {
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}

void fullscreen() {
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
}

void CursorView(int show) {
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}