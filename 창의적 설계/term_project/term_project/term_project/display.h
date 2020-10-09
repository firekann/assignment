#pragma once

void gotoxy(int x, int y);
void start_Render(int x, int y);
void Render_all(int sx, int sy, int ex, int ey);
void end_Render();
void Render(int x, int y, int def);
void remove_scrollbar();
void fullscreen();
void CursorView(int show);