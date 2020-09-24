SRC:=main.cpp resource.cpp
CXX_WIN:=i686-w64-mingw32-g++
CXX:=g++

All: format rcc win32

format:
	astyle -n --style=kr *.cpp *.h
rcc: $(SRC)
	$(CXX) --std=c++11 -o $@ $^
win32: $(SRC)
	$(CXX_WIN) --std=c++11 -o rcc.exe $^
clean: rcc rcc.exe
	rm -rf $^
