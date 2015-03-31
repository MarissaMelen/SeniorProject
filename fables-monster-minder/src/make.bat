set guifiles=GUI/AttackWindow.cpp GUI/ButtonsFrame.cpp GUI/EncounterWindow.cpp GUI/icon.cpp GUI/ListFrame.cpp GUI/monsterCustom.cpp GUI/MonsterFrame.cpp GUI/statusWindow.cpp GUI/Window.cpp 
set files=GUI/main.cpp attackmonster.cpp attribute.cpp calcElemDMG.cpp calcElement.cpp damagemonster.cpp element.cpp encounter.cpp monster.cpp monsterReader.cpp monsterstate.cpp status.cpp stringDuplication.cpp turn.cpp weapon.cpp
set exe="Sylvia's Monster Minder"
set directory=GTK32
set flags=-mwindows -Wall -mms-bitfields -std=c++11

g++ %guifiles% %files% -o %exe%.exe %flags% -IC:/%directory%/include/gtk-3.0 -I../include -IC:/%directory%/include/cairo -IC:/%directory%/include/pango-1.0 -IC:/%directory%/include/atk-1.0 -IC:/%directory%/include/pixman-1 -IC:/%directory%/include -IC:/%directory%/include/freetype2 -IC:/%directory%/include/libpng15 -IC:/%directory%/include/gdk-pixbuf-2.0 -IC:/%directory%/include/glib-2.0 -IC:/%directory%/lib/glib-2.0/include -LC:/%directory%/lib -lgtk-3 -lgdk-3 -lgdi32 -limm32 -lshell32 -lole32 -Wl,-luuid -lpangocairo-1.0 -lpangoft2-1.0 -lfreetype -lfontconfig -lpangowin32-1.0 -lgdi32 -lpango-1.0 -lm -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl
pause