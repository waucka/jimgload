all: libimageload.so
libimgload.so: IMGLoad.c IMGLoad.h
	$(CC) -o libimgload -shared -fPIC -Wall -Werror -I $(JAVA_HOME)/include IMGLoad.c -lpng12 -ljpeg

clean:
	rm -f *~ libimgload.so

#test: TestIMGLoad.class petra.png bobjagendorf_frozen.jpg
#	java -Djava.library.path=. TestIMGLoad petra.png bobjagendorf_frozen.jpg

.PHONY: all clean
