all: libimgload.so
libimgload.so: IMGLoad.c IMGLoad.h
	$(CC) -o $(BUILD_DIR)/libimgload.so -shared -fPIC -Wall -Werror -I $(JAVA_HOME)/include IMGLoad.c -lpng12 -ljpeg

clean:
	rm -f *~ $(BUILD_DIR)/libimgload.so

#test: TestIMGLoad.class petra.png bobjagendorf_frozen.jpg
#	java -Djava.library.path=. TestIMGLoad petra.png bobjagendorf_frozen.jpg

.PHONY: all clean
