#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include "Graphics.h"
#include "Structs.h"
#include "Files.h"
#include "Controls.h"




/*Rising edge:
0 -> Q		 1 -> W		 2 -> E
3 -> R		 4 -> T		 5 -> Up
6 -> Down    7 -> Left   8 -> Right
9 -> Enter  10 -> Plus  11 -> Minus
12 -> 6		13 -> 7		14 -> 8
15 -> 9		16 -> 0		17 -> Esc
*/


int main(void)
{
	extern struct b B;
	extern float pixel_ratio, piyel_ratio;
	extern short int risingEdge[18];
	extern short int pressed[10];

	struct node *Queue, *Queue2;
	extern int width, height;
	extern int fullscreen, offset;
	extern int pos_width[3];
	extern int pos_height[3];
	extern int pos_index;
	short int mods[3] = { 0, 0, 0 }; //[0] = HARD ROCK; [1] = FLASHLIGHT; [2] = NO FAIL
	float mod_modifier = 1.0f;
	long double deltay = 0;
	int deltay_prev = 0, read_scores = 0;

	ReadConfig();
	long double deltaTime;
	Queue = NULL;
	Queue2 = NULL;
	float radius = 100.0f;
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	GLFWmonitor *monitor;
	monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	window = glfwCreateWindow(width, height, "Bootleg Hero", fullscreen?monitor:NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	pixel_ratio = 2 / (float)width;
	piyel_ratio = 2 / (float)height;
	glfwSetKeyCallback(window, KeyCallback);
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	/* Start */
	extern struct slovo *reference[256];
	InitReference();

	FILE *naziv;

	struct Header Htemp;
	BITMAPFILEHEADER logoh;
	BITMAPINFOHEADER logoi;
	naziv = fopen("logo.bmp", "rb");
	fread(&logoh, sizeof(BITMAPFILEHEADER), 1, naziv);
	fread(&logoi, sizeof(BITMAPINFOHEADER), 1, naziv);
	GLubyte imageBuffer[640][480][3];
	int palac, palcic;
	for (palac = 0; palac < logoi.biWidth; palac++) {
		for (palcic = 0; palcic < logoi.biHeight; palcic++) {
			GLubyte r, g, b,a;

			fread(&b, 1, 1, naziv);
			fread(&g, 1, 1, naziv);
			fread(&r, 1, 1, naziv);
			imageBuffer[palac][palcic][0] = (GLubyte)r;
			imageBuffer[palac][palcic][1] = (GLubyte)g;
			imageBuffer[palac][palcic][2] = (GLubyte)b;
		}
	}
	fclose(naziv);

	char **songs = NULL;
	int songammount;
	struct node *p2_cur = NULL;

	//Deklaracije
	clock_t last = clock(), first;
	short int mod = 0, pos = 0, side = 0, switchh = 0, hold = 0, stop_y = 1, p2 = 0, hold2 = 0;
	long long int lasttime, timenow, frequency;
	long double score = 0, score2 = 0;
	int combo = 0, combo2 = 0, life = 50;
	float multiplier = 1.0f, multiplier2 = 1.0f, movement = -width / 2.0f + logoi.biWidth , moyement = logoi.biHeight / 2.0f - pos * 100 - 40, rotation = PI, prev_pos = logoi.biHeight / 2.0f - pos * 100 - 40;
	float real_r = 0.0f, real_g = 1.0f, real_b = 0.0f;
	float option_space = height / 5.0f;
	int xpos = 0, ypos = 0, player_ready = 0;
	char name[4] = {0, 0, 0, 0}, name2[4] = { 0, 0, 0, 0 };
	QueryPerformanceFrequency(&frequency);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	while (!glfwWindowShouldClose(window))
	{
		if (mod != 3) {
		first = clock();
		deltaTime = (double)(first - last) / CLOCKS_PER_SEC;
		}
		//Crtanje
		glClear(GL_COLOR_BUFFER_BIT);
		switch (mod) {
		case 0:
			if (deltaTime >= 3) {
				mod = 1;
				ListDirectoryContents("Music\\", &songs, &songammount);
				naziv = fopen("manu.bmp", "rb");
				fread(&logoh, sizeof(BITMAPFILEHEADER), 1, naziv);
				fread(&logoi, sizeof(BITMAPINFOHEADER), 1, naziv);
				int palac, palcic;

				for (palac = 0; palac < logoi.biWidth; palac++) {
					for (palcic = 0; palcic < logoi.biHeight; palcic++) {
						GLubyte r, g, b;

						fread(&b, 1, 1, naziv);
						fread(&g, 1, 1, naziv);
						fread(&r, 1, 1, naziv);
						imageBuffer[palac][palcic][0] = (GLubyte)r;
						imageBuffer[palac][palcic][1] = (GLubyte)g;
						imageBuffer[palac][palcic][2] = (GLubyte)b;
					}
				}
				fclose(naziv);
			}
			else {
				glRasterPos2f(-logoi.biWidth / 2.0f * pixel_ratio, -logoi.biHeight / 2.0f*piyel_ratio);
				GLubyte palcina[640][480][3];

				for (palac = 0; palac < logoi.biWidth; palac++) {
					for (palcic = 0; palcic < logoi.biHeight; palcic++) {
						palcina[palac][palcic][0] = (3 * deltaTime - deltaTime * deltaTime)*imageBuffer[palac][palcic][0] / 9 * 4;
						palcina[palac][palcic][1] = (3 * deltaTime - deltaTime * deltaTime)*imageBuffer[palac][palcic][1] / 9 * 4;
						palcina[palac][palcic][2] = (3 * deltaTime - deltaTime * deltaTime)*imageBuffer[palac][palcic][2] / 9 * 4;
					}
				}
				glDrawPixels(logoi.biWidth, logoi.biHeight, GL_RGB, GL_UNSIGNED_BYTE, palcina);
			}
			break;
		case 1:
			glRasterPos2f(-1.0f, -logoi.biHeight / 2.0f*piyel_ratio);
			glDrawPixels(logoi.biWidth, logoi.biHeight, GL_RGB, GL_UNSIGNED_BYTE, imageBuffer);
			if (!side && risingEdge[5])
				pos = pos > 0 ? pos - 1 : 0;
			if (!side && risingEdge[6])
				pos = pos < 4 ? pos + 1 : 4;
			if (side && risingEdge[5])
				deltay = deltay > 0 ? deltay - 1 : 0;
			if (side && risingEdge[6])
				deltay = deltay < songammount - 1 ? deltay + 1 : songammount - 1;
			if (risingEdge[7]) {
				if (side) {
					side = 0;
					stop_y = 0;
				}
			}
			if (risingEdge[8]) {
				if (!side) {
					side = 1;
					stop_y = 0;
				}
			}
			if (risingEdge[9]) {
				if (side) {
					side = 0;
					stop_y = 0;
				}
				else
					switch (pos) {
					case 0:
						mod = 2;
						deltay_prev = deltay;
						p2 = 0;
						break;
					case 1:
						mod = 2;
						deltay_prev = deltay;
						p2 = 1;
						break;
					case 2:
						mod = 5;
						break;
					case 3:
						mod = 6;
						break;
					case 4:
						goto GASI;
						break;
					}
			}
			float r, g, b;
			switch (pos) {
			case 0:
				r = 0.0f, g = 1.0f, b = 0.0f;
				break;
			case 1:
				r = 1.0f, g = 0.0f, b = 0.0f;
				break;
			case 2:
				r = 1.0f, g = 1.0f, b = 0.0f;
				break;
			case 3:
				r = 0.0f, g = 0.0f, b = 1.0f;
				break;
			case 4:
				r = 1.0f, g = 0.5f, b = 0.0f;
				break;
			}
			prev_pos = logoi.biHeight / 2.0f - pos * 100 - 40;
			if (side) {
				if (movement < -width / 16.0f) //tbh ne znam
					movement += (-width/16.0f + width / 2.0f - logoi.biWidth) * 1.75 * deltaTime;
				else
					movement = -width / 16.0f;
				if (rotation > 0)
					rotation -= PI * 1.75 * deltaTime;
				else
					rotation = 0;
				if (!stop_y && moyement < height / 4.0f + height / 40.0f) {
					moyement += (height / 4.0f + height / 40.0f - (logoi.biHeight / 2.0f - pos * 100 - 40)) * 1.75 * deltaTime;
				}
				else {
					moyement = height / 4.0f + height / 40.0f;
					stop_y = 1;
				}
				/*if (!stop_y && (((logoi.biHeight / 2.0f - pos * 100 - 40) > height / 4.0f + height / 40.0f && moyement > height / 4.0f + height / 40.0f) || ((logoi.biHeight / 2.0f - pos * 100 - 40) < height / 4.0f + height / 40.0f && moyement < height / 4.0f + height / 40.0f)))
					moyement -= (logoi.biHeight / 2.0f - pos * 100 - 40) * 2 * deltaTime;
				else {
					moyement = height / 4.0f + height / 40.0f;
					stop_y = 1;
				}*/
				if (!stop_y && real_r < 1.0f)
					real_r += (1.0f - r) * 1.75 * deltaTime;
				else
					real_r = 1.0f;
				if (!stop_y && real_g < 1.0f)
					real_g += (1.0f - g) * 1.75 * deltaTime;
				else
					real_g = 1.0f;
				if (!stop_y && real_b < 1.0f)
					real_b += (1.0f - b) * 1.75 * deltaTime;
				else
					real_b = 1.0f;
			}
			else {
				if (movement > -width / 2.0f + logoi.biWidth)
					movement -= (-width / 16.0f + width / 2.0f - logoi.biWidth) * 1.75 * deltaTime;
				else
					movement = -width / 2.0f + logoi.biWidth;
				if (rotation < PI)
					rotation += PI * 1.75 * deltaTime;
				else
					rotation = PI;
				if (!stop_y && moyement > logoi.biHeight / 2.0f - pos * 100 - 40) {
					moyement -= (height / 4.0f + height / 40.0f - (logoi.biHeight / 2.0f - pos * 100 - 40)) * 1.75 * deltaTime;
				}
				else {
					moyement = logoi.biHeight / 2.0f - pos * 100 - 40;
					stop_y = 1;
				}
				/*if (!stop_y && ((logoi.biHeight / 2.0f - pos * 100 - 40 > 0 && moyement < logoi.biHeight / 2.0f - pos * 100 - 40) || (logoi.biHeight / 2.0f - pos * 100 - 40 < 0 && moyement > logoi.biHeight / 2.0f - pos * 100 - 40)))
					moyement += (logoi.biHeight / 2.0f - pos * 100 - 40) * 2 * deltaTime;
				else {
					moyement = logoi.biHeight / 2.0f - pos * 100 - 40;
					stop_y = 1;
				}*/
				if (!stop_y && real_r > r)
					real_r -= (1.0f - r) * 1.75 * deltaTime;
				else
					real_r = r;
				if (!stop_y && real_g > g)
					real_g -= (1.0f - g) * 1.75 * deltaTime;
				else
					real_g = g;
				if (!stop_y && real_b > b)
					real_b -= (1.0f - b) * 1.75 * deltaTime;
				else
					real_b = b;
			}//-width / 2.0f + logoi.biWidth - movement
			Strelica(movement, moyement, real_r, real_g, real_b, 30.0f, 30.0f, rotation);
			if(mod==5)
				pos = 0;
			char pera[2048];
			for (int j = 0; j < songammount; j++) {
				Crop(songs[j], pera);
				if ((-j + deltay) * 40 == 0)
					print(reference, pera, 0, height / 4.0f + height / 40.0f, 1.0f, 1.0f, 1.0f, width / 80.0f, height / 40.0f, width / 280.0f, width / 200.0f);
				else
					print(reference, pera, 0, height / 4.0f + height / 40.0f + (-j + deltay) * height/18.0f, 0.6f, 0.6f, 0.6f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
			}
			last = first;
			break;
		case 2:
			srand(69);
			int size = 0;
			naziv = fopen(songs[(int)deltay], "rb");
			fseek(naziv, 0, 2);
			size = ftell(naziv);
			fclose(naziv);
			naziv = fopen(songs[(int)deltay], "rb");
			fread(&Htemp, 44, 1, naziv);
			if (Htemp.num_channels != 2) {
				fclose(naziv);
				mod = 4;
				break;
			}
			float dif = 1024.0f;
			double c = 1.0;
			long long int sum = 0;
			int i = 0, samplecounter = Htemp.bit_sample;
			long long int counter = 0, lastsum = 0, LastCounter = 0;
			short int truecopet_l, truecopet_r, copeti_l[1024], copeti_r[1024];
			float note_treshold = 2.0f * RADIUS * Htemp.sample_rate / 480.0f;

			float loadlast = 0, loadnow;

			B.rear = B.front;
			while (fread(&truecopet_l, Htemp.bit_sample / 4 / Htemp.num_channels, 1, naziv) != 0 && fread(&truecopet_r, Htemp.bit_sample / 4 / Htemp.num_channels, 1, naziv) != 0) {
				loadnow = (counter * (Htemp.bit_sample / 4 / Htemp.num_channels) * 2 + 44) / (float)size;

				if (loadnow - loadlast > 0.01f) {
					glClear(GL_COLOR_BUFFER_BIT);
					DrawRect(0, -height / 2.0f + 25, 1.0, 0.0, 0.0, 25, 500);//clear rect;
					DrawRect(-250 + loadnow / 2.0f * 500, -height / 2.0f + 25, 0.0, 1.0, 0.0, 25, loadnow * 500);
					glfwSwapBuffers(window);
					loadlast = loadnow;
				}
				counter++;
				if (Full_b(&B) && i < dif) {
					copeti_l[i] = truecopet_l;
					copeti_r[i] = truecopet_r;
					i++;
					sum += truecopet_l * truecopet_l + truecopet_r * truecopet_r;
				}
				else if (Full_b(&B)) {
					i = 0;
					long long int E = 0;
					for (int j = 0; j < SECOND; j++) {
						if (j != B.rear)
							E += B.notes[j];
					}
					E = E / 43;
					Delete_b(&B);
					Insert_b(&B, sum);

					struct node *latest;
					latest = Queue;
					if (!Empty_q(Queue)) {
						while (latest->next != NULL)
							latest = latest->next;
					}

					if (sum > 50000000 && sum > E*c && LastCounter + note_treshold < counter) {
						if (!Empty_q(Queue) && latest->info.l <= 4 * RADIUS * (1 + mods[0] * 0.5f)) {
							latest->info.y -= latest->info.l;
							latest->info.l = 0;
						}
						struct note temp_PP;
						temp_PP.x = (int)(rand() / (float)RAND_MAX * 5) * 2 * RADIUS - 4 * RADIUS;
						temp_PP.y = counter / (float)Htemp.sample_rate*480.0f*(1 + mods[0] * 0.5f) + LINE_H * height / 2.0f + 140;
						temp_PP.l = 0;
						Insert(&Queue, temp_PP);
						LastCounter = counter;
					}
					else if (sum > 50000000 && sum > E*c && !Empty_q(Queue)) {
						latest->info.l += (counter - LastCounter) / (float)Htemp.sample_rate*480.0f*(1 + mods[0] * 0.5f);
						latest->info.y = counter / (float)Htemp.sample_rate*480.0f*(1 + mods[0] * 0.5f) + LINE_H * height / 2.0f + 140;
						LastCounter = counter;
					}
					sum = 0;
				}
				Insert_b(&B, truecopet_l * truecopet_l + truecopet_r * truecopet_r);
			}
			if (p2) {
				p2_cur = Queue;
				while (p2_cur) {
					if (p2_cur->info.y - p2_cur->info.l - offset <= height) {
						Insert(&Queue2, p2_cur->info);
						p2_cur = p2_cur->next;
					}
					else
						break;
				}
			}
			fclose(naziv);
			mod = 3;
			switchh = 1;
			score = 0, score2 = 0;
			combo = 0, combo2 = 0;
			life = 50;
			break;
		case 3:
			if (Empty_q(Queue) && Empty_q(Queue2)) {
				name[0] = 0, name[1] = 0, name[2] = 0;
				name2[0] = 0, name2[1] = 0, name2[2] = 0;
				player_ready = 0;
				mod = 7;
				break;
			}
			if (switchh) {
				PlaySound(TEXT(songs[(int)deltay]), NULL, SND_ASYNC);
				deltay = 0;
				QueryPerformanceCounter(&timenow);
				switchh = 0;
			}
			lasttime = timenow;
			QueryPerformanceCounter(&timenow);
			deltaTime = (long double)(timenow - lasttime) / frequency;
			deltay += 480.0f*deltaTime*(1 + mods[0] * 0.5f);
			multiplier = 1 + sqrt((double)combo) / 2;
			multiplier2 = 1 + sqrt((double)combo2) / 2;

			if (p2 && p2_cur && p2_cur->info.y - p2_cur->info.l - deltay - offset <= height) {
				Insert(&Queue2, p2_cur->info);
				p2_cur = p2_cur->next;
			}

			if (hold == 1 && (!pressed[0] && !pressed[1] && !pressed[2] && !pressed[3] && !pressed[4])) {
				if (Queue && Queue->info.l > TRESHOLD - RADIUS) {
					hold = -1;
					combo = 0;
					life -= mods[0] ? 10 : 5;
				}
				else
					hold = 0;
			}

			if (p2 && hold2 == 1 && (!pressed[5] && !pressed[6] && !pressed[7] && !pressed[8] && !pressed[9])) {
				if (Queue2 && Queue2->info.l > TRESHOLD - RADIUS) {
					hold2 = -1;
					combo2 = 0;
					life += mods[0] ? 10 : 5;
				}
				else
					hold2 = 0;
			}

			if (Queue && Queue->info.y - deltay - Queue->info.l - offset > LINE_H * height / 2.0f - TRESHOLD) {
				for (int j = 0; j < 5; j++) {
					if (risingEdge[j]) {
						if (Queue->info.x == ((j - 2) * 2 * RADIUS)) {
							if (Queue->info.y - deltay - Queue->info.l - offset < LINE_H * height / 2.0f + TRESHOLD) {
								if (Queue->info.l == 0) {
									Delete(&Queue);
									score += 300 * multiplier * mod_modifier;
									combo++;
									life += mods[0] ? 10 : 5;
									hold = 0;
								}
								else if (hold != -1) {
									Queue->info.l = Queue->info.y - deltay - offset - LINE_H * height / 2.0f;
									hold = 1;
									combo++;
									life += mods[0] ? 10 : 5;
									score += 100 * multiplier * mod_modifier;
								}
							}
							else {
								combo = 0;
								life -= mods[0] ? 10 : 5;
							}
						}
						else {
							combo = 0;
							life -= mods[0] ? 10 : 5;
						}

					}
					else if (hold == 1 && pressed[j]) {
						if (Queue->info.x == ((j - 2) * 2 * RADIUS)) {
							if (Queue->info.y - deltay - Queue->info.l - offset < LINE_H * height / 2.0f + TRESHOLD) {
								if (Queue->info.l <= TRESHOLD - RADIUS) {
									Delete(&Queue);
									score += 100 * multiplier * mod_modifier;
									life += mods[0] ? 10 : 5;
									combo++;
									hold = 0;
								}
								else {
									Queue->info.l = Queue->info.y - deltay - offset - LINE_H * height / 2.0f;
									score += 1 * multiplier * mod_modifier * 100 * deltaTime;
								}
							}
							else {
								combo = 0;
							}
						}
						else {
							combo = 0;
						}
					}

				}
			}

			if (p2) {
				if (Queue2 && Queue2->info.y - deltay - Queue2->info.l - offset > LINE_H * height / 2.0f - TRESHOLD) {
					for (int j = 0; j < 5; j++) {
						if (risingEdge[j + 12]) {
							if (Queue2->info.x == ((j - 2) * 2 * RADIUS)) {
								if (Queue2->info.y - deltay - Queue2->info.l - offset < LINE_H * height / 2.0f + TRESHOLD) {
									if (Queue2->info.l == 0) {
										Delete(&Queue2);
										score2 += 300 * multiplier2 * mod_modifier;
										combo2++;
										life -= mods[0] ? 10 : 5;
										hold2 = 0;
									}
									else if (hold2 != -1) {
										Queue2->info.l = Queue2->info.y - deltay - offset - LINE_H * height / 2.0f;
										hold2 = 1;
										combo2++;
										life -= mods[0] ? 10 : 5;
										score2 += 100 * multiplier2 * mod_modifier;
									}
								}
								else {
									combo2 = 0;
									life += mods[0] ? 10 : 5;
								}
							}
							else {
								combo2 = 0;
								life += mods[0] ? 10 : 5;
							}

						}
						else if (hold2 == 1 && pressed[j + 5]) {
							if (Queue2->info.x == ((j - 2) * 2 * RADIUS)) {
								if (Queue2->info.y - deltay - Queue2->info.l - offset < LINE_H * height / 2.0f + TRESHOLD) {
									if (Queue2->info.l <= TRESHOLD - RADIUS) {
										Delete(&Queue2);
										score2 += 100 * multiplier2 * mod_modifier;
										life -= mods[0] ? 10 : 5;
										combo2++;
										hold2 = 0;
									}
									else {
										Queue2->info.l = Queue2->info.y - deltay - offset - LINE_H * height / 2.0f;
										score2 += 1 * multiplier2 * mod_modifier * 100 * deltaTime;
									}
								}
								else {
									combo2 = 0;
								}
							}
							else {
								combo2 = 0;
							}
						}

					}
				}
			}

			Linije(p2);
			Prsten(-4 * RADIUS - p2 * 10 * RADIUS, LINE_H*height / 2.0f, RADIUS, DETAIL, 0.0f, 1.0f, 0.0f);
			Prsten(-2 * RADIUS - p2 * 10 * RADIUS, LINE_H*height / 2.0f, RADIUS, DETAIL, 1.0f, 0.0f, 0.0f);
			Prsten(0 - p2 * 10 * RADIUS, LINE_H*height / 2.0f, RADIUS, DETAIL, 1.0f, 1.0f, 0.0f);
			Prsten(2 * RADIUS - p2 * 10 * RADIUS, LINE_H*height / 2.0f, RADIUS, DETAIL, 0.0f, 0.0f, 1.0f);
			Prsten(4 * RADIUS - p2 * 10 * RADIUS, LINE_H*height / 2.0f, RADIUS, DETAIL, 1.0f, 0.5f, 0.0f);
			if (p2) {
				Prsten(6 * RADIUS, LINE_H*height / 2.0f, RADIUS, DETAIL, 0.0f, 1.0f, 0.0f);
				Prsten(8 * RADIUS, LINE_H*height / 2.0f, RADIUS, DETAIL, 1.0f, 0.0f, 0.0f);
				Prsten(10 * RADIUS, LINE_H*height / 2.0f, RADIUS, DETAIL, 1.0f, 1.0f, 0.0f);
				Prsten(12 * RADIUS, LINE_H*height / 2.0f, RADIUS, DETAIL, 0.0f, 0.0f, 1.0f);
				Prsten(14 * RADIUS, LINE_H*height / 2.0f, RADIUS, DETAIL, 1.0f, 0.5f, 0.0f);
			}
			struct node *temp;
			temp = Queue;
			if (temp && temp->info.y - deltay - offset < LINE_H / piyel_ratio - TRESHOLD) {
				Delete(&Queue);
				hold = 0;
				life -= mods[0] ? 10 : 5;
				combo = 0;
				temp = Queue;
			}
			if (hold != -1 && temp && temp->info.y - temp->info.l - deltay - offset < LINE_H / piyel_ratio - TRESHOLD) {
				life -= mods[0] ? 10 : 5;
				combo = 0;
				hold = -1;
			}
			if (risingEdge[10]) {
				offset += 5;
			}
			if (risingEdge[11]) {
				offset -= 5;
			}
			while (temp) {
				if (temp->info.y - temp->info.l - deltay - offset <= height) {
					float r, g, b;
					switch ((int)temp->info.x) {
						case (int)(-4 * RADIUS) :
							r = 0.0f, g = 1.0f, b = 0.0f;
							break;
							case (int)(-2 * RADIUS) :
								r = 1.0f, g = 0.0f, b = 0.0f;
								break;
							case 0:
								r = 1.0f, g = 1.0f, b = 0.0f;
								break;
								case (int)(2 * RADIUS) :
									r = 0.0f, g = 0.0f, b = 1.0f;
									break;
									case (int)(4 * RADIUS) :
										r = 1.0f, g = 0.5f, b = 0.0f;
										break;
					}
					if (temp->info.y - deltay - temp->info.l - offset > LINE_H * height / 2.0f - TRESHOLD) {
						Kruzic(temp->info.x - p2 * 10 * RADIUS, temp->info.y - deltay - offset, RADIUS, DETAIL, r, g, b, temp->info.l);
					}
					else {
						Kruzic(temp->info.x - p2 * 10 * RADIUS, temp->info.y - deltay - offset, RADIUS, DETAIL, 0.3, 0.3, 0.3, temp->info.l);
					}
				}
				else
					break;
				if (temp)
					temp = temp->next;
			}
			if (p2) {
				temp = Queue2;
				if (temp && temp->info.y - deltay - offset < LINE_H / piyel_ratio - TRESHOLD) {
					Delete(&Queue2);
					hold2 = 0;
					life += mods[0] ? 10 : 5;
					combo2 = 0;
					temp = Queue2;
				}
				if (hold2 != -1 && temp && temp->info.y - temp->info.l - deltay - offset < LINE_H / piyel_ratio - TRESHOLD) {
					life += mods[0] ? 10 : 5;
					combo2 = 0;
					hold2 = -1;
				}
				while (temp) {
					if (temp->info.y - temp->info.l - deltay - offset <= height) {
						float r, g, b;
						switch ((int)temp->info.x) {
							case (int)(-4 * RADIUS) :
								r = 0.0f, g = 1.0f, b = 0.0f;
								break;
								case (int)(-2 * RADIUS) :
									r = 1.0f, g = 0.0f, b = 0.0f;
									break;
								case 0:
									r = 1.0f, g = 1.0f, b = 0.0f;
									break;
									case (int)(2 * RADIUS) :
										r = 0.0f, g = 0.0f, b = 1.0f;
										break;
										case (int)(4 * RADIUS) :
											r = 1.0f, g = 0.5f, b = 0.0f;
											break;
						}
						if (temp->info.y - deltay - temp->info.l - offset > LINE_H * height / 2.0f - TRESHOLD) {
							Kruzic(temp->info.x + p2 * 10 * RADIUS, temp->info.y - deltay - offset, RADIUS, DETAIL, r, g, b, temp->info.l);
						}
						else {
							Kruzic(temp->info.x + p2 * 10 * RADIUS, temp->info.y - deltay - offset, RADIUS, DETAIL, 0.3, 0.3, 0.3, temp->info.l);
						}
					}
					else
						break;
					if (temp)
						temp = temp->next;
				}
			}

			if (mods[1])
				Lampa(combo, combo2, p2);

			if (life >= 100) {
				life = 100;
				if (p2 && !mods[2]) {
					mod = 1;
					deltay = deltay_prev;
					while (Queue) Delete(&Queue);
					while (Queue2) Delete(&Queue2);
					PlaySound(NULL, NULL, NULL);
				}
			}
			if (life <= 0) {
				life = 0;
				if (!mods[2]) {
					mod = 1;
					deltay = deltay_prev;
					while (Queue) Delete(&Queue);
					while (Queue2) Delete(&Queue2);
					PlaySound(NULL, NULL, NULL);
				}
			}
			if (risingEdge[17]) {
				mod = 1;
				deltay = deltay_prev;
				while (Queue) Delete(&Queue);
				while (Queue2) Delete(&Queue2);
				PlaySound(NULL, NULL, NULL);
			}
			char zaharije[21];
			_itoa(score, zaharije, 10);
			print(reference, zaharije, 6 * RADIUS + 20.0f - p2 * (22 * RADIUS + 135.0f), LINE_H*height / 2.0f + 45.0f, 0.6f, 0.6f, 0.6f, 15.0f, 20.0f, 4.0f, 4.0f);
			_itoa(combo, zaharije, 10);
			print(reference, zaharije, 6 * RADIUS + 20.0f - p2 * (22 * RADIUS + 135.0f), LINE_H*height / 2.0f + 20.0f, 0.6f, 0.6f, 0.6f, 15.0f, 20.0f, 4.0f, 4.0f);
			
			HP(p2 ? 0 : (-300.0f ), p2 ? 0 : (LINE_H*height / 2.0f), p2?4*RADIUS:5*RADIUS, p2, life);
			Strelica(p2 ? 0 : (-300.0f), p2 ? 0 : (LINE_H*height / 2.0f), 0.6f, 0.6f, 0.6f, 10.0f, p2?80.0f:100.0f, PI - (life / 100.0*(PI - 2 * LIFE_ANGLE) + LIFE_ANGLE));
			
			if (p2) {
				_itoa(score2, zaharije, 10);
				print(reference, zaharije, 6 * RADIUS + 20.0f + p2 * (10 * RADIUS), LINE_H*height / 2.0f + 45.0f, 0.6f, 0.6f, 0.6f, 15.0f, 20.0f, 4.0f, 4.0f);
				_itoa(combo2, zaharije, 10);
				print(reference, zaharije, 6 * RADIUS + 20.0f + p2 * (10 * RADIUS), LINE_H*height / 2.0f + 20.0f, 0.6f, 0.6f, 0.6f, 15.0f, 20.0f, 4.0f, 4.0f);
			}
			for (int j = 0; j < 5; j++) {
				if (pressed[j] == 1)
					Krofna(j * 2 * RADIUS - 4 * RADIUS - p2 * 10 * RADIUS, LINE_H*height / 2.0f, TRESHOLD, TRESHOLD - RADIUS, 50, 1.0f, 0.5f, 0.5f);
				if (p2 && pressed[j + 5] == 1)
					Krofna(j * 2 * RADIUS - 4 * RADIUS + p2 * 10 * RADIUS, LINE_H*height / 2.0f, TRESHOLD, TRESHOLD - RADIUS, 50, 1.0f, 0.5f, 0.5f);
			}
			break;
		case 4:
			naziv = fopen("mono.bmp", "rb");
			fread(&logoh, sizeof(BITMAPFILEHEADER), 1, naziv);
			fread(&logoi, sizeof(BITMAPINFOHEADER), 1, naziv);
			int palac, palcic;
			for (palac = 0; palac < logoi.biWidth; palac++) {
				for (palcic = 0; palcic < logoi.biHeight; palcic++) {
					GLubyte r, g, b;

					fread(&b, 1, 1, naziv);
					fread(&g, 1, 1, naziv);
					fread(&r, 1, 1, naziv);
					imageBuffer[palac][palcic][0] = (GLubyte)r;
					imageBuffer[palac][palcic][1] = (GLubyte)g;
					imageBuffer[palac][palcic][2] = (GLubyte)b;
				}
			}
			fclose(naziv);
			glRasterPos2f(-logoi.biWidth / 2.0f * pixel_ratio, -logoi.biHeight / 2.0f*piyel_ratio);
			glDrawPixels(logoi.biWidth, logoi.biHeight, GL_RGB, GL_UNSIGNED_BYTE, imageBuffer);

			if (risingEdge[9]) {
				naziv = fopen("manu.bmp", "rb");
				fread(&logoh, sizeof(BITMAPFILEHEADER), 1, naziv);
				fread(&logoi, sizeof(BITMAPINFOHEADER), 1, naziv);

				for (palac = 0; palac < logoi.biWidth; palac++) {
					for (palcic = 0; palcic < logoi.biHeight; palcic++) {
						GLubyte r, g, b;

						fread(&b, 1, 1, naziv);
						fread(&g, 1, 1, naziv);
						fread(&r, 1, 1, naziv);
						imageBuffer[palac][palcic][0] = (GLubyte)r;
						imageBuffer[palac][palcic][1] = (GLubyte)g;
						imageBuffer[palac][palcic][2] = (GLubyte)b;
					}
				}
				fclose(naziv);
				mod = 1;
			}
			break;
		case 5:
			print(reference, "DISPLAY", -3 * width / 8.0f + width / 20.0f, height / 2.0f - 2 * height / 50.0f, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
			print(reference, "GAMEPLAY", width / 8.0f + width / 20.0f, height / 2.0f - 2 * height / 50.0f, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);

			char *hadzic[10], hadzic_temp[5];

			print(reference, "RESOLUTION", -width / 2.0 + width / 20.0f, height / 4.0f, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
			_itoa(pos_width[pos_index], hadzic, 10);
			strcat(hadzic, "X");
			_itoa(pos_height[pos_index], hadzic_temp, 10);
			strcat(hadzic, hadzic_temp);
			print(reference, hadzic, -width / 2.0 + width / 4.0f, height / 4.0f, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);

			print(reference, "FULLSCREEN", -width / 2.0 + width / 20.0f, height / 4.0f - option_space, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
			print(reference, fullscreen ? "ENABLED" : "DISABLED", -width / 2.0 + width / 4.0f, height / 4.0f - option_space, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);


			print(reference, "RETURN TO MAIN MENU", -width / 2.0 + width / 20.0f, height / 4.0f - 2 * option_space, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);

			print(reference, "OFFSET", -width / 2.0 + width / 20.0f, height / 4.0f - 3 * option_space, 0.4f, 0.4f, 0.4f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
			_itoa(offset, hadzic, 10);
			print(reference, hadzic, -width / 2.0 + width / 4.0f, height / 4.0f - 3 * option_space, 0.4f, 0.4f, 0.4f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);




			print(reference, "HARD ROCK", width / 20.0f, height / 4.0f, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
			print(reference, mods[0] ? "ENABLED" : "DISABLED", width / 2.0 - width / 4.0f, height / 4.0f, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);

			print(reference, "FLASHLIGHT", width / 20.0f, height / 4.0f - option_space, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
			print(reference, mods[1] ? "ENABLED" : "DISABLED", width / 2.0 - width / 4.0f, height / 4.0f - option_space, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);

			print(reference, "NO FAIL", width / 20.0f, height / 4.0f - 2 * option_space, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
			print(reference, mods[2] ? "ENABLED" : "DISABLED", width / 2.0 - width / 4.0f, height / 4.0f - 2 * option_space, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);

			mod_modifier = (mods[0] ? 1.25f : 1.0f) * (mods[1] ? 1.4f : 1.0f) * (mods[2] ? 0.5f : 1.0f);

			print(reference, "SCORE PERCENT", width / 20.0f, height / 4.0f - 3 * option_space, 0.4f, 0.4f, 0.4f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
			_itoa(100 * mod_modifier, hadzic, 10);
			print(reference, hadzic, width / 2.0 - width / 4.0f, height / 4.0f - 3 * option_space, 0.4f, 0.4f, 0.4f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);

			/*Rising edge:
			0 -> Q		 1 -> W		 2 -> E
			3 -> R		 4 -> T		 5 -> Up
			6 -> Down    7 -> Left   8 -> Right
			9 -> Enter  10 -> Plus  11 -> Minus
			12 -> 6		13 -> 7		14 -> 8
			15 -> 9		16 -> 0
			*/

			if (risingEdge[5])
				pos = pos > 0 ? pos - 1 : pos;
			if (risingEdge[6])
				pos = pos < 2 ? pos + 1 : pos;
			if (risingEdge[7])
				side = 0;
			if (risingEdge[8])
				side = 1;

			if (risingEdge[9]) {
				if (side)
					mods[pos] = !mods[pos];
				else
					switch (pos) {
					case 0:
						if (!side)
							pos_index = pos_index != 2 ? pos_index + 1 : 0;
						break;
					case 1:
						fullscreen = !fullscreen;
						break;
					case 2:
						mod = 1;
						pos = 0;
						break;
					};
			}

			if (side && rotation > 0)
				rotation -= PI * 4 * deltaTime;

			if (!side && rotation < PI)
				rotation += PI * 4 * deltaTime;

			if (rotation > PI)
				rotation = PI;
			if (rotation < 0)
				rotation = 0;

			if (mod == 5)
				Strelica(-height / 14.0f, height / 4.0f - pos * option_space, 1.0f, 1.0f, 1.0f, height / 35.0f, width / 50.0f, rotation);
			last = first;
			break;
		case 6:
			printf(""); //TOTALNO BESKORISNO
			char zika[256], misic[256] = "Scores\\";
			int score_counter = 0;
			Crop(songs[(int)deltay], zika);
			strcat(zika, ".duck");
			strcat(misic, zika);
			FILE *score_f;
			if (score_f = fopen(misic, "rb")) {
				print(reference, "HIGHSCORES", -width / 8.0f + width / 20.0f, height / 2.0f - 2 * height / 50.0f, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
				struct player cur_player;
				char broj_s[16];
				while (1) {
					size_t n = fread(&cur_player, sizeof(struct player), 1, score_f);
					if (n < 1)
						break;
					_itoa((int)cur_player.score, broj_s, 10);
					print(reference, cur_player.name, -width / 8.0f - width/20.0f, height / 4.0f - score_counter * option_space / 4.0f, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
					print(reference, broj_s, width / 8.0f, height / 4.0f - score_counter * option_space / 4.0f, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
					score_counter++;
				}
				fclose(score_f);
			}
			else
				print(reference, "THIS MAP HASNT BEEN PLAYED YET", -width / 4.0f + width / 20.0f, height / 2.0f - 2 * height / 50.0f, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
			print(reference, "PRESS ENTER TO RETURN TO MAIN MENU", -width / 4.0f + width/ 40.0f, - height / 2.0f + 2 * height / 50.0f, 0.6f, 0.6f, 0.6f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
			if (risingEdge[9])
				mod = 1;
			break;
		case 7:
			if (!p2) {
				print(reference, "YOU ROCK", -width / 8.0f, height / 2.0f - height / 10.0f, 1.0f, 1.0f, 1.0f, width / 50.0f, height / 20.0f, width / 200.0f, width / 100.0f);
				print(reference, "YOUR SCORE", -width / 4.0f, height / 4.0f - height / 20.0f, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
			}
			else {
				print(reference, score>score2?"PLAYER 1 WINS":(score==score2?"DRAW":"PLAYER 2 WINS"), -width / 8.0f, height / 2.0f - height / 10.0f, 1.0f, 1.0f, 1.0f, width / 50.0f, height / 20.0f, width / 200.0f, width / 100.0f);
				print(reference, "PLAYER 1 SCORE", -width / 4.0f, height / 3.0f - height / 20.0f, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
				print(reference, "PLAYER 2 SCORE", -width / 4.0f, height / 3.0f - height / 8.0f, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
			}
			print(reference, p2?(player_ready?"PLAYER 2 NAME":"PLAYER 1 NAME"):"ENTER YOUR NAME", -width / 4.0f, height / 4.0f - height / 8.0f, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
			print(reference, player_ready?name2:name, width / 4.0f, height / 4.0f - height / 8.0f, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);

			char miroslav[21];
			_itoa(score, miroslav, 10);
			print(reference, miroslav, width / 4.0f, p2?(height / 3.0f - height / 20.0f):(height / 4.0f - height / 20.0f), 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
			if (p2) {
				_itoa(score2, miroslav, 10);
				print(reference, miroslav, width / 4.0f, height / 3.0f - height / 8.0 , 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
			}

			char letter[2] = {'A', 0};
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 7; j++) {
					if (i == 3 && j > 4)
						break;
					print(reference, letter, -width / 3.0f + width/40.0f + j * width / 10.0f, -i * height / 8.0f, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
					letter[0]++;
				}
			}
			print(reference, "BCK", -width / 3.0f + width / 40.0f + 5 * width / 10.0f - width / 100.0f - width / 350.0f, -3 * height / 8.0f, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
			print(reference, "END", -width / 3.0f + width / 40.0f + 6 * width / 10.0f - width / 100.0f - width / 350.0f, -3 * height / 8.0f, 1.0f, 1.0f, 1.0f, width / 100.0f, height / 50.0f, width / 350.0f, width / 250.0f);
			if (risingEdge[5])
				ypos = ypos > 0 ? ypos-1 : 0;
			if (risingEdge[6])
				ypos = ypos < 3 ? ypos + 1 : 3;
			if (risingEdge[7])
				xpos = xpos > 0 ? xpos-1 : 0;
			if (risingEdge[8])
				xpos = xpos < 6 ? xpos+1 : 6;
			
			if (risingEdge[9]) {
				char c = 'A' + ypos * 7 + xpos;
				if (c <= 'Z') {
					if (!player_ready) {
						if(strlen(name)<3)
							name[strlen(name)] = c;
					}
					else {
						if (strlen(name2) < 3)
							name2[strlen(name2)] = c;
					}
				}
				else if (c == 'Z' + 1) {
					if (!player_ready) {
						if(strlen(name)>0)
							name[strlen(name) - 1] = 0;
					}
					else {
						if (strlen(name2) > 0)
							name2[strlen(name2) - 1] = 0;
					}
				}
				else if (c == 'Z' + 2) {
					if (p2 && !player_ready) {
						xpos = 0, ypos = 0;
						player_ready = !player_ready;
					}
					else {
						deltay = deltay_prev;
						char zika[256], misic[256] = "Scores\\";
						int score_counter = 0;
						struct player temp_player[10];

						Crop(songs[deltay_prev], zika);
						strcat(zika, ".duck");
						strcat(misic, zika);
						FILE *score_f;
											
						score_f = fopen(misic, "rb");
						if (score_f) {
							while (1) {
								size_t n = fread(&temp_player[score_counter], sizeof(struct player), 1, score_f);
								if (n < 1)
									break;
								score_counter++;
								if (score_counter == 10)
									break;
							}
							fclose(score_f);
						}
						score_f = fopen(misic, "wb");
						int za_for;
						short int tasha = 1;
						for (za_for = 0; za_for < ((score_counter + !tasha)>10?10: (score_counter + !tasha)); za_for++) {
							if (temp_player[za_for - (!tasha)].score >= score || !tasha) {
								size_t n = fwrite(temp_player + za_for - (!tasha), sizeof(struct player), 1, score_f);
							}
							else if (tasha) {
								struct player new_player;
								strcpy(new_player.name, name);
								new_player.score = score;
								size_t n =fwrite(&new_player, sizeof(struct player), 1, score_f);
								tasha = 0;
							}
						}
						if ((tasha && score_counter<10)) { //////T H I C C
							struct player new_player;
							strcpy(new_player.name, name);
							new_player.score = score;
							size_t n = fwrite(&new_player, sizeof(struct player), 1, score_f);
						}
						fclose(score_f);

						if (p2) {
							score_counter = 0;
							score_f = fopen(misic, "rb");
							if (score_f) {
								while (1) {
									size_t n = fread(&temp_player[score_counter], sizeof(struct player), 1, score_f);
									if (n < 1)
										break;
									score_counter++;
									if (score_counter == 10)
										break;
								}
								fclose(score_f);
							}
							score_f = fopen(misic, "wb");
							tasha = 1;
							for (za_for = 0; za_for < ((score_counter + !tasha) > 10 ? 10 : (score_counter + !tasha)); za_for++) {
								if (temp_player[za_for - (!tasha)].score >= score2 || !tasha) {
									size_t n = fwrite(temp_player + za_for - (!tasha), sizeof(struct player), 1, score_f);
								}
								else if (tasha) {
									struct player new_player;
									strcpy(new_player.name, name2);
									new_player.score = score2;
									size_t n = fwrite(&new_player, sizeof(struct player), 1, score_f);
									tasha = 0;
								}
							}
							if ((tasha && score_counter < 10)) { //////T H I C C
								struct player new_player;
								strcpy(new_player.name, name2);
								new_player.score = score2;
								size_t n = fwrite(&new_player, sizeof(struct player), 1, score_f);
							}
							fclose(score_f);
						}
						mod = 6;
					}
				}
			}
			Strelica(-width / 3.0f + width / 40.0f + xpos * width / 10.0f, -ypos * height / 8.0f + height/ 15.0f, 1.0f, 1.0f, 1.0f, height / 35.0f, width / 50.0f, -PI / 2.0);
			break;
		}
		for (int j = 0; j < 18; j++) {
			risingEdge[j] = 0;
		}
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	GASI: glfwTerminate();
	fclose(naziv);
	UpdateConfig();
}