#pragma once
#include "config.h"
#include <string.h>
#include "console.h"
#include "graphics.h"
#include "init.h"
#include "config.h"
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>


static char *_map = map;
int RandomInt(int min, int max);
COORD GetOnScreenPos(COORD p);
void PlacePlayer();
void AddCaveSegment(COORD punkt);
void InitializeLevel(int level);
void Move();
void TryMove(char direction);


