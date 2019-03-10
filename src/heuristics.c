#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/heuristics.h"
#include "../include/map.h"

int manhattanDistance(int nodeX, int nodeY, int goalX, int goalY) {
  int dx, dy;

  dx = abs(nodeX - goalX);
  dy = abs(nodeY - goalY);

  return dx*dx + dy*dy;
}

int breakingTies(int nodeX, int nodeY, int goalX, int goalY) {
  int dx1, dy1, dx2, dy2, cross;

  dx1 = nodeX - goalX;
  dy1 = nodeY - goalY;
  dx2 = 0 - goalX;
  dy2 = 0 - goalY;

  cross = abs(dx1*dy2 - dx2*dy1);

  return cross*0.001;
}

// Manhattan pela lateral
int h1(map_p map) {
  int i, j;

  i = j = 0;
  for(j=0; j<map->ncolumns; j++) {
    if((j+1 < map->ncolumns) && (map->map[0][j+1] != map->map[0][j])) {
      return manhattanDistance(i, j, map->ncolumns, map->nlines);
    }
  }

  for(i=0; i<map->nlines; i++) {
    if((i+1 < map->nlines) && (map->map[i+1][map->ncolumns-1] != map->map[i][map->ncolumns-1])) {
      return manhattanDistance(i, j, map->ncolumns, map->nlines);
    }
  }

  return 0;
}

// Caminho pela lateral
int h2(map_p map) {
  int i, j, swapL, swapC, path1;

  swapC = swapL = 0;

  for(j=0; j<map->ncolumns; j++) {
    if((j+1 < map->ncolumns) && (map->map[0][j+1] != map->map[0][j])) {
      swapC++;
    }
  }

  for(i=0; i<map->nlines; i++) {
    if((i+1 < map->nlines) && (map->map[i+1][map->ncolumns-1] != map->map[i][map->ncolumns-1])) {
      swapL++;
    }
  }

  path1 = swapC + swapL;

  return path1;
}

// Trocas de cores
int h3(map_p map) {
  int i, j, swapL, swapC, path2;
  
  swapC = swapL = 0;

  for(i=0; i<map->nlines; i++) {
    for(j=0; j<map->ncolumns; j++) {
      if((j+1 < map->ncolumns) && (map->map[i][j+1] != map->map[i][j])) {
        swapC++;
      }
    }
    if((i+1 < map->nlines) && (map->map[i+1][j] != map->map[i][j])) {
      swapL++;
    }
  }

  path2 = swapL + swapC;

  return path2;
}

// Tamanho do mapa a ser colorido
int h4(map_p map) {
  int i, j, count = 0;

  for(i=0; i<map->nlines-1; i++) {
    for(j=0; j<map->ncolumns-1; j++) {
      if(map->map[i][j] != map->map[0][0]) {
        count++;
      }
    }
  }

  return count;
}

// Caminho pela diagonal
int h5(map_p map) {
  int i, j, path = 0;

  for(i=0; i<map->nlines; i++) {
    for(j=0; j<map->ncolumns; j++) {
      if((i==j)&&(j+1 < map->ncolumns) && (i+1 < map->nlines) && (map->map[i+1][j+1] != map->map[i][j])) {
        path++;
      }
    }
  }

  return path;
}

// Caminho por baixo
int h6(map_p map) {
  int i, j, swapL, swapC, path1;

  swapC = swapL = 0;
  for(j=map->ncolumns-1; j>=0; j--) {
    if((j-1 >= 0) && (map->map[map->nlines-1][j-1] != map->map[map->nlines-1][j])) {
      swapC++;
    }
  }
   
  for(i=map->nlines-1; i>=0; i--) {
    if((i-1 >= 0) && (map->map[i-1][0] != map->map[i][0])) {
      swapL++;
    }
  }

  path1 = swapC + swapL;

  return path1;
}

// Caminho pela diagonal
int h7(map_p map) {
  int i, j;

  for(i=0; i<map->nlines; i++) {
    for(j=0; j<map->ncolumns; j++) {
      if((i==j)&&(j+1 < map->ncolumns) && (i+1 < map->nlines) && (map->map[i+1][j+1] != map->map[i][j])) {
        return manhattanDistance(i, j, map->ncolumns, map->nlines);
      }
    }
  }
  
  return 0;
}
