tt.out: tt.cpp main.cpp tt.h
	g++ -ggdb -std=c++11 -o tt.out main.cpp tt.cpp bst.cpp
clean:
	rm *.out

