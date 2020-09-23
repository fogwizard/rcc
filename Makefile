SRC:=main.cpp resource.cpp
CXX:=g++

All: rcc

rcc: $(SRC)
	$(CXX) --std=c++11 -o $@ $^
