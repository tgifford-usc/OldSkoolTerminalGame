// Fill out your copyright notice in the Description page of Project Settings.
#include "TerminalCartridge.h"

void UTerminalCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    // PrintLine("Welcome! Press <TAB> to begin."); // This line is only necessary in an actual Unreal project
    PrintLine("Would you like to play a dice duel? (y/n)");
}

void UTerminalCartridge::OnInput(const FString& Input) // When the player hits enter
{
    
}