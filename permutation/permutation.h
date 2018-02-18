#include <string>
#include <initializer_list>

class Permutation
{
public:
	// Constructors
	Permutation(size_t maximum);
	Permutation(size_t maximum, size_t e1, size_t e2);
	Permutation(std::initializer_list<size_t> list);
	Permutation(size_t maximum, std::initializer_list<size_t> list);
	Permutation(const Permutation & other);
	Permutation(Permutation && other) noexcept;
	~Permutation() noexcept;
	
	// Assignment
	Permutation& operator=(const Permutation &other)=delete;
	Permutation& operator=(Permutation &&other) noexcept;
	
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
	size_t operator[](const size_t point) const;
	void swap(const size_t x1, const size_t x2);
	void swapExisting(const size_t x1, const size_t x2) noexcept
	void swap(Permutation &&other) noexcept;
private:
	size_t maximum;
	size_t *permutation;
};
