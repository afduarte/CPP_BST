default: release

prepare: src/binary_tree.cpp
	@mkdir -p obj
	@g++ -c src/binary_tree.cpp -o obj/binary_tree.o -std=c++11
	@echo "Preparation ran successfully"

debug: src/test.cpp src/binary_tree.h
	@mkdir -p out
	@g++ -g src/my_test.cpp src/binary_tree.cpp -o out/BSTtest -std=c++11 -D DEBUG
	@echo "Debug Built Successfully"

release: clean prepare src/test.cpp src/binary_tree.h
	@mkdir -p out
	@echo "Compiling sources"
	@g++ src/test.cpp obj/binary_tree.o -o out/BSTtest -std=c++11 -D RELEASE
	@echo "Release Built Successfully"
	@echo "=========================="

test: release
	@out/BSTtest
	@echo "==============================="
	@echo "Tested successfully"
	@echo "==================="

clean:
	@echo "Removing out/ and obj/"
	@-rm -r out
	@-rm -r obj
	@echo "Project is clean"
