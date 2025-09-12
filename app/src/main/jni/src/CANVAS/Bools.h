#ifndef BOOLS_H
#define BOOLS_H
#include <jni.h>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/mman.h>
#include <android/log.h>
#include "StructsCommon.h":

bool isPlayerLine = false;
bool isPlayerBox = false;
bool isPlayerName = false;
bool isPlayerIdent = false;
bool isPlayerDist = false;
bool isPlayerHealth = false;
bool isVehicleLine = false;
bool EspCaidos = true;
bool crosshair = false;
bool espFromCross = false;



bool EspName = true;
bool EspLine2 = false;
bool EspFire2 = false;
bool EspBox = true;
bool EspMoco = true;
bool EspLine = true;
float MocoSize = 42;

int Tamano = 19.0f;
Color CaidoColor = Color::Red();
Color EspColor = Color::White();
Color EspColor2 = Color(0, 0, 255);

int linex = 0;
int liney = 0;
#endif
