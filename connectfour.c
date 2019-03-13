
#define ROWS 6
#define COLS 7

typedef struct slot {
	char value = ' ';
	struct slot *above;
	struct slot *below
	struct slot *left;
	struct slot *right;
} slot;

int main(int argc, char *argv[]){