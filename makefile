default: release

prepare: src/binary_tree.cpp
	mkdir -p obj
	g++ -c src/binary_tree.cpp -o obj/binary_tree.o -std=c++11

debug: prepare src/test.cpp src/binary_tree.h
	mkdir -p out
	g++ -g src/test.cpp src/binary_tree.cpp -o out/BSTtest -std=c++11 -D DEBUG

release: prepare src/test.cpp src/binary_tree.h
	mkdir -p out
	g++ src/test.cpp obj/binary_tree.o -o out/BSTtest -std=c++11 -D RELEASE

test: release
	out/BSTtest
	echo "Built and tested successfully"

clean:
	rm -r out
	rm -r obj