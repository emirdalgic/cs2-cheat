#include "cheats.h"

int main()
{
    const auto mem = Memory("cs2.exe");

    const auto client = mem.GetModuleAddress("client.dll");

    std::cout << "client.dll -> " << "0x" << std::hex << client << std::dec << std::endl;
    
    std::thread triggerBotThread([&mem, client]() {
        triggerBot(mem, client);
        });

    std::thread bunnyHopThread([&mem, client]() {
        bunnyHop(mem, client);
        });

    triggerBotThread.join();
    bunnyHopThread.join();
    
}
