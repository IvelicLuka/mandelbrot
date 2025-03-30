#include <stdio.h>
#include <math.h>
#include "raylib.h" 
#define COLS 500
#define ROWS 500
#define WIDTH COLS
#define HEIGHT ROWS
#define SQ_SIDE (WIDTH/COLS)
#define ITS 1000
#define SPEED 0.5
#define LIMIT 10

typedef long double REAL;

REAL ox = 0.0, oy = 0.0;
REAL zoom = 1;
REAL polje[ROWS][COLS] = { 0 };

void calc() {	
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			//if (skip) break;
			//int skip = 0;
			REAL cx = (j/(REAL)COLS - 0.5)*2/zoom  + ox;
			REAL cy = (i/(REAL)ROWS - 0.5)*2/zoom  + oy;

			//REAL cx = ((REAL)j/(REAL)COLS - 0.5);
			//REAL cy = ((REAL)i/(REAL)ROWS - 0.5);
			REAL sx = 0;
			REAL sy = 0;
			for (int k = 0; k < ITS; k++) {
				//printf("C: %lf %lf\n", cx, cy);
				///printf("S: %lf %lf\n", sx, sy);
				if (sx > LIMIT || sx < -LIMIT || sy > LIMIT || sy < -LIMIT) {
					//polje[i][j] = k;
					//polje[i][j] = 0;
					sx = 0.5; sy = 0.5;
					//sx = 0; sy = 0;
					break;
				}
				REAL nx = (sx*sx - sy*sy);
				//printf("N: %lf %lf\n", nx, ny);
				REAL ny = 2*sx*sy;
				sx = nx + cx;
				sy = ny + cy;
				//printf("NS: %lf %lf\n", sx, sy);
			}
			polje[i][j] = (sx*sx + sy*sy)*2;
		}
	}
}

int main(void) {
	InitWindow(WIDTH, HEIGHT, "mandel");
	calc();
	REAL num = 1; 
	while(!WindowShouldClose()) {
		if (IsKeyDown(KEY_M)) num += 0.1;
		if (IsKeyDown(KEY_N)) num -= 0.1;
		if (IsKeyPressed(KEY_W)) {
			oy -= SPEED / zoom;
			calc();
		}
		if (IsKeyPressed(KEY_A)) {
			ox -= SPEED / zoom;
			calc();
		}
		if (IsKeyPressed(KEY_S)) {
			oy += SPEED / zoom;
			calc();
		}
		if (IsKeyPressed(KEY_D)) {
			ox += SPEED / zoom;
			calc();
		}
		if (IsKeyPressed(KEY_U)) {
			zoom *= 1.25;
			calc();
		}
		if (IsKeyPressed(KEY_I)) {
			zoom /= 1.25;
			calc();
		}
		if (IsKeyPressed(KEY_P)) {
			calc();
		}
		BeginDrawing();
			ClearBackground(BLACK);
			for (int i = 0; i < ROWS; i++) {
				for (int j = 0; j < COLS; j++) {
					//if (polje[i][j] != ITS)
						//DrawPixel(j, i, ColorFromHSV(ITS/polje[i][j] * 360, 1, ITS/polje[i][j]));
						//if (polje[i][j]) 
						//DrawPixel(j, i, ColorFromHSV(polje[i][j]*360, 1, 1));
						DrawPixel(j, i, CLITERAL(Color){(unsigned char)(polje[i][j]*255),
														(unsigned char)(polje[i][j]*255),
														(unsigned char)(polje[i][j]*255),
														255});
				}
			}
		EndDrawing();
	}
	CloseWindow();
}



