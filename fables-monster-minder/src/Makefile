LDFLAGS = -lcurses -lm
CXXFLAGS = -std=c++11 -ggdb -Wall -Wextra -pedantic -Werror -O0
INCLUDE = -I ../include/
OBJECTS = monsterstate.o encounter.o element.o attribute.o monster.o stringDuplication.o monsterReader.o weapon.o damagemonster.o calcElement.o calcElemDMG.o attackmonster.o status.o turn.o

all: minder

minder: $(OBJECTS)
	cp $(OBJECTS) GUI
	$(MAKE) -C GUI
	mv minder ..

calcElement.o: calcElement.cpp
	$(CXX) $(INCLUDE) -std=c++11 -ggdb -Wall -Wextra -pedantic -O0 -c $< -o $@

%.o: %.cpp 
	$(CXX) $(INCLUDE) $(CXXFLAGS) -c $< -o $@

clean::
	$(MAKE) -C GUI -k clean
	rm $(OBJECTS)

