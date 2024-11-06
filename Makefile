CPP    = cl.exe
CFLAGS = /EHsc /c /O2
LINK   = link.exe
LIBS   = User32.lib Ole32.lib OleAut32.lib Strmiids.lib

all: main.exe

main.exe:	obj/main.obj obj/CVideo.obj
			taskkill /F /T /FI "IMAGENAME eq main.exe"
			$(LINK) obj/main.obj obj/CVideo.obj $(LIBS)
			
obj/main.obj:	main.cpp
				$(CPP) $(CFLAGS) /Foobj/main.obj main.cpp

obj/CVideo.obj:	CVideo.h CVideo.cpp 
				$(CPP) $(CFLAGS) /Foobj/CVideo.obj CVideo.cpp

start:			main.exe
			taskkill /F /T /FI "IMAGENAME eq main.exe"
			start main.exe