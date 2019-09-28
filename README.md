# LifeOGame
Literally just conway's game of life.

All in a terminal.

With pdcurses (which is cool)

# Controls
**SPACE** to pause

**MOUSE1** to toggle a cell

**RIGHT ARROW** to step forward

**r** to clear the screen

**q** to quit

# Compilation For Not Windows
if you've got a mac you can compile it with ncurses and it _should_ (hopefully) work. You'll need Microsoft Visual Studio 2019 to open the .sln file. Modify the include directories for wherever ncurses.h is, the code should auto-switch to ncurses. You'll also need to modify the library directories to include wherever the ncurses.lib file is, and change the linker libraries to look for ncurses.lib instead of pdcurses.lib.

I'll be honest though, this is all theoretical, I don't have a mac to test it on.

# Legal
Just GPL. Please keep it open source in other words. (Although what you would do that is commercial with this is beyond me)
