# LifeOGame
Literally just conway's game of life.

All in a terminal.

With pdcurses.

# Controls
**SPACE** to pause

**MOUSE1** to toggle a cell

**RIGHT ARROW** to step forward

**r** to clear the screen

**q** to quit

# Compilation For Not Windows
if you've got a mac you can compile it with ncurses and it _should_ (hopefully) work. You'll need Microsoft Visual Studio 2019 to open the .sln file, and the enviornment variable **CURSES** (all caps) pointing to where ncurses.h is. You'll also need to modify the library directories to include wherever the ncurses.lib file is, and change the linker libraries to look for ncurses.lib instead of pdcurses.lib.

I'll be honest though, this is all theoretical, I don't have a mac to test it on.
