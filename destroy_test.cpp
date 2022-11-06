
#include <iostream>
#include <memory>
#include <new>

struct Tracer {
	int value;
	~Tracer() {
		std::cout << value << " destructed\n";
	}
};

int main() {

	alignas(Tracer) unsigned char buffer[sizeof(Tracer) * 8];

	for (int i = 0; i < 8; ++i)
		new(buffer + sizeof(Tracer) * i) Tracer{ i };

	auto ptr = std::launder(reinterpret_cast<Tracer*>(buffer));

	std::destroy(ptr, ptr + 8);
	return 0;
}
