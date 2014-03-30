all: libjimgload.so
libjimgload.so: IMGLoad.c IMGLoad.h
	$(CC) -o $(BUILD_DIR)/libjimgload.so -shared -fPIC -Wall -Werror -I $(JAVA_HOME)/include IMGLoad.c -lpng12 -ljpeg

clean:
	rm -f *~ $(BUILD_DIR)/libjimgload.so

.PHONY: all clean
