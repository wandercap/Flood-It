#ifndef _HEURISTICS_H_
#define _HEURISTICS_H_

#include "map.h"

int manhattanDistance(int nodeX, int nodeY, int goalX, int goalY);
int breakingTies(int nodeX, int nodeY, int goalX, int goalY);
int h1(map_p map);
int h2(map_p map);
int h3(map_p map);
int h4(map_p map);
int h5(map_p map);
int h6(map_p map);
int h7(map_p map);

#endif