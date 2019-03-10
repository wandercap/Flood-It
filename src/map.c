#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "../include/map.h"
#include "../include/util.h"
void fronteira(map_p map, list_borders_p borders, int l, int c, int fundo);

void readMap(char *file, map_p map) {
  char buffer[100];
  int i, j;
  FILE *f;

  f = fopen(file, "r");
  if(!f)
    err_exit("Unable to read the file!");
  
  fgets(buffer, sizeof(buffer), f);
  sscanf(buffer, "%d %d %d", &map->nlines, &map->ncolumns, &map->ncolors);

  map->map = (int**) malloc(map->nlines * sizeof(int*));
  if(!map->map)
    err_exit("Unable to create a new Map Line!");

  for(i = 0; i < map->nlines; i++) {
    map->map[i] = (int*) malloc(map->ncolumns * sizeof(int));
    if(!map->map[i])
      err_exit("Unable to create a new Map Column!");

    for(j = 0; j < map->ncolumns; j++) {
      if (!fscanf(f, "%d", &map->map[i][j]))
        break;
    }
  }

  fclose(f);
}

void newMap(map_p map, int seed) {
  if(!map)
    err_exit("The Map is empty!");

  int i, j;

  if(seed < 0)
    srand(time(NULL));
  else
    srand(seed);

  map->map = (int**) malloc(map->nlines * sizeof(int*));
  if(!map->map)
    err_exit("Unable to create a new Map Line!");

  for(i = 0; i < map->nlines; i++) {
    map->map[i] = (int*) malloc(map->ncolumns * sizeof(int));
    if(!map->map[i])
      err_exit("Unable to create a new Map Column!");

    for(j = 0; j < map->ncolumns; j++)
      map->map[i][j] = 1 + rand() % map->ncolors;
  }
}

int isColor(map_p map) {
  return map->map[0][0];
}

int oneColor(map_p map, int *pColor) {
  int i, j;

  for(i=0; i<map->nlines; i++) {
    for(j=0; j<map->ncolumns; j++) {
      if(map->map[i][j] != map->map[0][0]) {
        *pColor = map->map[i][j];
        return 0;
      }
    }
  }
  return 1;
}

void copyMap(map_p newMap, map_p map) {
  if(!map)
    err_exit("The Map is empty!");

  int i, j;

  newMap->nlines = map->nlines;
  newMap->ncolumns = map->ncolumns;
  newMap->ncolors = map->ncolors;

  newMap->map = (int**) malloc(map->nlines * sizeof(int*));
  if(!map->map)
    err_exit("Unable to create a new Map Line!");
  
  for(i = 0; i < map->nlines; i++) {
    newMap->map[i] = (int*) malloc(map->ncolumns * sizeof(int));
    if(!map->map[i])
      err_exit("Unable to create a new Map Column!");

    for(j = 0; j < map->ncolumns; j++)
      newMap->map[i][j] = map->map[i][j];
  }
}

void LoadMap(map_p map) {
  if(!map)
    err_exit("The Map is empty!");

  int i, j;

  scanf("%d", &(map->nlines));
  scanf("%d", &(map->ncolumns));
  scanf("%d", &(map->ncolors));
  map->map = (int**) malloc(map->nlines * sizeof(int*));
  if(!map->map)
    err_exit("Unable to create a new Map Line!");

  for(i = 0; i < map->nlines; i++) {
    map->map[i] = (int*) malloc(map->ncolumns * sizeof(int));
    if(!map->map[i])
      err_exit("Unable to create a new Map Column!");

    for(j = 0; j < map->ncolumns; j++)
      scanf("%d", &(map->map[i][j]));
  }
}

void showMap(map_p map) {
  if(!map)
    err_exit("The Map is empty!");

  int i, j;

  printf("%d %d %d\n", map->nlines, map->ncolumns, map->ncolors);
  for(i = 0; i < map->nlines; i++) {
    for(j = 0; j < map->ncolumns; j++)
      if(map->ncolors > 10)
	printf("%02d ", map->map[i][j]);
      else
	printf("%d ", map->map[i][j]);
    printf("\n");
  }
}

void showcolorMap(map_p map) {
  if(!map)
    err_exit("The Map is empty!");

  int i, j;
  char* color_ansi[] = { "\x1b[0m",
		       "\x1b[31m", "\x1b[32m", "\x1b[33m",
		       "\x1b[34m", "\x1b[35m", "\x1b[36m",
		       "\x1b[37m", "\x1b[30;1m", "\x1b[31;1m",
		       "\x1b[32;1m", "\x1b[33;1m", "\x1b[34;1m",
		       "\x1b[35;1m", "\x1b[36;1m", "\x1b[37;1m" };

  if(map->ncolors > 15) {
    showMap(map);
    return;
  }
  printf("%d %d %d\n", map->nlines, map->ncolumns, map->ncolors);
  for(i = 0; i < map->nlines; i++) {
    for(j = 0; j < map->ncolumns; j++)
      if(map->ncolors > 10)
	printf("%s%02d%s ", color_ansi[map->map[i][j]], map->map[i][j], color_ansi[0]);
      else
	printf("%s%d%s ", color_ansi[map->map[i][j]], map->map[i][j], color_ansi[0]);
    printf("\n");
  }
  printf("\n");
}

void paint(map_p map, int l, int c, int fundo, int color) {
  if(!map)
    err_exit("The Map is empty!");

  map->map[l][c] = color;
  if(l < map->nlines - 1 && map->map[l+1][c] == fundo)
    paint(map, l+1, c, fundo, color);
  if(c < map->ncolumns - 1 && map->map[l][c+1] == fundo)
    paint(map, l, c+1, fundo, color);
  if(l > 0 && map->map[l-1][c] == fundo)
    paint(map, l-1, c, fundo, color);
  if(c > 0 && map->map[l][c-1] == fundo)
    paint(map, l, c-1, fundo, color);
}

void mapPaint(map_p map, int color) {
  if(!map)
    err_exit("The Map is empty!");
    
  map->color = color;

  if(color == map->map[0][0])
    return;
  paint(map, 0, 0, map->map[0][0], color);
}

list_borders_p initBorders() {
  list_borders_p borders = (list_borders_p)malloc(sizeof(list_borders_t));

  borders->nBorders = 0;
  borders->border = NULL;

  return borders;
}

void addBorder(list_borders_p borders, int line, int column, int color) {
  border_p aux = borders->border;

  if(!aux){
      borders->border = (border_p)malloc(sizeof(border_t));
      borders->border->line = line;
      borders->border->column = column;
      borders->border->color = color;
      borders->border->next = NULL;
  }else{
      while(aux->next!=NULL) {
        aux = aux->next;
      }
      aux->next = (border_p)malloc(sizeof(border_t));
      aux->next->line = line;
      aux->next->column = column;
      aux->next->color = color;
      aux->next->next = NULL;
  }
  borders->nBorders++;

}

void getBorders(map_p map, list_borders_p borders) {
  int i, j;

  addBorder(borders, 0, 0, map->map[0][0]);

   for(i=0; i<map->nlines; i++) {
     for(j=0; j<map->ncolumns; j++) {
       if(map->map[i][j] == map->map[0][0]) {
        addBorder(borders, i, j, map->color);
      }
     }
  }
}

void fronteira(map_p map, list_borders_p borders, int l, int c, int fundo) {
  if(map->map[l][c] == fundo) {
    map->map[l][c] *= -1;
    if(l < map->nlines - 1)
      fronteira(map, borders, l+1, c, fundo);
    if(c < map->ncolumns - 1)
      fronteira(map,borders, l, c+1, fundo);
    if(l > 0)
      fronteira(map, borders, l-1, c, fundo);
    if(c > 0)
      fronteira(map, borders, l, c-1, fundo);
  }
  else if((map->map[l][c] != -fundo)&&(map->map[l][c]>0)) {
    addBorder(borders, l, c, map->map[l][c]);
    map->map[l][c] = 0;
  }
}

void printBorders(list_borders_p borders) {
  border_p aux = borders->border;
  printf("Bordas: %d\n", borders->nBorders);
  while(aux!=NULL) {
    printf("(%d, %d)\n", aux->line, aux->column);
    aux = aux->next;
  }
  printf("\n");
}
