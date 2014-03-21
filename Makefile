TARGET = libBlitz2D.a
CC_FLAGS = -fstack-protector -Wl,-z,relro -Wl,-z,now -Wformat-security -Wpointer-arith -Wformat-nonliteral -Winit-self -Werror -std=c++0x -Wformat -Wl,-O1 -lSDL
all: $(TARGET)

clean:
	rm -fR Debug
	rm -fR Release
	rm -f libBlitz2D.a
	rm -f *.o

$(TARGET): Blitz2D.o Blitz_Buffer.o Blitz_Drawing.o Blitz_Font.o Blitz_Image.o Blitz_Input.o BlitzAPI.o
	ar rcs $(TARGET) Blitz2D.o Blitz_Buffer.o Blitz_Drawing.o Blitz_Font.o Blitz_Image.o Blitz_Input.o BlitzAPI.o 
	
%.o : %.cpp %.h
	g++ -c $@ -o $@.o $(CC_FLAGS)
	
BlitzAPI.o : BlitzAPI.cpp
	g++ -c BlitzAPI.cpp -o BlitzAPI.o $(CC_FLAGS)