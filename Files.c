#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Files.h"

float pixel_ratio, piyel_ratio;
int width, height;
int fullscreen, offset = 0;
int pos_width[3] = { 1280, 1600, 1920 };
int pos_height[3] = { 720, 900, 1080 };
int pos_index;

void Crop(char *song_file, char *song_name) {
	char *i = song_file, *j = NULL;
	while (i = strchr(i, '\\'))
	{
		j = i++;
	}
	j++;
	i = song_name;
	while (*j != '.') {
		*(i++) = toupper(*(j++));
	}
	*i = 0;
}

int ListDirectoryContents(const char *sDir, char ***rez, int *n)
{
	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;

	*rez = malloc(sizeof(char**));
	*n = 0;
	char sPath[2048];
	sprintf(sPath, "%s\\*.wav", sDir);

	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		//printf("Path not found: [%s]\n", sDir);
		return 0;
	}

	do
	{
		if (strcmp(fdFile.cFileName, ".") != 0 && strcmp(fdFile.cFileName, "..") != 0)
		{
			sprintf(sPath, "%s\\%s", sDir, fdFile.cFileName);
			if (fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
			{

				//printf("folder nije dozvoljen\n");
			}
			else {
				++(*n);
				*rez = realloc(*rez, (*n) * sizeof(char*));
				*(*rez + (*n - 1)) = malloc(strlen(sPath) + 1);
				strcpy(*(*rez + (*n - 1)), sPath);
				//printf("File: %s\n", sPath);
			}
		}
	} while (FindNextFile(hFind, &fdFile));

	FindClose(hFind);

	return 1;
}

void ReadConfig() {

	FILE *config = fopen("config.ini", "r");
	if (config) {
		char ponjavic[20];
		fscanf(config, "%s", ponjavic);
		fscanf(config, "%d", &width);
		fscanf(config, "%s", ponjavic);
		fscanf(config, "%d", &height);
		if ((width != pos_width[0] || height != pos_height[0]) && (width != pos_width[1] || height != pos_height[1]) && (width != pos_width[2] || height != pos_height[2])) {
			printf("Molimo da se korisnik ne pravi pametan\n");
			width = pos_width[0];
			height = pos_height[0];
		}
		fscanf(config, "%s", ponjavic);
		fscanf(config, "%d", &fullscreen);
		fscanf(config, "%s", ponjavic);
		fscanf(config, "%d", &offset);
		fclose(config);
	}
	else {
		config = fopen("config.ini", "w");
		fputs("Width: 1600\n", config);
		fputs("Height: 900\n", config);
		fputs("Fullscreen: 0\n", config);
		fputs("Offset: 0", config);
		fclose(config);

		width = 1600;
		height = 900;
		fullscreen = 0;
	}
	for (int i = 0; i < 3; i++) {
		if (height == pos_height[i]) {
			pos_index = i;
			break;
		}
	}
}

void UpdateConfig() {
	char danko[20], danko_temp[20];
	FILE *config = fopen("config.ini", "w");

	strcpy(danko, "Width: ");
	_itoa(pos_width[pos_index], danko_temp, 10);
	strcat(danko, danko_temp);
	strcat(danko, "\n");
	fputs(danko, config);

	strcpy(danko, "Height: ");
	_itoa(pos_height[pos_index], danko_temp, 10);
	strcat(danko, danko_temp);
	strcat(danko, "\n");
	fputs(danko, config);

	strcpy(danko, "Fullscreen: ");
	_itoa(fullscreen, danko_temp, 10);
	strcat(danko, danko_temp);
	strcat(danko, "\n");
	fputs(danko, config);

	strcpy(danko, "Offset: ");
	_itoa(offset, danko_temp, 10);
	strcat(danko, danko_temp);
	fputs(danko, config);

	fclose(config);
	return 0;

}