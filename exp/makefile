all: generator main seed_gen
main:
	g++ ../SimCalculator/main.cpp -o ./SimCalculator.exe --std=c++11
generator:
	g++ ../Generator/main.cpp -o ./generator.exe --std=c++11
seed_gen:
	g++ ./seed_gen.cpp -o seed_gen.exe --std=c++11
clear:
	rm -rf ./*.exe ./sources
