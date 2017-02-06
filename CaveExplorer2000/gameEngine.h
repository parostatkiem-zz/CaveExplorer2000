#pragma once
#include "config.h"



int RandomInt(int min, int max);
COORD GetOnScreenPos(COORD p);
int CalculateDistance(COORD a, COORD b);
void PlacePlayer();
void MoveEnemies();
void AddCaveSegment(COORD punkt);
void InitializeLevel(int level);
void Move();
void TryMove(char direction);
void ShowMenu();
void Atack();
void Death();
void RegenerateLife();
void PlacePortal();
void CheckPortal();