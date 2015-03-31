set CWD=C:/Users/V/Documents/School/COMP189-Senior_Project/GTK_Testing/src/MonsterManagerTest_4
set GUI=GUI/Window.cpp GUI/ListFrame.cpp GUI/MonsterFrame.cpp GUI/ButtonsFrame.cpp
set Main=Main/Main.cpp
set MonsterManager=MonsterManager/MonsterManager.cpp
set exe=MMWindowTest_4
set directory=GTK32
set flags=-mwindows -Wall -mms-bitfields -std=c++11

g++ %Main% %GUI% %MonsterManager% -o %exe%.exe %flags% -IC:/%directory%/include/gtk-3.0 -IC:/%directory%/include/cairo -IC:/%directory%/include/pango-1.0 -IC:/%directory%/include/atk-1.0 -IC:/%directory%/include/pixman-1 -IC:/%directory%/include -IC:/%directory%/include/freetype2 -IC:/%directory%/include/libpng15 -IC:/%directory%/include/gdk-pixbuf-2.0 -IC:/%directory%/include/glib-2.0 -IC:/%directory%/lib/glib-2.0/include -LC:/%directory%/lib -lgtk-3 -lgdk-3 -lgdi32 -limm32 -lshell32 -lole32 -Wl,-luuid -lpangocairo-1.0 -lpangoft2-1.0 -lfreetype -lfontconfig -lpangowin32-1.0 -lgdi32 -lpango-1.0 -lm -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl
pause