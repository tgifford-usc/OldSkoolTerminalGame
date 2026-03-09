#include "Terminal.h"
#include "Console/Cartridge.h"

void Terminal::AttachCartridge(UCartridge* NewCartridge)
{
    Cartridge = NewCartridge;
    if (Cartridge != nullptr)
    {
        Cartridge->SetTerminal(this);
    }
}

void Terminal::Run()
{
    if (Cartridge == nullptr)
    {
        std::cerr << "No cartridge attached.\n";
        return;
    }

    Cartridge->BeginPlay();

    std::string RawInput;
    while (bIsRunning && std::getline(std::cin, RawInput))
    {
        Cartridge->OnInput(FString(RawInput));
    }
}

void Terminal::PrintLine(const FString& Line) const
{
    std::cout << Line << std::endl;
}

void Terminal::ClearScreen() const
{
    for (int i = 0; i < 40; ++i)
    {
        std::cout << std::endl;
    }
}

void Terminal::Exit()
{
    bIsRunning = false;
}

bool Terminal::IsRunning() const
{
    return bIsRunning;
}
