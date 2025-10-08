build:
	g++ main.cpp -o BCB.bin
clean:
	rm -f *.bin *.exe
run:
	./BCB
buildWin:
	x86_64-w64-mingw32-g++ main.cpp -o BCB_win64.exe -static -static-libgcc -static-libstdc++
runWin:
	wine BCB_win64.exe
