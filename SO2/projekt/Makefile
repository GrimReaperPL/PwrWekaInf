CC = g++
CFLAGS = -Wall -Wextra -std=c++11 -g -pthread -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

TARGET = so2
SOURCE = Main.cpp App.cpp Timer.cpp Screen.cpp Texture.cpp CarSquare.cpp

all: $(TARGET)
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)
	
.PHONY: clean

clean:
	$(RM) $(TARGET)
