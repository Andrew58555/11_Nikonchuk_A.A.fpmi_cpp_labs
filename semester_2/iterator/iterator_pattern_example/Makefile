# without fsanitize
# terminal command: make iterator_pattern
iterator_pattern:
	g++ -Wall -Wextra simple_container.cpp container_iterator.cpp main.cpp
	./a.out
	rm a.out


# with fsanitize
# terminal command: make iterator_pattern_asan
iterator_pattern_asan:
	g++ -Wall -Wextra -fsanitize=address,undefined,leak simple_container.cpp container_iterator.cpp main.cpp
	./a.out
	rm a.out


# with fsanitize on Mac
# terminal command: make iterator_pattern_asan_mac
iterator_pattern_asan_mac:
	g++ -Wall -Wextra -fsanitize=address,undefined simple_container.cpp container_iterator.cpp main.cpp
	./a.out
	rm a.out
