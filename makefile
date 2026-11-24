cloudy.exe: main.cpp perlin.o worley.o perlin-worley.o utils.o
	g++ main.cpp perlin.o worley.o perlin-worley.o utils.o -o cloudy.exe

perlin.o: perlin.cpp
	g++ -c perlin.cpp

worley.o: worley.cpp
	g++ -c worley.cpp

perlin-worley.o: perlin-worley.cpp
	g++ -c perlin-worley.cpp

utils.o: utils.cpp
	g++ -c utils.cpp