#include <pthread.h>
#include <jni.h>
#include <stdio.h>
#include <wchar.h>
#include <src/Substrate/SubstrateHook.h>
#include "src/Unity/Quaternion.hpp"
#include "src/Unity/Vector3.hpp"
#include "src/Unity/Vector3.hpp"
#include "src/Unity/Unity.h"
#include "src/Unity/Hook.h"
#include "src/Unity/Global.h"
#include "src/CANVAS/Bools.h"
#include "src/CANVAS/ESP.h"
#include "KittyMemory/MemoryPatch.h"
#include "Includes/Logger.h"
#include "Boolean.h"
#include "Includes/obfuscate.h"
//#include "Includes/Macros.h"
#define targetLibName OBFUSCATE("libFileA.so")

#define OBFUSCATE_BNM(str) str 

# define HOOK_LIB(offset, ptr, orig) MSHookFunction((void *)getRealOffset(offset), (void *)ptr, (void **)&orig)

using namespace std;

ESP espOverlay;
Vector3 InimigoLocation = Vector3(0, 0, 0);

extern "C" {
JNIEXPORT jboolean JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_EnableSounds(
JNIEnv *env,
jobject activityObject) {
return true;
}

JNIEXPORT jstring JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_ForegroundGravity(JNIEnv *env,jobject activityObject) {
jstring str = env->NewStringUTF((OBFUSCATE("DEXX-TER")));
return str;
}

JNIEXPORT jstring JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Gravity(JNIEnv *env,jobject activityObject) {
jstring str = env->NewStringUTF((OBFUSCATE("Premium ImGui Style")));
return str;
}

JNIEXPORT jobjectArray JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_getFeatureList(JNIEnv *env, jobject activityObject) {
jobjectArray ret;

const char *features[] = {

OBFUSCATE("CT_ MENU AIM"),//0
OBFUSCATE("Toggle_ AIM BOT"),//1
OBFUSCATE("Toggle55_ AIMKILL"),//2
OBFUSCATE("SB_ AIM FOV%_0_360"),//3
OBFUSCATE("SB_ RUN SPEED%_0_5"),//4
OBFUSCATE("Toggle_ AIM FIRE"),//5
OBFUSCATE("Toggle_ AIM SCOPE"),//6
OBFUSCATE("Toggle_ AIM VISBEL"),//7
OBFUSCATE("CT_ MENU ESP"),//8
OBFUSCATE("Toggle_ ESP GRENDA"),//9
OBFUSCATE("Toggle_ ESP FIRE BLUE"),//10
OBFUSCATE("Toggle_ ESP INFO"),//11
OBFUSCATE("CT_ MENU FLY"),//12
OBFUSCATE("Toggle_ FLY HACK"),//13
OBFUSCATE("SB_ FLY HEIGHT_0_175"),//14
OBFUSCATE("SB_ FLY SPEED_0_10000"),//15
OBFUSCATE("Toggle_ TELEKILL (FLY)"),//16
OBFUSCATE("Toggle_ TELEPORT PRO"),//17
OBFUSCATE("Toggle_ Ghost Hack V2"),//18
OBFUSCATE("CT_ MENU OTHER"),//19
OBFUSCATE("Toggle_ AUTO CHANGE (GUN)"),//20
OBFUSCATE("Toggle_ AIM WITH MOVEMENT"),//21
OBFUSCATE("Toggle_ MEDKIT RUN"),//22
OBFUSCATE("Toggle2_ BLACK BODY"),//23
OBFUSCATE("Toggle_ DIMOND HACK"),//24
OBFUSCATE("Toggle_ GOLD HACK"),//25
OBFUSCATE("Toggle2_ NO SCOPE"),//26
OBFUSCATE("Toggle2_ ULTIMATE AMMO"),//27
OBFUSCATE("Toggle_ V (BADGE)"),//28
OBFUSCATE("Toggle_ REMOVE GUEST"),//29

OBFUSCATE("Toggle_ ESP LINE TRY"),//28
OBFUSCATE("Toggle_ ESP BOX TRY"),//29

};

int Total_Feature = (sizeof features / sizeof features[0]); //Now you dont have to manually update the number everytime;
ret = (jobjectArray) env->NewObjectArray(Total_Feature, env->FindClass("java/lang/String"),env->NewStringUTF(""));
int i;
for (i = 0; i < Total_Feature; i++)
env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));
return (ret);
}

JNIEXPORT void JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Changes(JNIEnv *env, jobject activityObject, jint feature, jint value) {
    
switch (feature) {

case 0:
break;
    
case 1:
StartMenu = !StartMenu;
break;

case 2:
//AimKill = !AimKill;
break;

case 3:
Aim_Fov = value;
break;

case 4:
Speed = (int)value;
break;

case 5:
AimFire = !AimFire;
break;

case 6:
AimScope = !AimScope;
break;

case 7:
CheckVisible = !CheckVisible;
break;

case 8:
break;

case 9:
EspGrenade = !EspGrenade;
break;

case 10:
ESPFire2 = !ESPFire2;
break;

case 11:
EspAlerta = !EspAlerta;
break;

case 12:
break;

case 13:
HackFly = !HackFly;
break;

case 14:
FlyHack = value;
break;

case 15:
Flyspeed = value;
break;

case 16:
TelePro = !TelePro;
break;

case 17:
TelePro2 = !TelePro2;
break;

case 18:
GhostHack = !GhostHack;
break;

case 19:
break;

case 20:
autotroca = !autotroca;
break;

case 21:
AimMove = !AimMove;
if (AimMove) {
AimMovement.Modify();
} else {
AimMovement.Restore();
}
break;

case 22:
MedikitCorriendo = !MedikitCorriendo;
if (MedikitCorriendo) {
Medikit.Modify();
Medikit2.Modify();
} else {
Medikit2.Restore();
Medikit.Restore();
}
break;

case 23:
KMHack1 = !KMHack1;
if (KMHack1) {
Blackbody.Modify();
} else {
Blackbody.Restore();
}
break;

case 24:
KMHack2 = !KMHack2;
if (KMHack2) {
DiamondHack.Modify();
} else {
DiamondHack.Restore();
}
break;

case 25:
KMHack3 = !KMHack3;
if (KMHack3) {
GoldHack.Modify();
} else {
GoldHack.Restore();
}
break;

case 26:
KMHack4 = !KMHack4;
if (KMHack4) {
NoScope.Modify();
} else {
NoScope.Restore();
}
break;

case 27:
KMHack5 = !KMHack5;
if (KMHack5) {
Ultimateammo.Modify();
} else {
Ultimateammo.Restore();
}
break;

case 28:
KMHack6 = !KMHack6;
if (KMHack6) {
GetVBadge.Modify();
} else {
GetVBadge.Restore();
}
break;

case 29:
KMHack7 = !KMHack7;
if (KMHack7) {
ResetGuest.Modify();
} else {
ResetGuest.Restore();
}
break;

case 30:
KMHack7 = !KMHack7;
isPlayerLine = !isPlayerLine;
break;

case 31:
KMHack7 = !KMHack7;
isPlayerBox = !isPlayerBox;
break;

}
}
}

static void *GetLeech(void *lammer) {
    void *(*_leech)(void *lammer) = (void *(*)(void *))getRealOffset(address.GetHeadTF);
    return _leech(lammer);
}

Vector3 GetHeadPosition(void* player) {
    return get_position_Injected(GetLeech(player));
}

static void *GetHipLeech(void *lammer) {
    void *(*_leech)(void *lammer) = (void *(*)(void *))getRealOffset(address.HipTF);
    return _leech(lammer);
}

Vector3 GetHipPosition(void* player) {
    return get_position_Injected(GetHipLeech(player));
}

static void *GetToeLeech(void *lammer) {
    void *(*_leech)(void *lammer) = (void *(*)(void *))getRealOffset(address.ToeTF);
    return _leech(lammer);
}

Vector3 GetToePosition(void* player) {
    return get_position_Injected(GetToeLeech(player));
}

static void *GetLShoulderLeech(void *lammer) {
    void *(*_leech)(void *lammer) = (void *(*)(void *))getRealOffset(address.LShoulder);
    return _leech(lammer);
}

Vector3 GetLShoulderPosition(void* player) {
    return get_position_Injected(GetLShoulderLeech(player));
}

static void *GetRShoulderLeech(void *lammer) {
    void *(*_leech)(void *lammer) = (void *(*)(void *))getRealOffset(address.RShoulder);
    return _leech(lammer);
}

Vector3 GetRShoulderPosition(void* player) {
    return get_position_Injected(GetRShoulderLeech(player));
}

Vector3 CameraMain(void* player) {
    return get_position_Injected(*(void**) ((uint64_t) player + address.MainCameraTransform));
}

static void spofNick(void *players) {
void (*_spof_nick)(void *player, monoString *nick) = (void (*)(void *, monoString *))getRealOffset(address.FakeName);
_spof_nick(players, CreateString((OBFUSCATE("[FF0000]YOUTUBE : [00FF00]GOD X MODS TEAM"))));
}

void *GetVehicle(void * Match) {
if (!Match) return nullptr;
void* veiculo = nullptr;
void* PlayerClient = GetLocalPlayer2(Match);//0
void* vehicle = GetLocalVehicle(PlayerClient);
bool dirigindo = get_IsDriver(PlayerClient);
if (vehicle != nullptr && !get_IsPassenger(PlayerClient)) {
veiculo = vehicle;
}
return veiculo;
}

bool Visible_Check(void * player) {
if(player != NULL) {
void *hitObj = NULL;
Vector3 cameraLocation = get_position_Injected(get_transform(get_main()));
Vector3 headLocation = get_position_Injected(get_transform(get_HeadCollider(player)));
return !Physics_Raycast(cameraLocation, headLocation, 12, &hitObj);
}
return false;
}

/*namespace Save{
        void* DamageInfo;
        void* DamagerWeaponDynamicInfo;
        clock_t AimDelay;
        int AimFPS = (1000000 / 15);
}

void (*DamageInfo)(void*);
void DamageInfoHook(void* Player){
        return DamageInfo(Save::DamageInfo=Player);
}


static void AimSkill(void* Enemy) {
    if (Enemy != nullptr) {
        if(Save::DamageInfo != NULL && clock() > Save::AimDelay){
            
        Save::AimDelay = clock() + Save::AimFPS;
        void* LocalPlayer = Current_Local_Player();
        if (LocalPlayer && !get_isWatching(LocalPlayer)){
                void* WeaponOnHand = PlayerWeaponOnHand(LocalPlayer);
        
        *(int32_t*)((uintptr_t) Save::DamageInfo + 0xC) = 1;
        *(void**)((uintptr_t) Save::DamageInfo + 0x18) = *(void**)((uintptr_t) LocalPlayer + 0x148);
        *(void**)((uintptr_t) Save::DamageInfo + 0x18) = *(void**)((uintptr_t) LocalPlayer + 0xd38);
        *(void**)((uintptr_t) Save::DamageInfo + 0x30) = WeaponOnHand;
        *(Vector3*)((uintptr_t) Save::DamageInfo + 0x38) = CameraMain(LocalPlayer);
        *(Vector3*)((uintptr_t) Save::DamageInfo + 0x44) = GetHeadPosition(Enemy);
                
          Vector3 m_Head = GetHeadPosition(Enemy);
          Vector3 m_HeadLocal = GetHeadPosition(Current_Local_Player());
          void *WeaponHand = PlayerWeaponOnHand(Current_Local_Player());
            if (WeaponHand != nullptr) {
                                StartWholeBodyFiring(Current_Local_Player(),WeaponHand);
                LateKillUpdate(Enemy, *(int *) ((long) WeaponHand + 0x58),
                           get_PlayerID(Current_Local_Player()), Save::DamageInfo, GetWeapon(WeaponHand),
                           m_HeadLocal, m_Head, *(monoList<float> *) ((long) Enemy + 0x8C0), 0, 0);
                                StopFire(Current_Local_Player(),WeaponHand);
            }
        }
    }
}
}


/*void (*DamageInfo)(void* Player);
void DamageInfoHook(void* Player){
Save::DamageInfoo=Player;
return DamageInfo(Player);
}

void PlayerTakeDamage(void* Player){
void* Match = CurrentMatch();
void* LocalPlayer1 = GetLocalPlayer2(Match);//1
if ((StartMenu) && Match) {
if(Save::DamageInfoo != NULL && clock() > Save::AimDelay){
Save::AimDelay = clock() + AimFPS;
if (Visible_Check(Player)) {
if (Visible_Check != nullptr) {
void * GetWeaponHand1 = GetWeaponOnHand1(LocalPlayer1);
if (GetWeaponHand1 != nullptr) {
Vector3 HeadPOS1 = GetHeadPosition(Player);
*(void**)((uintptr_t) Save::DamageInfoo + 0x18) = *(void**)((uintptr_t) LocalPlayer1 + 0x118);// protected IHAAMHPPLMG KFMGKCJMCAM; 2
if (Save::DamageInfoo != nullptr) {
*(void**)((uintptr_t) Save::DamageInfoo + 0x30) = GetWeaponHand1;
*(Vector3*)((uintptr_t) Save::DamageInfoo + 0x38) = CameraPosition(LocalPlayer1);
*(Vector3*)((uintptr_t) Save::DamageInfoo + 0x44) = HeadPOS1;
*(int*) ((uintptr_t) Save::DamageInfoo + 0xC) = 1;
*(void**)((uintptr_t) Save::DamageInfoo + 0x10);
StartWholeBodyFiring(LocalPlayer1, GetWeaponHand1);
TakeDamage(Player, *(int *) ((long) GetWeaponHand1 + 0x58),
get_PlayerID(LocalPlayer1), Save::DamageInfoo, GetWeapon(GetWeaponHand1),
CameraPosition(LocalPlayer1), HeadPOS1, *(monoList<float> *) ((long) Player + 0x82c), 0, 0);// private GameObject IGEHMJFLFLK;
TakeDamagee(Player,Save::DamageInfoo,NULL,*(void**)((uintptr_t) Player + 0x80c),0);// private GameObject JHHABGNEDGC;
StartFiring(LocalPlayer1, GetWeaponHand1);
StopFire1(LocalPlayer1, GetWeaponHand1);
}
}
}
}
}
}
}
*/



Vector3 AlvoEnemyPos = Vector3(0, 0, 0);
Vector3 AlvoLocalPos = Vector3(0, 0, 0);

void *GetClosestEnemy(void *match) {
if(!match) {
return NULL;
}
 
float shortestDistance = 99999.0f;
float maxAngle = Aim_Fov;
void* closestEnemy = NULL;
void* LocalPlayer = GetLocalPlayer2(match);//2
if(LocalPlayer != NULL && !get_IsDieing(LocalPlayer)) {
monoDictionary<uint8_t *, void **> *players = *(monoDictionary<uint8_t*, void **> **)((long)match + address.Dictionary);
for(int u = 0; u < players->getNumValues(); u++) {
void* Player = players->getValues()[u];
if(Player != NULL && !IsLocalTeammate(Player) && !get_IsDieing(Player) && IsVisible(Player) && get_MaxHP(Player)) {

Vector3 PlayerPos = GetHipPosition(Player);
Vector3 LocalPlayerPos = GetHeadPosition(LocalPlayer);
Vector3 CenterWS = GetAttackableCenterWS(LocalPlayer);

if(StartMenu) {
if(!CheckVisible) {
if(FOV) {
Vector3 targetDir = Vector3::Normalized(PlayerPos - LocalPlayerPos);
float angle = Vector3::Angle(targetDir, get_forward(get_transform(get_main()))) * 100;
if(angle <= maxAngle) {
if(angle < shortestDistance) {
shortestDistance = angle;
closestEnemy = Player;
}
}
}
} else {
if(maxAngle < shortestDistance) {
shortestDistance = maxAngle;
closestEnemy = Player;
}
}
}

if (EspFire) {
void *imo = get_imo(LocalPlayer);
if (imo != NULL ) {
set_esp(imo, CenterWS, PlayerPos);
}
}

if (ESPFire2) {
void *imo = get_imo(LocalPlayer);
if (imo != NULL ) {
set_esp2(imo, CenterWS, PlayerPos);
}
}

if(CheckVisible) {
Vector3 targetDir = Vector3::Normalized(PlayerPos - LocalPlayerPos);
float angle = Vector3::Angle(targetDir, get_forward(get_transform(get_main()))) * 100.0;
if(angle <= maxAngle) {
if(Visible_Check(Player)) {
if(angle < shortestDistance) {
shortestDistance = angle;
closestEnemy = Player;
}
}
}
} else {
if(maxAngle < shortestDistance) {
shortestDistance = maxAngle;
closestEnemy = Player;
}
}
/*if (AimKill) {
                AimSkill(closestEnemy);
                   }*/

}
}
}
return closestEnemy;
}

/*int pLoopDamage1 = 0;
int WorkTakeDamage1 = 0;
int LoopFire1 = 0;
bool StartFire1 = true;
bool StopFire22 = false;

void *pCurrentLocalPlayer1 = nullptr;
void *GetWeaponHand1 = nullptr;

struct DataRemote1 {
void *DevilyRemote1 = nullptr;
int32_t DevilyRemote2 = 0;
void *DevilyRemote3 = nullptr;
void *DevilyRemote4 = nullptr;
int32_t DevilyRemote5 = 0;
Vector3 DevilyRemote6 = Vector3::Zero();
Vector3 DevilyRemote7 = Vector3::Zero();
monoList<float *> DevilyRemote8;
void *DevilyRemote9 = nullptr;
int32_t DevilyRemote10 = 0;
}pData1 ;

int32_t (*orig_TakeDamage1)(void *player, int32_t p_damage, void *get_KillerPlayerID, void *p_info, int WeaponDataID, Vector3 FirePos, Vector3 TargetPos, monoList<float *> CheckParams, void *p_idk1, int32_t p_idk2);
int32_t hook_TakeDamage1(void *player, int32_t p_damage, void *get_KillerPlayerID, void *p_info, int WeaponDataID, Vector3 FirePos, Vector3 TargetPos, monoList<float *> CheckParams, void *p_idk1, int32_t p_idk2) {
if(StartMenu) {
if (Skill) {
pData1.DevilyRemote1 = player;
pData1.DevilyRemote2 = p_damage;
pData1.DevilyRemote3 = get_KillerPlayerID;
pData1.DevilyRemote4 = p_info;
pData1.DevilyRemote5 = WeaponDataID;
pData1.DevilyRemote6 = FirePos;
pData1.DevilyRemote7 = TargetPos;
pData1.DevilyRemote8 = CheckParams;
pData1.DevilyRemote9 = p_idk1;
pData1.DevilyRemote10 = p_idk2;
} else {
pData1. DevilyRemote1 = nullptr;
}
return orig_TakeDamage1(player, p_damage, get_KillerPlayerID, p_info, WeaponDataID, FirePos, TargetPos, CheckParams, p_idk1, p_idk2);
}
}

static void NetworkTakeDamage1(void * closestEnemy) {
void* Match = CurrentMatch();
if((StartMenu) && Match) {
if (Skill && pData1.DevilyRemote1 != nullptr) {
pCurrentLocalPlayer1 = GetLocalPlayer2(Match);
if(Save::DamageInfoo != NULL && clock() > Save::AimDelay){
Save::AimDelay = clock() + AimFPS;
if (Visible_Check(closestEnemy)) {
void * GetWeaponHand1 = GetWeaponOnHand1(pCurrentLocalPlayer1);
void* LocalCar = VehicleIAmIn(pCurrentLocalPlayer1);
if (LocalCar != nullptr) {
Vector3 HeadPOS1 = GetHeadPosition(closestEnemy);
*(void**)((uintptr_t) Save::DamageInfoo + 0x18) = *(void**)((uintptr_t) pCurrentLocalPlayer1 + 0x118);// protected IHAAMHPPLMG KFMGKCJMCAM; 2
*(void**)((uintptr_t) Save::DamageInfoo + 0x30) = GetWeaponHand1;
*(Vector3*)((uintptr_t) Save::DamageInfoo + 0x38) = CameraPosition(pCurrentLocalPlayer1);
*(Vector3*)((uintptr_t) Save::DamageInfoo + 0x44) = HeadPOS1;
*(int*) ((uintptr_t) Save::DamageInfoo + 0xC) = 1;
*(void**)((uintptr_t) Save::DamageInfoo + 0x10);
if (Skill) {
StartFire1 = true;
StopFire22 = false;
pLoopDamage1 = 15;
}
if (Skill) {
TakeDamagee(closestEnemy,Save::DamageInfoo,NULL,*(void**)((uintptr_t) closestEnemy + 0x80c),0);// private GameObject JHHABGNEDGC;
orig_TakeDamage1(closestEnemy, pData1.DevilyRemote2, pData1.DevilyRemote3, pData1.DevilyRemote4, pData1.DevilyRemote5, pData1.DevilyRemote6, pData1.DevilyRemote7, pData1.DevilyRemote8, pData1.DevilyRemote9, pData1.DevilyRemote10);
WorkTakeDamage1 = 18;
}
if (Skill) {
StartWholeBodyFiring(pCurrentLocalPlayer1, GetWeaponHand1);
LoopFire1 = 15;
} 
if (StartFire1) {
if (pCurrentLocalPlayer1) {
if (GetWeaponHand1) {
StartFiring(pCurrentLocalPlayer1, GetWeaponHand1);
}
}
StartFire1 = true;
StopFire22 = false;
}
if (StopFire1) {
if (pCurrentLocalPlayer1) {
if (GetWeaponHand1) {
StopFire1(pCurrentLocalPlayer1,GetWeaponHand1);
}
}
StartFire1 = false;
StopFire22 = true;
} 
}
}
}
}
}
}
*/
static bool isReady() {
return false;
}

long StartIl2cpp;
long AbsoluteAddress(long Offset){
if(StartIl2cpp == 0){
StartIl2cpp = AfindLibrary("libil2cpp.so");
if(StartIl2cpp == 0){
StartIl2cpp = 0;
}
}
return StartIl2cpp + Offset;
}

void (*Update)(void* gamestartup);
void _Update(void* gamestartup) {
if(StartMenu) {
void* Match = CurrentMatch();
if ((AimScope || AimFire) && Match) {
auto *PlayerClient = GetLocalPlayer2(Match);
if (PlayerClient) {
/* void* LocalPlayer = GetLocalPlayer(Match);
if (LocalPlayer) {*/
tS++;
if (tS > 1 && autotroca) {
auto now = steady_clock::now();
auto elapsed = duration_cast<milliseconds>(now - lastSwapTime).count();
if (elapsed >= 300) {
sID = !sID;
SwapWeapon(PlayerClient, sID, true);
tS = 0;
lastSwapTime = now;
}
}
 
void* closestEnemy = GetClosestEnemy(Match);
if (closestEnemy && !get_IsDieing(closestEnemy)) {

/*if (Skill && pData1.DevilyRemote1 != nullptr) {
NetworkTakeDamage1(closestEnemy);
} 
++WorkTakeDamage1;
++pLoopDamage1;
++Save::AimDelay;
++AimFPS;
*/
Vector3 EnemyLocation = GetHeadPosition(closestEnemy);
Vector3 EnemyLocation2 = GetHeadPosition(PlayerClient);
Vector3 PlayerLocation = CameraMain(PlayerClient);//01
Vector3 CenterWS = GetAttackableCenterWS(PlayerClient);//02

Quaternion PlayerLook = GetRotationToLocation(GetHeadPosition(closestEnemy), 0.1f, PlayerLocation);
Quaternion PlayerLook2 = GetRotationToLocation(GetHipPosition(closestEnemy), 0.1f, PlayerLocation);
Quaternion PlayerLook3 = GetRotationToLocation(GetToePosition(closestEnemy), 0.1f, PlayerLocation);

float distance = Vector3::Distance(CenterWS, EnemyLocation);
int Health = get_CurHP(closestEnemy);

Vector3 LocalPlayerPos = GetHeadPosition(PlayerClient);//03
Vector3 LocalPlayerPos2 = GetAttackableCenterWS(PlayerClient);//04
Vector3 PlayerPos = GetHeadPosition(closestEnemy);
 
bool scope = get_IsSighting(PlayerClient);//05
bool firing = IsFiring(PlayerClient);//06
bool caido = get_IsDieing(closestEnemy);
bool dirigindo = get_IsDriver(PlayerClient);
 
if (StartMenu) {
spofNick(PlayerClient);//07
}
 
if (EspAlerta) { 
void *ui = CurrentUIScene();
if (ui != NULL) {
monoString *nick = get_NickName(PlayerClient);//08
monoString *distances = U3DStrFormat(distance);
ShowAssistantText(ui, nick, distances);
}
}
 
if (TeleCar) {
void *_TeleCarTP = get_transform(closestEnemy);
if (_TeleCarTP != NULL) {
Vector3 TeleCarTP = get_position_Injected(_TeleCarTP) - (get_forward(_TeleCarTP) * 0);
void* LocalCar = VehicleIAmIn(PlayerClient);
if (LocalCar != NULL) {
set_position_Injected(get_transform(LocalCar), Vvector3(TeleCarTP.X, TeleCarTP.Y, TeleCarTP.Z));
}
}
}
 
if (Skill && distance < 100.99 && dirigindo) {
void *_TeleCarTP = get_transform(closestEnemy);
if (_TeleCarTP != NULL) {
Vector3 TeleCarTP = get_position_Injected(_TeleCarTP) - (get_forward(_TeleCarTP) * 0);
void* LocalCar = VehicleIAmIn(PlayerClient);
if (LocalCar != NULL) {
set_position_Injected(get_transform(LocalCar), Vvector3(TeleCarTP.X, TeleCarTP.Y + 2.0, TeleCarTP.Z));
}
}
}
 
if (TelePro && distance < 600.99 && PlayerClient) {
void *_TeleKillTP = get_transform(closestEnemy);
if (_TeleKillTP != NULL) {
Vector3 TeleKillTP = get_position_Injected(_TeleKillTP) -(get_forward(_TeleKillTP) * 0);
set_position_Injected(get_transform(PlayerClient),Vvector3(TeleKillTP.X, TeleKillTP.Y, TeleKillTP.Z ));
}
}
 
if (TelePro2 && distance < 600.99 && PlayerClient) {
void *_TeleKillTP = get_transform(closestEnemy);
if (_TeleKillTP != NULL) {
Vector3 TeleKillTP = get_position_Injected(_TeleKillTP) -(get_forward(_TeleKillTP) * 0);
set_position_Injected(get_transform(PlayerClient),Vvector3(TeleKillTP.X, TeleKillTP.Y + 1.0, TeleKillTP.Z ));
}
}


if(EspGrenade) {
//if(Visible_Check(closestEnemy)){
GrenadeLine_DrawLine(Grenade2, LocalPlayerPos, LocalPlayerPos, Vector3(0,1,0) * 0.1);
((void (*)(void *, Color))getRealOffset(address.set_startColor))(Render2, Color::Red());
((void (*)(void *, Color))getRealOffset(address.set_endColor))(Render2, Color::Red());
if (Render2) {
LineRenderer_Set_PositionCount(Render2, 0x2); 
LineRenderer_SetPosition(Render2, 0, LocalPlayerPos);
LineRenderer_SetPosition(Render2, 1, PlayerPos);
}
}


 
if (scope && AimScope) {
SetAimRotation(PlayerClient, PlayerLook);//09
}
if (firing && AimFire) {
SetAimRotation(PlayerClient, PlayerLook);//10
}
}
}
}
}
Update(gamestartup);
}
//}

void _FlyW(void * _this){
if (_this) {
if (StartMenu) {
void *Match = CurrentMatch();
if (Match) {
void *LocalPlayer = *(void **) ((long) Match + 0x10);
if (LocalPlayer != NULL) {
if (FlyHack > 0) {
bool StopCatapult = false;
if (IsCatapultFalling(LocalPlayer)) {
if (!StopCatapult) {
StopCatapult = true;
OnStopCatapultFalling(LocalPlayer);
}
} else {
StopCatapult = false;
}
if (FlyHack > 0 || Flyspeed > 0) {
void *MyPhsXData = get_MyPhsXData(LocalPlayer);
if (FlyHack != 0 || Flyspeed != 0) {
float altura;
float speed;
if (IsFiring(LocalPlayer) || get_IsSighting(LocalPlayer)){
altura = (float)FlyHack/25;
speed = Flyspeed/1000;
} else {
if (FlyHack == 1 || Flyspeed == 0) {
altura = (float)FlyHack/25;
speed = Flyspeed/1000;
} else {
altura = (float)FlyHack/25;
speed = Flyspeed/1000;
}
}
*(float *) ((long) MyPhsXData + address.PetSkillCDEvt) = altura;//0x28
*(float *) ((long) MyPhsXData + address.HudPlayerSkillBrightAnimEvt) = speed;//0x2c
}
if(HackFly) {
Vector3 SalvarPosicao = get_position_Injected(get_transform(LocalPlayer));
Vector3 FlyCamera = get_position_Injected(get_transform(LocalPlayer)) + (get_forward(get_transform(get_main())) * Flyspeed/1000);
if (IsFiring(LocalPlayer) || get_IsSighting(LocalPlayer)) {
set_position_Injected(get_transform(LocalPlayer), Vvector3(TFPosX, TFPosY, TFPosZ));
} else {
TFPosY = SalvarPosicao.Y;
TFPosZ = SalvarPosicao.Z;
TFPosX = SalvarPosicao.X;
if (FlyHack == 1) TFPosY += FlyHack/25;
set_position_Injected(get_transform(LocalPlayer), Vvector3(FlyCamera.X, SalvarPosicao.Y, FlyCamera.Z));
}
}
}
}
}
}
}
}
}

void(*UpdateFly)(void *_this);
void(_UpdateFly)(void *_this) {
if (_this == nullptr)
return;
_FlyW(_this);
UpdateFly(_this);
}

int (*orig_GetPhysXPose)(void*_this);
int hook_GetPhysXPose(void*_this) {
if (_this != NULL) {
if (StartMenu) {
if(FlyHack > 0 || Flyspeed > 0) {
return 10;//10
// } else if(Jump > 0 || Speed > 0) {
//return 2;
} 
}
return orig_GetPhysXPose(_this);
}
}

int (*orig_GetPhysXPoseNEW)(void*_this);
int hook_GetPhysXPoseNEW(void*_this){
if (_this != NULL) {
if (StartMenu) {
if(FlyHack > 0 || Flyspeed > 0) {
return 12;//12
}
}
return orig_GetPhysXPoseNEW(_this);
}
}

bool (*orig_IsIgnoreHighFalling)(void *_this);
bool hook_IsIgnoreHighFalling(void *_this) {
if (_this != NULL){
if (StartMenu) {
if(FlyHack > 0 || Flyspeed > 0) {
return true;
}
return orig_IsIgnoreHighFalling(_this);
}
}
}

bool (*orig_get_IsPoseFallingHigh)(void *_this);
bool hook_IsPoseFallingHigh(void *_this) {
if (_this != NULL){
if (StartMenu) {
if(FlyHack > 0) {
return true;
}
return orig_get_IsPoseFallingHigh(_this);
}
}
}

bool (*OnStopCatapultFalling_)(void* _this);
bool _OnStopCatapultFalling(void* _this) {
if (_this != NULL) {
if (StartMenu) {
if(Flyspeed > 0) {
return true;
}
return OnStopCatapultFalling_(_this);
}
}
}

int (*GetPhysXState2)(void*_this, int value);
int _GetPhysXState2(void*_this, int value){
if (_this != NULL) {
if (StartMenu) {
if(FlyHack > 0) {
return 11;
} else if(HackBoard) {
return false;
}
}
return GetPhysXState2(_this, value);
}
}

int (*GetPhysXState)(void*_this, int value);
int _GetPhysXState(void*_this, int value){
if (_this != NULL) {
if (StartMenu) {
if(TelePro) {
return 2;//2
} else if(HackBoard2) {
return 13;//13
} 
}
return GetPhysXState(_this, value);
}
}

void (*SpeedCar)(void *updatedoflyfds);
void _SpeedCar(void *updatedoflyfds) {
if (StartMenu) {
void *Match = CurrentMatch();
if (Match) {
void* LocalPlayer = GetLocalPlayer2(Match);//4
if (LocalPlayer != NULL) {
Vector3 MountCarro = get_position_Injected(get_transform(LocalPlayer));
void* LocalCarro = VehicleIAmIn(LocalPlayer);
if (LocalCarro) {
ContolCarro = get_position_Injected(get_transform(LocalCarro)) + (get_forward(get_transform(get_main())) * SpeedFlyCarro/10.0f);
if (FlyCarroConfig == 0 || !VehicleIAmIn(LocalCarro)) {
FupdmdCarroY = MountCarro.Y;
FupdmdCarroZ = MountCarro.Z;
FupdmdCarroX = MountCarro.X;
}
if (FlyCarroConfig > 0) {
if (get_IsSighting(LocalPlayer) || IsFiring(LocalPlayer)) {
set_position_Injected(get_transform(LocalCarro), Vvector3(FupdmdCarroX, FupdmdCarroY, FupdmdCarroZ));
} else if (FlyCarroConfig == 1) {
FupdmdCarroX = MountCarro.X;
FupdmdCarroY = MountCarro.Y;
FupdmdCarroZ = MountCarro.Z;
if (VehicleIAmIn(LocalPlayer)){
if (FlyCarroConfig > 2) set_position_Injected(get_transform(LocalCarro), Vvector3(ContolCarro.X, MountCarro.Y + 000.0001f, ContolCarro.Z)); 
if (FlyCarroConfig > 3) set_position_Injected(get_transform(LocalCarro), Vvector3(ContolCarro.X, MountCarro.Y + 000.3f, ContolCarro.Z)); 
if (FlyCarroConfig > 4) set_position_Injected(get_transform(LocalCarro), Vvector3(ContolCarro.X, MountCarro.Y + 000.4f, ContolCarro.Z)); 
if (FlyCarroConfig > 5) set_position_Injected(get_transform(LocalCarro), Vvector3(ContolCarro.X, MountCarro.Y + 000.5f, ContolCarro.Z)); 
if (FlyCarroConfig > 6) set_position_Injected(get_transform(LocalCarro), Vvector3(ContolCarro.X, MountCarro.Y + 000.6f, ContolCarro.Z)); 
if (FlyCarroConfig > 7) set_position_Injected(get_transform(LocalCarro), Vvector3(ContolCarro.X, MountCarro.Y + 000.7f, ContolCarro.Z)); 
if (FlyCarroConfig > 8) set_position_Injected(get_transform(LocalCarro), Vvector3(ContolCarro.X, MountCarro.Y + 000.8f, ContolCarro.Z)); 
if (FlyCarroConfig > 9) set_position_Injected(get_transform(LocalCarro), Vvector3(ContolCarro.X, MountCarro.Y + 000.9f, ContolCarro.Z)); 
if (FlyCarroConfig > 10) set_position_Injected(get_transform(LocalCarro), Vvector3(ContolCarro.X, MountCarro.Y + 000.10f, ContolCarro.Z)); 
if (FlyCarroConfig > 11) set_position_Injected(get_transform(LocalCarro), Vvector3(ContolCarro.X, MountCarro.Y + 000.11f, ContolCarro.Z)); 
if (FlyCarroConfig > 12) set_position_Injected(get_transform(LocalCarro), Vvector3(ContolCarro.X, MountCarro.Y + 000.12f, ContolCarro.Z)); 
if (SpeedFlyCarro > 0) {
if (!get_IsSighting(LocalPlayer) || !IsFiring(LocalPlayer))
set_position_Injected(get_transform(LocalCarro), Vvector3(ContolCarro.X, MountCarro.Y, ContolCarro.Z));
}
} else if (FlyCarroConfig > 1) {
FupdmdCarroX = MountCarro.X;
FupdmdCarroY = MountCarro.Y;
FupdmdCarroZ = MountCarro.Z;
if (FlyCarroConfig == 2) FupdmdCarroY += 000.0001f;
if (FlyCarroConfig == 3) FupdmdCarroY += 000.3f;
if (FlyCarroConfig == 4) FupdmdCarroY += 000.4f;
if (FlyCarroConfig == 5) FupdmdCarroY += 000.5f;
if (FlyCarroConfig == 6) FupdmdCarroY += 000.6f;
if (FlyCarroConfig == 7) FupdmdCarroY += 000.7f;
if (FlyCarroConfig == 8) FupdmdCarroY += 000.8f;
if (FlyCarroConfig == 9) FupdmdCarroY += 000.9f;
if (FlyCarroConfig == 10) FupdmdCarroY += 000.10f;
if (FlyCarroConfig == 11) FupdmdCarroY += 000.11f;
if (FlyCarroConfig == 12) FupdmdCarroY += 000.12f;
set_position_Injected(get_transform(LocalCarro), Vvector3(MountCarro.X, FupdmdCarroY, MountCarro.Z)); 
}
}
}
}
SpeedCar(updatedoflyfds);
}
}
}
}

bool (*orig_get_InFallingState)(void *_this);
bool get_InFallingState(void *_this) {
if (_this != NULL){
if (StartMenu) {
return false;
}
return orig_get_InFallingState(_this);
}
}
 
bool (*switchbellara)(void* _this, int value);
bool _SwitchFast(void* _this, int value){
if (_this != NULL){
if (StartMenu) {
return false;
}
}
return switchbellara(_this, value);
}

bool (*Ghost)(void* _this, int value);
bool _Ghost(void* _this, int value){
if (_this != NULL){
if (StartMenu) {
if (GhostHack){
return false;
}
}
return Ghost(_this, value);
}
}

float (*GetSpecialRunJumpScale)(void * _this);
float _GetSpecialRunJumpScale(void * _this) {
if (_this != NULL) {
if (StartMenu) {
if(Jump == 1) {
return 1.1;
} else if(Jump == 2) {
return 1.2;
} else if(Jump == 3) {
return 1.4;
} else if(Jump == 4) {
return 1.8;
} else if(Jump == 5) {
return 2.3;
} 
}
return GetSpecialRunJumpScale(_this);
}
}

float (*GetSpecialRunSpeedScale)(void * _this);
float _GetSpecialRunSpeedScale(void * _this) {
if (_this != NULL) {
if (StartMenu) {
if(Speed == 1) {
return 1.8;
} else if(Speed == 2) {
 return 2.8;
} else if(Speed == 3) {
return 4.8;
} else if(Speed == 4) {
return 8.8;
} else if(Speed == 5) {
return 88;
} 
}
return GetSpecialRunSpeedScale(_this);
}
}

void *(*orig_Vehicle)(Vector3 pVehicle);
void *hook_Vehicle(Vector3 pVehicle) {
if (Flycar >= 0 || Undercar >= 0) {
void * vehicle = GetVehicle(CurrentMatch());
if (vehicle != nullptr) {
if (StartMenu) {
pVehicle.X;
pVehicle.Y = pVehicle.Y + Flycar/100;
pVehicle.Y = pVehicle.Y - Undercar/10;
pVehicle.Z;
return orig_Vehicle(pVehicle);
}
}
return orig_Vehicle(pVehicle);
}
}

void (*LateUpdate)(void *componentPlayer);
void *playerlate = NULL;
void *get_Player(void *player){
playerlate = player;
return playerlate;
}

void *fakeEnemy;
void _LateUpdate(void *player){
if (player != NULL) {
if(StartMenu) {
void *current_Match = CurrentMatch();
if (current_Match) {
void* local_player = GetLocalPlayer2(current_Match);
if (local_player) { 
if (!isReady()) {
monoDictionary<uint8_t *, void **> *players = *(monoDictionary<uint8_t *, void **> **) ((long) current_Match + address.Dictionary);
for (int u = 0; u < players->getNumValues(); u++) {
void *closestEnemy = players->getValues()[u];
if (closestEnemy && IsVisible(closestEnemy) && !get_IsDieing(closestEnemy) && !IsLocalTeammate(closestEnemy)) {
 
Vector3 EnemyLocation = GetHeadPosition(closestEnemy);
Vector3 CenterWS = GetAttackableCenterWS(local_player);


if(EspFire2Azul) {
void *imo = get_imo(local_player);
if (imo != NULL) {
if (get_IsDieing(closestEnemy)){
set_esp(imo, CenterWS, EnemyLocation);
}else{
set_esp2(imo, CenterWS, EnemyLocation);
}
}
}
}
}
}
}
}
}
}
get_Player(player);
LateUpdate(player);
}

static bool isEspReady(){
return false;
}

void DrawESP(ESP esp, int screenWidth, int screenHeight) {

if(crosshair) {
esp.DrawCrosshair( Color(EspColor), Vector3(screenWidth / 2, screenHeight/2), 80);
}

esp.DrawCustomColor(Color::Red(),
Vector2(screenWidth / 2 - screenHeight / 6, screenHeight / 16),
Vector2(screenWidth / 2 + screenHeight / 6, screenHeight / 10.1));
esp.DrawCustomText(Color::Black(), 0.6f, ("DEXX-TER"),
Vector3(screenWidth / 2, screenHeight / 11), 30);
 
//if(ActivateAimbot) {
if(ActivateEsp) {
float maxTexto = Tamano;
 
void *Amjad = playerlate;
if (Amjad != nullptr) {
void *current_Match = CurrentMatch();
if (current_Match) {
void* local_player = GetLocalPlayer2(current_Match);
if (local_player) { 
if (!isEspReady()) {
monoDictionary<uint8_t *, void **> *players = *(monoDictionary<uint8_t*, void **> **)((long)current_Match + address.Dictionary);
void *camera = get_main(); 
if (players != nullptr && camera != nullptr) { 
for(int u = 0; u < players->getNumValues(); u++) {
void* closestEnemy = players->getValues()[u];
if (closestEnemy && IsVisible(closestEnemy) && !IsLocalTeammate(closestEnemy) && get_MaxHP(closestEnemy)) {
 
 Vector3 PositionHead = WorldToScreenPoint(camera, GetHeadPosition(closestEnemy));
 Vector3 GetHead = Vector3((screenWidth - (screenWidth - PositionHead.X - EspKanan + EspKiri)), screenHeight - PositionHead.Y - EspAtas + EspBawah);
 if (PositionHead.Z < -0) continue;
 
 Vector3 PositionToe = WorldToScreenPoint(camera, GetToePosition(closestEnemy));
 Vector3 GetToe = Vector3((screenWidth - (screenWidth - PositionToe.X - EspKanan + EspKiri)), screenHeight - PositionToe.Y - EspAtas + EspBawah);
 if (PositionToe.Z < -0) continue; 
 
 Vector3 PositionHip = WorldToScreenPoint(camera, GetHipPosition(closestEnemy)); 
 Vector3 GetHip = Vector3((screenWidth - (screenWidth - PositionHip.X - EspKanan + EspKiri)), screenHeight - PositionHip.Y - EspAtas + EspBawah);
 if (PositionHip.Z < -0) continue;
 
 Vector3 RShoulder = WorldToScreenPoint(camera,GetRShoulderPosition(closestEnemy));
 if (RShoulder.Z < -0) continue;
 
 Vector3 LShoulder = WorldToScreenPoint(camera,GetLShoulderPosition(closestEnemy));
 if (LShoulder.Z < -0) continue;
 
 Vector3 EnemyLocation = GetHeadPosition(closestEnemy);
 Vector3 CenterWS = GetAttackableCenterWS(local_player); 
 float distance = Vector3::Distance(CenterWS, EnemyLocation);
 bool caido = get_IsDieing(closestEnemy);
 
 Vector3 End = PositionHead;
 Vector3 End2 = PositionToe;
 
 float Tamanho = 0.0f;
 float Distance2 = Vector3::Distance(GetHeadPosition(local_player), GetHeadPosition(closestEnemy));
 if (Distance2 > 15.0f) {
 Tamanho = 15.0f;
 } else if (Distance2 > 25.0f) {
 Tamanho = 0.0f;
 }
 
 float boxHeight = ((screenHeight - End2.Y) - (screenHeight - End.Y));
 float boxWidth = static_cast<float>( ((screenWidth - RShoulder.X * 0.995) - (screenWidth - LShoulder.X * 1.005)) * 1.5);
 Rect PlayerRect(screenWidth - (screenWidth - (End2.X - (boxWidth / 2) - EspKiri + EspKanan)), (screenHeight - End.Y - EspAtas + EspBawah), boxWidth, boxHeight);
 float boxHeight2 = ((screenHeight - End.Y) - (screenHeight - End2.Y));
 //Rect PlayerRect2(screenWidth - (screenWidth - (End.X - (boxWidth / 2) - EspKiri + EspKanan)), (screenHeight - End2.Y - EspAtas + EspBawah), boxWidth, boxHeight2);
 
 Rect PlayerRect2(End.X - (boxWidth / 2), (screenHeight - End.Y - 10.0f), boxWidth, boxHeight + Tamanho);
 
 bool ind = *(bool*)((uintptr_t)closestEnemy + address.IsClientBot);
 if (ind) {
 indetifiq = "[__BOT__]";
 } else {
 indetifiq = "[__PLAYER__]";
 }
 
 char dstc[50]; 
 sprintf(dstc, "[%.2f m]", distance);
 std::string dist; 
 dist = dstc;
 
 int Health = get_CurHP(closestEnemy);
 char Hps[128] = {};
 sprintf(Hps, "[HP : %d]", Health);
 std::string vida;
 vida = Hps;
 std::string caidos;
 caidos ="[Fallen]";
 std::string nulls;
 nulls ="";
 
 
 if(isPlayerLine) {
 if(caido && EspCaidos) {
 esp.DrawLine(Color(CaidoColor), 1.5, Vector3((screenWidth / 2), screenHeight / 16.9f), Vector3((screenWidth - (screenWidth - PositionHead.X)), (screenHeight - PositionHead.Y)));
 } else {
 esp.DrawLine(EspColor, 1.5, Vector3((screenWidth / 2), screenHeight / 16.9f), Vector3((screenWidth - (screenWidth - PositionHead.X)), (screenHeight - PositionHead.Y)));
 }
 }
 
 
 if(espFromCross) {
 if(caido && EspCaidos) {
 esp.DrawLine(Color(CaidoColor), 1.5, Vector3((screenWidth / 2), (screenHeight / 2)), Vector3((screenWidth - (screenWidth - PositionHead.X)), (screenHeight - PositionHead.Y - 8.0f)));
 } else {
 esp.DrawLine(EspColor, 1.5, Vector3((screenWidth / 2), (screenHeight / 2)), Vector3((screenWidth - (screenWidth - PositionHead.X)), (screenHeight - PositionHead.Y - 8.0f)));
 }
 }
 
 
 if(isPlayerBox) {
 if(caido && EspCaidos) {
 esp.DrawBox(Color(CaidoColor), 1.5, PlayerRect2);
 } else {
 esp.DrawBox(EspColor, 1.5, PlayerRect2);
 }
 }
 
 monoString* nick = get_NickName(closestEnemy);
 std::string names;
 if(nick != NULL) {
 int nick_Len = nick ->getLength();
 for(int i = 0; i < nick_Len; i++) {
 char data = get_Chars(nick, i);
 names += isascii(data) ? data : data;
 }
 }
 std::string dnames;
 dnames ="["+ names+"]";
 
 if(isPlayerIdent && isPlayerName){
 if(ind){
 dnames ="["+ names+"]";
 }else{
 dnames ="["+ names+"]";
 }
 }
 
 if(isPlayerName) {
 if(caido && EspCaidos) {
 esp.DrawText(Color(CaidoColor), 0.6f,
 nulls.c_str(),
 Vector3(PlayerRect.x + (PlayerRect.width / 2), PlayerRect.y - 12.0f),
 maxTexto);
 }else{
 esp.DrawText(Color(EspColor), 0.6f,
 dnames.c_str(),
 Vector3(PlayerRect.x + (PlayerRect.width / 2), PlayerRect.y - 12.0f),
 maxTexto);
 }
 }
 
 if(isPlayerIdent) {
 if(caido && EspCaidos) {
 if(isPlayerName){
 esp.DrawText(Color(CaidoColor), 0.6f,
 nulls.c_str(),
 Vector3(PlayerRect.x + (PlayerRect.width / 2), PlayerRect.y - 12.0f),
 maxTexto);
 }else{
 esp.DrawText(Color(CaidoColor), 0.6f,
 nulls.c_str(),
 Vector3(PlayerRect.x + (PlayerRect.width / 2), PlayerRect.y - 12.0f),
 maxTexto);
 }
 
 } else {
 if(isPlayerName){
 esp.DrawText(Color(EspColor), 0.6f,
 dnames.c_str(),
 Vector3(PlayerRect.x + (PlayerRect.width / 2), PlayerRect.y - 12.0f),
 maxTexto);
 }else{
 esp.DrawText(Color(EspColor), 0.6f,
 indetifiq.c_str(),
 Vector3(PlayerRect.x + (PlayerRect.width / 2), PlayerRect.y - 12.0f),
 maxTexto);
 }
 }
 }
 
 if(isPlayerHealth && isPlayerDist){
 dist =dist + " - " + vida;
 }
 
 if(isPlayerDist) {
 if(caido && EspCaidos) {
 esp.DrawText(Color(CaidoColor), 0.6, caidos.c_str(),
 Vector3(PlayerRect.x + (PlayerRect.width / 2),
 PlayerRect.y + PlayerRect.height + 12.5f), maxTexto);
 }else{
 esp.DrawText(Color(EspColor), 0.6, dist.c_str(),
 Vector3(PlayerRect.x + (PlayerRect.width / 2),
 PlayerRect.y + PlayerRect.height + 12.5f), maxTexto);
 }
 }
 
 if(isPlayerHealth) {
 if(caido && EspCaidos) {
 if(isPlayerDist){
 esp.DrawText(Color(CaidoColor), 0.6f,
 caidos.c_str(),
 Vector3(PlayerRect.x + (PlayerRect.width / 2), PlayerRect.y + PlayerRect.height + 12.5f),
 maxTexto);
 }else{
 esp.DrawText(Color(CaidoColor), 0.6f,
 caidos.c_str(),
 Vector3(PlayerRect.x + (PlayerRect.width / 2), PlayerRect.y + PlayerRect.height + 12.5f),
 maxTexto);
 }
 } else {
 if(isPlayerDist){
 esp.DrawText(Color(EspColor), 0.6f,
 dist.c_str(),
 Vector3(PlayerRect.x + (PlayerRect.width / 2), PlayerRect.y + PlayerRect.height + 12.5f),
 maxTexto);
 }else{
 esp.DrawText(Color(EspColor), 0.6f,
 vida.c_str(),
 Vector3(PlayerRect.x + (PlayerRect.width / 2), PlayerRect.y + PlayerRect.height + 12.5f),
 maxTexto);
 }
 }
 }
 }
 }
 }
 }
 }
 }
 }
 }
 }
 

bool(*orig_Test)(void* _this); 
bool _Test(void* _this) { 
return false;
return orig_Test(_this);
}

void(*MatchMaking)(void* _this); 
void _MatchMaking(void* _this) { 
return;
return MatchMaking(_this);
}

bool(*FixGame)(void* _this);
bool _FixGame(void* _this) {
if (_this != NULL) {
return true; 
}
}

bool(*GetBlackList)(void* _this); 
bool _GetBlackList(void* _this) {
return false;
}

bool(*GetBlack)(void* _this); 
bool _GetBlack(void* _this) {
return true;
}

void(*AntBan)(void* _this);
void _AntBan(void* _this){
if (AntBan != NULL) {
return;
}
return AntBan(_this);
}

void(*ChanBypass)(void* _this);
void _ChanBypass(void* _this){
return;
return ChanBypass(_this);
}

bool(*Filedone)(void* _this);
bool _Filedone(void* _this){
return false;
}

bool(*AntiCrash)(void*_this, int value);
bool _AntiCrash(void*_this, int value){
if (_this != NULL) {
return 10000000;
return AntiCrash(_this, value);
}
}

bool(*Bypass)(void* _this);
bool _Bypass(void* _this){
return false;
}

void(*Yuim)(void* _this); 
void _Yuim(void* _this) { 
return;
return Yuim(_this);
}

void *hack_thread(void *) {
ProcMap il2cppMap;
do {
il2cppMap = KittyMemory::getLibraryMap("libil2cpp.so");
sleep(1);
} while (!il2cppMap.isValid());


/**/FastReload = MemoryPatch("libil2cpp.so",0x18062e0,"\x16\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);//ok


/**/NoScope = MemoryPatch("libil2cpp.so",0x14fd8b0,"\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);//ok
// public virtual Boolean IsSightingUIAvailable() { }

/**/FreeWater = MemoryPatch("libil2cpp.so",0x149db48,"\x06\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);//ok
// public EPhysXState GetPhysXState() { }

/**/AutoJump = MemoryPatch("libil2cpp.so",0x46316fc,"\x01\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);//ok
// public override EPlayerRequestType GetRequestType() { }

/**/DriveSpeed = MemoryPatch::createWithHex("libil2cpp.so",0x2b1ba8c,"C8 02 44 E3 1E FF 2F E1");//ok
// public Single get_DriveSpeedScale() { }

/**/WhiteBody1 = MemoryPatch("libil2cpp.so", 0x10ae4cc, "\x01\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
/**/WhiteBody2 = MemoryPatch("libil2cpp.so", 0x442cdf0, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);

/**/Blackbody = MemoryPatch::createWithHex("libil2cpp.so", 0x5ab1b78, "01 00 A0 E3 1E FF 2F E1");//ok
/**/Ultimateammo = MemoryPatch::createWithHex("libil2cpp.so", 0x1b86eb4, "01 00 A0 E3 1E FF 2F E1");//ok
/**/DiamondHack = MemoryPatch::createWithHex("libil2cpp.so", 0x3471100, "99 05 A0 E3 1E FF 2F E1");//ok
/**/GoldHack = MemoryPatch::createWithHex("libil2cpp.so", 0x34710f0, "99 05 A0 E3 1E FF 2F E1");//ok

/**/ResetGuest = MemoryPatch::createWithHex("libil2cpp.so", 0x5316084, "01 00 A0 E3 1E FF 2F E1");//ok

/**/GetVBadge = MemoryPatch("libil2cpp.so",0x47706e4,"\x01\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);//ok



// AimBot
HOOK_LIB(0x14cce98, _Update, Update);//ok
HOOK_LIB(0x14dee2c, _LateUpdate, LateUpdate);//ok

HOOK_LIB(0x2ab428c, _UpdateLine, UpdateLine);//ok
HOOK_LIB(0x2ab51f0, _UpdateLine, UpdateLine);// private Void Update() { }

// Speed Jump
HOOK_LIB(0x2b1918c, _GetSpecialRunSpeedScale, GetSpecialRunSpeedScale);//
HOOK_LIB(0x1557ed8, _GetSpecialRunJumpScale, GetSpecialRunJumpScale);//

// Drive Skill
HOOK_LIB(0x6945d2c, hook_Vehicle, orig_Vehicle);//
HOOK_LIB(0x6d5d6a4, _SpeedCar, SpeedCar);//
// private Void LateUpdate() { }   |  Class: UIScrollView


//HOOK_LIB(address.TakeDamage, hook_TakeDamage1, orig_TakeDamage1);

// Ghost Guest
HOOK_LIB(0x1f4cf40, _Ghost, Ghost);// private Boolean NeedSendMessage(Player player) { }

// FlyPlayer
HOOK_LIB(address.UpdateFly, _UpdateFly, UpdateFly);//
HOOK_LIB(address.orig_GetPhysXPoseNEW, hook_GetPhysXPoseNEW, orig_GetPhysXPoseNEW);//
HOOK_LIB(address.orig_GetPhysXPose, hook_GetPhysXPose, orig_GetPhysXPose);//
HOOK_LIB(address.GetPhysXState, _GetPhysXState, GetPhysXState);//
HOOK_LIB(address.GetPhysXState2, _GetPhysXState2, GetPhysXState2);
HOOK_LIB(address.orig_get_IsPoseFallingHigh, hook_IsPoseFallingHigh, orig_get_IsPoseFallingHigh);
HOOK_LIB(address.orig_IsIgnoreHighFalling, hook_IsIgnoreHighFalling, orig_IsIgnoreHighFalling);
HOOK_LIB(address.OnStopCatapultFalling, _OnStopCatapultFalling, OnStopCatapultFalling_);

// AimKill
//HOOK_LIB(0x188c654, DamageInfoHook, DamageInfo);
HOOK_LIB(address.orig_get_InFallingState, get_InFallingState, orig_get_InFallingState);//
HOOK_LIB(address.switchbellara, _SwitchFast, switchbellara);//

Damage = MemoryPatch("libil2cpp.so", 0x19e4050,"\x01\x00\xA0\xE3\x1E\xFF\x2F\xE1",8);
AimMovement = MemoryPatch("libil2cpp.so",0x14eb2d4, "\x01\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);
/**/Medikit = MemoryPatch("libil2cpp.so",0x3e5e3c4,"\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);//
/**/Medikit2 = MemoryPatch("libil2cpp.so",0x146db54,"\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);//

/*1.105*HOOK_LIB(0x1425220, _ChanBypass, ChanBypass);//public static void StartLogGameLag() { }
/*1.105*HOOK_LIB(0x1425bcc, _ChanBypass, ChanBypass);//public static void SendGameLagLog() { }

/// FixGame
*
MemoryPatch("libil2cpp.so", 0x15d4c08, "00 00 A0 E3 1E FF 2F E1", 4).Modify(); //[1.94] public bool IsBypassed(Uri host) { }

        MemoryPatch("libil2cpp.so", 0x1f7a104, "40 0F 43 E3 1E FF 2F E1", 4).Modify(); //[1.94] public bool IsBypassed(Uri host) { }
        MemoryPatch("libil2cpp.so", 0x17cd2a8, "00 00 00 00", 4).Modify(); //[1.94] public bool IsBypassed(Uri host) { }
        
        
        
   MemoryPatch::createWithHex("libil2cpp.so", 0x56c3b6c + 116, "00 F0 20 E3", 4).Modify();
    MemoryPatch::createWithHex("libil2cpp.so", 0x5111c10 + 136, "00 F0 20 E3", 4).Modify();
                
    MemoryPatch::createWithHex("libil2cpp.so", 0X3450EB8 + 116, "00 F0 20 E3", 4).Modify();
    MemoryPatch::createWithHex("libil2cpp.so", 0x4886848 + 136, "00 F0 20 E3", 4).Modify();
    
    
    
        
MSHookFunction((void *)getRealOffset(0x179dab8), (void *)_Test, (void **)&orig_Test); // private Void DetectAndroidApplications() { }
MSHookFunction((void *)getRealOffset(0x6025d98), (void *)_MatchMaking, (void **)&MatchMaking); //public static bool IsInstanceOf(IntPtr obj, IntPtr clazz) { }
MSHookFunction((void *)getRealOffset(0x179acb8), (void *)_Test, (void **)&orig_Test); // private Void ProcessANOGGP(LoginRes loginRes, (void **)&MajorLoginRes majorRes) { }
MSHookFunction((void *)getRealOffset(0x521f4f0), (void *)_Test, (void **)&orig_Test); // public static Byte[] IIHDEHLHKEC(String LODDOINFPPA) { }
MSHookFunction((void *)getRealOffset(0x46f4574), (void *)_Test, (void **)&orig_Test);// public static Void DPLMGOJKKCM(Int32 EFDAAJBHMPD) { }
MSHookFunction((void *)getRealOffset(0x510cc1c), (void *)_Test, (void **)&orig_Test); // public static Byte[] LHAJPJBCOLC(String IDNEFEOPGIF) { }
MSHookFunction((void *)getRealOffset(0x510c0c0), (void *)_Test, (void **)&orig_Test); // public static void CCNEAFOPMIH(string DJKDKPMGKGH, string[] CLFFPBABFLP) { }

MSHookFunction((void *)getRealOffset(0x46f42d4), (void *)_Bypass, (void **)&Bypass); // public static void CCNEAFOPMIH(string DJKDKPMGKGH, string[] CLFFPBABFLP) { }

    MSHookFunction((void *)getRealOffset(0x46f4578), (void *)_AntiCrash, (void **)&AntiCrash);
    MSHookFunction((void *)getRealOffset(0x1105908), (void *)_AntiCrash, (void **)&AntiCrash);
    MSHookFunction((void *)getRealOffset(0x510bf70), (void *)_AntiCrash, (void **)&AntiCrash);
    MSHookFunction((void *)getRealOffset(0x510c0c0), (void *)_AntiCrash, (void **)&AntiCrash);
    MSHookFunction((void *)getRealOffset(0x179dab8), (void *)_AntiCrash, (void **)&AntiCrash);
    MSHookFunction((void *)getRealOffset(0x347ac80), (void *)_AntiCrash, (void **)&AntiCrash);
    MSHookFunction((void *)getRealOffset(0x1598910), (void *)_AntiCrash, (void **)&AntiCrash);
    MSHookFunction((void *)getRealOffset(0x1598ac8), (void *)_AntiCrash, (void **)&AntiCrash);
    MSHookFunction((void *)getRealOffset(0x159d224), (void *)_AntiCrash, (void **)&AntiCrash);
    MSHookFunction((void *)getRealOffset(0x1589914), (void *)_AntiCrash, (void **)&AntiCrash);
    MSHookFunction((void *)getRealOffset(0x431c734), (void *)_AntiCrash, (void **)&AntiCrash);
    
    MSHookFunction((void *)getRealOffset(0x4aaae48), (void *)_AntiCrash, (void **)&AntiCrash);
    MSHookFunction((void *)getRealOffset(0x19e33a8), (void *)_AntiCrash, (void **)&AntiCrash);
    MSHookFunction((void *)getRealOffset(0x19e3860), (void *)_AntiCrash, (void **)&AntiCrash);
    
    
MemoryPatch::createWithHex("libil2cpp.so", 0x46f4578, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libil2cpp.so", 0x1105908, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libil2cpp.so", 0x510bf70, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libil2cpp.so", 0x510c0c0, "00 00 A0 E3 1E FF 2F E1").Modify();


// Fix band team 4 Done
MSHookFunction((void *)getRealOffset(0x1588af4), (void *)_Yuim, (void **)&Yuim);
MSHookFunction((void *)getRealOffset(0x1589c7c), (void *)_Yuim, (void **)&Yuim);
MSHookFunction((void *)getRealOffset(0x158a1b0), (void *)_Yuim, (void **)&Yuim); 
MSHookFunction((void *)getRealOffset(0x1598910), (void *)_Yuim, (void **)&Yuim);
MSHookFunction((void *)getRealOffset(0x1598c40), (void *)_Yuim, (void **)&Yuim);
MSHookFunction((void *)getRealOffset(0x15b6dc8), (void *)_Yuim, (void **)&Yuim);
MSHookFunction((void *)getRealOffset(0x15eb3e4), (void *)_Yuim, (void **)&Yuim);
MSHookFunction((void *)getRealOffset(0x3938cd8), (void *)_Yuim, (void **)&Yuim); 
MSHookFunction((void *)getRealOffset(0x3939970), (void *)_Yuim, (void **)&Yuim);
MSHookFunction((void *)getRealOffset(0x522a2c4), (void *)_Yuim, (void **)&Yuim);
MSHookFunction((void *)getRealOffset(0x522a41c), (void *)_Yuim, (void **)&Yuim); 
MSHookFunction((void *)getRealOffset(0x522a6fc), (void *)_Yuim, (void **)&Yuim); 
MSHookFunction((void *)getRealOffset(0x522a798), (void *)_Yuim, (void **)&Yuim);

///_&&&&_&

MSHookFunction((void *)getRealOffset(0x52cd5c0), (void *)_Yuim, (void **)&Yuim);//public Void .ctor() { }
MSHookFunction((void *)getRealOffset(0x431ef30), (void *)_Yuim, (void **)&Yuim);//private static Void .cctor() { }
MSHookFunction((void *)getRealOffset(0x431ed98), (void *)_Yuim, (void **)&Yuim);//public Void .ctor() { }
/*
MSHookFunction((void *)getRealOffset(0x431ea6c), (void *)_GetBlackList, (void **)&GetBlackList);//public static Int32 ReportUserAudio(String reportUserID, String customData) { }
MSHookFunction((void *)getRealOffset(0x431e8d4), (void *)_GetBlackList, (void **)&GetBlackList);//public static Int32 SetReportInfo(Int32 nTimeSec, String language) { }
MSHookFunction((void *)getRealOffset(0x431ca30), (void *)_GetBlackList, (void **)&GetBlackList);//public static Int32 JoinRoom(RoomInfo info) { }
MSHookFunction((void *)getRealOffset(0x431cbb4), (void *)_GetBlackList, (void **)&GetBlackList);//public static Void OnJoined(String room_id) { }
MSHookFunction((void *)getRealOffset(0x2eb74b4), (void *)_GetBlackList, (void **)&GetBlackList);//public Void Update(Single gameTime) { }

/*
        // RVA: 0x52cd5c0 VA: 0xb7c545c0
        public Void .ctor() { }
    
        // RVA: 0x51d8608 VA: 0xb7b5f608
        public static String EAFJGAEHOGK(Boolean KOPAFJHCIIM) { }
    
        // RVA: 0x51d8070 VA: 0xb7b5f070
        public static String DGFDEECPIDP() { }
    
        // RVA: 0x431ef30 VA: 0xb6ca5f30
        private static Void .cctor() { }
    
        // RVA: 0x431ed98 VA: 0xb6ca5d98
        public static Int32 SetVoiceReciver(String roomId, String userList) { }
    
        // RVA: 0x431ec04 VA: 0xb6ca5c04
        public static Void SetUserVolume(String userId, UInt32 volume) { }
    
        // RVA: 0x431ea6c VA: 0xb6ca5a6c
        public static Int32 ReportUserAudio(String reportUserID, String customData) { }
    
        // RVA: 0x431e8d4 VA: 0xb6ca58d4
        public static Int32 SetReportInfo(Int32 nTimeSec, String language) { }
    
        // RVA: 0x431e5c0 VA: 0xb6ca55c0
        public static Int32 MuteTargetPlayer(String player_id, Boolean is_mute) { }
    
        // RVA: 0x431e440 VA: 0xb6ca5440
        public static Void EnableVoiceCaptureCallBack(Boolean enable) { }
    
        // RVA: 0x431e2c8 VA: 0xb6ca52c8
        public static Void OnUpdate() { }
    
        // RVA: 0x431de58 VA: 0xb6ca4e58
        public static Void SetMicAndSpeakerMute(Boolean micro_mute, Boolean speaker_mute) { }
    
        // RVA: 0x431dcd0 VA: 0xb6ca4cd0
        public static Boolean IsSameWithCurSpeakerMute(Boolean value) { }
    
        // RVA: 0x431db48 VA: 0xb6ca4b48
        public static Boolean IsSameWithCurMicMute(Boolean value) { }
    
        // RVA: 0x431d9c8 VA: 0xb6ca49c8
        public static Void SetVolume(UInt32 volume) { }
    
        // RVA: 0x431d804 VA: 0xb6ca4804
        public static String ParseErrorCodeName(Int32 error_code) { }
    
        // RVA: 0x431d640 VA: 0xb6ca4640
        public static String ParseEventName(Int32 event_id) { }
    
        // RVA: 0x431d4a8 VA: 0xb6ca44a8
        public static EGameVoiceEvent ParseEventType(Int32 event_id, String param) { }
    
        // RVA: 0x431d324 VA: 0xb6ca4324
        public static Boolean HasError(Int32 error_code) { }
    
        // RVA: 0x431d1a8 VA: 0xb6ca41a8
        public static Int32 UnInit() { }
    
        // RVA: 0x431d030 VA: 0xb6ca4030
        public static Void SetMicCallback() { }
    
        // RVA: 0x431ceb0 VA: 0xb6ca3eb0
        public static Void PauseChannel(Boolean is_pause) { }
    
        // RVA: 0x431cd34 VA: 0xb6ca3d34
        public static Int32 LeaveRoom() { }
    
        // RVA: 0x431cbb4 VA: 0xb6ca3bb4
        public static Void OnJoined(String room_id) { }
    
        // RVA: 0x431ca30 VA: 0xb6ca3a30
        public static Int32 JoinRoom(RoomInfo info) { }
    
        // RVA: 0x431c8b8 VA: 0xb6ca38b8
        public static Void OnInited() { }
    
        // RVA: 0x431c734 VA: 0xb6ca3734
        public static Int32 Init(String callBack_objectName) { }
    
        // RVA: 0x431c5b4 VA: 0xb6ca35b4
        public static Void SetExtraConfig(Object extra_config) { }
    
        // RVA: 0x431c420 VA: 0xb6ca3420
        public static Void SetAppkeySecret(String appKey, String appSecret) { }
    
        // RVA: 0x431c28c VA: 0xb6ca328c
        public static Void SetRegion(Int32 region_id, String region_name) { }
    
        // RVA: 0x431c10c VA: 0xb6ca310c
        public static Void SetGroupEnvironment(String environment) { }
    
        // RVA: 0x431c04c VA: 0xb6ca304c
        public static Void SetImpl(IGameVoiceInterface impl) { }
    
        // RVA: 0x431be7c VA: 0xb6ca2e7c
        public static GameVoiceImpl_FreeFireVoice get_FreeFireVoiceImpl() { }
    
        // RVA: 0x4319da4 VA: 0xb6ca0da4
        public static Int32 setUTData(String utData) { }
    
        // RVA: 0x2eb74b4 VA: 0xb583e4b4
        public Void Update(Single gameTime) { }
    
    
    
    
    


MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x4b7b2c0), (void *)_FixGame, (void **)&FixGame);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x488d7d0), (void *)_FixGame, (void **)&FixGame);//ok

MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x62cbb24), (void *)_FixGame, (void **)&FixGame);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x579326c), (void *)_FixGame, (void **)&FixGame);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x5712280), (void *)_FixGame, (void **)&FixGame);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x5714dcc), (void *)_FixGame, (void **)&FixGame);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x5714c94), (void *)_FixGame, (void **)&FixGame);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x60806f4), (void *)_FixGame, (void **)&FixGame);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x6080148), (void *)_FixGame, (void **)&FixGame);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x60801f4), (void *)_FixGame, (void **)&FixGame);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x4acea14), (void *)_FixGame, (void **)&FixGame);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x1502c30), (void *)_FixGame, (void **)&FixGame);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x1501d2c), (void *)_FixGame, (void **)&FixGame);//ok

MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x1705a90), (void *)_FixGame, (void **)&FixGame);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x1704a94), (void *)_FixGame, (void **)&FixGame);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x1706ee8), (void *)_FixGame, (void **)&FixGame);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x545b7f8), (void *)_FixGame, (void **)&FixGame);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x530e9b8), (void *)_FixGame, (void **)&FixGame);//ok

MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x4911d80), (void *)_GetBlackList, (void **)&GetBlackList);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x64a7a40), (void *)_GetBlackList, (void **)&GetBlackList);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x488d920), (void *)_GetBlackList, (void **)&GetBlackList);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x3be2e50), (void *)_GetBlackList, (void **)&GetBlack);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x3be32f8), (void *)_GetBlackList, (void **)&GetBlack);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x3be36e8), (void *)_GetBlackList, (void **)&GetBlack);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x3be3b50), (void *)_GetBlackList, (void **)&GetBlack);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x47e3020), (void *)_GetBlackList, (void **)&GetBlack);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x542a8c8), (void *)_GetBlackList, (void **)&GetBlack);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x176fee0), (void *)_GetBlackList, (void **)&GetBlack);//ok
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x15d3e88), (void *)_GetBlack, (void **)&GetBlack);//ok
/*MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x64265c8), (void *)_GetBlackList, (void **)&GetBlack);//
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x6426680), (void *)_GetBlack, (void **)&GetBlack);//
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x6427200), (void *)_AntBan, (void **)&AntBan);//
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x563e820), (void *)_AntBan, (void **)&AntBan);//
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x56c60f4), (void *)_AntBan, (void **)&AntBan);//
MSHookFunction((void *)AgetAbsoluteAddress("libil2cpp.so", 0x4b7b2b8), (void *)_AntBan, (void **)&AntBan);//ok


HOOK_LIB(0x17824a8,_Test, orig_Test); // private Void DetectAndroidApplications() { }
HOOK_LIB(0x64a7a40,_MatchMaking, MatchMaking); //public static bool IsInstanceOf(IntPtr obj, IntPtr clazz) { }
HOOK_LIB(0x177f5c4,_Test, orig_Test); // private Void ProcessANOGGP(LoginRes loginRes, MajorLoginRes majorRes) { }
HOOK_LIB(0x550ddb4,_Test, orig_Test); // public static Byte[] IIHDEHLHKEC(String LODDOINFPPA) { }
*/
return NULL;
}

extern "C" 
JNIEXPORT void JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_DrawOn(JNIEnv *env, jclass type, jobject espView, jobject canvas) {
espOverlay = ESP(env, espView, canvas);
if (espOverlay.isValid()){
DrawESP(espOverlay, espOverlay.getWidth(), espOverlay.getHeight());
}
}


JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
JNIEnv *globalEnv;
vm->GetEnv((void **) &globalEnv, JNI_VERSION_1_6);
pthread_t ptid;
pthread_create(&ptid, NULL, hack_thread, NULL);
return JNI_VERSION_1_6;
}
