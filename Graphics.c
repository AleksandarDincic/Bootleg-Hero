#include <GLFW/glfw3.h>
#include "Graphics.h"
#include "Structs.h"
#include <math.h>

extern float pixel_ratio, piyel_ratio;

void Kruzic(float x, float y, float radius, int detail, float r, float g, float b, float length) {
	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	for (int i = 0; i <= detail; i++) {
		float temp = 2 * radius * i / (float)detail - radius;
		glVertex2f((x + temp)*pixel_ratio, (y + sqrt(radius*radius - temp * temp))*piyel_ratio);
	}
	for (int i = detail; i >= 0; i--) {
		float temp = 2 * radius * i / (float)detail - radius;
		glVertex2f((x + temp)*pixel_ratio, (y - length - sqrt(radius*radius - temp * temp))*piyel_ratio);
	}
	glEnd();
}

void Krofna(float x, float y, float radius, float fat, int detail, float r, float g, float b) {
	float current_radius = radius;
	while (current_radius - fat >= 0) {
		glBegin(GL_LINE_LOOP);
		glColor3f(r, g, b);
		for (int i = 0; i <= detail; i++) {
			float temp = 2 * current_radius * i / (float)detail - current_radius;
			glVertex2f((x + temp)*pixel_ratio, (y + sqrt(current_radius*current_radius - temp * temp))*piyel_ratio);
		}
		for (int i = detail; i >= 0; i--) {
			float temp = 2 * current_radius * i / (float)detail - current_radius;
			glVertex2f((x + temp)*pixel_ratio, (y - sqrt(current_radius*current_radius - temp * temp))*piyel_ratio);
		}
		current_radius = current_radius - 0.5f;
		glEnd();
	}
}

void Prsten(float x, float y, float radius, int detail, float r, float g, float b) {
	glBegin(GL_LINE_LOOP);
	glColor3f(r, g, b);
	for (int i = 0; i <= detail; i++) {
		float temp = 2 * radius * i / (float)detail - radius;
		glVertex2f((x + temp)*pixel_ratio, (y + sqrt(radius*radius - temp * temp))*piyel_ratio);
	}
	for (int i = detail; i >= 0; i--) {
		float temp = 2 * radius * i / (float)detail - radius;
		glVertex2f((x + temp)*pixel_ratio, (y - sqrt(radius*radius - temp * temp))*piyel_ratio);
	}
	glEnd();
}

void Linije(int p2) {
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f((5 * RADIUS - p2 * 10 * RADIUS)*pixel_ratio, LINE_H);
	glVertex2f((-5 * RADIUS - p2 * 10 * RADIUS)*pixel_ratio, LINE_H);
	glEnd();
	if (p2) {
		glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f((5 * RADIUS + p2 * 10 * RADIUS)*pixel_ratio, LINE_H);
		glVertex2f((-5 * RADIUS + p2 * 10 * RADIUS)*pixel_ratio, LINE_H);
		glEnd();
	}
	for (int i = 0; i <= 5 * (1 + p2) + p2; i++) {
		glBegin(GL_LINES);
		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex2f((i * 2 - 5 - p2 * 10 + (i > 5) * 8)*RADIUS*pixel_ratio, -1.0f);
		glVertex2f((i * 2 - 5 - p2 * 10 + (i > 5) * 8)*RADIUS*pixel_ratio, 1.0f);
		glEnd();
	}
}

void Strelica(float x, float y, float r, float g, float b, float w, float l, float rad) {
	float temp, L;

	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	glVertex2d((x + w / 6.0f * cos(rad + 3.14f / 2.0f))*pixel_ratio, (y + w / 6.0f * sin(rad + 3.14f / 2.0f))*piyel_ratio);
	glVertex2d((x + w / 6.0f * cos(rad - 3.14f / 2.0f))*pixel_ratio, (y + w / 6.0f * sin(rad - 3.14f / 2.0f))*piyel_ratio);
	temp = atan(w / 6.0f / 2.0f / l * 3.0f);
	L = sqrt((w / 6.0f)*(w / 6.0f) + (2.0f / 3.0f * l)*(2.0f / 3.0f * l));
	glVertex2d((x + L * cos(rad - temp))*pixel_ratio, (y + L * sin(rad - temp))*piyel_ratio);
	glVertex2d((x + L * cos(rad + temp))*pixel_ratio, (y + L * sin(rad + temp))*piyel_ratio);
	glEnd();

	glBegin(GL_TRIANGLES);
	temp = atan(w / 2.0f / 2.0f / l * 3.0f);
	L = sqrt((w / 2.0f)*(w / 2.0f) + (2.0f / 3.0f * l)*(2.0f / 3.0f * l));
	glColor3f(r, g, b);
	glVertex2d((x + L * cos(rad + temp))*pixel_ratio, (y + L * sin(rad + temp))*piyel_ratio);
	glVertex2d((x + L * cos(rad - temp))*pixel_ratio, (y + L * sin(rad - temp))*piyel_ratio);
	glVertex2d((x + l * cos(rad))*pixel_ratio, (y + l * sin(rad))*piyel_ratio);
	glEnd();
}

void Lampa(int combo, int combo2, short int p2) {
	float neki_radius = (12 - p2 * 6)*RADIUS * pow(1.01+p2*0.01, -combo) + 8 * RADIUS;
	float neki_radius2 = (12 - p2 * 6) * RADIUS * pow(1.01+p2*0.01, -combo2) + 8 * RADIUS;
	//printf("%f\n", neki_radius);
	for (int i = 90; i > 0; i--) {
		glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 0.0f);
		float temp = 2 * neki_radius * i / 90.0 - neki_radius, temp2 = 2 * neki_radius * (i-1) / 90.0 - neki_radius;
		glVertex2f(temp*pixel_ratio - p2 * 10 * RADIUS * pixel_ratio, LINE_H + sqrt(neki_radius*neki_radius - temp * temp)*piyel_ratio);
		glVertex2f(temp2*pixel_ratio - p2 * 10 * RADIUS* pixel_ratio, LINE_H + sqrt(neki_radius*neki_radius - temp2 * temp2)*piyel_ratio);
		glVertex2f(temp2*pixel_ratio - p2 * 10 * RADIUS* pixel_ratio, 1.0f);
		glVertex2f(temp*pixel_ratio - p2 * 10 * RADIUS* pixel_ratio, 1.0f);
		glEnd();
		if (p2) {
			glBegin(GL_POLYGON);
			glColor3f(0.0f, 0.0f, 0.0f);
			temp = 2 * neki_radius2 * i / 90.0 - neki_radius2, temp2 = 2 * neki_radius2 * (i - 1) / 90.0 - neki_radius2;
			glVertex2f(temp*pixel_ratio + p2 * 10 * RADIUS* pixel_ratio, LINE_H + sqrt(neki_radius2*neki_radius2 - temp * temp)*piyel_ratio);
			glVertex2f(temp2*pixel_ratio + p2 * 10 * RADIUS* pixel_ratio, LINE_H + sqrt(neki_radius2*neki_radius2 - temp2 * temp2)*piyel_ratio);
			glVertex2f(temp2*pixel_ratio + p2 * 10 * RADIUS* pixel_ratio, 1.0f);
			glVertex2f(temp*pixel_ratio + p2 * 10 * RADIUS* pixel_ratio, 1.0f);
			glEnd();
		}
	}
}

void HP(float x, float y, float radius, short int p2, int hp) {
	glBegin(GL_POLYGON);
	if (!p2)
		glColor3f(hp <= 33 ? 1.0f : 0.2f, 0.0f, 0.0f);
	else
		glColor3f(hp <= 33 ? 1.0f : 0.2f, 0.0f, 0.0f);
	glVertex2f(x*pixel_ratio, y*piyel_ratio);
	for (int i = 0; i <= 25; i++) {
		float temp = 2 * radius * i / 100.0 - radius;
		glVertex2f((x + temp)*pixel_ratio, (y + sqrt(radius*radius - temp * temp))*piyel_ratio);
	}
	glEnd();
	
	glBegin(GL_POLYGON);
	if (!p2)
		glColor3f((hp > 33 && hp <= 66) ? 1.0f : 0.2f, (hp > 33 && hp <= 66) ? 1.0f : 0.2f, 0.0f);
	else
		glColor3f(0.0f, 0.0f, (hp > 33 && hp <= 66) ? 1.0f : 0.2f);
	glVertex2f(x*pixel_ratio, y*piyel_ratio);
	for (int i = 25; i <= 75; i++) {
		float temp = 2 * radius * i / 100.0 - radius;
		glVertex2f((x + temp)*pixel_ratio, (y + sqrt(radius*radius - temp * temp))*piyel_ratio);
	}
	glEnd();
	
	glBegin(GL_POLYGON);
	if(!p2)
		glColor3f(0.0f, hp > 66 ? 1.0f : 0.2f, 0.0f);
	else
		glColor3f(hp > 66 ? 1.0f : 0.2f, 0.0f, 0.0f);
	glVertex2f(x*pixel_ratio, y*piyel_ratio);
	for (int i = 75; i <= 100; i++) {
		float temp = 2 * radius * i / 100.0 - radius;
		glVertex2f((x + temp)*pixel_ratio, (y + sqrt(radius*radius - temp * temp))*piyel_ratio);
	}
	glEnd();
}

void DrawRect(float x, float y, float r, float g, float b, float w, float l) {
	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	glVertex2d((x - l / 2.0f)*pixel_ratio, (y + w / 2.0f)*piyel_ratio);
	glVertex2d((x + l / 2.0f)*pixel_ratio, (y + w / 2.0f)*piyel_ratio);
	glVertex2d((x + l / 2.0f)*pixel_ratio, (y - w / 2.0f)*piyel_ratio);
	glVertex2d((x - l / 2.0f)*pixel_ratio, (y - w / 2.0f)*piyel_ratio);
	glEnd();
}

void DrawLongHexa(float x, float y, float r, float g, float b, float w, float l, float rad) {
	float temp, L;

	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	glVertex2d((x + l / 2.0f * cos(rad))*pixel_ratio, (y + l / 2.0f  * sin(rad))*piyel_ratio);
	temp = atan(w / 2.0f / 3.0f / l * 8.0f);
	L = sqrt((w / 2.0f)*(w / 2.0f) + (3.0f / 8.0f * l)*(3.0f / 8.0f * l));
	glVertex2d((x + L * cos(rad + temp))*pixel_ratio, (y + L * sin(rad + temp))*piyel_ratio);
	glVertex2d((x - L * cos(rad - temp))*pixel_ratio, (y - L * sin(rad - temp))*piyel_ratio);
	glVertex2d((x - l / 2.0f * cos(rad))*pixel_ratio, (y - l / 2.0f  * sin(rad))*piyel_ratio);
	glVertex2d((x - L * cos(rad + temp))*pixel_ratio, (y - L * sin(rad + temp))*piyel_ratio);
	glVertex2d((x + L * cos(rad - temp))*pixel_ratio, (y + L * sin(rad - temp))*piyel_ratio);
	glEnd();
}

void DrawChar(struct slovo c, float x, float y, float r, float g, float b, float w, float l, float bb) {
	short int i = 0, temp = 1;
	float angle = atan(l / w), L = sqrt(l*l + w * w);
	while ((short int)(temp << i)) {
		if (temp << i & c.bitmap) {
			switch (i) {
			case 0:
				DrawLongHexa(x - w / 4.0f, y + l / 2.0f, r, g, b, bb, w / 2.0f, 0);
				break;
			case 1:
				DrawLongHexa(x + w / 4.0f, y + l / 2.0f, r, g, b, bb, w / 2.0f, 0);
				break;
			case 2:
				DrawLongHexa(x - w / 2.0f, y + l / 4.0f, r, g, b, bb, l / 2.0f, PI / 2.0f);
				break;
			case 3:
				DrawLongHexa(x - w / 4.0f, y + l / 4.0f, r, g, b, bb, L / 2.0f, -angle);
				break;
			case 4:
				DrawLongHexa(x, y + l / 4.0f, r, g, b, bb, l / 2.0f, PI / 2.0f);
				break;
			case 5:
				DrawLongHexa(x + w / 4.0f, y + l / 4.0f, r, g, b, bb, L / 2.0f, angle);
				break;
			case 6:
				DrawLongHexa(x + w / 2.0f, y + l / 4.0f, r, g, b, bb, l / 2.0f, PI / 2.0f);
				break;
			case 7:
				DrawLongHexa(x - w / 4.0f, y, r, g, b, bb, w / 2.0f, 0);
				break;
			case 8:
				DrawLongHexa(x + w / 4.0f, y, r, g, b, bb, w / 2.0f, 0);
				break;
			case 9:
				DrawLongHexa(x - w / 2.0f, y - l / 4.0f, r, g, b, bb, l / 2.0f, PI / 2.0f);
				break;
			case 10:
				DrawLongHexa(x - w / 4.0f, y - l / 4.0f, r, g, b, bb, L / 2.0f, angle);
				break;
			case 11:
				DrawLongHexa(x, y - l / 4.0f, r, g, b, bb, l / 2.0f, PI / 2.0f);
				break;
			case 12:
				DrawLongHexa(x + w / 4.0f, y - l / 4.0f, r, g, b, bb, L / 2.0f, -angle);
				break;
			case 13:
				DrawLongHexa(x + w / 2.0f, y - l / 4.0f, r, g, b, bb, l / 2.0f, PI / 2.0f);
				break;
			case 14:
				DrawLongHexa(x - w / 4.0f, y - l / 2.0f, r, g, b, bb, w / 2.0f, 0);
				break;
			case 15:
				DrawLongHexa(x + w / 4.0f, y - l / 2.0f, r, g, b, bb, w / 2.0f, 0);
				break;
			}
		}
		i++;
	}
}

void print(struct slovo *reference[], char *s, float x, float y, float rc, float gc, float bc, float wc, float lc, float bbc, float spacing) {
	if (s != 0) {
		struct slovo temp;
		temp.bitmap = 0xffff;
		int i = 0;
		while (s[i]) {
			if (reference[s[i]])
				DrawChar(*reference[s[i]], x, y, rc, gc, bc, wc, lc, bbc);
			else
				DrawChar(temp, x, y, rc, gc, bc, wc, lc, bbc);
			x += wc + spacing;
			i++;
		}
	}
}