#pragma once

#include "CoreMinimal.h"

class UCartridge;

class Terminal
{
public:
    Terminal() = default;

    void AttachCartridge(UCartridge* NewCartridge);
    void Run();

    void PrintLine(const FString& Line) const;
    void ClearScreen() const;
    void Exit();
    bool IsRunning() const;

private:
    UCartridge* Cartridge = nullptr;
    bool bIsRunning = true;
};
