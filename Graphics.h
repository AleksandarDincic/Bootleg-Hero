#ifndef GRAPHICS
#define GRAPHICS

#define RADIUS 20.0f
#define DETAIL 50
#define PI 3.14159265358979323846l
#define LIFE_ANGLE PI/36
#define LINE_H -0.8f

void Kruzic(float, float, float, int, float, float, float, float);

void Krofna(float, float, float, float, int, float, float, float);

void Prsten(float, float, float, int, float, float, float);

void Linije(int);

void Lampa(int, int, short int);

void Strelica(float, float, float, float, float, float, float, float);

void DrawRect(float, float, float, float, float, float, float);

void DrawLongHexa(float, float, float, float, float, float, float, float);

void DrawChar(struct slovo, float, float, float, float, float, float, float, float);

void print(struct slovo *[], char *, float, float, float, float, float, float, float, float, float);

void HP(float x, float y, float radius, short int p2, int hp);

#endif