#ifndef __MAP_H__
#define __MAP_H__

#include <stdbool.h>

typedef struct map {
  int nlines;
  int ncolumns;
  int ncolors;
  int lmax;
  int cmax;
  int color;
  int **map;
} map_t, *map_p;

typedef struct border {
  int line;
  int column;
  int color;
  struct border *next;
} border_t, *border_p;

typedef struct list_borders {
  border_t *border;
  int nBorders;
} list_borders_t, *list_borders_p;

void readMap(char *file, map_p map);
void newMap(map_p map, int seed);
void copyMap(map_p newMap, map_p map);
void loadMap(map_p map);
void showMap(map_p map);
void showcolorMap(map_p map);
void paint(map_p map, int l, int c, int back, int color);
void mapPaint(map_p map, int color);
int oneColor(map_p map, int *pColor);
int isColor(map_p map);
list_borders_p initBorders();
void addBorder(list_borders_p borders, int line, int column, int color);
void getBorders(map_p map, list_borders_p borders);
void fronteira(map_p map, list_borders_p borders, int l, int c, int fundo);
void printBorders(list_borders_p borders);

#endif
