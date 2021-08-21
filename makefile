
pixel:
	g++ main.cpp -o bin/pixelme/pixelme.exe -std=c++17 -DSFML_STATIC -I "../sfml/include" -L "../sfml/lib-x64" -static -static-libgcc -static-libstdc++ -lsfml-graphics-s -lsfml-window-s -lsfml-network-s -lsfml-audio-s -lsfml-system-s -lwinmm -lopengl32 -lfreetype -lgdi32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lws2_32 -lComdlg32
c:
	del /F /Q "bin\\pixelme\\pixelme.exe"
