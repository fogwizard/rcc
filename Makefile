SRC:=main.cpp resource.cpp
CXX:=g++

All: format rcc

format:
	astyle -n --style=kr *.cpp *.h
rcc: $(SRC)
	$(CXX) --std=c++11 -o $@ $^
