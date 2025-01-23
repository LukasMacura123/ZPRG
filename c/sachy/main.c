#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

const char abc[] = "abcdefgh";
int *removedPieces = NULL;
int removedPiecesSize;

int POLE[8][8] = {
    {10,8,9,11,12,9,8,10},
    {7,7,7,7,7,7,7,7},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1},
    {4,2,3,5,6,3,2,4}
};

void moveCursor(int col, int row) {
    printf("\033[%d;%dH", row, col);
}
void setTextColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void drawBoard(){
 
    const int arr[8] = {8,7,6,5,4,3,2,1};
    printf("   a b c d e f g h\n\n");
    for(int y = 0; y<8; y++){

        printf("%d ", arr[y]);
        for(int x = 0; x<8; x++){

            if(y%2 == 0){
                if(x%2 == 0) printf(" %c", 254);
                else printf(" -");
            
            }else{
                if(x%2 == 1) printf(" %c", 254);
                else printf(" -");
            }
        }
        printf("\n");
    }

    printf("\n\n1 -> pawn\n2 -> knight\n3 -> bishop\n4 -> rook\n5 -> qween\n6 -> king");
}
void push(int* array, int* size, int value) {

    *size += 1;
    *array = realloc(*array, *size * sizeof(int));
    if (*array == NULL) {
        perror("push failed");
        exit(EXIT_FAILURE);
    }

    (*array)[*size - 1] = value;
}
int charNaSouradnice(char AazH){

    for(int i = 0; i<8; i++){
        if(AazH == abc[i]) return i;
    }
}
int validInput(char arr[3]){

    int valid[2] = {0,0};
    for(int i = 0; i<8; i++){

        if(abc[i] == arr[0]) valid[0] = 1;
        if(i+48 == arr[1]) valid[1] = 1;
    }
    return valid[0] && valid[1];
}
void drawPieces(){

    for(int y = 0; y<8; y++){

        for(int x = 0; x<8; x++){
            
            if(POLE[y][x] != 0){
                moveCursor((x+2)*2, y+3);
                
                if(POLE[y][x] > 6){
                    setTextColor(12);
                    printf("%d", POLE[y][x]-6);
                }else{
                    setTextColor(2);
                    printf("%d", POLE[y][x]);
                } 
            }
        }
    }

    moveCursor(0,24);
}
void movePiece(int currX, int currY, int destX, int destY){

    int piece;
    piece = POLE[currY][currX];

    POLE[currY][currX] = 0;
    POLE[destY][destX] = piece;

    moveCursor((currX+2)*2, currY+3);
    
    if(currY%2 == 0){
        if(currX%2 == 0) printf("%c", 254);
        else printf("-");
    }else{
        if(currX%2 == 1) printf("%c", 254);
        else printf("-");
    }

    if(POLE[destY][destX] == 0){
        push(removedPieces, removedPiecesSize, POLE[destY][destX]);
    }
    POLE[destY][destX] = piece;

    moveCursor((destX+2)*2, destY+3);
    printf("%d", (piece > 6 ? piece-6 : piece));
}
int main(){

    drawBoard();
    drawPieces(POLE);

    char souradnice[2][3];
    int tah = 1;
    
    while(1){

        if(tah){

            setTextColor(8);
            moveCursor(0,24);
            printf("bily na tahu");
            moveCursor(0,25);
            printf("vlozte souradnici figurky s kterou chcete pohnout - ");
            setTextColor(7);
            scanf("%2s", souradnice[0]);
            
            moveCursor(0,25);
            setTextColor(8);            
            printf("vlozte souradnice na ktere chcete figurku presunout - ");
            setTextColor(7);
            scanf("%2s", souradnice[1]);

            souradnice[0][0] = charNaSouradnice(souradnice[0][0]);
            souradnice[0][1] -= 49;
            souradnice[1][0] = charNaSouradnice(souradnice[1][0]);
            souradnice[1][1] -= 49;

            moveCursor(0,30);
            printf("%d - %d\n%d - %d", souradnice[0][0], souradnice[0][1], souradnice[1][0], souradnice[1][1]);

            movePiece(souradnice[0][0], souradnice[0][1], souradnice[1][0], souradnice[1][1]);

        }else{  

        }
    }
    
    return 0;
}