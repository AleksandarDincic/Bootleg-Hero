#ifndef STRUCTS
#define STRUCTS

#define SECOND 44
#define TRESHOLD 40

struct slovo {
	char c;
	short int bitmap;
};

struct Header {
	char ChunkID[4];
	int ChunkSize;
	char Format[4];
	char fmt_header[4];
	int fmt_chunk_size;
	short audio_format;
	short num_channels;
	int sample_rate;
	int byte_rate;
	short blockAlign;
	short bit_sample;
	char data_header[4];
	int data_bytes;
};

struct note {
	long double x, y;
	float l;
};

struct node {
	struct note info;
	struct node *next;
};

struct b {
	int front, rear;
	long long int notes[SECOND];
};

struct player {
	char name[4];
	long double score;
};

int Len_q(struct node *);

int Empty_q(struct node *);

void Insert(struct node **, struct note);

void Delete(struct node **);

int Len_b(struct b *);

int Empty_b(struct b *);

int Full_b(struct b *);

void Insert_b(struct b *, long long int);

long long int Delete_b(struct b *);

void InitReference();

#endif