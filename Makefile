all:
	g++ -O3 -std=c++11 hw3.cpp -o Nonogram.out
run:
	./Nonogram.out
clean:
	re -rf Nonogram.out