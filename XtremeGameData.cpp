#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "pch-il2cpp.h"

enum class DataDeathReason { None, Disconnect, Kill /* Define other reasons as needed */ };

class PlayerStates {
public:
    static std::unordered_map<int, std::shared_ptr<PlayerStates>> AllPlayerStates;

    std::shared_ptr<PlayerControl> Player;
    std::string PlayerName;
    int PlayerColor;
    bool IsImpostor = false;
    bool IsDead = false;
    bool IsDisconnected = false;
    bool Murdered = false;
    bool Exiled = false;
    bool RoleAssigned = false;
    RoleTypes__Enum RoleWhenAlive;
    RoleTypes__Enum RoleAfterDeath;
    DataDeathReason RealDeathReason = DataDeathReason::None;
    std::shared_ptr<PlayerStates> RealKiller = nullptr;
    int TotalTaskCount = 0;
    int CompleteTaskCount = 0;
    int KillCount = 0;

    PlayerStates(std::shared_ptr<PlayerControl> player, std::string playerName, int colorId)
        : Player(player), PlayerName(playerName), PlayerColor(colorId) {}

    bool IsTaskCompleted() const {
        return TotalTaskCount == CompleteTaskCount;
    }

    void SetDead() {
        IsDead = true;
    }

    void SetDisconnected() {
        IsDisconnected = true;
        SetDead();
        SetDeathReason(DataDeathReason::Disconnect);
    }

    void SetIsImp(bool isImp) {
        IsImpostor = isImp;
    }

    void SetRole(RoleTypes__Enum role) {
        if (!RoleAssigned)
            RoleWhenAlive = role;
        else
            RoleAfterDeath = role;
        RoleAssigned = true;
    }

    void SetDeathReason(DataDeathReason deathReason, bool focus = false) {
        if (IsDead && RealDeathReason == DataDeathReason::None || focus)
            RealDeathReason = deathReason;
    }

    void SetRealKiller(std::shared_ptr<PlayerStates> killer) {
        SetDead();
        SetDeathReason(DataDeathReason::Kill);
        killer->KillCount++;
        Murdered = true;
        RealKiller = killer;
    }

    void SetTaskTotalCount(int taskTotalCount) {
        TotalTaskCount = taskTotalCount;
    }

    void CompleteTask() {
        CompleteTaskCount++;
    }




    static std::shared_ptr<PlayerStates> GetPlayerStatesById(int id) {
        auto it = AllPlayerStates.find(id);
        return (it != AllPlayerStates.end()) ? it->second : nullptr;
    }

    static std::string GetPlayerNameById(int id) {
        auto data = GetPlayerStatesById(id);
        return data ? data->PlayerName : "";
    }

    static int GetLongestNameByteCount() {
        int maxByteCount = 0;
        for (const auto& [id, data] : AllPlayerStates) {
            int byteCount = static_cast<int>(data->PlayerName.length()); // Simplified byte count
            maxByteCount = (std::max)(maxByteCount, byteCount);
        }
        return maxByteCount;
    }
};

std::unordered_map<int, std::shared_ptr<PlayerStates>> PlayerStates::AllPlayerStates;

class PlayerVersion {
public:
    std::string Version;
    std::string Tag;
    std::string ForkId;

    PlayerVersion(const std::string& ver, const std::string& tagStr, const std::string& forkId)
        : Version(ver), Tag(tagStr), ForkId(forkId) {}

    bool IsEqual(const PlayerVersion& pv) const {
        return pv.Version == Version && pv.Tag == Tag;
    }
};

// GameStates Class
class GameStates {
public:
    static bool InGame;
    static bool AlreadyDied;
    static bool IsModHost;
    static bool IsLobby;
    static bool IsInGame;
    static bool IsEnded;
    static bool IsNotJoined;
    static bool IsOnlineGame;
    static bool IsLocalPlayerGame;
    static bool IsFreePlay;
    static bool IsInTask;
    static bool IsMeeting;
    static bool IsVoting;
    static bool IsCountDown;
    static bool IsShip;
    static bool IsCanMove;
    static bool IsDead;
    static bool IsNormalGame;
    static bool IsHideNSeek;
    static bool SkeldIsActive;
    static bool MiraHQIsActive;
    static bool PolusIsActive;
    static bool DleksIsActive;
    static bool AirshipIsActive;
    static bool FungleIsActive;
    static bool IsVanillaServer;

};

// Utility Functions
std::shared_ptr<PlayerStates> GetPlayerStates(const std::shared_ptr<PlayerControl>& pc) {
    return PlayerStates::GetPlayerStatesById(pc->fields.PlayerId);
}

bool IsAlive(const std::shared_ptr<PlayerControl>& pc) {
    auto data = GetPlayerStates(pc);
    return GameStates::IsLobby || (data && !data->IsDead);
}

std::string GetDataName(const std::shared_ptr<PlayerControl>& pc) {
    auto data = GetPlayerStates(pc);
    return data ? data->PlayerName : "";
}

void SetDead(const std::shared_ptr<PlayerControl>& pc) {
    auto data = GetPlayerStates(pc);
    if (data) data->SetDead();
}

void SetDisconnected(const std::shared_ptr<PlayerControl>& pc) {
    auto data = GetPlayerStates(pc);
    if (data) data->SetDisconnected();
}

void SetIsImp(const std::shared_ptr<PlayerControl>& pc, bool isImp) {
    auto data = GetPlayerStates(pc);
    if (data) data->SetIsImp(isImp);
}

void SetRole(const std::shared_ptr<PlayerControl>& pc, RoleTypes__Enum role) {
    auto data = GetPlayerStates(pc);
    if (data) data->SetRole(role);
}

void SetDeathReason(const std::shared_ptr<PlayerControl>& pc, DataDeathReason deathReason, bool focus = false) {
    auto data = GetPlayerStates(pc);
    if (data) data->SetDeathReason(deathReason, focus);
}

void SetRealKiller(const std::shared_ptr<PlayerControl>& pc, const std::shared_ptr<PlayerControl>& killer) {
    auto data = GetPlayerStates(pc);
    auto killerData = GetPlayerStates(killer);
    if (data && killerData) data->SetRealKiller(killerData);
}

void SetTaskTotalCount(const std::shared_ptr<PlayerControl>& pc, int taskTotalCount) {
    auto data = GetPlayerStates(pc);
    if (data) data->SetTaskTotalCount(taskTotalCount);
}

void OnCompleteTask(const std::shared_ptr<PlayerControl>& pc) {
    auto data = GetPlayerStates(pc);
    if (data) data->CompleteTask();
}

bool IsModClient(const std::shared_ptr<PlayerControl>& player) {
    // Implement this logic based on your specific requirements
    return false;
}
