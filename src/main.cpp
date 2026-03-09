#include "Terminal.h"
#include "TerminalCartridge.h"

int main()
{
    Terminal TerminalApp;
    UTerminalCartridge Cartridge;

    TerminalApp.AttachCartridge(&Cartridge);
    TerminalApp.Run();

    return 0;
}
