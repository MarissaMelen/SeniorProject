CXXFLAGS=-Wall -Wextra -pedantic -std=c++11 `pkg-config --cflags gtk+-3.0` -ggdb -O0
LDFLAGS = `pkg-config --libs gtk+-3.0`
INCLUDE = -I ../../include 
OBJECTS=Window.o ListFrame.o MonsterFrame.o ButtonsFrame.o main.o monsterCustom.o EncounterWindow.o AttackWindow.o statusWindow.o icon.o
SRCOBJECTS = monsterstate.o encounter.o element.o attribute.o monster.o stringDuplication.o monsterReader.o weapon.o damagemonster.o calcElement.o calcElemDMG.o attackmonster.o status.o turn.o

all: minder

minder: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(SRCOBJECTS) -o $@ $(LDFLAGS)
	mv $@ ..

main.o: main.cpp
	$(CXX)  $(INCLUDE) $(CXXFLAGS)  -c $< -o $@

%.o: %.cpp
	$(CXX)  $(INCLUDE) $(CXXFLAGS)  -c $< -o $@

clean::
	rm $(OBJECTS)
	rm $(SRCOBJECTS)

