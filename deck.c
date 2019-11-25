#include "deck.h"

Deck* createDeck () {
  return NULL;
}

Point getFront (Deck *d) {
    if(d == NULL)
      exit(1);
    return d->p;
}

Point getRear (Deck *d) {
  if(d == NULL)
    exit(1);
    Deck *aux = d;
    while(aux->next != NULL)
      aux = aux->next;


    return aux->p;
}

Deck* insertFront (Deck *d, Point p, char field[][SIZE]) {
   /*Terminar ...*/
   Deck *novo = (Deck *)malloc(sizeof(Deck));
   field[p.x][p.y] = '*';
   novo->p = p;
   novo->prev = NULL;
   novo->next = d;
   if(d != NULL)
    d->prev = novo;
   return novo;
}

Deck* insertRear (Deck *d, Point p, char field[][SIZE]) {
  Deck *novo = (Deck *)malloc(sizeof(Deck));
  novo->p = p;
  novo->prev = NULL;
  novo->next = NULL;
  field[p.x][p.y] = '*';  /*Ponto inserido faz parte do corpo da Snake!*/
  if(d!= NULL){
    Deck *aux = d;
    while(aux->next != NULL){
     aux = aux->next;
   }
   novo->prev = aux;
   aux->next = novo;

   return d;
   /*Pronto ...*/
}
}

Deck* deleteFront (Deck *d, char field[][SIZE]) {
  if(d != NULL){
    Deck *aux = d;
    if(aux->next != NULL){
      aux->next->prev = NULL;
    }
    d = d->next;
   field[aux->p.x][aux->p.y] = ' ';
   free (aux);
   return d;
 }
 else
   return NULL;
}

Deck* deleteRear (Deck *d, char field[][SIZE]) {
  if(d != NULL){
    Deck *aux = d;
    while(aux->next != NULL){
    aux = aux->next;
    }
   field[aux->p.x][aux->p.y] = ' ';  /*Ponto inserido faz parte do corpo da Snake!*/
   aux->prev->next = NULL;
   free(aux);
   return d;
 }
 else
  return NULL;

}

Deck *setApple (Deck *apple, Point p, char field[][SIZE]){
  Deck *novo = (Deck *)malloc(sizeof(Deck));
  field[p.x][p.y] = '0';
  novo->p = p;
  novo->prev = NULL;
  novo->next = NULL;
  return novo;
}

Point getApple(Deck *apple){
  if(apple == NULL)
    exit(1);

  return apple->p;

}
int destruct (Deck *d, Point deck, char field[][SIZE]){
      Deck *novo = (Deck *)malloc(sizeof(Deck));
      novo->p = deck;
      novo->prev = NULL;
      novo->next = NULL;
      int au = 1;
      if(d!= NULL){
        Deck *aux = d;
        while(aux->next != NULL){
          if(deck.x == aux->p.x && deck.y == aux->p.y){
            au = 0;
          }
         aux = aux->next;
       }
       return au;
     }
}
/*
Deck *destr = d;
while(destr->next != NULL){
  if(d->p.x == destr->p.x && d->p.y == destr->p.y){
    exit(1);
    field[d->p.x][d->p.y] = 'X';
  }
  destr = destr->next;
}
return d;
*/
