#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>
#define CLEAR_SCREEN "\e[1;1H\e[2J"

//Dione Garcia Agapito// // matricula 2113332098 //
// valores fixo para movimentar as peças//
enum
{
    KEY_ESC     = 27,
    ARROW_UP    = 256 + 72,
    ARROW_DOWN  = 256 + 80,
    ARROW_LEFT  = 256 + 75,
    ARROW_RIGHT = 256 + 77
};

static int get_code(void);
void startGame(int *matrixSize);
void removeMatrix (int **matrix, int matrixSize);
void randomMatrix(int **matrix, int MatrixSize);
void swapValue(int **matrix, int x1, int y1, int x2, int y2);
void printMatrix (int **matrix, int matrixSize);
void movePiece(int **matrix, int *quantMoves, int matrixSize, int direction);
int **createMatrix (int matrixSize);
int isSolved(int **matrix, int matrixSize);
void removeMatrix();
//função principal//
int main ()
{
    setlocale(LC_ALL, "");
    int** puzzleMatrix = NULL;
    int quantMovimentos;
    int matrixSize;
    int keyChar;

    do
    {
        startGame(&matrixSize);
    }
    while(matrixSize < 3 || matrixSize > 5);

    quantMovimentos = 0;
    puzzleMatrix = createMatrix(matrixSize);
    randomMatrix(puzzleMatrix, matrixSize);

    do
    {

        system("cls");
        printf("\n\t \t \t  Use as setas para mover o zero");
        printf("\n\t \t \t Precione ESC se deseja desistir");
        printf("\n");
        printMatrix(puzzleMatrix, matrixSize);

        printf("\n Quantidade de Movimentos: %d", quantMovimentos);
        printf("\n");

        keyChar = get_code();

        movePiece(puzzleMatrix, &quantMovimentos, matrixSize, keyChar);

        if (isSolved(puzzleMatrix, matrixSize) == 1)
        {
            system("cls");
            printf("\n\t \t \t Parabens você venceu !!!! \n");
            printf("\n");
            printMatrix(puzzleMatrix, matrixSize);
            printf("\n");
            printf("\n\t \t \t Quantidade de Movimentos: %d \n", quantMovimentos);
            break;
        }
    }
    while (keyChar != KEY_ESC );

    removeMatrix(puzzleMatrix, matrixSize);
    system("pause");
    return 0;
}
// obter codigo do caracter//
static int get_code(void)
{
    int ch = getch();

    if (ch == 0 || ch == 224)
        ch = 256 + getch();

    return ch;
}
// iniciar game//
void startGame (int *matrixSize)
{
    system("cls");
    printf ("\t \t \t \t --------------\n");
        printf ("\t \t \t \t| Bem vindo ao |\n");
        printf ("\t \t \t \t|  Jogo dos 8  |\n");
        printf ("\t \t \t \t -------------- \n");

    int  cond;

        printf("\n\t \t \t Se estiver pronto para começar \n\t \t \t    Digite (1) - Para SIM  \n \t \t \t \t   (2) - Para NÃO \n");
        scanf("%d", &cond);
        printf("\t \t \t \tVocê escolheu: %d\n\n ",cond);


    if ( cond == 1)
        printf("\t \t \t  [Se prepare, vamos começar:]\n\n\n");
    else
    {
        if ( cond == 2)
        printf(" \n\t \t \t    Você não começou o jogo.\n\t \t \t \tPor favor recomece \n");
        exit (0);
    }
    printf("\n\t \tQual tamanho do tabuleiro gostaria de jogar 3,4,5: ");
    scanf("%d",matrixSize);
}

int** createMatrix (int matrixSize)
{
    int row, col;
    int **matrix = NULL;
    matrix = malloc (sizeof (int) * matrixSize * matrixSize);

    if (matrix != NULL)
    {
        for (row = 0; row < matrixSize; row++)
        {
            matrix[row] = malloc (sizeof (int) * matrixSize);
        }
    }

    return matrix;
}
// bloco de aleatoriedade e logica de movimento//
void randomMatrix(int **matrix, int matrixSize)
{
    srand(time(0));
    int row, col;
    int value = 1;
    for(row = 0; row < matrixSize; row++)
    {
        for(col = 0; col < matrixSize; col++)
        {
            if((row + 1)*(col + 1) != matrixSize*matrixSize){
                matrix[row][col] = value;
                value++;
            } else {
                matrix[row][col] = 0;
            }
        }
    }

    int  quantShorts;
    int rowFirst, colFirst, rowSecond, colSecond;

    for (quantShorts = 0; quantShorts < 100; quantShorts++)
    {
        int direction = rand() % 4;
        int minX = 0;
        int minY = 0;
        int maxX = (matrixSize - 1);
        int maxY = (matrixSize - 1);

        int startX, startY, targetX, targetY;
        int row, col;
        int isFounded = 0;

        for(row = 0; row < matrixSize; row++)
        {
            for(col = 0; col < matrixSize; col++)
            {
                if(matrix[row][col] == 0)
                {
                    startX = row;
                    startY = col;
                    isFounded = 1;
                    break;
                }
            }

            if(isFounded == 1)
            {
                break;
            }
        }

        switch (direction)
        {

        case 0:
            targetX = startX - 1;
            targetY = startY;
            if(targetX >= minX)
            {
                swapValue(matrix, startX, startY, targetX, targetY);
            }
            break;

        case 1:
            targetX = startX + 1;
            targetY = startY;
            if(targetX <= maxX)
            {
                swapValue(matrix, startX, startY, targetX, targetY);
            }
            break;

        case 2:
            targetY = startY - 1;
            targetX = startX;
            if(targetY >= minY)
            {
                swapValue(matrix, startX, startY, targetX, targetY);
            }
            break;

        case 3:
            targetY = startY + 1;
            targetX = startX;
            if(targetY <= maxY)
            {
                swapValue(matrix, startX, startY, targetX, targetY);
            }
            break;
        }
    }

}
//sobrepor matrix//
void removeMatrix (int **matrix, int matrixSize)
{
    int row;
    for (row = 0; row < matrixSize; row++)
    {
        free (matrix[row]);
    }
    free (matrix);
}
//troca de posição//
void swapValue(int **matrix, int x1, int y1, int x2, int y2)
{
    int aux = matrix[x1][y1];
    matrix[x1][y1] = matrix[x2][y2];
    matrix[x2][y2] = aux;
}
//movimento//
void movePiece(int **matrix, int *quantMoves, int matrixSize, int direction)
{
    int minX = 0;
    int minY = 0;
    int maxX = (matrixSize - 1);
    int maxY = (matrixSize - 1);

    int startX, startY, targetX, targetY;
    int row, col;
    int isFounded = 0;

    for(row = 0; row < matrixSize; row++)
    {
        for(col = 0; col < matrixSize; col++)
        {
            if(matrix[row][col] == 0)
            {
                startX = row;
                startY = col;
                isFounded = 1;
                break;
            }
        }

        if(isFounded == 1)
        {
            break;
        }
    }

    switch (direction)
    {

    case ARROW_UP:
        targetX = startX - 1;
        targetY = startY;
        if(targetX >= minX)
        {
            swapValue(matrix, startX, startY, targetX, targetY);
            (*quantMoves)++;
        }
        break;

    case ARROW_DOWN:
        targetX = startX + 1;
        targetY = startY;
        if(targetX <= maxX)
        {
            swapValue(matrix, startX, startY, targetX, targetY);
            (*quantMoves)++;
        }
        break;

    case ARROW_LEFT:
        targetY = startY - 1;
        targetX = startX;
        if(targetY >= minY)
        {
            swapValue(matrix, startX, startY, targetX, targetY);
            (*quantMoves)++;
        }
        break;

    case ARROW_RIGHT:
        targetY = startY + 1;
        targetX = startX;
        if(targetY <= maxY)
        {
            swapValue(matrix, startX, startY, targetX, targetY);
            (*quantMoves)++;
        }
        break;
    }
}
//comparar//
int isSolved(int **matrix, int matrixSize)
{
    int vectorIndex = 0;
    int row, col;

    for(row = 0; row < matrixSize; row++)
    {
        for(col = 0; col < matrixSize; col++)
        {
            if( (vectorIndex + 1) != matrixSize*matrixSize){
                if(matrix[row][col] != (vectorIndex + 1))
                {
                    return 0;
                }
            }
             vectorIndex++;
        }
    }
    return 1;
}
//print da matrix//
void printMatrix(int **matrix, int matrixSize)
{
    int row;
    int col;
    if (matrix != NULL)
    {

        printf ("\n");
        for (row = 0; row < matrixSize; row++)
        {
            for (col = 0; col < matrixSize; col++)
            {
                printf ("\t %d ", matrix[row][col]);
                if (col == (matrixSize - 1))
                {
                    printf ("\n");
                }
            }
        }

    }
}
