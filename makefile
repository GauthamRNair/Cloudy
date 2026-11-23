cloudy.exe: main.cpp perlin.o worley.o
	g++ main.cpp perlin.o worley.o -o cloudy.exe

perlin.o: perlin.cpp
	g++ -c perlin.cpp

worley.o: worley.cpp
	g++ -c worley.cpp