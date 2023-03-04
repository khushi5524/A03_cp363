#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
	int row;
	int column;
} parameters;

pthread_t rowThread, clmThread, onetrd, twotrd, threetrd, fourtrd,
		fivetrd, sixtrd, seventrd, eighttrd, ninetrd;

int check[11];
int grid[9][9];

void* rowWork(void *parameter);
void* clmWork(void *parameter);
void* dataWork(void *parameter);

int mingrid = 2;

int main(int argc, char *argv[]) {

	if (argc == 1) {
		printf("Unsufficient arguments\n");
	} else {
		FILE *table = fopen(argv[1], "r");

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				fscanf(table, "%d ", &grid[i][j]);
			}
		}

		void *clm;
		void *row;
		void *sOne;
		void *sTwo;
		void *sThree;
		void *sFour;
		void *sFive;
		void *sSix;
		void *sSeven;
		void *sEight;
		void *sNine;

		parameters* dataC = (parameters*) malloc(sizeof(parameters));
        dataC->row = 0;
        dataC->column = 0;

        parameters* dataR = (parameters*) malloc(sizeof(parameters));
        dataR->row = 0; 
        dataR->column = 0;

        parameters* dataOne = (parameters*) malloc(sizeof(parameters));
        dataOne->row = 0;
        dataOne->column = 0;

        parameters* dataTwo = (parameters*) malloc(sizeof(parameters));
        dataTwo->row = 0;
        dataTwo->column = 3;

        parameters* dataThree = (parameters*) malloc(sizeof(parameters));
        dataThree->row = 0;
        dataThree->column = 6;

        parameters* dataFour = (parameters*) malloc(sizeof(parameters));
        dataFour->row = 3;
        dataFour->column = 0;

        parameters* dataFive = (parameters*) malloc(sizeof(parameters));
        dataFive->row = 3;
        dataFive->column = 3;

        parameters* dataSix = (parameters*) malloc(sizeof(parameters));
        dataSix->row = 3;
        dataSix->column = 6;

        parameters* dataSeven = (parameters*) malloc(sizeof(parameters));
        dataSeven->row = 6;
        dataSeven->column = 0;

        parameters* dataEight = (parameters*) malloc(sizeof(parameters));
        dataEight->row = 6;
        dataEight->column = 3;

        parameters* dataNine = (parameters*) malloc(sizeof(parameters));
        dataNine->row = 6;
        dataNine->column = 6;


		pthread_create(&clmThread, NULL, clmWork, (void*) dataC);
		pthread_create(&rowThread, NULL, rowWork, (void*) dataR);
		pthread_create(&onetrd, NULL, dataWork, (void*) dataOne);
		pthread_create(&twotrd, NULL, dataWork, (void*) dataTwo);
		pthread_create(&threetrd, NULL, dataWork, (void*) dataThree);
		pthread_create(&fourtrd, NULL, dataWork, (void*) dataFour);
		pthread_create(&fivetrd, NULL, dataWork, (void*) dataFive);
		pthread_create(&sixtrd, NULL, dataWork, (void*) dataSix);
		pthread_create(&seventrd, NULL, dataWork, (void*) dataSeven);
		pthread_create(&eighttrd, NULL, dataWork, (void*) dataEight);
		pthread_create(&ninetrd, NULL, dataWork, (void*) dataNine);

		pthread_join(clmThread, &clm);
		pthread_join(rowThread, &row);
		pthread_join(onetrd, &sOne);
		pthread_join(twotrd, &sTwo);
		pthread_join(threetrd, &sThree);
		pthread_join(fourtrd, &sFour);
		pthread_join(fivetrd, &sFive);
		pthread_join(sixtrd, &sSix);
		pthread_join(seventrd, &sSeven);
		pthread_join(eighttrd, &sEight);
		pthread_join(ninetrd, &sNine);
		int n = 0;
		printf("Sudoku Puzzle Solution is:\n");
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				printf("%d ", grid[i][j]);

			}
			printf("\n");
		}
		while (n < 11) {

			if (check[n] == 1) {
				n++;
			} else {
				printf("Sudoku puzzle is NOT valid\n");
				exit(0);
			}
		}
		printf("Sudoku puzzle is valid\n");
	}

}

void* rowWork(void *prmts) {

	parameters* workR = (parameters*) prmts;
	int clm = workR->column;
	int row = workR->row;

	for (int i = clm; i < 9; i++) {
		int numrow[9] = { 0 };
		for (int j = row; j < 9; j++) {
			int num = grid[i][j];

			if (numrow[num - 1] == 0 && num > 0) {
				numrow[num - 1] = num;
			} else {
				if (check[1] < 3) {
                    check[1] = 0;
                }
                pthread_exit(0);
            }

        }
    }
    if (check[1] < 3) {
        check[1] = 1;
    }
    pthread_exit(0);

}

void* dataWork(void *prmts) {
	int numCol[9] = { 0 };
	parameters* work = (parameters*) prmts;
	int clm = work->column;
	int row = work->row;

	for (int i = row; i < row + 3; ++i) {
		for (int j = clm; j < clm + 3; ++j) {
			int num = grid[i][j];

			if (numCol[num - 1] == 0 && num > 0) {
				numCol[num - 1] = num;
			} else {
				if (mingrid < 11) {
                    check[mingrid] = 0;
                }
                mingrid++;
                pthread_exit(0);
            }

        }
    }

    if (mingrid < 11) {
        check[mingrid] = 1;
    }
    mingrid++;
    pthread_exit(0);

}

void* clmWork(void *prmts) {

	parameters* workC = (parameters*) prmts;
	int clm = workC->column;
	int row = workC->row;

	for (int i = clm; i < 9; i++) {
		int numCol[9] = { 0 };
		for (int j = row; j < 9; j++) {
			int num = grid[i][j];

			if (numCol[num - 1] == 0 && num > 0) {
				numCol[num - 1] = num;
			} else {
				check[0] = 0;

				pthread_exit(0);
			}

		}
	}

	check[0] = 1;
	pthread_exit(0);
}