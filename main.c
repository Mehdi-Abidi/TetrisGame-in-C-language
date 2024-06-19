#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include<ctype.h>
#include <time.h>
#define WIDTH 10
#define HEIGHT 20
//conio.h library used//
//get keyboard input.
int keyinput(){
    if(kbhit()){//check rather the key is pressed or not//
	  return getch();//returns the ascii value of the pressed key//
    }
    else{
	  return 1;
   }
}
//move cursor.
void gotoxy(int x, int y){
    COORD C;//coordinates accesing 
    C.X = 2*x;//Controlling Map X axis
    C.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), C);//Predefined Functionn to handle cursor position//
}
int mainmenu(){
    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
    int keyInput;
    gotoxy(1,2);
    SetConsoleTextAttribute(hand, 3);
    printf("************************");
    gotoxy(1,3);
    SetConsoleTextAttribute(hand, 4);
    printf("~WELCOME TO TETRIS~");
    SetConsoleTextAttribute(hand, 3);
    gotoxy(1,4);
    printf("************************\n");
    SetConsoleTextAttribute(hand, 4);
    gotoxy(2,6);
    printf("Instructions\n");
    SetConsoleTextAttribute(hand, 3);
    gotoxy(2,7);
    printf("Left :left arrow key\n");
    gotoxy(2,8);
    printf("Right :right arrow key \n");
    gotoxy(2,9);
    printf("Down:down arrow key \n");
    gotoxy(2,10);
    printf("Exit:'e'\n");
    while(1){
        keyInput = keyinput();
        if(keyInput == 's' ) break;
        if(keyInput == 'e') break;
        gotoxy(7, 15);
        SetConsoleTextAttribute(hand, 4);
        printf("Press s To Start");
    }
    return keyInput;
}
typedef char Gamemap ;
void wall(Gamemap map[HEIGHT][WIDTH]){
    int h, w;
    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);//predefine function to handle colors
    SetConsoleTextAttribute(hand, 12);//predefine function ,numbers is used to control colors
    for(h=0; h<=HEIGHT +1; h++){
        for(w=0; w<=WIDTH+1; w++){
            gotoxy(w+1,h+1);
            if(h==0 || w==0 || h==HEIGHT+1 || w==WIDTH+1)
                printf("%c%c",254,222);//Making Of Borders//
//               printf(" %d,%d ",h,w);
        }
        printf("\n");
    }
}
void maps(Gamemap map[HEIGHT][WIDTH]){
    int h, w;
    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
       SetConsoleTextAttribute(hand,rand()%5+6);
    for(h=0; h<HEIGHT; h++){
        for(w=0; w<WIDTH; w++){
            gotoxy(w+2,h+2);
            if(map[h][w] == 0){
                printf("  ");
            }else if(map[h][w] == 1){
             
                printf("%c%c",254,256);
			}
        }
        
        printf("\n");
         
    }
}
void calculation(int best, int score){//best score and current score//
    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, 4);
	gotoxy(20, 4);
    printf("Best :");
    gotoxy(20, 5);
    printf("Score :");
    gotoxy(20, 7);
    printf("Exit : 'e' ");
    gotoxy(20,8);
    printf("Pause : 'p'");
    SetConsoleTextAttribute(hand, 14);
    gotoxy(24, 4);
    printf("%d", best);
    gotoxy(24, 5);
    printf("%d", score);
}
typedef struct currentloc{
    int X;
    int Y;
} Loc;
void internalmap(Gamemap map[HEIGHT][WIDTH]){
    int i, j=0;
    for(i=0;i<HEIGHT;i++){
        for(j=0; j<WIDTH; j++){
            map[i][j] = 0;//use to clear the  internal map //
        }
    }
}
void coordinates_of_block(Loc * ptr){
    ptr->X =3;//The coordinate from where the 1 falls//
    ptr->Y =0;
}
void copy1(int Shape[4][4], int copy[4][4]){
    int i, j;
    for(i=0;i<4;i++){
        for(j=0; j<4;j++){
            Shape[i][j] = copy[i][j];
        }
    }
}
void makeshape(int Shape[4][4]){
    int shape[5][4][4] = {
            {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}},{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},{{0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0}},{{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},{{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},};
   srand(time(0));
   int i=rand()%5;
   HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
    switch(i) {
        case 0:
        	SetConsoleTextAttribute(hand, 10);
            copy1(Shape, shape[0]);
            break;
        case 1:
        	SetConsoleTextAttribute(hand, 9);
            copy1(Shape, shape[1]);
            break;
        case 2:
        	SetConsoleTextAttribute(hand, 8);
            copy1(Shape, shape[2]);
            break;
        case 3:
        	SetConsoleTextAttribute(hand, 7);
            copy1(Shape, shape[3]);
            break;
        case 4:
        	SetConsoleTextAttribute(hand, 6);
            copy1(Shape, shape[4]);
            break;
        default :
            break;
    }
}

int shapeleft(int Shape[4][4]){
    int h, w, y=3;
    for(w=0; w<4;w++){
        for(h=0; h<4;h++){
            if(Shape[h][w] == 1){
                if(y > w)
                    y = w;
            }
        }
    }
    return y;
}

void shapes(Gamemap map[HEIGHT][WIDTH],int shape[4][4], Loc ptr){
    int h, w;
    for(h=0; h<4;h++){
        for(w=0; w<4;w++){
            if(shape[h][w] ==1){
                map[ptr.Y+ h][ptr.X +w]=1;
            }
        }
    }
}
void removeShape(Gamemap map[HEIGHT][WIDTH], int Shape[4][4], Loc * ptr){
    int h, w;
    for(h=0; h<4;h++){
        for(w=0; w<4;w++){
            if(Shape[h][w] ==1)
                map[ptr->Y + h][ptr->X + w]=0;
        }
    }
}

int shaperight(int Shape[4][4]){
    int h, w, x=0;
    for(w=3; w>=0;w--){
        for(h=3; h>=0;h--){
            if(Shape[h][w] == 1){
                if(x < w)
                    x = w;
            }
        }
    }
    return x+1;
}
int shapedown(int Shape[4][4]){
    int h, w, x=0;
    for(w=3; w>=0;w--){
        for(h=3; h>=0;h--){
            if(Shape[h][w] == 1){
                if(x < h)
                    x =h;
            }
        }
    }
    return x+1;
}
int downward(int Shape[4][4], int w){
    int h, x=-1;
    for(h=3; h>=0;h--){
        if(Shape[h][w] == 1){
            if(x < h)
                x =h;
        }
    }
    return x;
}
int leftward(int Shape[4][4], int h){
    int w, y= 5;
    for(w=0; w<4;w++){
        if(Shape[h][w] == 1){
            if(y > w)
                y = w;
        }
    }
    return y;
	}
	void goLeft(Gamemap map[HEIGHT][WIDTH],int Shape[4][4], Loc *ptr){
    int y = shapeleft(Shape);
    int corners[4] ={0};
    int i;
    for(i=0; i<4;i++){
        corners[i] = leftward(Shape, i);
}
    if((ptr->X) + y > 0){
        if(!((corners[0] != 5 && map[ptr->Y][ptr->X + corners[0] -1] != 0)||(corners[1] != 5 && map[ptr->Y +1][ptr->X + corners[1] -1] != 0)||(corners[2] != 5 && map[ptr->Y +2][ptr->X + corners[2] -1] != 0)||(corners[3] != 5 && map[ptr->Y +3][ptr->X + corners[3] -1] != 0))){
            removeShape(map, Shape,ptr);
            (ptr->X)--;
        }
    }
}
int rightward(int Shape[4][4], int h){
    int w, x= -1;
    for(w=0; w<4;w++){
        if(Shape[h][w] == 1){
            if(x < w)
                x = w;
        }
    }
    return x;
}

void goRight(Gamemap map[HEIGHT][WIDTH],int Shape[4][4], Loc *ptr){
    int x = shaperight(Shape);
    int corners[4] ={0};
    int i;
    for(i=0; i<4;i++){
        corners[i] = leftward(Shape, i);

    }
    if((ptr->X) + x < WIDTH){
        if(!((corners[0] != 5 && map[ptr->Y][ptr->X + corners[0] +1] != 0)||(corners[1] != 5 && map[ptr->Y +1][ptr->X + corners[1] +1] != 0)||(corners[2] != 5 && map[ptr->Y +2][ptr->X + corners[2] +1] != 0) ||(corners[3] != 5 && map[ptr->Y +3][ptr->X + corners[3] +1] != 0))){
             removeShape(map, Shape,ptr);
            (ptr->X)++;
        }
    }
}
int goDown(Gamemap map[HEIGHT][WIDTH], int Shape[4][4], Loc *ptr){
    int x = shapedown(Shape);
    int touchline[4] = {0};
    int i;
    for(i=0; i<4; i++){
        touchline[i] = downward(Shape, i);
    }
    if(ptr->Y + x  == HEIGHT||(touchline[1] != -1 && map[ptr->Y + touchline[1] +1][ptr->X + 1] != 0)||(touchline[0] != -1 && map[ptr->Y + touchline[0] +1][ptr->X + 0] != 0)||(touchline[3] != -1 && map[ptr->Y + touchline[3] +1][ptr->X + 3] != 0)||(touchline[2] != -1 && map[ptr->Y + touchline[2] +1][ptr->X + 2] != 0)){
    	return 1;
    }
   if(ptr->Y + x < HEIGHT){
        removeShape(map, Shape, ptr);
        Sleep(1000/8);
        (ptr->Y)++;
    }
     return 0;
}

void check(Gamemap map[HEIGHT][WIDTH], Loc ptr, int * score){
    int h, w, count =0;
    for(h=HEIGHT ; h >= 0; h--){
        count =0;
        for(w=0; w<WIDTH  ;w++){
            if(map[h][w] == 0){
                break;
            }else{
                count++;
            }
        }
        if(count== WIDTH){
            (*score) += 10;
         while(h > 0){            // max h= 0(borders) h=1 (inner area)
        for(w=0; w<WIDTH;w++){
            map[h][w] = map[h-1][w];
        }
        h--;
    }
        }
    }
}
int GameOver(Gamemap map[HEIGHT][WIDTH],int score, int bestScore){
    FILE * fptr1;
    int w=0;
    for(w=0; w<WIDTH; w++){
        if(map[0][w] == 1){
            HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hand, 14);
            gotoxy(13, 8);
            printf("GAME OVER");
            gotoxy(14, 9);
            printf("Your Score : %4d\n", score);
            gotoxy(1, 23);
            if(score >= bestScore){
                fptr1= fopen("score.txt", "w");
                fprintf(fptr1, "%d", score);
                fclose(fptr1);
            }
            system("pause");
            return score;
        }
    }
   return 0;
}
int Start(Gamemap map[HEIGHT][WIDTH]){
    int press;
    int below = 0,score =0, bestScore =0, Shape[4][4] ={0}, copy[4][4] = {0};
    Loc ptr={2,2};
    FILE * fptr;
    if((fptr = fopen("score.txt", "r")) == NULL){
        FILE * fptr;
        fptr= fopen("score.txt", "w");
        fprintf(fptr, "%d", score);
        fclose(fptr);
    }
    fscanf(fptr, "%d", &bestScore);
    wall(map);
    internalmap(map);
    maps(map);
    coordinates_of_block(&ptr);
    makeshape(Shape);
    while(1){
       if(below == 1){//true
            if(GameOver(map,score, bestScore)) 
			return 0;
            check(map, ptr, &score);
            coordinates_of_block(&ptr);
            copy1(Shape, copy);
            makeshape(copy);
            below = 0;//true
        }
        calculation(bestScore,score);
        shapes(map,Shape, ptr);
        maps(map);
        below = goDown(map, Shape, &ptr);
        if(below == 1) continue;
        press = keyinput();
        if(press == 'e' ) break;
        if(press == 'p' ){
	        system("pause"); 
			system("cls");
	        maps(map); 
			wall(map);
        }
        if(press==224 || press ==0){
            press = getch();
            if(press == 75){
                goLeft(map, Shape, &ptr);
            }else if(press== 77){
                goRight(map, Shape, &ptr);
            }
        }
    }
    return 0;
}
int main() {
    char map[HEIGHT][WIDTH] ={0};   //map
    int press;
    while(1){
        press = mainmenu();
        if(press == 'e' ) break;
        system("cls");
        Start(map);
    }
    return 0;
}
