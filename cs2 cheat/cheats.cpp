#include "cheats.h"


void triggerBot(const Memory& mem, const uintptr_t client) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        if (GetAsyncKeyState(0x5) < 0) {
            const auto& local_player_pawn = mem.Read<uintptr_t>(client + client_dll::dwLocalPlayerPawn);
            const auto& local_player_id = mem.Read<int32_t>(local_player_pawn + C_CSPlayerPawnBase::m_iIDEntIndex);

            if (local_player_id > 0) {
                const auto& entityList = mem.Read<uintptr_t>(client + client_dll::dwEntityList);
                const std::vector<uintptr_t> enemies = mem.ReadVector<uintptr_t>(entityList, 64);

                for (const auto& enemy : enemies) {
                    const auto& entityTeam = mem.Read<int32_t>(enemy + C_BaseEntity::m_iTeamNum);
                    const auto& local_player_team = mem.Read<int32_t>(local_player_pawn + C_BaseEntity::m_iTeamNum);

                    if (entityTeam != local_player_team) {
                        const auto& enemyHp = mem.Read<int32_t>(enemy + C_BaseEntity::m_iHealth);
                        if (enemyHp > 0) {
                            std::this_thread::sleep_for(std::chrono::milliseconds(5));
                            mem.Write(client + client_dll::dwForceAttack, 65537);
                            std::this_thread::sleep_for(std::chrono::milliseconds(2));
                            mem.Write(client + client_dll::dwForceAttack, 256);
                            break;
                        }
                    }
                }
            }
        }
    }
}


void bunnyHop(const Memory& mem, const uintptr_t client) {

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        const auto local_player_pawn = mem.Read<std::uintptr_t>(client + client_dll::dwLocalPlayerPawn);

        if (local_player_pawn == 0)
            continue;

        const auto flags = mem.Read<std::uint32_t>(local_player_pawn + C_BaseEntity::m_fFlags);

        const bool inAir = flags & (1 << 0);
        const bool spacePressed = GetAsyncKeyState(VK_SPACE);
        auto fJump = mem.Read<DWORD>(client + client_dll::dwForceJump);

        if (spacePressed && inAir && fJump != 65537) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            mem.Write(client + client_dll::dwForceJump, 65537);
        }
        else if (!spacePressed && inAir && fJump == 65537) {
            mem.Write(client + client_dll::dwForceJump, 256);
        }
        else if (!inAir && fJump == 65537) {
            mem.Write(client + client_dll::dwForceJump, 256);
        }
    }
}