CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := 
CC_FLAGS := 

solver.exe: $(OBJ_FILES)
	g++ -std=c++11 $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp
	g++ -std=c++11 $(CC_FLAGS) -c -o $@ $<

clean: 
	rm -f *.exe obj/*.o	
