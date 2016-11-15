all: seed_gen sim_calculator file_generator LSH_calculator

sim_calculator:
	g++ ./SimCalculator/main.cpp -o ./exp/SimCalculator.exe --std=c++11
file_generator:
	g++ ./Generator/main.cpp -o ./exp/generator.exe --std=c++11
seed_gen:
	g++ ./exp/seed_gen.cpp -o ./exp/seed_gen.exe --std=c++11
LSH_calculator:
	g++ ./LSH/main.cpp -o ./exp/lsh.exe --std=c++11
clear:
	rm -rf ./exp/*.exe
