// Plain C++ compatibility layer for the Unreal teaching example.
#pragma once

#include "CoreMinimal.h"

class Terminal;

UCLASS(Abstract)
class TERMINALGAME_API UCartridge : public UActorComponent
{
    GENERATED_BODY()
public:
    virtual void OnInput(const FString& Input) PURE_VIRTUAL(UCartridge::OnInput,);

    void SetTerminal(Terminal* NewTerminal);

protected:
    void BeginPlay() override;

    void PrintLine(const FString& Line) const;
    void PrintLine(const TCHAR* Line) const;

    template<SIZE_T N, typename ...Types>
    void PrintLine(const TCHAR (&Fmt)[N], Types... Args) const
    {
        PrintLine(FString::Printf(Fmt, Args...));
    }

    void ClearScreen() const;
    void Exit() const;

private:
    friend class Terminal;
    Terminal* TerminalInstance = nullptr;
};
