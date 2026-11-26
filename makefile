cloudy.exe: main.cpp perlin.o worley.o perlin-worley.o utils.o texture.o raymarcher.o consts.h
	g++ main.cpp perlin.o worley.o perlin-worley.o utils.o texture.o raymarcher.o -fopenmp -O2 -Wall -o cloudy.exe

utils.o: utils.cpp
	g++ -c utils.cpp

perlin.o: perlin.cpp consts.h
	g++ -c perlin.cpp

worley.o: worley.cpp
	g++ -c worley.cpp

perlin-worley.o: perlin-worley.cpp
	g++ -c perlin-worley.cpp

texture.o: texture.cpp consts.h
	g++ -c texture.cpp

raymarcher.o: raymarcher.cpp consts.h
	g++ -c raymarcher.cpp