tt.out: tt.cpp main.cpp tt.h
	g++ -std=c++11 -o tt.out main.cpp tt.cpp
clean:
	rm *.out

