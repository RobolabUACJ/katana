LIBS=`pkg-config --cflags --libs playerc++`

all:
	g++ -o eeg_client main.cpp $(LIBS) eeg.cpp

clean:
	rm -f *.o *.so

cfg:
	export PKG_CONFIG_PATH="/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH"

