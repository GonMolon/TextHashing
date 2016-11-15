all: generator main seed_gen
main:
	g++ ./SimCalculator/main.cpp -o ./exp/SimCalculator.exe --std=c++11
generator:
	g++ ./Generator/main.cpp -o ./exp/generator.exe --std=c++11
seed_gen:
	g++ ./exp/seed_gen.cpp -o ./exp/seed_gen.exe --std=c++11
clear:
	rm -rf ./exp/*.exe
