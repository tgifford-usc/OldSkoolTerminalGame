#include "Console/Cartridge.h"
#include "Terminal.h"

void UCartridge::SetTerminal(Terminal* NewTerminal)
{
    TerminalInstance = NewTerminal;
}

void UCartridge::BeginPlay()
{
    UActorComponent::BeginPlay();
    checkf(TerminalInstance != nullptr, TEXT("No Terminal found"));
}

void UCartridge::PrintLine(const FString& Line) const
{
    TerminalInstance->PrintLine(Line);
}

void UCartridge::PrintLine(const TCHAR* Line) const
{
    TerminalInstance->PrintLine(FString(Line));
}

void UCartridge::ClearScreen() const
{
    TerminalInstance->ClearScreen();
}

void UCartridge::Exit() const
{
    TerminalInstance->Exit();
}
