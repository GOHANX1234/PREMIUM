#ifndef ANDROID_MOD_MENU_HOOK_H
#define ANDROID_MOD_MENU_HOOK_H

#include "Global.h"
#include <sys/syscall.h>
using namespace std;
#include <string>
#include <sstream>
#include <iostream>
#include<sstream>
#define HOOK(offset, ptr, orig)
# define getRealOffset(offset) AgetAbsoluteAddress("libil2cpp.so",offset)
long AfindLibrary(const char *library) {
    char filename[0xFF] = {0},
            buffer[1024] = {0};
    FILE *fp = NULL;
    long address = 0;

    sprintf( filename, "/proc/self/maps");

    fp = fopen( filename, "rt" );
    if( fp == NULL ){
        perror("fopen");
        goto done;
    }

    while( fgets( buffer, sizeof(buffer), fp ) ) {
        if(strstr( buffer, library ) ){
            address = (long)strtoul( buffer, NULL, 16 );
            goto done;
        }
    }

    done:

    if(fp){
        fclose(fp);
    }

    return address;
}

long ClibBase;

long AgetAbsoluteAddress(const char* libraryName, long relativeAddr) {
    if (ClibBase == 0) {
        ClibBase = AfindLibrary(libraryName);
        if (ClibBase == 0) {
            ClibBase = 0;
        }
    }
    return ClibBase + relativeAddr;
}

class Vvector3 {
public:
    float X;
    float Y;
    float Z;
    Vvector3() : X(0), Y(0), Z(0) {}
    Vvector3(float x1, float y1, float z1) : X(x1), Y(y1), Z(z1) {}
    Vvector3(const Vvector3 &v);
    ~Vvector3();
};
Vvector3::Vvector3(const Vvector3 &v) : X(v.X), Y(v.Y), Z(v.Z) {}
Vvector3::~Vvector3() {}

static void *GetLocalPlayer2(void* Match) {
    void *(*_GetLocalPlayer2)(void *match) = (void *(*)(void *))getRealOffset(address.GetLocalPlayer);
    return _GetLocalPlayer2(Match);
}

static Vector3 GetAttackableCenterWS(void *player) {
    Vector3 (*_GetAttackableCenterWS)(void *players) = (Vector3 (*)(void *))getRealOffset(address.GetAttackableCenterWS);
    return _GetAttackableCenterWS(player);
}

static bool IsLocalTeammate(void *player) {
    bool (*_IsLocalTeammate)(void *players) = (bool (*)(void *))getRealOffset(address.IsLocalTeammate);
    return _IsLocalTeammate(player);
}

static bool get_IsDieing(void *player) {
    bool (*_get_IsDieing)(void *players) = (bool (*)(void *))getRealOffset(address.get_IsDieing);
    return _get_IsDieing(player);
}

static int get_MaxHP(void* enemy) {
    int (*_get_MaxHP)(void* player) = (int(*)(void *))getRealOffset(address.get_MaxHP);
    return _get_MaxHP(enemy);
}

static bool IsFiring(void *player) {
    bool (*_IsFiring)(void *players) = (bool (*)(void *))getRealOffset(address.IsFiring);
    return _IsFiring(player);
}

static bool get_IsSighting(void *player) {
    bool (*_get_IsSighting)(void *players) = (bool (*)(void *))getRealOffset(address.get_IsSighting);
    return _get_IsSighting(player);
}

static bool IsVisible(void *player) {
    bool (*_IsVisible)(void *players) = (bool (*)(void *))getRealOffset(address.IsVisible);
    return _IsVisible(player);
}

static Vector3 get_forward(void *player) {
    Vector3 (*_get_forward)(void *players) = (Vector3 (*)(void *))getRealOffset(address.get_forward);
    return _get_forward(player);
}

static Vector3 get_position_Injected(void *player) {
    Vector3 out = Vector3::Zero();
    void (*_get_position_Injected)(void *transform, Vector3 * out) = (void (*)(void *, Vector3 *))getRealOffset(address.get_position_Injected);
    _get_position_Injected(player, &out);
    return out;
}

static void SetAimRotation(void *player, Quaternion look) {
    void (*_SetAimRotation)(void *players, Quaternion lock) = (void (*)(void *, Quaternion))getRealOffset(address.SetAimRotation);
    _SetAimRotation(player, look);
}

static void set_position_Injected(void *player, Vvector3 inn) {
    void (*_set_position_Injected)(void *transform, Vvector3 in) = (void (*)(void *, Vvector3))getRealOffset(address.set_position_Injected);
    _set_position_Injected(player, inn);
}

static void *get_transform(void *player) {
    void *(*_get_transform)(void *component) = (void *(*)(void *))getRealOffset(address.get_transform);
    return _get_transform(player);
}

static void *get_main() {
    void *(*_get_main)(void *nuls) = (void *(*)(void *))getRealOffset(address.get_main);
    return _get_main(nullptr);
}

static void *CurrentMatch() {
    void *(*_CurrentMatch) (void *nuls) = (void *(*)(void *))getRealOffset(address.CurrentMatch);
    return _CurrentMatch(NULL);
}

static int get_CurHP(void* player) {
    int (*_get_CurHP)(void* players) = (int(*)(void *))getRealOffset(address.get_CurHP);
    return _get_CurHP(player);
}

static Vector3 WorldToScreenPoint(void *WorldCam, Vector3 WorldPos) {
    Vector3 (*_WorldToScreenPoint)(void* Camera, Vector3 position) = (Vector3 (*)(void*, Vector3)) getRealOffset(address.WorldToScreenPoint);
    return _WorldToScreenPoint(WorldCam,WorldPos);
}

static bool Physics_Raycast(Vector3 camLocation, Vector3 headLocation, unsigned int LayerID, void* collider) {
    bool (*_Physics_Raycast)(Vector3 camLocation, Vector3 headLocation, unsigned int LayerID, void* collider) = (bool(*)(Vector3, Vector3, unsigned int, void*))getRealOffset(address.Physics_Raycast);
    return _Physics_Raycast(camLocation, headLocation, LayerID, collider);
}

static void *get_HeadCollider(void *player){
    void *(*_get_HeadCollider)(void *players) = (void *(*)(void *))getRealOffset(address.get_HeadCollider);
    return _get_HeadCollider(player);
}

static monoString* get_NickName(void *player) {
    monoString* (*_get_NickName)(void *players) = (monoString * (*)(void *))getRealOffset(address.get_NickName);
    return _get_NickName(player);
}

static monoString *CreateString(const char *str) {
    monoString *(*_CreateString)(void *_this, const char *str) = (monoString * (*)(void *, const char *))getRealOffset(address.CreateString);
    return _CreateString(NULL, str);
}

static void *CurrentUIScene() {
    void *(*_CurrentUIScene)(void *nuls) = (void *(*)(void *))getRealOffset(address.CurrentUIScene);
    return _CurrentUIScene(NULL);
}

static monoString *U3DStrFormat(float distance) {
    char buffer[128] = {0};
    sprintf(buffer, "%.2f M", distance);
    return CreateString(buffer);
}


//grenda



static void *get_imo(void *player) {
    void *(*_get_imo)(void *players) = (void *(*)(void *))getRealOffset(address.get_imo);
    return _get_imo(player);
}

static void set_esp(void *imo, Vector3 x, Vector3 y) {
    void (*_set_esp)(void *imo, Vector3 X, Vector3 Y) = (void (*)(void *, Vector3, Vector3))getRealOffset(address.set_esp);
    _set_esp(imo, x, y);
}

static void set_esp2(void *imo, Vector3 x, Vector3 y) {
    void (*_set_esp2)(void *imo, Vector3 X, Vector3 Y) = (void (*)(void *, Vector3, Vector3))getRealOffset(address.set_esp2);
    _set_esp2(imo, x, y);
}

static void *VehicleIAmIn(void *playerCar) {
    void *(*_VehicleIAmIn)(void *Player) = (void *(*)(void *))getRealOffset(address.VehicleIAmIn);
    return _VehicleIAmIn(playerCar);
}

static bool get_IsDriver(void *player) {
    bool (*_get_IsDriver)(void *players) = (bool (*)(void *))getRealOffset(address.get_IsDriver);
    return _get_IsDriver(player);
}

static monoString *FormatCount(int enemy, int bot) {
    char buf[128] = {};
    sprintf(buf, "[ Players %d | Bots %d ]", enemy, bot);
    return CreateString(buf);
}

static bool get_Crhp(void *player) {
    bool (*_get_Crhp)(void *players) = (bool (*)(void *))getRealOffset(address.get_MaxHP);
    return _get_Crhp(player);
}

static bool IsCatapultFalling(void *player) {
    bool (*_IsCatapultFalling)(void *players) = (bool (*)(void *))getRealOffset(address.IsCatapultFalling);
    return _IsCatapultFalling(player);
}

static void OnStopCatapultFalling(void *player) {
    void (*_OnStopCatapultFalling)(void *players) = (void (*)(void *))getRealOffset(address.OnStopCatapultFalling);
    return _OnStopCatapultFalling(player);
}

static void *get_MyPhsXData(void *player) {
    void *(*_get_MyPhsXData)(void *component) = (void *(*)(void *))getRealOffset(address.get_MyPhsXData);
    return _get_MyPhsXData(player);
}

static void *GetLocalVehicle(void* local) {
    void *(*_GetLocalVehicle)(void * player) = (void *(*)(void *))getRealOffset(address.VehicleIAmIn);
    return _GetLocalVehicle(local);
}

static bool get_IsPassenger(void * Pass) {
    bool (*_get_IsPassenger)(void * pass) = (bool (*)(void *))getRealOffset(address.get_IsPassenger);
    return _get_IsPassenger(Pass);
}

char get_Chars(monoString *str, int index) {
    char (*_get_Chars)(monoString *str, int index) = (char (*)(monoString *, int))getRealOffset(address.get_Chars);
    return _get_Chars(str, index);
}

static void ShowAssistantText(void *player, monoString *nick, monoString *grup) {
    void (*_ShowAssistantText)(void *players, monoString * nicks, monoString * nickss) = (void (*)(void *, monoString *, monoString *))getRealOffset(address.ShowAssistantText);
    void *ui = CurrentUIScene();
    if (ui != NULL) {
        _ShowAssistantText(player, nick, grup);
    }
}

static void LineRenderer_SetPosition(void *Render, int value, Vector3 Location){
    void (*_LineRenderer_SetPosition)(void *Render, int value, Vector3 Location) = (void (*)(void*, int, Vector3))getRealOffset(address.SetPosition);//
    return _LineRenderer_SetPosition(Render, value, Location);
}

static void LineRenderer_Set_PositionCount(void *Render, int value){
    void (*_LineRenderer_Set_PositionCount)(void *Render, int value) = (void (*)(void*, int))getRealOffset(address.Set_PositionCount);//
    return _LineRenderer_Set_PositionCount(Render, value);
}

static void GrenadeLine_DrawLine(void *instance, Vector3 start, Vector3 end, Vector3 position) {
    void (*_GrenadeLine_DrawLine)(void *clz, Vector3 throwPos, Vector3 throwVel, Vector3 gravity) = (void (*)(void*, Vector3, Vector3,Vector3)) getRealOffset(address.DrawLine2);//
    return _GrenadeLine_DrawLine(instance, start, end, position);
}

void *Grenade2 = NULL;
void *Render2 = NULL;

void (*UpdateLine)(void *instance);
void _UpdateLine(void *instance) {
    if (instance != NULL) {
    Grenade2 = instance;
    *(bool *)((uintptr_t)instance + 0x14) = true;//m_ShowGrenadeLine
    Render2 = *(void **)((long)instance + 0x18);//LineRenderer m_GrenadeLine
 }
    UpdateLine(instance);
}

static void SwapWeapon(void* player, int POFFNNMOOBM, bool GDKLMFLNNGM) {
    void (*_SwapWeapon)(void* player, int POFFNNMOOBM, bool GDKLMFLNNGM) = (void (*)(void *, int, bool))getRealOffset(address.SwapWeapon);
     _SwapWeapon(player, POFFNNMOOBM, GDKLMFLNNGM);
}


struct COW_GamePlay_MKFEKBKJCKE_o;
struct COW_GamePlay_IHAAMHPPLMG_o {
    uint32_t NBPDJAAAFBH;
    uint32_t JEDDPHIHGKL;
    uint8_t IOICFFEKAIL;
    uint8_t PHAFNFOFFDB;
    uint64_t BNFAIDHEHOM;
};

static void *Current_Local_Player() {
    void *(*_Local_Player)(void *players) = (void *(*)(void *))getRealOffset(address.Current_Local_Player);//
    return _Local_Player(NULL);
}

static void* PlayerWeaponOnHand(void* Player){
    void*(*WeaponOnHand)(void*) = (void*(*)(void*))getRealOffset(address.GetWeaponOnHand);//
    return WeaponOnHand(Player);
}

static int GetWeapon(void* enemy) {
    int (*GetWeapon)(void *player) = (int(*)(void *))getRealOffset(address.GetWeaponType);//
    return GetWeapon(enemy);
}

static int32_t LateKillUpdate(void *_this, int32_t KOCMLPLOILD,COW_GamePlay_IHAAMHPPLMG_o HLJDHPGGODB, void* DamageInfo, int32_t BOEIBGAABDL, Vector3 NJMFBKNHMBP, Vector3 DOBOBMFMKBJ, monoList<float> NBKBEBFNDBE, COW_GamePlay_MKFEKBKJCKE_o* damagerWeaponDynamicInfo, uint32_t damagerVehicleID) {
    return ((int32_t (*)(void*, int32_t, COW_GamePlay_IHAAMHPPLMG_o, void*, int32_t, Vector3, Vector3, monoList<float>, COW_GamePlay_MKFEKBKJCKE_o*, uint32_t))getRealOffset(address.TakeDamage))(_this, KOCMLPLOILD, HLJDHPGGODB, DamageInfo, BOEIBGAABDL, NJMFBKNHMBP, DOBOBMFMKBJ, NBKBEBFNDBE, damagerWeaponDynamicInfo, damagerVehicleID);
}

static void *StartWholeBodyFiring(void* Player,void* WeaponOnHand){
    void *(*_StartWholeBodyFiring)(void*,void*) = (void*(*)(void*,void*))getRealOffset(address.StartWholeBodyFiring);//
    return _StartWholeBodyFiring(Player,WeaponOnHand);
}

static void *StopFire(void* Player,void* WeaponOnHand){
    void *(*_StopFire)(void*,void*) = (void*(*)(void*,void*))getRealOffset(address.StopFire);//
    return _StopFire(Player,WeaponOnHand);
}

static void *StartFiring(void* Player,void* WeaponOnHand){
    void *(*_StartFiring)(void*,void*) = (void*(*)(void*,void*))getRealOffset(address.StartFiring);//
    return _StartFiring(Player,WeaponOnHand);
}

static bool get_isWatching(void *player) {
    bool (*_get_isWatching)(void *players) = (bool (*)(void *))getRealOffset(address.get_isWatching);//
    return _get_isWatching(player);
}

static COW_GamePlay_IHAAMHPPLMG_o get_PlayerID(void *retstr) {
    COW_GamePlay_IHAAMHPPLMG_o (*get_PlayerID)(void *retstr) = (COW_GamePlay_IHAAMHPPLMG_o (*)(void *))getRealOffset(address.GetPlayerID);//
    return get_PlayerID(retstr);
}


#endif
