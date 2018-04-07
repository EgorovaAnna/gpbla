all: test
	
test: test.o  Object.o GeoObject.o PVO.o Map.o UAV.o Aim.o ChangeHeight.o MapImage.o Image.o Point.o
	g++ -o test test.o GeoObject.o Object.o PVO.o Map.o UAV.o Aim.o MapImage.o Image.o Point.o -lm 
	
test.o: test.cpp
	g++ -c test.cpp
	
PVO.o: PVO.cpp PVO.h
	g++ -c PVO.cpp PVO.h GeoObject.h

GeoObject.o: GeoObject.cpp GeoObject.h
	g++ -c GeoObject.cpp GeoObject.h Object.h
	
Object.o: Object.cpp Object.h
	g++ -c Object.cpp Object.h
	
UAV.o: UAV.cpp UAV.h
	g++ -c UAV.cpp UAV.h Aim.h
	
Aim.o: Aim.cpp Aim.h
	g++ -c Aim.cpp Aim.h Object.h

ChangeHeight.o: ChangeHeight.cpp ChangeHeight.h
	g++ -c ChangeHeight.cpp ChangeHeight.h Object.h
	
Map.o: Map.cpp Map.h
	g++ -c Map.cpp Map.h UAV.h Object.h Aim.h
	
MapImage.o: MapImage.cpp MapImage.h
	g++ -c MapImage.cpp MapImage.h Map.h Image.h

Image.o: Image.cpp Image.h
	g++ -c Image.cpp Image.h Point.h
	
Point.o: Point.cpp Point.h
	g++ -c Point.cpp Point.h

clear:
	rm *.o *.gch
