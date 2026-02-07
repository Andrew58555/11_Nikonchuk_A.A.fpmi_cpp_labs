# without fsanitize
# run program with "#ifdef SIMPLE" part
# terminal command: make simple_inv
simple_inv:
	g++ -std=c++17 -DSIMPLE main.cpp -o main.out
	./main.out
	rm main.out



# with fsanitize
# run program with "#ifdef SIMPLE" part
# terminal command: make simple_inv_asan
simple_inv_asan:
	g++ -std=c++17 -DSIMPLE -fsanitize=address,undefined,leak main.cpp -o main.out
	./main.out
	rm main.out


# with fsanitize on Mac
# run program with "#ifdef SIMPLE" part
# terminal command: make simple_inv_asan_mac
simple_inv_asan_mac:
	g++ -std=c++17 -DSIMPLE -fsanitize=address,undefined main.cpp -o main.out
	./main.out
	rm main.out


# without fsanitize
# run program with "#ifdef RANDOM" part
# terminal command: make generate_inv
random_inv:
	g++ -std=c++17 -DRANDOM main.cpp -o main.out
	./main.out
	rm main.out


# with fsanitize
# run program with "#ifdef RANDOM" part
# terminal command: make generate_inv_asan
random_inv_asan:
	g++ -std=c++17 -DRANDOM -fsanitize=address,undefined,leak main.cpp -o main.out
	./main.out
	rm main.out


# with fsanitize on Mac
# run program with "#ifdef RANDOM" part
# terminal command: make generate_inv_asan_mac
random_inv_asan_mac:
	g++ -std=c++17 -DRANDOM -fsanitize=address,undefined main.cpp -o main.out
	./main.out
	rm main.out
