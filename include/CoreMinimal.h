#pragma once

#include <algorithm>
#include <cctype>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <exception>
#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

using int32 = std::int32_t;
using uint32 = std::uint32_t;
using SIZE_T = std::size_t;
using TCHAR = char;

template <typename T>
using TArray = std::vector<T>;

class FString
{
public:
    FString() = default;
    FString(const char* Text) : Value(Text == nullptr ? "" : Text) {}
    FString(const std::string& Text) : Value(Text) {}
    FString(std::string&& Text) noexcept : Value(std::move(Text)) {}

    FString& operator=(const char* Text)
    {
        Value = (Text == nullptr ? "" : Text);
        return *this;
    }

    FString& operator=(const std::string& Text)
    {
        Value = Text;
        return *this;
    }

    const char* c_str() const { return Value.c_str(); }
    const char* operator*() const { return Value.c_str(); }
    bool IsEmpty() const { return Value.empty(); }
    int32 Len() const { return static_cast<int32>(Value.size()); }

    FString Left(int32 Count) const
    {
        if (Count <= 0) return FString("");
        return FString(Value.substr(0, static_cast<std::size_t>(Count)));
    }

    FString RightChop(int32 Count) const
    {
        if (Count <= 0) return *this;
        const std::size_t Start = static_cast<std::size_t>(std::min<int32>(Count, Len()));
        return FString(Value.substr(Start));
    }

    void RemoveAt(int32 Index)
    {
        if (Index >= 0 && Index < Len())
        {
            Value.erase(Value.begin() + Index);
        }
    }

    FString ToLower() const
    {
        std::string Copy = Value;
        std::transform(Copy.begin(), Copy.end(), Copy.begin(), [](unsigned char Character) {
            return static_cast<char>(std::tolower(Character));
        });
        return FString(std::move(Copy));
    }

    FString ToUpper() const
    {
        std::string Copy = Value;
        std::transform(Copy.begin(), Copy.end(), Copy.begin(), [](unsigned char Character) {
            return static_cast<char>(std::toupper(Character));
        });
        return FString(std::move(Copy));
    }

    bool Split(const char* Delimiter, FString* LeftPart, FString* RightPart) const
    {
        const std::string Delim = (Delimiter == nullptr ? "" : Delimiter);
        if (Delim.empty()) return false;
        const std::size_t Position = Value.find(Delim);
        if (Position == std::string::npos) return false;
        if (LeftPart != nullptr) *LeftPart = FString(Value.substr(0, Position));
        if (RightPart != nullptr) *RightPart = FString(Value.substr(Position + Delim.size()));
        return true;
    }

    static FString Printf(const char* Format, ...)
    {
        va_list Args1;
        va_start(Args1, Format);

        va_list Args2;
        va_copy(Args2, Args1);

        const int Length = std::vsnprintf(nullptr, 0, Format, Args1);
        va_end(Args1);

        if (Length < 0)
        {
            va_end(Args2);
            return FString("");
        }

        std::string Buffer(static_cast<std::size_t>(Length) + 1, '\0');
        std::vsnprintf(&Buffer[0], Buffer.size(), Format, Args2);
        va_end(Args2);

        Buffer.resize(static_cast<std::size_t>(Length));
        return FString(std::move(Buffer));
    }

    operator const std::string&() const { return Value; }
    operator std::string&() { return Value; }

    friend FString operator+(const FString& A, const FString& B) { return FString(A.Value + B.Value); }
    friend FString operator+(const FString& A, const char* B) { return FString(A.Value + std::string(B == nullptr ? "" : B)); }
    friend FString operator+(const char* A, const FString& B) { return FString(std::string(A == nullptr ? "" : A) + B.Value); }
    FString& operator+=(const FString& Other) { Value += Other.Value; return *this; }
    FString& operator+=(const char* Other) { Value += (Other == nullptr ? "" : Other); return *this; }
    FString& Append(const FString& Other) { Value += Other.Value; return *this; }
    FString& Append(const char* Other) { Value += (Other == nullptr ? "" : Other); return *this; }
    FString& Append(const std::string& Other) { Value += Other; return *this; }

    friend bool operator==(const FString& A, const FString& B) { return A.Value == B.Value; }
    friend bool operator!=(const FString& A, const FString& B) { return A.Value != B.Value; }
    friend std::ostream& operator<<(std::ostream& Stream, const FString& Text) { Stream << Text.Value; return Stream; }

private:
    std::string Value;
};

#define TEXT(x) x
#define UCLASS(...)
#define GENERATED_BODY()
#define TERMINALGAME_API
#define UFUNCTION(...)
#define UPROPERTY(...)
#define BlueprintAssignable
#define BlueprintCallable
#define BlueprintPure
#define Category(...)
#define ClassGroup(...)
#define meta(...)
#define EditAnywhere
#define Abstract
#define PURE_VIRTUAL(Func, Body) = 0
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(Name, Type, ParamName) struct Name { void Broadcast(const Type&) const {} }

class UActorComponent
{
public:
    virtual ~UActorComponent() = default;
    virtual void BeginPlay() {}
};

#define Super UCartridge

inline void CheckfImpl(bool Condition, const char* Message)
{
    if (!Condition)
    {
        throw std::runtime_error(Message == nullptr ? "checkf failed" : Message);
    }
}

#define checkf(Condition, Format, ...) CheckfImpl((Condition), FString::Printf((Format), ##__VA_ARGS__).c_str())

class FMath
{
public:
    static int32 RandRange(int32 Min, int32 Max)
    {
        if (Min > Max)
        {
            std::swap(Min, Max);
        }
        static std::random_device RandomDevice;
        static std::mt19937 Generator(RandomDevice());
        std::uniform_int_distribution<int32> Distribution(Min, Max);
        return Distribution(Generator);
    }
};

inline FString TrimCopy(const FString& Text)
{
    const std::string& Raw = static_cast<const std::string&>(Text);
    const auto Start = Raw.find_first_not_of(" \t\r\n");
    if (Start == std::string::npos)
    {
        return FString("");
    }
    const auto End = Raw.find_last_not_of(" \t\r\n");
    return FString(Raw.substr(Start, End - Start + 1));
}

inline FString ToLowerCopy(const FString& Text)
{
    return Text.ToLower();
}

inline FString ToUpperCopy(const FString& Text)
{
    return Text.ToUpper();
}