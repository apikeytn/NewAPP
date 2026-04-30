
#include <map>
#include <vector>
#include <fstream>
#define FMT_HEADER_ONLY
#include "fmt/core.h"
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stdlib.h>
#include <chrono>
#import "menuUIKIT/Vars.h"
#include <chrono>
#include <fstream>
#include <string>

uintptr_t string2Offset(const char* hexStr) {
    return strtoull(hexStr, nullptr, 16);
}
typedef struct {
    void* methodPtr;
    void* invokerMethod;
} VirtualInvokeData;

typedef struct {
    void* data[32];
} Il2CppClass_1;

typedef struct {
    void* data[8]; 
} Il2CppClass_2;

#include <unordered_map> 
#include <float.h>  
#include <ctime>


bool aimkill92 = false;
int FlySpeed3 = {};
int FlyHack3 = {};

bool flyalt = false;
bool Noreload = false;
bool IgnoreBot = false;
bool IgnoreKnocked2 = false;

// ESP Color Selection (0=White, 1=Red, 2=Blue, 3=Green, 4=Pink)
int ESPLineColor = 0;
int ESPBoxColor = 0;
int ESPSkeletonColor = 0;
int ESPNameColor = 0;

// Aimbot FOV Color and Thickness
int AimbotFOVColor = 0;
float AimbotFOVThickness = 0.2f;

// Menu Color Theme (0=Red, 1=Blue, 2=Green, 3=Pink)
int MenuColorTheme = 0;




CGPoint pointOnBezierPath(UIBezierPath *path, CGFloat percent) {
    if (percent <= 0) return [path currentPoint];
    if (percent >= 1) {
        CGPoint points[3];
 
        return points[0];
    }
    

    
    CGPoint startPoint = CGPointMake(0, 0);
    CGPoint endPoint = CGPointMake(0, 0);
    
    CGRect bounds = path.bounds;
    startPoint = CGPointMake(bounds.origin.x, bounds.origin.y);
    endPoint = CGPointMake(bounds.origin.x + bounds.size.width, 
                          bounds.origin.y + bounds.size.height);
    
    return CGPointMake(startPoint.x + (endPoint.x - startPoint.x) * percent,
                      startPoint.y + (endPoint.y - startPoint.y) * percent);
}

CGPoint interpolatePoint(CGPoint start, CGPoint end, CGFloat progress) {
    return CGPointMake(start.x + (end.x - start.x) * progress,
                      start.y + (end.y - start.y) * progress);
}

bool Physics_Raycast(Vector3 OOFIJHADLNI, Vector3 CHGADBAMMOP, uint32_t ONEDHFJBCMJ, void **JEEIBOEGGPD)
{
    return ((bool (*)(Vector3, Vector3, uint32_t, void **))getRealOffset(ENCRYPTOFFSET("0x1046F7B08")))(OOFIJHADLNI, CHGADBAMMOP, ONEDHFJBCMJ, JEEIBOEGGPD);
}

#define OBFUSCATEOFFSET(x) ENCRYPTOFFSET(x)
#define OBFUSCATE(x) oxo(x)

std::unordered_map<void*, float> localOriginalY;
bool localCameraAdjusted = false;

 std::map<void *, std::vector<Vector3>> BacktrackMap;
std::map<void*, float> enemyOriginalY;
bool cameraAdjusted = false;


static Vector3 up() { 
    return Vector3(0, 1, 0); 
}

namespace Save {
    extern void* DamageInfo;
    extern clock_t AimDelay;
    extern const clock_t AimFPS; 
    const clock_t AimFPS_V6 = CLOCKS_PER_SEC / 5;
}
namespace Save {
    extern void* DamageInfo;
    extern clock_t AimDelay;
    extern const clock_t AimFPS;
     clock_t AimDelayV6 = 0;
}
bool playertakedamage001 = false;

float LastDamageTimeV10 = 0.0f;
float CooldownTimeV10 = 0.10f;
void* Save::DamageInfo = nullptr;

void DamageInfoHook(void* Player) {
    Save::DamageInfo = Player;
}
clock_t Save::AimDelay = 0;
const clock_t Save::AimFPS = CLOCKS_PER_SEC / 20;    
    


int TimerTakeDamageinit = 0;

float maxDistanceAimkill = 5000.0f;

bool force = false;
bool playertakedamage = false;
template <typename T>
class List {
public:
    void* klass;
    void* monitor;
    void* bounds;
    int32_t size;
    T* items;
};


 static Vector3 Direction(const Vector3& from, const Vector3& to) {
    Vector3 dir = { to.x - from.x, to.y - from.y, to.z - from.z };
    float len = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    if (len > 0.0001f) {
        dir.x /= len;
        dir.y /= len;
        dir.z /= len;
    }
    return dir;
}




void* GetHeadTF(void *player)
{
    return ((void* (*)(void *))getRealOffset(ENCRYPTOFFSET("0x1051C5228")))(player);
}

void* GetHipTF(void *player)
{
    return ((void* (*)(void *))getRealOffset(ENCRYPTOFFSET("0x1051C5378")))(player);
}












void *get_HeadCollider(void *pthis)
{
    return ((void* (*)(void *))getRealOffset(0x105144E64))(pthis);
}




bool IsClientBot(void* _this) { return *(bool*)((uint64_t)_this + 0x3D0); }





static void *CurentMatch() {
    void *(*_CurentMatch) (void *instance) = (void *(*)(void *))getRealOffset(ENCRYPTOFFSET("0x101283110")); 
    return _CurentMatch(NULL);
}



static void *GetLocalPlayer(void* Match) {
    void *(*_GetLoalPlayer)(void *match) = (void *(*)(void *))getRealOffset(ENCRYPTOFFSET("0x103FF6CD4")); 
    return _GetLoalPlayer(Match);
}

static void *Current_Local_Player() {
    void *(*_Local_Player)(void *players) = (void *(*)(void *))getRealOffset(ENCRYPTOFFSET("0x1012835E0"));
    return _Local_Player(NULL);
}






static monoString* U3DStr(const char* str) {
    monoString* (*String_CreateString)(void*, const char*) = (monoString* (*)(void*, const char*))getRealOffset(0x106180620);
    return String_CreateString(NULL, str);
}


static Vector3 Transform_INTERNAL_GetPosition(void *transform) {
    Vector3 out = Vector3::zero();
    void (*_GetPos)(void *, Vector3 *) = (void (*)(void *, Vector3 *))getRealOffset(oxo("0x105FE7D14"));
    _GetPos(transform, &out);
    return out;
}



static void Transform_INTERNAL_SetPosition(void *transform, Vvector3 in) {
    void (*_SetPos)(void *, Vvector3) = (void (*)(void *, Vvector3))getRealOffset(oxo("0x105FE7DB8"));
    _SetPos(transform, in);
}




static void* Camera_main() {
    void* (*_Camera_main)(void*) = (void* (*)(void*))getRealOffset(ENCRYPTOFFSET("0x105F9A79C"));
    return _Camera_main(nullptr);
}




// static Quaternion GetRotation(void* player) {
//     Quaternion (*_GetRotation)(void* players) = (Quaternion(*)(void *))getRealOffset(ENCRYPTOFFSET("0x104169FE4"));
//     return _GetRotation(player);
// }







class game_sdk_t
{
public:
    void init();
    int (*GetHp)(void *player);
bool (*get_IsCatapultFalling)(void *);
void (*OnStopCatapultFalling)(void *);


void* (*GetWeaponOnHand)(void*);
void (*StartWholeBodyFiring)(void*, void*);
void* (*GetLocalPlayer_Facade)();
void (*TakeDamage)(void*, void*);








    void *(*Curent_Match)();
    void *(*GetLocalPlayer)(void *Game);
    void *(*GetHeadPositions)(void *player);
    Vector3 (*get_position)(void *player);
    void *(*Component_GetTransform)(void *player);
    void *(*get_camera)();
    Vector3 (*WorldToScreenPoint)(void *, Vector3);
    bool (*get_isVisible)(void *player);
    bool (*get_isLocalTeam)(void *player);
    bool (*get_IsDieing)(void *player);
    int (*get_MaxHP)(void *player);
    Vector3 (*GetForward)(void *player);
    void (*set_aim)(void *player, Quaternion look);
    bool (*get_IsSighting)(void *player);
    bool (*get_IsFiring)(void *player);
    monoString *(*name)(void *player);



    void *(*_GetHeadPositions)(void *);
    void *(*_newHipMods)(void *);
    void *(*_GetLeftAnkleTF)(void *);
    void *(*_GetRightAnkleTF)(void *);
    void *(*_GetLeftToeTF)(void *);
    void *(*_GetRightToeTF)(void *);
    void *(*_getLeftHandTF)(void *);
    void *(*_getRightHandTF)(void *);
    void *(*_getLeftForeArmTF)(void *);
    void *(*_getRightForeArmTF)(void *);
};

game_sdk_t *game_sdk = new game_sdk_t();
void game_sdk_t::init()
{




  this->GetHp = (int (*)(void *))getRealOffset(oxo("0x1051AAF78"));
    this->Curent_Match = (void *(*)())getRealOffset(oxo("0x101283110"));
    this->GetLocalPlayer = (void *(*)(void *))getRealOffset(oxo("0x103FF6CD4"));
    this->GetHeadPositions = (void *(*)(void *))getRealOffset(oxo("0x1051C5228"));
    this->get_position = (Vector3(*)(void *))getRealOffset(oxo("0x105FE7CE4"));
    this->Component_GetTransform = (void *(*)(void *))getRealOffset(oxo("0x105F9CC54"));
    this->get_camera = (void *(*)())getRealOffset(oxo("0x105F9A79C"));
    this->WorldToScreenPoint = (Vector3(*)(void *, Vector3))getRealOffset(oxo("0x105F9A154"));
    this->get_isVisible = (bool (*)(void *))getRealOffset(oxo("0x10514A22C"));
    this->get_isLocalTeam = (bool (*)(void *))getRealOffset(oxo("0x10515FFFC"));
    this->get_IsDieing = (bool (*)(void *))getRealOffset(oxo("0x105133838"));
    this->get_MaxHP = (int (*)(void *))getRealOffset(oxo("0x1051AB020"));
    this->GetForward = (Vector3(*)(void *))getRealOffset(oxo("0x105FE8694"));
    this->set_aim = (void (*)(void *, Quaternion))getRealOffset(oxo("0x1051468F0"));
    this->get_IsSighting = (bool (*)(void *))getRealOffset(oxo("0x10513AA94"));
    this->get_IsFiring = (bool (*)(void *))getRealOffset(oxo("0x105135E20"));
    this->name = (monoString * (*)(void *player)) getRealOffset(oxo("0x105141C3C"));
  
    this->_GetHeadPositions = (void *(*)(void *))getRealOffset(oxo("0x1051C5228"));
    this->_newHipMods = (void *(*)(void *))getRealOffset(oxo("0x1051C5378"));
    this->_GetLeftAnkleTF = (void *(*)(void *))getRealOffset(oxo("0x1051C56AC"));
    this->_GetRightAnkleTF = (void *(*)(void *))getRealOffset(oxo("0x1051C5750"));
    this->_GetLeftToeTF = (void *(*)(void *))getRealOffset(oxo("0x1051C57F4"));
    this->_GetRightToeTF = (void *(*)(void *))getRealOffset(oxo("0x1051C5898"));
    this->_getLeftHandTF = (void *(*)(void *))getRealOffset(oxo("0x105145BD0"));
    this->_getRightHandTF = (void *(*)(void *))getRealOffset(oxo("0x105145C7C"));
    this->_getLeftForeArmTF = (void *(*)(void *))getRealOffset(oxo("0x105145D20"));
    this->_getRightForeArmTF = (void *(*)(void *))getRealOffset(oxo("0x105145DC4"));
}

namespace CameraUIKit {
    CGPoint Regular(Vector3 pos) {
        UIWindow *window = [UIApplication sharedApplication].keyWindow;
        if (!window) return CGPointZero;

        CGSize screenSize = window.bounds.size;
        void *camera = game_sdk->get_camera();
        if (!camera) return CGPointZero;

        Vector3 screen = game_sdk->WorldToScreenPoint(camera, pos);
        if (screen.z <= 1) return CGPointZero;

        return CGPointMake(screenSize.width * screen.x,
                           screenSize.height - screen.y * screenSize.height);
    }

    CGPoint Checker(Vector3 pos, BOOL &isVisible) {
        UIWindow *window = [UIApplication sharedApplication].keyWindow;
        if (!window) return CGPointZero;

        CGSize screenSize = window.bounds.size;
        void *camera = game_sdk->get_camera();
        if (!camera) return CGPointZero;

        Vector3 screen = game_sdk->WorldToScreenPoint(camera, pos);
        isVisible = screen.z > 1;

        return CGPointMake(screenSize.width * screen.x,
                           screenSize.height - screen.y * screenSize.height);
    }
}

Vector3 GetBonePosition(void *player, void *(*transformGetter)(void *))
{
    if (!player || !transformGetter)
        return Vector3(0, 0, 0);
    @try {
        void *transform = transformGetter(player);
        if (!transform) return Vector3(0, 0, 0);
        void *compTransform = game_sdk->Component_GetTransform(transform);
        if (!compTransform) return Vector3(0, 0, 0);
        Vector3 pos = game_sdk->get_position(compTransform);
        if (isnan(pos.x) || isnan(pos.y) || isnan(pos.z) ||
            isinf(pos.x) || isinf(pos.y) || isinf(pos.z)) {
            return Vector3(0, 0, 0);
        }
        return pos;
    } @catch (NSException *exception) {
        return Vector3(0, 0, 0);
    }
}

Vector3 getPosition(void *transform)
{
    return game_sdk->get_position(game_sdk->Component_GetTransform(transform));
}

static Vector3 GetHeadPosition(void *player)
{
    return game_sdk->get_position(game_sdk->GetHeadPositions(player));
}

static Vector3 GetNeckPosition(void *player) {
    Vector3 headPos = GetBonePosition(player, game_sdk->_GetHeadPositions);
    Vector3 chestPos = GetBonePosition(player, game_sdk->_newHipMods);
    // Neck is between head and chest, slightly closer to head
    if (headPos != Vector3::zero() && chestPos != Vector3::zero()) {
        return Vector3(
            headPos.x + (chestPos.x - headPos.x) * 0.2f,
            headPos.y + (chestPos.y - headPos.y) * 0.2f,
            headPos.z + (chestPos.z - headPos.z) * 0.2f
        );
    }
    return headPos; // Fallback to head if calculation fails
}

static Vector3 GetChestPosition(void *player) {
    return GetBonePosition(player, game_sdk->_newHipMods);
}




static Vector3 CameraMain(void *player) {
    return game_sdk->get_position(*(void **)((uint64_t)player + oxo("0x318")));
}
Quaternion GetRotationToTheLocation(Vector3 Target, float Height, Vector3 MyEnemy)
{
    return Quaternion::LookRotation((Target + Vector3(0, Height, 0)) - MyEnemy, Vector3(0, 1, 0));
}


class tanghinh
{
       public:
    static Vector3 Transform_GetPosition(void *player)
    {
        Vector3 out = Vector3::zero();
        void (*_Transform_GetPosition)(void *transform, Vector3 *out) = (void (*)(void *, Vector3 *))getRealOffset(oxo("0x105FE7D14"));
        _Transform_GetPosition(player, &out);
        return out;
    }
   static void *Player_GetHeadCollider(void *player) {
        void *(*_Player_GetHeadCollider)(void *players) = (void *(*)(void *))getRealOffset(oxo("0x105144E64"));
        return _Player_GetHeadCollider(player);
    }

    static bool Physics_Raycast(Vector3 camLocation, Vector3 headLocation, unsigned int LayerID, void *collider) {
        bool (*_Physics_Raycast)(Vector3 camLocation, Vector3 headLocation, unsigned int LayerID, void *collider) = (bool (*)(Vector3, Vector3, unsigned int, void *))getRealOffset(oxo("0x1046F7B08")); // sai offset 
        return _Physics_Raycast(camLocation, headLocation, LayerID, collider);
    }
    static bool isVisible(void *enemy)
    {
        if (enemy != NULL)
        {
            void *hitObj = NULL;
            auto Camera = Transform_GetPosition(game_sdk->Component_GetTransform(game_sdk->get_camera()));
            auto Target = Transform_GetPosition(game_sdk->Component_GetTransform(Player_GetHeadCollider(enemy)));
            return !Physics_Raycast(Camera, Target, 12, &hitObj);
        }
        return false;
    }
};



bool isFov(Vector3 vec1, Vector3 vec2, int radius)
{
    int x = vec1.x;
    int y = vec1.y;
    int x0 = vec2.x;
    int y0 = vec2.y;
    if ((pow(x - x0, 2) + pow(y - y0, 2)) <= pow(radius, 2))
    {
        return true;
    }
    return false;
}



enum TargetPriority {
    PRIORITY_CLOSEST = 0,
    PRIORITY_LOWEST_HP = 1,
    PRIORITY_HEADSHOT = 2
};

void *GetClosestEnemy2() {
    try {
        float bestScore = 9999.0f;
        void *closestEnemy = NULL;

        void *get_MatchGame = game_sdk->Curent_Match();
        if (!get_MatchGame) return NULL;

        void *LocalPlayer = game_sdk->GetLocalPlayer(get_MatchGame);
        if (!LocalPlayer || !game_sdk->Component_GetTransform(LocalPlayer)) return NULL;

        if (!Vars.Enable) return NULL;

        Dictionary<uint8_t *, void **> *players = *(Dictionary<uint8_t *, void **> **)((long)get_MatchGame + oxo("0x120"));
        if (!players || !players->getValues()) return NULL;

        Vector3 LocalPlayerPos = getPosition(LocalPlayer);
        Vector3 screenCenter = Vector3(0.5f, 0.5f, 0);
        
        int priorityMode = PRIORITY_CLOSEST;
        if (Vars.TargetPriority >= 0 && Vars.TargetPriority <= 2) {
            priorityMode = Vars.TargetPriority;
        }

        for (int u = 0; u < players->getNumValues(); u++) {
            void *Player = players->getValues()[u];
            if (!Player || Player == LocalPlayer) continue;
            if (!game_sdk->get_MaxHP(Player)) continue;
            if (game_sdk->get_IsDieing(Player)) continue;
            if (IgnoreBot && IsClientBot(Player)) continue;
            if (!game_sdk->get_isVisible(Player)) continue;
            if (game_sdk->get_isLocalTeam(Player)) continue;

            Vector3 currentHead = GetHeadPosition(Player);
            if (currentHead != Vector3::zero()) {
                BacktrackMap[Player].push_back(currentHead);
                if (BacktrackMap[Player].size() > 10) {
                    BacktrackMap[Player].erase(BacktrackMap[Player].begin());
                }
            }

            int hp = game_sdk->GetHp(Player);
            int maxHP = game_sdk->get_MaxHP(Player);
            if (IgnoreKnocked2 && (hp <= 0 || game_sdk->get_IsDieing(Player))) continue;

            Vector3 PlayerPos = getPosition(Player);
            float distance = Vector3::Distance(LocalPlayerPos, PlayerPos);

            Vector3 targetDir = Vector3::Normalized(PlayerPos - LocalPlayerPos);
            float angle = Vector3::Angle(targetDir, game_sdk->GetForward(game_sdk->Component_GetTransform(game_sdk->get_camera()))) * 100.0f;

            Vector3 screenPos = game_sdk->WorldToScreenPoint(game_sdk->get_camera(), PlayerPos);
            if (screenPos.z <= 1) continue;

            bool isFov1 = isFov(
                Vector3(screenPos.x, screenPos.y),
                Vector3(screenCenter.x, screenCenter.y),
                Vars.AimFov
            );

            float priorityScore = 9999.0f;
            
            if (priorityMode == PRIORITY_CLOSEST) {
                if (!Vars.AimNearestEnemy) {
                    if (angle <= Vars.AimFov && isFov1) {
                        priorityScore = angle;
                    }
                } else {
                    priorityScore = distance;
                }
            } else if (priorityMode == PRIORITY_LOWEST_HP) {
                if (maxHP > 0 && hp > 0) {
                    float hpPercent = (float)hp / (float)maxHP;
                    priorityScore = hpPercent * 1000.0f + distance * 0.1f;
                }
            } else if (priorityMode == PRIORITY_HEADSHOT) {
                Vector3 headPos = GetHeadPosition(Player);
                if (headPos.x != 0 || headPos.y != 0 || headPos.z != 0) {
                    Vector3 headScreen = game_sdk->WorldToScreenPoint(game_sdk->get_camera(), headPos);
                    if (headScreen.z > 0.1f) {
                        priorityScore = distance;
                    } else {
                        continue;
                    }
                } else {
                    continue;
                }
            }

            if (priorityScore < bestScore) {
                if (tanghinh::isVisible(Player)) {
                    bestScore = priorityScore;
                    closestEnemy = Player;
                }
            }
        }

        return closestEnemy;
    } catch (...) {
        return NULL;
    }
}

static std::vector<void*> g_AllEnemies;

void* GetClosestEnemy2ToAimkill(void* match) {
    g_AllEnemies.clear();

    try {
        if (!match) return nullptr;

        void* local = game_sdk->GetLocalPlayer(match);
        if (!local || !game_sdk->Component_GetTransform(local)) return nullptr;

        uintptr_t dictPtr = *(uintptr_t*)((uintptr_t)match + 0x120);
        if (dictPtr < 0x1000) return nullptr;

        Dictionary<uint8_t*, void**>* players = (Dictionary<uint8_t*, void**>*)dictPtr;
        if (!players || !players->getValues()) return nullptr;

        int count = players->getNumValues();
        if (count <= 0 || count > 1000) return nullptr;

        for (int i = 0; i < count; i++) {
            void* enemy = players->getValues()[i];
            if (!enemy || enemy == local) continue;

            void* enemyTransform = game_sdk->Component_GetTransform(enemy);
            if (!enemyTransform) continue;

            if (!game_sdk->get_MaxHP(enemy)) continue;
            if (game_sdk->get_IsDieing(enemy)) continue;
            if (game_sdk->GetHp(enemy) <= 0) continue;
            if (game_sdk->get_isLocalTeam(enemy)) continue;
            if (IgnoreBot && IsClientBot(enemy)) continue;
            if (IgnoreKnocked2 && (game_sdk->GetHp(enemy) <= 0 || game_sdk->get_IsDieing(enemy))) continue;

            if (!game_sdk->get_isVisible(enemy)) continue;

            Vector3 head = GetHeadPosition(enemy);
            if (head != Vector3::zero()) {
                BacktrackMap[enemy].push_back(head);
                if (BacktrackMap[enemy].size() > 10) {
                    BacktrackMap[enemy].erase(BacktrackMap[enemy].begin());
                }
            }

            g_AllEnemies.push_back(enemy);
        }

        return g_AllEnemies.empty() ? nullptr : match;

    } catch (...) {
        g_AllEnemies.clear();
        return nullptr;
    }
}

const std::vector<void*>& GetAllEnemies() {
    return g_AllEnemies;
}



void* GetClosestEnemy2ToAimkill_V4(void* match) {
    try {
        float shortestDistance = 9999.0f;
        void* closestEnemy = nullptr;

        if (!match) return nullptr;

        void* local = game_sdk->GetLocalPlayer(match);
        if (!local || !game_sdk->Component_GetTransform(local)) return nullptr;

        uintptr_t dictPtr = *(uintptr_t*)((uintptr_t)match + 0x120);
        if (dictPtr < 0x1000) return nullptr;

        Dictionary<uint8_t*, void**>* players = (Dictionary<uint8_t*, void**>*)dictPtr;
        if (!players || !players->getValues()) return nullptr;

        int count = players->getNumValues();
        if (count <= 0 || count > 1000) return nullptr;

        void* localTransform = game_sdk->Component_GetTransform(local);
        if (!localTransform) return nullptr;

        Vector3 localPos = game_sdk->get_position(localTransform);

        for (int i = 0; i < count; i++) {
            void* enemy = players->getValues()[i];
            if (!enemy || enemy == local) continue;

            void* enemyTransform = game_sdk->Component_GetTransform(enemy);
            if (!enemyTransform) continue;

            if (!game_sdk->get_MaxHP(enemy)) continue;
            if (game_sdk->get_IsDieing(enemy)) continue;
            if (game_sdk->GetHp(enemy) <= 0) continue;
            if (game_sdk->get_isLocalTeam(enemy)) continue;
            if (IgnoreBot && IsClientBot(enemy)) continue;
            if (IgnoreKnocked2 && (game_sdk->GetHp(enemy) <= 0 || game_sdk->get_IsDieing(enemy))) continue;

            if (!game_sdk->get_isVisible(enemy)) continue;

            Vector3 head = GetHeadPosition(enemy);
            if (head != Vector3::zero()) {
                BacktrackMap[enemy].push_back(head);
                if (BacktrackMap[enemy].size() > 10) {
                    BacktrackMap[enemy].erase(BacktrackMap[enemy].begin());
                }
            }

            Vector3 enemyPos = game_sdk->get_position(enemyTransform);
            float distance = Vector3::Distance(localPos, enemyPos);

            if (distance < shortestDistance) {
                shortestDistance = distance;
                closestEnemy = enemy;
            }
        }

        return closestEnemy;
    } catch (...) {
        return nullptr;
    }
}
/*

static void FF_Weapon_DoFire(void* weapon) {
    if (!weapon) return;
    return ((void (*)(void*))getRealOffset(0x1024CBB70))(weapon);
}

static bool FF_Weapon_CanFire(void* weapon) {
    if (!weapon) return false;
    return ((bool (*)(void*))getRealOffset(0x1003BF0A4))(weapon);
}

static int FF_Weapon_GetAmmo(void* weapon) {
    if (!weapon) return 0;
    return ((int (*)(void*))getRealOffset(0x100383414))(weapon);
}

static void FF_Weapon_SyncAmmo(void* weapon, int ammo) {
    if (!weapon) return;
    return ((void (*)(void*, int))getRealOffset(0x10039BF48))(weapon, ammo);
}

static void StartonFiring(void* LocalPlayer, void* WeaponHand) {
    if (!LocalPlayer || !WeaponHand) return;
    StartFiring(LocalPlayer, WeaponHand);
    StartWholeBodyFiring(LocalPlayer, WeaponHand);
}
*/





void RunTelekill() {
    if (!Vars.Enable || !Vars.Telekill)
        return;

    void *match = game_sdk->Curent_Match();
    if (!match) return;

    void *local = game_sdk->GetLocalPlayer(match);
    if (!local || !game_sdk->Component_GetTransform(local)) return;

    Dictionary<uint8_t *, void **> *players = *(Dictionary<uint8_t *, void **> **)((long)match + 0x120);
    if (!players || !players->getValues()) return;

    void *localTF = game_sdk->Component_GetTransform(local);
    Vector3 localPos = game_sdk->get_position(localTF);
    Vector3 forward = game_sdk->GetForward(localTF);

    for (int i = 0; i < players->getNumValues(); i++) {
        void *enemy = players->getValues()[i];
        if (!enemy || enemy == local) continue;
        if (!game_sdk->Component_GetTransform(enemy)) continue;
        if (!game_sdk->get_MaxHP(enemy)) continue;
        if (game_sdk->get_IsDieing(enemy)) continue;
        if (game_sdk->GetHp(enemy) <= 0) continue;
        if (game_sdk->get_isLocalTeam(enemy)) continue;

        void *enemyTF = game_sdk->Component_GetTransform(enemy);
        Vector3 enemyPos = game_sdk->get_position(enemyTF);
        float distance = Vector3::Distance(localPos, enemyPos);

        if (distance > 8.0f)
            continue;

        
        Vector3 stableFront = localPos + forward * 0.5f;
        stableFront.y = localPos.y;

        Transform_INTERNAL_SetPosition(enemyTF, Vvector3(stableFront.x, stableFront.y, stableFront.z));
    }
}


float Lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

void RunUpPlayer() {
    if (!Vars.UpPlayer) return;

    static auto lastTime = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float>(now - lastTime).count();
    lastTime = now;

    void *match = game_sdk->Curent_Match();
    if (!match) return;

    void *local = game_sdk->GetLocalPlayer(match);
    if (!local || !game_sdk->Component_GetTransform(local)) return;

    Dictionary<uint8_t *, void **> *players = *(Dictionary<uint8_t *, void **> **)((long)match + 0x120);
    if (!players || !players->getValues()) return;

    for (int i = 0; i < players->getNumValues(); i++) {
        void *enemy = players->getValues()[i];
        if (!enemy || enemy == local) continue;
        if (!game_sdk->Component_GetTransform(enemy)) continue;
        if (!game_sdk->get_MaxHP(enemy)) continue;
        if (game_sdk->get_IsDieing(enemy)) continue;
        if (game_sdk->GetHp(enemy) <= 0) continue;
        if (game_sdk->get_isLocalTeam(enemy)) continue;

        void *enemyTF = game_sdk->Component_GetTransform(enemy);
        void *localTF = game_sdk->Component_GetTransform(local);
        if (!enemyTF || !localTF) continue;

        Vector3 enemyPos = getPosition(enemyTF);
        Vector3 localPos = getPosition(localTF);

        float groundY = enemyPos.y;
        float targetY = groundY + (Vars.UpPlayer ? 6.0f : 0.0f);

        float speed = 3.0f;
        enemyPos.y = Lerp(enemyPos.y, targetY, speed * deltaTime);

        Transform_INTERNAL_SetPosition(enemyTF, Vvector3(enemyPos.x, enemyPos.y, enemyPos.z));
    }
}
  









void RunBrutalTelekill() {
    if (!Vars.Enable || !Vars.BrutalMode) return;

    void* match = game_sdk->Curent_Match();
    if (!match) return;

    void* local = game_sdk->GetLocalPlayer(match);
    if (!local || !game_sdk->Component_GetTransform(local)) return;

    Dictionary<uint8_t*, void**>* players = *(Dictionary<uint8_t*, void**>**)((long)match + 0x120);
    if (!players || !players->getValues()) return;    


    void* camera = game_sdk->get_camera();
    if (!camera) return;

    Vector3 localPos = game_sdk->get_position(game_sdk->Component_GetTransform(local));
    Vector3 camPos = getPosition(camera);
    Vector3 camForward = game_sdk->GetForward(game_sdk->Component_GetTransform(camera));

    Vector3 crosshairPos = camPos + camForward * Vars.BrutalTelekillDistance;

    for (int i = 0; i < players->getNumValues(); i++) {
        void* enemy = players->getValues()[i];
        if (!enemy || enemy == local) continue;
        if (!game_sdk->Component_GetTransform(enemy)) continue;
        if (game_sdk->get_IsDieing(enemy)) continue;
        if (game_sdk->GetHp(enemy) <= 0) continue;
        if (game_sdk->get_isLocalTeam(enemy)) continue;

        void* enemyTF = game_sdk->Component_GetTransform(enemy);
        Vector3 enemyPos = game_sdk->get_position(enemyTF);
        float distanceToEnemy = Vector3::Distance(localPos, enemyPos);

        if (tanghinh::isVisible(enemy)) continue;

        Vector3 targetPos;
        bool useCrosshair = false;

        if (Vector3::Distance(enemyPos, crosshairPos) < Vars.BrutalTelekillDistance) {
            targetPos = crosshairPos;
            useCrosshair = true;
        } else {
            const int points = 8;
            const float radius = Vars.BrutalTelekillDistance;
            
            for (int j = 0; j < points; j++) {
                float angle = 2 * M_PI * j / points;
                Vector3 offset(cos(angle) * radius, 0, sin(angle) * radius);
                Vector3 candidate = enemyPos + offset;

                void* hitObj = nullptr;
                if (!Physics_Raycast(camPos, candidate, 12, &hitObj)) {
                    targetPos = candidate;
                    break;
                }
            }
        }

        if (targetPos != Vector3::zero()) {
            Transform_INTERNAL_SetPosition(enemyTF, Vvector3(targetPos.x, targetPos.y, targetPos.z));
            
            if (useCrosshair) {
                int currentHealth = game_sdk->GetHp(enemy);
                int newHealth = currentHealth - 50;
                if (newHealth < 0) newHealth = 0;
                
                *(int*)((uintptr_t)enemy + 0x348) = newHealth;
            }
        }
    }
}

void SpeedAuto() {
    if (!SpeedHack) return;

    void* match = CurentMatch();
    if (!match) return;

    void* player = GetLocalPlayer(match);
    if (!player) return;


    void* PlayerAttributes = *(void**)((uint64_t)player + 0x680);

*(float*)((uintptr_t)PlayerAttributes + 0x250) = 1.9f;


}




void ProcessAimbot() {
    if (!Vars.Aimbot) return;

    void* CurrentMatch = game_sdk->Curent_Match();
    if (!CurrentMatch) return;

    void* LocalPlayer = game_sdk->GetLocalPlayer(CurrentMatch);
    if (!LocalPlayer) return;

    void* localTF = game_sdk->Component_GetTransform(LocalPlayer);
    if (!localTF) return;

    if (game_sdk->get_IsDieing(LocalPlayer)) return;

    void* closestEnemy = GetClosestEnemy2();
    if (!closestEnemy) return;

    void* enemyTF = game_sdk->Component_GetTransform(closestEnemy);
    if (!enemyTF) return;

    if (game_sdk->get_IsDieing(closestEnemy)) return;
    if (IgnoreBot && IsClientBot(closestEnemy)) return;
    if (IgnoreKnocked2 && game_sdk->GetHp(closestEnemy) <= 0) return;
    if (!game_sdk->get_isVisible(closestEnemy)) return;

    Vector3 EnemyLocation = Vector3::zero();

    switch (Vars.Target) {
        case 0: // HEAD
            EnemyLocation = GetBonePosition(closestEnemy, game_sdk->_GetHeadPositions);
            break;

        case 1: // NECK
            EnemyLocation = GetNeckPosition(closestEnemy);
            if (EnemyLocation.Magnitude(EnemyLocation) > 0.001f) {
                EnemyLocation.y -= 0.15f;
            }
            break;

        case 2: // BODY
            EnemyLocation = GetBonePosition(closestEnemy, game_sdk->_newHipMods);
            break;

        default:
            EnemyLocation = GetHeadPosition(closestEnemy);
            break;
    }

    if (EnemyLocation.Magnitude(EnemyLocation) < 0.001f) return;

    Vector3 PlayerLocation = CameraMain(LocalPlayer);
    if (PlayerLocation.Magnitude(PlayerLocation) < 0.001f) return;

    Quaternion PlayerLook = GetRotationToTheLocation(
        EnemyLocation,
        0.1f,
        PlayerLocation
    );

    bool IsScopeOn = game_sdk->get_IsSighting(LocalPlayer);
    bool IsFiring = game_sdk->get_IsFiring(LocalPlayer);

    bool shouldAim =
        (Vars.AimWhen == 0) ||
        (Vars.AimWhen == 1 && IsFiring) ||
        (Vars.AimWhen == 2 && IsScopeOn);

    if (!shouldAim) return;

    float dist = Vector3::Distance(PlayerLocation, EnemyLocation);
    if (dist > 0.1f) {
        game_sdk->set_aim(LocalPlayer, PlayerLook);
    }
}



void IncreaseRF() {

if (!Vars.rateoffire)
     return;

    void* current_Match = CurentMatch();
    if (!current_Match) return;



        void *local_player = GetLocalPlayer(current_Match);
    if (!local_player) return;
void* PlayerAttributes = *(void**)((uint64_t)local_player + 0x688);
if (!PlayerAttributes) return;

*(float*)((uintptr_t)PlayerAttributes + 0x1E8) = 2.0f;  

*(float*)((uintptr_t)PlayerAttributes + 0x1EC) = 0.5f;  

*(float*)((uintptr_t)PlayerAttributes + 0x1F0) = 0.5f;  
}












void get_players() {
    if (!Vars.Enable) return;

    void *current_Match = game_sdk->Curent_Match();
    if (!current_Match) return;



    void *local_player = GetLocalPlayer(current_Match);
    if (!local_player) return;




RunTelekill();
      
SpeedAuto();



    try {
        void *targetEnemy = GetClosestEnemy2ToAimkill(current_Match);
        if (!targetEnemy) return;

    ProcessAimbot();

IncreaseRF();


      
        RunBrutalTelekill();
      
        RunUpPlayer();
    
     
    } catch (...) {
    }
}
UIView *espContainer = nil;
UIView *boxContainer = nil;
UIView *nameContainer = nil;
UIView *skeletonContainer = nil;
UIView *aimbotContainer = nil;
UIView *enemyCountContainer = nil;

static int espFrameCounter = 0;
static int boxFrameCounter = 0;
static int nameFrameCounter = 0;
static int skeletonFrameCounter = 0;
static int aimbotFrameCounter = 0;
static int enemyCountFrameCounter = 0;
static const int FRAME_SKIP = 3;

BOOL IsLocalPlayerAlive(void *localPlayer) {
    if (!localPlayer) return NO;
    @try {
        if (game_sdk->get_IsDieing(localPlayer)) return NO;
        if (game_sdk->GetHp(localPlayer) <= 0) return NO;
        return YES;
    } @catch (NSException *exception) {
        return NO;
    }
}

BOOL IsEnemyValid(void *enemy, void *localPlayer) {
    if (!enemy || !localPlayer || enemy == localPlayer) return NO;
    @try {
        if ((uintptr_t)enemy == 0 || (uintptr_t)enemy == 0xFFFFFFFFFFFFFFFF) return NO;
        
        if (game_sdk->get_isLocalTeam(enemy)) return NO;
        
        if (game_sdk->get_IsDieing(enemy)) return NO;
        int hp = game_sdk->GetHp(enemy);
        if (hp <= 0) return NO;
        
        if (!game_sdk->get_isVisible(enemy)) return NO;
        
        return YES;
    } @catch (NSException *exception) {
        return NO;
    }
}

void ClearAllESPDrawings() {
    if (espContainer) {
        espContainer.layer.sublayers = nil;
    }
    if (boxContainer) {
        boxContainer.layer.sublayers = nil;
    }
    if (nameContainer) {
        for (UIView *view in nameContainer.subviews.copy) {
            [view removeFromSuperview];
        }
    }
    if (skeletonContainer) {
        skeletonContainer.layer.sublayers = nil;
    }
    if (aimbotContainer) {
        aimbotContainer.layer.sublayers = nil;
    }
    if (enemyCountContainer) {
        for (UIView *view in enemyCountContainer.subviews.copy) {
            [view removeFromSuperview];
        }
    }
}

BOOL shouldUpdateESP() {
    espFrameCounter = (espFrameCounter + 1) % FRAME_SKIP;
    return espFrameCounter == 0;
}

BOOL shouldUpdateBox() {
    boxFrameCounter = (boxFrameCounter + 1) % FRAME_SKIP;
    return boxFrameCounter == 0;
}

BOOL shouldUpdateName() {
    nameFrameCounter = (nameFrameCounter + 1) % FRAME_SKIP;
    return nameFrameCounter == 0;
}

BOOL shouldUpdateSkeleton() {
    skeletonFrameCounter = (skeletonFrameCounter + 1) % FRAME_SKIP;
    return skeletonFrameCounter == 0;
}

BOOL shouldUpdateAimbot() {
    aimbotFrameCounter = (aimbotFrameCounter + 1) % FRAME_SKIP;
    return aimbotFrameCounter == 0;
}

BOOL shouldUpdateEnemyCount() {
    enemyCountFrameCounter = (enemyCountFrameCounter + 1) % FRAME_SKIP;
    return enemyCountFrameCounter == 0;
}

void applyStreamModeToContainer(UIView *container) {
    if (StreamMode && container) {
        UpdateStreamProtectionForView(container);
    }
}

#ifdef __cplusplus
extern "C" {
#endif
UIColor* GetThemeAccentColor(void);
UIColor* GetThemeTextColor(void);
UIColor* GetThemeGlowColor(void);
#ifdef __cplusplus
}
#endif

UIColor* getESPColor() {
    UIColor* themeColor = GetThemeAccentColor();
    if (themeColor) {
        return themeColor;
    }
    return [UIColor colorWithRed:1.0 green:1.0 blue:1.0 alpha:1.0];
}

// Color selection helper function
UIColor* getColorFromIndex(int colorIndex) {
    switch (colorIndex) {
        case 0: // White
            return [UIColor colorWithRed:1.0 green:1.0 blue:1.0 alpha:1.0];
        case 1: // Red
            return [UIColor colorWithRed:1.0 green:0.2 blue:0.2 alpha:1.0];
        case 2: // Blue
            return [UIColor colorWithRed:0.2 green:0.5 blue:1.0 alpha:1.0];
        case 3: // Green
            return [UIColor colorWithRed:0.2 green:1.0 blue:0.2 alpha:1.0];
        case 4: // Pink
            return [UIColor colorWithRed:1.0 green:0.4 blue:0.8 alpha:1.0];
        default:
            return [UIColor colorWithRed:1.0 green:1.0 blue:1.0 alpha:1.0];
    }
}

void drawLineWithOutline(CGPoint from, CGPoint to, UIColor *color, CGFloat width, UIView *container) {
    BOOL isSkeleton = (container == skeletonContainer);
    BOOL shouldGlow = Vars.Glow && isSkeleton;
    
    if (Vars.Outline) {
        UIBezierPath *outlinePath = [UIBezierPath bezierPath];
        [outlinePath moveToPoint:from];
        [outlinePath addLineToPoint:to];
        
        CAShapeLayer *outlineLayer = [CAShapeLayer layer];
        outlineLayer.path = outlinePath.CGPath;
        outlineLayer.strokeColor = [UIColor blackColor].CGColor;
        outlineLayer.lineWidth = width + 0.5;
        outlineLayer.fillColor = [UIColor clearColor].CGColor;
        outlineLayer.lineCap = kCALineCapRound;
        
        [container.layer addSublayer:outlineLayer];
    }
    
    UIBezierPath *linePath = [UIBezierPath bezierPath];
    [linePath moveToPoint:from];
    [linePath addLineToPoint:to];
    
    CAShapeLayer *lineLayer = [CAShapeLayer layer];
    lineLayer.path = linePath.CGPath;
    lineLayer.strokeColor = color.CGColor;
    lineLayer.lineWidth = width;
    lineLayer.fillColor = [UIColor clearColor].CGColor;
    lineLayer.lineCap = kCALineCapRound;
    
    if (shouldGlow) {
        UIColor *themeColor = GetThemeAccentColor();
        CGFloat red, green, blue, alpha;
        [themeColor getRed:&red green:&green blue:&blue alpha:&alpha];
        
        UIColor *darkGlowColor = [UIColor colorWithRed:red * 0.6f 
                                                  green:green * 0.6f 
                                                   blue:blue * 0.6f 
                                                  alpha:0.8f];
        
        UIColor *brightGlowColor = [UIColor colorWithRed:MIN(1.0f, red * 1.2f)
                                                    green:MIN(1.0f, green * 1.2f)
                                                     blue:MIN(1.0f, blue * 1.2f)
                                                    alpha:0.9f];
        
        CAShapeLayer *outerGlow = [CAShapeLayer layer];
        outerGlow.path = linePath.CGPath;
        outerGlow.strokeColor = darkGlowColor.CGColor;
        outerGlow.lineWidth = width + 4.0;
        outerGlow.fillColor = [UIColor clearColor].CGColor;
        outerGlow.lineCap = kCALineCapRound;
        outerGlow.opacity = 0.6;
        outerGlow.shadowColor = darkGlowColor.CGColor;
        outerGlow.shadowRadius = 8.0;
        outerGlow.shadowOpacity = 0.8;
        outerGlow.shadowOffset = CGSizeZero;
        [container.layer addSublayer:outerGlow];
        
        CAShapeLayer *middleGlow = [CAShapeLayer layer];
        middleGlow.path = linePath.CGPath;
        middleGlow.strokeColor = themeColor.CGColor;
        middleGlow.lineWidth = width + 2.0;
        middleGlow.fillColor = [UIColor clearColor].CGColor;
        middleGlow.lineCap = kCALineCapRound;
        middleGlow.opacity = 0.7;
        middleGlow.shadowColor = themeColor.CGColor;
        middleGlow.shadowRadius = 5.0;
        middleGlow.shadowOpacity = 0.9;
        middleGlow.shadowOffset = CGSizeZero;
        [container.layer addSublayer:middleGlow];
        
        CAShapeLayer *innerGlow = [CAShapeLayer layer];
        innerGlow.path = linePath.CGPath;
        innerGlow.strokeColor = brightGlowColor.CGColor;
        innerGlow.lineWidth = width + 1.0;
        innerGlow.fillColor = [UIColor clearColor].CGColor;
        innerGlow.lineCap = kCALineCapRound;
        innerGlow.opacity = 0.8;
        innerGlow.shadowColor = brightGlowColor.CGColor;
        innerGlow.shadowRadius = 3.0;
        innerGlow.shadowOpacity = 1.0;
        innerGlow.shadowOffset = CGSizeZero;
        [container.layer addSublayer:innerGlow];
    }
    
    [container.layer addSublayer:lineLayer];
}

void drawGlowingHeadCircle(CGPoint center, UIColor *color, UIView *container) {
    CGFloat radius = 4.0f;
    
    UIBezierPath *circlePath = [UIBezierPath bezierPathWithArcCenter:center
                                                               radius:radius
                                                           startAngle:0
                                                             endAngle:M_PI * 2
                                                            clockwise:YES];
    
    CAShapeLayer *circleLayer = [CAShapeLayer layer];
    circleLayer.path = circlePath.CGPath;
    circleLayer.fillColor = color.CGColor;
    circleLayer.strokeColor = color.CGColor;
    circleLayer.lineWidth = 1.5;
    
    if (Vars.Glow) {
        UIColor *themeColor = GetThemeAccentColor();
        CGFloat red, green, blue, alpha;
        [themeColor getRed:&red green:&green blue:&blue alpha:&alpha];
        
        UIColor *darkGlowColor = [UIColor colorWithRed:red * 0.6f 
                                                  green:green * 0.6f 
                                                   blue:blue * 0.6f 
                                                  alpha:0.7f];
        
        UIColor *brightGlowColor = [UIColor colorWithRed:MIN(1.0f, red * 1.2f)
                                                    green:MIN(1.0f, green * 1.2f)
                                                     blue:MIN(1.0f, blue * 1.2f)
                                                    alpha:0.8f];
        
        CAShapeLayer *outerGlow = [CAShapeLayer layer];
        outerGlow.path = circlePath.CGPath;
        outerGlow.fillColor = darkGlowColor.CGColor;
        outerGlow.strokeColor = darkGlowColor.CGColor;
        outerGlow.lineWidth = 1.0;
        outerGlow.shadowColor = darkGlowColor.CGColor;
        outerGlow.shadowRadius = 4.0;
        outerGlow.shadowOpacity = 0.8;
        outerGlow.shadowOffset = CGSizeZero;
        [container.layer addSublayer:outerGlow];
        
        CAShapeLayer *innerGlow = [CAShapeLayer layer];
        innerGlow.path = circlePath.CGPath;
        innerGlow.fillColor = brightGlowColor.CGColor;
        innerGlow.strokeColor = brightGlowColor.CGColor;
        innerGlow.lineWidth = 1.0;
        innerGlow.shadowColor = brightGlowColor.CGColor;
        innerGlow.shadowRadius = 2.0;
        innerGlow.shadowOpacity = 1.0;
        innerGlow.shadowOffset = CGSizeZero;
        [container.layer addSublayer:innerGlow];
    }
    
    [container.layer addSublayer:circleLayer];
}

void drawBoxWithOutline(CGRect rect, UIColor *color, CGFloat width, UIView *container) {
    if (Vars.Outline) {
        UIBezierPath *outlinePath = [UIBezierPath bezierPathWithRect:rect];
        CAShapeLayer *outlineLayer = [CAShapeLayer layer];
        outlineLayer.path = outlinePath.CGPath;
        outlineLayer.strokeColor = [UIColor blackColor].CGColor;
        outlineLayer.lineWidth = width + 0.5;
        outlineLayer.fillColor = [UIColor clearColor].CGColor;
        outlineLayer.lineCap = kCALineCapRound;
        
        [container.layer addSublayer:outlineLayer];
    }
    
    UIBezierPath *boxPath = [UIBezierPath bezierPathWithRect:rect];
    CAShapeLayer *boxLayer = [CAShapeLayer layer];
    boxLayer.path = boxPath.CGPath;
    boxLayer.strokeColor = color.CGColor;
    boxLayer.lineWidth = width;
    boxLayer.fillColor = [UIColor clearColor].CGColor;
    boxLayer.lineCap = kCALineCapRound;
    
    [container.layer addSublayer:boxLayer];
}

void espUIKIT() {
    if (!Vars.Enable || !Vars.lines) {
        if (espContainer) {
            [espContainer removeFromSuperview];
            espContainer = nil;
        }
        return;
    }

    if (!shouldUpdateESP()) return;

    // ✅ Safe keyWindow (iOS 13+)
    UIWindow *window = nil;
    for (UIWindow *w in UIApplication.sharedApplication.windows) {
        if (w.isKeyWindow) {
            window = w;
            break;
        }
    }
    if (!window) return;

    // ✅ Clear sublayers safely (no crash)
    if (espContainer) {
        for (CALayer *l in [espContainer.layer.sublayers copy]) {
            [l removeFromSuperlayer];
        }
    } else {
        espContainer = [[UIView alloc] initWithFrame:window.bounds];
        espContainer.userInteractionEnabled = NO;
        [window addSubview:espContainer];
        applyStreamModeToContainer(espContainer);
    }

    void *match = game_sdk->Curent_Match();
    if (!match) return;

    void *localPlayer = game_sdk->GetLocalPlayer(match);
    if (!localPlayer || !IsLocalPlayerAlive(localPlayer)) return;

    Dictionary<uint8_t *, void **> *players =
        *(Dictionary<uint8_t *, void **> **)((long)match + 0x120);
    if (!players || !players->getValues()) return;

    auto cam = game_sdk->get_camera();
    if (!cam) return;

    CGSize screenSize = window.bounds.size;
    CGPoint topMiddle = CGPointMake(screenSize.width / 2.0f, 0);
    UIColor *lineColor = getColorFromIndex(ESPLineColor);

    for (int i = 0; i < players->getNumValues(); i++) {
        void *enemy = players->getValues()[i];
        if (!IsEnemyValid(enemy, localPlayer)) continue;

        Vector3 enemyPos = getPosition(enemy);
        Vector3 headPos = enemyPos + Vector3(0, 1.7f, 0);

        Vector3 screenPos = game_sdk->WorldToScreenPoint(cam, headPos);
        if (screenPos.z <= 0.1f) continue;

        CGPoint point = CGPointMake(screenSize.width * screenPos.x,
                                    screenSize.height - screenPos.y * screenSize.height);

        drawLineWithOutline(topMiddle, point, lineColor, 1.2f, espContainer);
    }
}


void boxUIKIT() {
    if (!Vars.Box) {
        if (boxContainer) {
            [boxContainer removeFromSuperview];
            boxContainer = nil;
        }
        return;
    }

    if (!shouldUpdateBox()) return;

    // ✅ Safe keyWindow (iOS 13+)
    UIWindow *window = nil;
    for (UIWindow *w in UIApplication.sharedApplication.windows) {
        if (w.isKeyWindow) {
            window = w;
            break;
        }
    }
    if (!window) return;

    // ✅ Clear sublayers safely
    if (boxContainer) {
        for (CALayer *l in [boxContainer.layer.sublayers copy]) {
            [l removeFromSuperlayer];
        }
    } else {
        boxContainer = [[UIView alloc] initWithFrame:window.bounds];
        boxContainer.userInteractionEnabled = NO;
        [window addSubview:boxContainer];
        applyStreamModeToContainer(boxContainer);
    }

    void *match = game_sdk->Curent_Match();
    if (!match) return;

    void *localPlayer = game_sdk->GetLocalPlayer(match);
    if (!localPlayer || !IsLocalPlayerAlive(localPlayer)) return;

    Dictionary<uint8_t *, void **> *players =
    *(Dictionary<uint8_t *, void **> **)((long)match + 0x120);
    if (!players || !players->getValues()) return;

    auto cam = game_sdk->get_camera();
    if (!cam) return;

    CGSize screenSize = window.bounds.size;
    UIColor *boxColor = getColorFromIndex(ESPBoxColor);

    for (int i = 0; i < players->getNumValues(); i++) {
        void *enemy = players->getValues()[i];
        if (!IsEnemyValid(enemy, localPlayer)) continue;

        Vector3 enemyPos = getPosition(enemy);
        Vector3 headPos = enemyPos + Vector3(0, 1.8f, 0);
        Vector3 footPos = enemyPos;

        Vector3 headScreen = game_sdk->WorldToScreenPoint(cam, headPos);
        Vector3 footScreen = game_sdk->WorldToScreenPoint(cam, footPos);

        if (headScreen.z <= 0.1f || footScreen.z <= 0.1f) continue;

        CGPoint top = CGPointMake(screenSize.width * headScreen.x,
                                  screenSize.height - headScreen.y * screenSize.height);
        CGPoint bottom = CGPointMake(screenSize.width * footScreen.x,
                                     screenSize.height - footScreen.y * screenSize.height);

        float boxHeight = (bottom.y - top.y) * 1.1f;
        if (boxHeight <= 5.0f) continue; // ✅ tránh crash CGRect

        float boxWidth = boxHeight * 0.5f;
        float centerX = (top.x + bottom.x) * 0.5f;

        CGRect boxRect = CGRectMake(centerX - boxWidth * 0.5f,
                                    top.y,
                                    boxWidth,
                                    boxHeight);

        drawBoxWithOutline(boxRect, boxColor, 1.2, boxContainer);

        if (Vars.Health) {
            int currentHP = 100;
            int maxHP = 100;

            int gameMaxHP = game_sdk->get_MaxHP(enemy);
            if (gameMaxHP > 0) {
                maxHP = gameMaxHP;
                currentHP = game_sdk->GetHp(enemy);
            }

            float healthPercent = (float)currentHP / (float)maxHP;
            healthPercent = MAX(0, MIN(1, healthPercent));

            UIColor *healthColor;
            if (healthPercent > 0.6f)
                healthColor = UIColor.greenColor;
            else if (healthPercent > 0.3f)
                healthColor = UIColor.yellowColor;
            else
                healthColor = UIColor.redColor;

            float healthHeight = boxHeight * healthPercent;

            CGRect healthRect = CGRectMake(boxRect.origin.x - 4,
                                           boxRect.origin.y + (boxHeight - healthHeight),
                                           2,
                                           healthHeight);

            UIBezierPath *healthPath = [UIBezierPath bezierPathWithRect:healthRect];
            CAShapeLayer *healthLayer = [CAShapeLayer layer];
            healthLayer.path = healthPath.CGPath;
            healthLayer.fillColor = healthColor.CGColor;
            healthLayer.strokeColor = UIColor.blackColor.CGColor;
            healthLayer.lineWidth = 0.2f;
            [boxContainer.layer addSublayer:healthLayer];
        }
    }
}


void nameAndDistanceUIKIT() {
    BOOL showName = Vars.Name;
    BOOL showDistance = Vars.Distance;
    
    if (!showName && !showDistance) {
        if (nameContainer) {
            [nameContainer removeFromSuperview];
            nameContainer = nil;
        }
        return;
    }
    
    if (!shouldUpdateName()) return;
    
    UIWindow *window = [UIApplication sharedApplication].keyWindow;
    if (!window) {
        if (nameContainer) {
            for (UIView *view in nameContainer.subviews.copy) {
                [view removeFromSuperview];
            }
        }
        return;
    }
    
    if (nameContainer) {
        for (UIView *view in nameContainer.subviews.copy) {
            [view removeFromSuperview];
        }
    } else {
        nameContainer = [[UIView alloc] initWithFrame:window.bounds];
        nameContainer.userInteractionEnabled = NO;
        [window addSubview:nameContainer];
        applyStreamModeToContainer(nameContainer);
    }
    
    void *match = game_sdk->Curent_Match();
    if (!match) return;
    
    void *localPlayer = game_sdk->GetLocalPlayer(match);
    if (!localPlayer || !IsLocalPlayerAlive(localPlayer)) return;
    
    Dictionary<uint8_t *, void **> *players = *(Dictionary<uint8_t *, void **> **)((long)match + 0x120);
    if (!players || !players->getValues()) return;
    
    CGSize screenSize = window.bounds.size;
    UIColor *textColor = getColorFromIndex(ESPNameColor);
    int validEnemiesDrawn = 0;
    
    for (int i = 0; i < players->getNumValues(); i++) {
        void *enemy = players->getValues()[i];
        if (!IsEnemyValid(enemy, localPlayer)) continue;
        
        Vector3 enemyPos = getPosition(enemy);
        Vector3 localPos = getPosition(localPlayer);
        float distance = Vector3::Distance(enemyPos, localPos);
        
        if (distance > 300.0f) continue;
        
        Vector3 headPos = enemyPos + Vector3(0, 1.8f, 0);
        Vector3 headScreen = game_sdk->WorldToScreenPoint(game_sdk->get_camera(), headPos);
        if (headScreen.z <= 0.1f) continue;
        
        CGPoint boxTop = CGPointMake(screenSize.width * headScreen.x,
                                     screenSize.height - headScreen.y * screenSize.height);
        
        NSString *displayText = @"";
        
        if (showName) {
            monoString *nameStr = game_sdk->name(enemy);
            if (nameStr) {
                std::string name = nameStr->toCPPString();
                if (!name.empty()) {
                    displayText = [NSString stringWithUTF8String:name.c_str()];
                }
            }
        }
        
        if (showDistance) {
            NSString *distStr = [NSString stringWithFormat:@"%.0fm", distance];
            if (displayText.length > 0) {
                displayText = [NSString stringWithFormat:@"%@ | %@", displayText, distStr];
            } else {
                displayText = distStr;
            }
        }
        
        if (displayText.length == 0) continue;
        
        UIFont *font = [UIFont systemFontOfSize:8];
        CGSize textSize = [displayText sizeWithAttributes:@{NSFontAttributeName: font}];
        
        UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, textSize.width, textSize.height)];
        label.center = CGPointMake(boxTop.x, boxTop.y - 5);
        label.text = displayText;
        label.textColor = textColor;
        label.font = font;
        label.backgroundColor = [UIColor clearColor];
        
        if (Vars.Outline) {
            label.layer.shadowColor = [UIColor blackColor].CGColor;
            label.layer.shadowOffset = CGSizeZero;
            label.layer.shadowRadius = 1.0;
            label.layer.shadowOpacity = 1.0;
        }
        
        [nameContainer addSubview:label];
        validEnemiesDrawn++;
    }
    
    if (validEnemiesDrawn == 0 && nameContainer) {
        for (UIView *view in nameContainer.subviews.copy) {
            [view removeFromSuperview];
        }
    }
}

void nameUIKIT() {
    nameAndDistanceUIKIT();
}

void distanceUIKIT() {
    nameAndDistanceUIKIT();
}

Vector3 GetBonePositionSafe(void *enemy, void *(*transformGetter)(void *)) {
    if (!enemy || !transformGetter) {
        return Vector3(0, 0, 0);
    }
    
    @try {
        Vector3 pos = GetBonePosition(enemy, transformGetter);
        if (isnan(pos.x) || isnan(pos.y) || isnan(pos.z) ||
            isinf(pos.x) || isinf(pos.y) || isinf(pos.z)) {
            return Vector3(0, 0, 0);
        }
        return pos;
    } @catch (NSException *exception) {
        return Vector3(0, 0, 0);
    }
}





void skeleton() {
    if (!Vars.Skeleton) {
        if (skeletonContainer) {
            [skeletonContainer removeFromSuperview];
            skeletonContainer = nil;
        }
        return;
    }
    
    if (!shouldUpdateSkeleton()) return;
    
    UIWindow *window = [UIApplication sharedApplication].keyWindow;
    if (!window) {
        if (skeletonContainer) {
            skeletonContainer.layer.sublayers = nil;
        }
        return;
    }
    
    if (skeletonContainer) {
        skeletonContainer.layer.sublayers = nil;
    } else {
        skeletonContainer = [[UIView alloc] initWithFrame:window.bounds];
        skeletonContainer.userInteractionEnabled = NO;
        [window addSubview:skeletonContainer];
        applyStreamModeToContainer(skeletonContainer);
    }
    
    void *match = game_sdk->Curent_Match();
    if (!match) return;
    
    void *localPlayer = game_sdk->GetLocalPlayer(match);
    if (!localPlayer || !IsLocalPlayerAlive(localPlayer)) return;
    
    Dictionary<uint8_t *, void **> *players = *(Dictionary<uint8_t *, void **> **)((long)match + 0x120);
    if (!players || !players->getValues()) return;
    
    CGSize screenSize = window.bounds.size;
    UIColor *boneColor = getColorFromIndex(ESPSkeletonColor);
    
    for (int i = 0; i < players->getNumValues(); i++) {
        @try {
            void *enemy = players->getValues()[i];
            if (!IsEnemyValid(enemy, localPlayer)) continue;
            
            Vector3 enemyPos = getPosition(enemy);
            Vector3 localPos = getPosition(localPlayer);
            float distance = Vector3::Distance(enemyPos, localPos);
            
            if (distance > 200.0f) continue;
            
            Vector3 headBone = GetHeadPosition(enemy);
            Vector3 hipBone = GetBonePositionSafe(enemy, game_sdk->_newHipMods);
            
            if (headBone.x == 0 && headBone.y == 0 && headBone.z == 0) continue;
            if (hipBone.x == 0 && hipBone.y == 0 && hipBone.z == 0) continue;
            
            Vector3 leftArmBone = GetBonePositionSafe(enemy, game_sdk->_getLeftForeArmTF);
            Vector3 rightArmBone = GetBonePositionSafe(enemy, game_sdk->_getRightForeArmTF);
            Vector3 leftLegBone = GetBonePositionSafe(enemy, game_sdk->_GetLeftAnkleTF);
            Vector3 rightLegBone = GetBonePositionSafe(enemy, game_sdk->_GetRightAnkleTF);
            
            @try {
                Vector3 screen1 = game_sdk->WorldToScreenPoint(game_sdk->get_camera(), headBone);
                Vector3 screen2 = game_sdk->WorldToScreenPoint(game_sdk->get_camera(), hipBone);
                if (screen1.z > 0.1f && screen2.z > 0.1f && 
                    !isnan(screen1.x) && !isnan(screen2.x)) {
                    CGPoint p1 = CGPointMake(screenSize.width * screen1.x, screenSize.height - screen1.y * screenSize.height);
                    CGPoint p2 = CGPointMake(screenSize.width * screen2.x, screenSize.height - screen2.y * screenSize.height);
                    drawLineWithOutline(p1, p2, boneColor, 2.5, skeletonContainer);
                }
            } @catch (NSException *e) {}
            
            if (!(leftArmBone.x == 0 && leftArmBone.y == 0 && leftArmBone.z == 0)) {
                @try {
                    Vector3 screen1 = game_sdk->WorldToScreenPoint(game_sdk->get_camera(), headBone);
                    Vector3 screen2 = game_sdk->WorldToScreenPoint(game_sdk->get_camera(), leftArmBone);
                    if (screen1.z > 0.1f && screen2.z > 0.1f && 
                        !isnan(screen1.x) && !isnan(screen2.x)) {
                        CGPoint p1 = CGPointMake(screenSize.width * screen1.x, screenSize.height - screen1.y * screenSize.height);
                        CGPoint p2 = CGPointMake(screenSize.width * screen2.x, screenSize.height - screen2.y * screenSize.height);
                        drawLineWithOutline(p1, p2, boneColor, 2.5, skeletonContainer);
                    }
                } @catch (NSException *e) {}
            }
            
            if (!(rightArmBone.x == 0 && rightArmBone.y == 0 && rightArmBone.z == 0)) {
                @try {
                    Vector3 screen1 = game_sdk->WorldToScreenPoint(game_sdk->get_camera(), headBone);
                    Vector3 screen2 = game_sdk->WorldToScreenPoint(game_sdk->get_camera(), rightArmBone);
                    if (screen1.z > 0.1f && screen2.z > 0.1f && 
                        !isnan(screen1.x) && !isnan(screen2.x)) {
                        CGPoint p1 = CGPointMake(screenSize.width * screen1.x, screenSize.height - screen1.y * screenSize.height);
                        CGPoint p2 = CGPointMake(screenSize.width * screen2.x, screenSize.height - screen2.y * screenSize.height);
                        drawLineWithOutline(p1, p2, boneColor, 2.5, skeletonContainer);
                    }
                } @catch (NSException *e) {}
            }
            
            if (!(leftLegBone.x == 0 && leftLegBone.y == 0 && leftLegBone.z == 0)) {
                @try {
                    Vector3 screen1 = game_sdk->WorldToScreenPoint(game_sdk->get_camera(), hipBone);
                    Vector3 screen2 = game_sdk->WorldToScreenPoint(game_sdk->get_camera(), leftLegBone);
                    if (screen1.z > 0.1f && screen2.z > 0.1f && 
                        !isnan(screen1.x) && !isnan(screen2.x)) {
                        CGPoint p1 = CGPointMake(screenSize.width * screen1.x, screenSize.height - screen1.y * screenSize.height);
                        CGPoint p2 = CGPointMake(screenSize.width * screen2.x, screenSize.height - screen2.y * screenSize.height);
                        drawLineWithOutline(p1, p2, boneColor, 2.5, skeletonContainer);
                    }
                } @catch (NSException *e) {}
            }
            
            if (!(rightLegBone.x == 0 && rightLegBone.y == 0 && rightLegBone.z == 0)) {
                @try {
                    Vector3 screen1 = game_sdk->WorldToScreenPoint(game_sdk->get_camera(), hipBone);
                    Vector3 screen2 = game_sdk->WorldToScreenPoint(game_sdk->get_camera(), rightLegBone);
                    if (screen1.z > 0.1f && screen2.z > 0.1f && 
                        !isnan(screen1.x) && !isnan(screen2.x)) {
                        CGPoint p1 = CGPointMake(screenSize.width * screen1.x, screenSize.height - screen1.y * screenSize.height);
                        CGPoint p2 = CGPointMake(screenSize.width * screen2.x, screenSize.height - screen2.y * screenSize.height);
                        drawLineWithOutline(p1, p2, boneColor, 2.5, skeletonContainer);
                    }
                } @catch (NSException *e) {}
            }
            
        } @catch (NSException *exception) {
            continue;
        }
    }
}

void aimbot() {
    static CAShapeLayer *fovLayer = nil;
    static CAShapeLayer *fovOutlineLayer = nil;
    static CAShapeLayer *lineLayer = nil;

    if (!Vars.Aimbot) {
        if (aimbotContainer) {
            [aimbotContainer removeFromSuperview];
            aimbotContainer = nil;
            fovLayer = nil;
            fovOutlineLayer = nil;
            lineLayer = nil;
        }
        return;
    }

    if (!shouldUpdateAimbot()) return;

    // ✅ Safe window (iOS 13+)
    UIWindow *window = nil;
    for (UIWindow *w in UIApplication.sharedApplication.windows) {
        if (w.isKeyWindow) {
            window = w;
            break;
        }
    }
    if (!window) return;

    void *match = game_sdk->Curent_Match();
    if (!match) return;

    void *localPlayer = game_sdk->GetLocalPlayer(match);
    if (!localPlayer || !IsLocalPlayerAlive(localPlayer)) return;

    // ✅ Create container ONCE
    if (!aimbotContainer) {
        aimbotContainer = [[UIView alloc] initWithFrame:window.bounds];
        aimbotContainer.userInteractionEnabled = NO;
        aimbotContainer.backgroundColor = UIColor.clearColor;
        [window addSubview:aimbotContainer];
        applyStreamModeToContainer(aimbotContainer);
    }

    CGSize screenSize = window.bounds.size;
    CGPoint center = CGPointMake(screenSize.width * 0.5f,
                                 screenSize.height * 0.5f);

    /* ================= FOV ================= */
    if (Vars.isAimFov && Vars.AimFov > 0) {
        UIBezierPath *circlePath =
        [UIBezierPath bezierPathWithArcCenter:center
                                       radius:Vars.AimFov
                                   startAngle:0
                                     endAngle:M_PI * 2
                                    clockwise:YES];

        if (Vars.Outline) {
            if (!fovOutlineLayer) {
                fovOutlineLayer = [CAShapeLayer layer];
                fovOutlineLayer.fillColor = UIColor.clearColor.CGColor;
                fovOutlineLayer.strokeColor = UIColor.blackColor.CGColor;
                fovOutlineLayer.opacity = 0.7;
                [aimbotContainer.layer addSublayer:fovOutlineLayer];
            }
            fovOutlineLayer.path = circlePath.CGPath;
            fovOutlineLayer.lineWidth = 0.7;
        } else if (fovOutlineLayer) {
            [fovOutlineLayer removeFromSuperlayer];
            fovOutlineLayer = nil;
        }

        if (!fovLayer) {
            fovLayer = [CAShapeLayer layer];
            fovLayer.fillColor = UIColor.clearColor.CGColor;
            fovLayer.opacity = 0.7;
            [aimbotContainer.layer addSublayer:fovLayer];
        }

        fovLayer.path = circlePath.CGPath;
        fovLayer.strokeColor = getColorFromIndex(AimbotFOVColor).CGColor;
        fovLayer.lineWidth = AimbotFOVThickness;
    } else {
        if (fovLayer) { [fovLayer removeFromSuperlayer]; fovLayer = nil; }
        if (fovOutlineLayer) { [fovOutlineLayer removeFromSuperlayer]; fovOutlineLayer = nil; }
    }

    /* ================= TARGET ================= */
    void *target = GetClosestEnemy2();
    if (!target || !IsEnemyValid(target, localPlayer)) {
        if (lineLayer) lineLayer.hidden = YES;
        return;
    }

    Vector3 targetPos;
    switch (Vars.Target) {
        case 0:
            targetPos = GetBonePosition(target, game_sdk->_GetHeadPositions);
            if (fabs(targetPos.y) > 0.001f) targetPos.y -= 0.15f;
            break;
        case 1:
            targetPos = GetNeckPosition(target);
            break;
        case 2:
            targetPos = GetBonePosition(target, game_sdk->_newHipMods);
            break;
        default:
            targetPos = GetHeadPosition(target);
            break;
    }

    if (fabs(targetPos.x) < 0.001f &&
        fabs(targetPos.y) < 0.001f &&
        fabs(targetPos.z) < 0.001f) {
        if (lineLayer) lineLayer.hidden = YES;
        return;
    }

    auto cam = game_sdk->get_camera();
    if (!cam) return;

    Vector3 screenPos = game_sdk->WorldToScreenPoint(cam, targetPos);
    if (screenPos.z <= 0.1f) {
        if (lineLayer) lineLayer.hidden = YES;
        return;
    }

    CGPoint targetPoint = CGPointMake(screenSize.width * screenPos.x,
                                      screenSize.height - screenPos.y * screenSize.height);

    /* ================= LINE ================= */
    if (!lineLayer) {
        lineLayer = [CAShapeLayer layer];
        lineLayer.fillColor = UIColor.clearColor.CGColor;
        lineLayer.lineWidth = 1.2;
        [aimbotContainer.layer addSublayer:lineLayer];
    }

    UIBezierPath *linePath = [UIBezierPath bezierPath];
    [linePath moveToPoint:center];
    [linePath addLineToPoint:targetPoint];

    UIColor *aimbotColor = GetThemeAccentColor() ?: UIColor.redColor;
    lineLayer.strokeColor = aimbotColor.CGColor;
    lineLayer.path = linePath.CGPath;
    lineLayer.hidden = NO;
}


void enemyCountUIKIT() {
    if (!Vars.enemycount) {
        if (enemyCountContainer) {
            [enemyCountContainer removeFromSuperview];
            enemyCountContainer = nil;
        }
        return;
    }
    
    if (!shouldUpdateEnemyCount()) return;
    
    UIWindow *window = [UIApplication sharedApplication].keyWindow;
    if (!window) return;
    
    void *match = game_sdk->Curent_Match();
    if (!match) {
        if (enemyCountContainer) {
            for (UIView *view in enemyCountContainer.subviews.copy) {
                [view removeFromSuperview];
            }
        }
        return;
    }
    
    void *localPlayer = game_sdk->GetLocalPlayer(match);
    if (!localPlayer || !IsLocalPlayerAlive(localPlayer)) {
        if (enemyCountContainer) {
            for (UIView *view in enemyCountContainer.subviews.copy) {
                [view removeFromSuperview];
            }
        }
        return;
    }
    
    Dictionary<uint8_t *, void **> *players = *(Dictionary<uint8_t *, void **> **)((long)match + 0x120);
    if (!players || !players->getValues()) {
        if (enemyCountContainer) {
            for (UIView *view in enemyCountContainer.subviews.copy) {
                [view removeFromSuperview];
            }
        }
        return;
    }
    
    int alive = 0;
    int knocked = 0;
    
    for (int i = 0; i < players->getNumValues(); i++) {
        void *enemy = players->getValues()[i];
        if (!enemy || enemy == localPlayer) continue;
        if (game_sdk->get_isLocalTeam(enemy)) continue;
        
        bool isDying = game_sdk->get_IsDieing(enemy);
        int hp = game_sdk->GetHp(enemy);
        
        if (isDying && hp <= 0) continue;
        
        if (isDying && hp > 0) {
            knocked++;
        } else if (hp > 0) {
            alive++;
        }
    }
    
    NSString *text = @"";
    if (knocked > 0) {
        text = [NSString stringWithFormat:@"ENEMIES: %d (%d K)", alive, knocked];
    } else {
        text = [NSString stringWithFormat:@"ENEMIES: %d", alive];
    }
    
    UIColor *textColor = getColorFromIndex(ESPNameColor);
    UIFont *font = [UIFont systemFontOfSize:11];
    
    CGSize textSize = [text sizeWithAttributes:@{NSFontAttributeName: font}];
    CGRect frame = CGRectMake((window.bounds.size.width - textSize.width - 12) / 2,
                             40, textSize.width + 12, 20);
    
    if (!enemyCountContainer) {
        enemyCountContainer = [[UIView alloc] initWithFrame:frame];
        enemyCountContainer.userInteractionEnabled = NO;
        [window addSubview:enemyCountContainer];
        applyStreamModeToContainer(enemyCountContainer);
    } else {
        enemyCountContainer.frame = frame;
        [enemyCountContainer.subviews makeObjectsPerformSelector:@selector(removeFromSuperview)];
    }
    
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, frame.size.width, frame.size.height)];
    label.text = text;
    label.textColor = textColor;
    label.font = font;
    label.textAlignment = NSTextAlignmentCenter;
    label.backgroundColor = [UIColor clearColor];
    
    if (Vars.Outline) {
        label.layer.shadowColor = [UIColor blackColor].CGColor;
        label.layer.shadowOffset = CGSizeZero;
        label.layer.shadowRadius = 1.0;
        label.layer.shadowOpacity = 1.0;
    }
    
    [enemyCountContainer addSubview:label];
}

void reapplyStreamModeToAllESP() {
    if (!StreamMode) return;
    
    if (espContainer) UpdateStreamProtectionForView(espContainer);
    if (boxContainer) UpdateStreamProtectionForView(boxContainer);
    if (nameContainer) UpdateStreamProtectionForView(nameContainer);
    if (skeletonContainer) UpdateStreamProtectionForView(skeletonContainer);
    if (aimbotContainer) UpdateStreamProtectionForView(aimbotContainer);
    if (enemyCountContainer) UpdateStreamProtectionForView(enemyCountContainer);
}

void renderGlow() {
}
