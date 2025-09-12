#ifndef BOOLEAN_H
#define BOOLEAN_H

bool ActivateAimbot = true;
bool ActivateEsp = true;

bool StartMenu = false;
bool AimKill = false;
//bool Autotroca = false; bool sID = false; int tS = 3000;
bool TelePro = false;
int FlyCarroConfig = 1; 
int SpeedFlyCarro = 0;
bool WallHack = false; 
MemoryPatch WallCar; 
MemoryPatch WallCar2;
bool TeleCar = false;
bool Skill = false; 
MemoryPatch Damage;
float Flycar = 0;
float Undercar = 0;
bool HackBoard = false;
bool HackBoard2 = false;
bool AimMove = false; 
MemoryPatch AimMovement;
MemoryPatch ResetGuest;
bool MedikitCorriendo = false; 
MemoryPatch Medikit; 
MemoryPatch Medikit2;
bool HackFly = false;
int FlyHack = 0;
int Flyspeed = 0;
bool TelePro2 = false;
bool GhostHack = false;
int Jump = 0;
int Speed = 0;
int FlyModder = 0;
float Aim_Fov = 0; 
bool FOV = false;
int AimSmooth = 0;

bool AimFire = false; 
bool AimScope = false;
bool CheckVisible = false;
bool ESPFire2 = false;
bool EspAlerta = false;
bool EspFire = false;
bool EspFire2Azul = false;
bool EspGrenade = false;

bool KMHack1 = false,
KMHack2 = false,
KMHack3 = false,
KMHack4 = false,
KMHack5 = false,
KMHack6 = false,
KMHack7 = false,
KMHack8 = false,
KMHack9 = false,
KMHack10 = false,
KMHack11 = false,
KMHack12 = false,
KMHack13 = false,
KMHack14 = false,
KMHack15 = false,
KMHack16 = false;

MemoryPatch FreeWater;
MemoryPatch DoubleGun;
MemoryPatch FastReload;
MemoryPatch NoScope;
MemoryPatch SwapGun;
MemoryPatch GetVBadge;
MemoryPatch AutoJump;
MemoryPatch DriveSpeed;
MemoryPatch DiamondHack;
MemoryPatch GoldHack;
MemoryPatch WhiteBody1;
MemoryPatch WhiteBody2;
MemoryPatch NightMode;

MemoryPatch Blackbody;
MemoryPatch Blackhouse;

MemoryPatch Ultimateammo;
MemoryPatch Demo5;

using namespace std::chrono;

bool autotroca = false;
bool sID = false;
int tS = 0;
steady_clock::time_point lastSwapTime;

Vector3 ContolCarro;
float TFPosX = 0;
float TFPosY = 0;
float TFPosZ = 0;
float FupdmdCarroX = 0;
float FupdmdCarroY = 0;
float FupdmdCarroZ = 0;
float EspAtas = 0;
float EspBawah = 0;
float EspKanan = 0;
float EspKiri = 0;
std::string indetifiq;



#endif
