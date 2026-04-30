// Vars.h - UPDATED with all getters
#pragma once

#include <mutex>

enum AimTarget {
    HEAD,
    HEADv2,
    BODY
};

enum ProfileType {
    PROFILE_SAFE,
    PROFILE_BRUTAL,
    PROFILE_CUSTOM
};

struct Vars_t {
    // Boolean values
    bool UseCustomTelekillDistance;
    float TelekillDistance;
    bool ShowNinjaRunUI;
    bool Telekillv3;
    bool NinjaRun;
    bool NinjaRun_Slow;
    bool NinjaRun_Fast;
    int NinjaRunTick;
    bool BrutalMode;
    float BrutalTelekillDistance;
    bool Enable;
    bool Aimbot;
    float AimFov;
    bool ShowAITeleKillUI;
    int AimCheck;
    bool PerfectAim;
    int AimType;
    int AimWhen;
    bool SilentAim;
    bool isAimFov;
    bool Telekill;
    bool lines;
    bool EnableGhost;
    bool Muni;
    bool playertakedamage2T;
    bool UndergroundKill2;
    bool EnableGuestReset;
    bool PlayerTakeDamageV10;
    bool TeleVIP;
    bool SkipWallCheck;
    bool BypassEnabled;
    bool ShowNinjaRunButton;
    bool UndergroundKill;
    float SafeTeleportDistance;
    bool FakeKnocked;
    bool AITelekill;
    bool cameraDown;
    float CrosshairRange;
    float TelekillMaxDistance;
    bool ShowGhostButton;
    bool UpPlayer;
    bool ShowButtons;
    bool ShowFlyAlturaUI;
    bool ShowFlyNormalUI;
    bool AimNearestEnemy;
    bool AimInvisible;
    bool FlyPatchUI;
    AimTarget Target;
    bool fly;
    bool FlyAltura;
    float flySpeed;
    float flyHeight;
    float ESPLineThickness;
    float ESPBoxThickness;
    bool PlayerTakeDamageV7;
    float DamageCooldownTime;
    float LastDamageTime;
    bool Foreceq;
    bool ShowTeleVIPButton;
    bool ForceResult;
    bool antiCatapult;
    bool AutoWeaponSwitch;
    int WeaponSwitchMode;
    int DamageMultiplier;
    bool ShowUndergroundButton;
    bool Box;
    bool Anticheat;
    float fovLineColor[4];
    bool aimkillsend;
    bool Outline;
    bool Name;
    bool Health;
    bool Distance;
    bool fovaimglow;
    bool Skeleton;
    bool circlepos;
    bool headup;
    bool skeleton;
    bool SpeedHack;
    bool SpeedHackEnabled;
    int WeaponSwapSpeedSlider;
    bool silentrun;
    bool OOF;
    bool playertakedamage2;
    bool LapTa;
    float LapTaAmount;
    bool WeaponSwapSafe;
    int CurrentTab;
    bool enemycount;
    bool TeleVIP2;
    float AimSpeed;
    int currentProfile;
    bool AimPrediction;
    float AimSmooth;
    bool fastswitch2;
    bool ewid;
    bool ShowEn;
    bool Aimsilent69;
    bool ewid2;
    bool Aimkillsend;
    bool flyNoGravity;
    bool invisible;
    bool ShowSavePosButton;
    bool ShowClearAntiuButton;
    bool Glow;
    int TargetPriority;
    bool MagnetKill;
    bool ShowMagnetKillButton;
    bool rateoffire;
};

// Global vars
extern Vars_t Vars;
extern bool HighFPS;
extern bool autoFireEnabled;
extern bool StreamMode;
extern bool Guest2;
extern bool SpeedHack;

