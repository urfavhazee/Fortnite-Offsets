pragma once
#include <cstdint>
#include <unordered_map>
#include <fstream>

namespace offsets {

    // ===== Globals =====
    uintptr_t UWorld = 0x17B96228;
    uintptr_t UWorldXorKey = 0x7B40E797ULL;
    uintptr_t GNames = 0x17A50D00;
    uintptr_t GEngine = 0x175CAC68;
    uintptr_t GObjects = 0x17B2DC58;
    uintptr_t GObjectsCount = 0x17560ED4;
    uintptr_t StaticFindObject = 0x5E4332;

    uintptr_t ProcessEvent = 0x949CA;
    uintptr_t ProcessEventIndex = 0x98;

    // ===== Player / Controller =====
    uintptr_t LocalPlayers = 0x38;
    uintptr_t PlayerController = 0x30;
    uintptr_t PlayerCameraManager = 0x368;
    uintptr_t AcknowledgedPawn = 0x358;
    uintptr_t PlayerState = 0x2D0;
    uintptr_t TeamIndex = 0x11B1;
    uintptr_t bIsDying = 0x728;
    uintptr_t bIsDBNO = 0x841;
    uintptr_t bIsABot = 0x2BA;

    uintptr_t Platform = 0x440;
    uintptr_t TargetedFortPawn = 0x1830;
    uintptr_t KillScore = 0x11C8;
    uintptr_t PlayerName = 0xA08;
    uintptr_t PlayerNamePrivate = 0x348;
    uintptr_t RankedProgress = 0xD8;
    uintptr_t PlayerAimOffset = 0x2BD0;

    // ===== World =====
    uintptr_t OwningGameInstance = 0x240;
    uintptr_t GameState = 0x1C8;
    uintptr_t PlayerArray = 0x2C8;
    uintptr_t Levels = 0x1E0;

    // ===== Actor / Pawn =====
    uintptr_t AActor = 0x208;
    uintptr_t RootComponent = 0x1B0;
    uintptr_t PawnPrivate = 0x328;

    // ===== Mesh / Components =====
    uintptr_t Mesh = 0x330;
    uintptr_t BoneArray = 0x5F0;
    uintptr_t BoneCache = 0x5F8;

    uintptr_t ComponentToWorld = 0x1E0;
    uintptr_t ComponentVelocity = 0x188;
    uintptr_t AdditionalAimOffset = 0x2BA0;
    uintptr_t LastRenderTime = 0x328;
    uintptr_t LocationUnderReticle = 0x2A50;

    // ===== Camera =====
    uintptr_t CameraLocation = 0x178;
    uintptr_t CameraRotation = 0x188;

    // ===== Weapons =====
    uintptr_t CurrentWeapon = 0x990;
    uintptr_t WeaponData = 0x688;
    uintptr_t AmmoCount = 0x11CC;
    uintptr_t ReloadAnimation = 0x1608;
    uintptr_t ServerWorldTimeSecondsDelta = 0x2E8;

    // ===== Items / Loot =====
    uintptr_t PrimaryPickupItemEntry = 0x3A8;
    uintptr_t ItemName = 0x40;
    uintptr_t ItemType = 0xA8;
    uintptr_t ItemTier = 0xA2;
    uintptr_t ItemRarity = 0xAA;
    uintptr_t Rarity = 0xAA;

    // ===== Misc =====
    uintptr_t HabaneroComponent = 0x948;
};

// Offsets from https://github.com/urfavhazee/Fortnite-Offsets/
