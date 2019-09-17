#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "deck.h"

int kbhit(void) {
  struct termios oldt, newt;
  int ch;
  int oldf;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  if(ch != EOF) {
    ungetc(ch, stdin);
    return 1;
  }
  return 0;
}

void initialize_field (char field[SIZE][SIZE]) {
   int i, j;
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         field[i][j] = ' ';
      }
   }
}

void print_field (char field[SIZE][SIZE]) {
   int i, j;
   printf("  ");
   for (i = 0; i < SIZE; i++) {
      printf(" #");
   }
   printf("\n");
   for (i = 0; i < SIZE; i++) {
      printf(" # ");
      for (j = 0; j < SIZE; j++) {
         printf("%c ", field[i][j]);
      }
      printf("#\n");
   }
   printf("  ");
   for (i = 0; i < SIZE; i++) {
      printf(" #");
   }
   printf("\n");
}

int finish (Deck *d) {
   /*Terminar!*/
   Point p = getRear (d);
   if (p.x < 1 || p.x > SIZE-2 || p.y < 1 || p.y > SIZE-1)
      return 1;
   else
      return 0;
}

int main () {

   char field[SIZE][SIZE];
   initialize_field (field);
   int center = SIZE/2;
   int snake_size = 3;
   Deck *d = createDeck ();
   Deck *apple = createDeck();
   srand(time(NULL));
   /*Inserindo a Snake no centro do campo: */
   int i;
   for (i = center-snake_size/2; i <= center+snake_size/2; i++) {
      d = insertFront (d, (Point){center, i}, field);
   }
   /*Setando a maçã */
   apple = setApple(d, (Point){rand()%SIZE,rand()%SIZE}, field);
   /*AQUI FUNCIONOU*/
   char pressionou_prv = ' ';
   char pressionou_act = 'a';
   int reverse = 0; /*variável para inverter cabeça com cauda (e vice-versa)*/
   while (!finish(d)) {
     while((!kbhit()) && (!finish(d))) {
       if (reverse) {
           Point p = getFront (d);
           if (pressionou_act ==  'w') { d = insertFront (d, (Point){p.x-1, p.y}, field); }
           else if (pressionou_act ==  's') { d = insertFront (d, (Point){p.x+1, p.y}, field); }
           else if (pressionou_act ==  'a') { d = insertFront (d, (Point){p.x, p.y-1}, field); }
           else { d = insertFront (d, (Point){p.x, p.y+1}, field); }
           d = deleteRear (d, field);
        }
        else {
           Point p = getRear (d);
           if (pressionou_act ==  'w') { d = insertRear (d, (Point){p.x-1, p.y}, field); }
           else if (pressionou_act ==  's') { d = insertRear (d, (Point){p.x+1, p.y}, field); }
           else if (pressionou_act ==  'a') { d = insertRear (d, (Point){p.x, p.y-1}, field); }
           else { d = insertRear (d, (Point){p.x, p.y+1}, field); }
           d = deleteFront (d, field);
        }
        Point head = getFront(d);
        Point p_apple = getApple(apple);
        Point cauda = getRear(d);
        if(p_apple.x == head.x && p_apple.y == head.y){
          apple = setApple(d, (Point){rand()%SIZE,rand()%SIZE}, field);
          d = insertRear(d, (Point){cauda.x, cauda.y}, field);
        }
        // IMPLEMENTAÇÃO DA DESTRUIÇÃO //
        //d = destruct(d, field);
        print_field (field);
        //usleep(250000);
        usleep(100000);
        system("clear");
     }
     if (!finish(d)) {

        /*Cada vez que uma tecla é pressionada o controle executa esse trecho: */
        pressionou_prv = pressionou_act;
        pressionou_act = getchar();
        if ((pressionou_act ==  's') && (pressionou_prv ==  'w')) { reverse = !reverse; }
        else if ((pressionou_act ==  'w') && (pressionou_prv ==  's')) { reverse = !reverse; }
        else if ((pressionou_act ==  'a') && (pressionou_prv ==  'd')) { reverse = !reverse; }
        else if ((pressionou_act ==  'd') && (pressionou_prv ==  'a')) { reverse = !reverse; }
     }
   }
   return 0;
}
