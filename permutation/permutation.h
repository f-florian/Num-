#include <string>
#include <initializer_list>

class Permutation
{
public:
	// Constructors
	Permutation(size_t max):max{max};
	Permutation(size_t max, size_t e1, size_t e2):max{max};
	Permutation(std::initializer_list<size_t> list);
	Permutation(size_t max, std::initializer_list<size_t> list):max{max};
	Permutation(Permutation & other);
	Permutation(Permutation && other) noexcept;
	~Permutation() noexcept;
	
	// Assignment
	Permutation& operator= (operator &other);
	Permutation& operator= (operator &&other) noexcept;
	
	// Arithmetic
	Permutation operator* (const Permutation &other) const;
	void operator*= (const Permutation &other);
	Permutation inverse() const;
	void invert() noexcept;
	Permutation operator/ (const Permutation &other) const;
	void operator/= (const Permutation &other) noexcept;

	// Comparison
	bool operator==(const Permutation &other) const noexcept;
	bool operator<=(const Permutation &other) const noexcept;
	bool operator>=(const Permutation &other) const noexcept;
	bool operator!=(const Permutation &other) const noexcept;
	bool operator<(const Permutation &other) const noexcept;
	bool operator>(const Permutation &other) const noexcept;

	// Other
	std::string print() const noexcept;
	size_t operator[](const size_t point) const noexcept;
	
private:
	size_t max;
	size_t *permutation;
};
