#include "MagicalContainer.hpp"
#include <math.h>
#include <iostream>
#include <algorithm>

using namespace ariel;
using namespace std;

// Check if a number is prime
bool MagicalContainer::isPrime(int num) const
{
    if (num <= 1)
        return false;
    for (int i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

// Copy constructor
MagicalContainer::MagicalContainer(const MagicalContainer &other)
    : regular(other.regular),
      cross(other.cross),
      sort(other.sort),
      prime(other.prime) {}

// Copy assignment operator
MagicalContainer &MagicalContainer::operator=(const MagicalContainer &other)
{
    if (this == &other)
        return *this;

    regular = other.regular;
    cross = other.cross;
    sort = other.sort;
    prime = other.prime;

    return *this;
}

// Move constructor
MagicalContainer::MagicalContainer(MagicalContainer &&other) noexcept
    : regular(std::move(other.regular)),
      cross(std::move(other.cross)),
      sort(std::move(other.sort)),
      prime(std::move(other.prime)) {}

// Move assignment operator
MagicalContainer &MagicalContainer::operator=(MagicalContainer &&other) noexcept
{
    if (this == &other)
        return *this;

    regular = std::move(other.regular);
    cross = std::move(other.cross);
    sort = std::move(other.sort);
    prime = std::move(other.prime);

    return *this;
}

// Copy assignment operator for BasicIterator
MagicalContainer::BasicIterator &MagicalContainer::BasicIterator::operator=(const BasicIterator &other)
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::runtime_error("Cant assign from iterator of a different MagicalContainer");

    magicalContainer = other.magicalContainer;
    pos = other.pos;
    it = other.it;
    return *this;
}

// Helper functions
void ariel::MagicalContainer::initCross(std::vector<int *> &cross)
{
    cross.clear();
}

void ariel::MagicalContainer::updateFromStart(std::vector<int *>::iterator &start_it, std::vector<int *> &cross)
{
    cross.push_back(*start_it);
    ++start_it;
}

void ariel::MagicalContainer::updateFromEnd(std::vector<int *>::reverse_iterator &end_it, std::vector<int *> &cross)
{
    cross.push_back(*end_it);
    ++end_it;
}

// MagicalContainer member function
void MagicalContainer::optimise_cross()
{
    initCross(cross);
    auto start_it = sort.begin();
    auto end_it = sort.rbegin();

    bool add_from_start = true;

    for (int i = 0; i < sort.size(); i++)
    {
        if (add_from_start)
        {
            updateFromStart(start_it, cross);
        }
        else
        {
            updateFromEnd(end_it, cross);
        }
        add_from_start = !add_from_start;
    }
}

bool ariel::MagicalContainer::BasicIterator::compareIntPointers(int *a, int *b)
{
    return *a < *b;
}

// The 'optimise_sort()' function utilizing the helper function
void MagicalContainer::optimise_sort()
{
    sort.clear();

    for (auto it = regular.begin(); it != regular.end(); ++it)
    {
        sort.push_back(&(*it));
    }

    std::sort(sort.begin(), sort.end(), BasicIterator::compareIntPointers);
}

// Update the prime vector
void MagicalContainer::optimise_prime()
{
    prime.clear();

    for (auto it = regular.begin(); it != regular.end(); ++it)
    {
        if (isPrime(*it))
        {
            prime.push_back(&(*it));
        }
    }
}

// Default constructor
MagicalContainer::MagicalContainer() = default;

// Destructor
MagicalContainer::~MagicalContainer() = default;

// Add an element to the container
void MagicalContainer::addElement(int element)
{
    regular.push_back(element);
    optimise_prime();
    optimise_sort();
    optimise_cross();
}

// Remove an element from the container
void MagicalContainer::removeElement(int element)
{
    auto it = std::find(regular.begin(), regular.end(), element);

    if (it == regular.end())
    {
        throw std::runtime_error("Element not found in container");
        return;
    }

    int *p = &(*it);

    regular.erase(it);

    sort.erase(std::find(sort.begin(), sort.end(), p));

    if (isPrime(element))
    {
        prime.erase(std::find(prime.begin(), prime.end(), p));
    }
    optimise_prime();
    optimise_cross();
    optimise_sort();
}

// Get the size of the container
size_t MagicalContainer::size() const
{
    return regular.size();
}

// Equality comparison operator
bool MagicalContainer::operator==(const MagicalContainer &other) const
{
    return regular == other.regular;
}

// Inequality comparison operator
bool MagicalContainer::operator!=(const MagicalContainer &other) const
{
    return regular != other.regular;
}

// BasicIterator constructor
MagicalContainer::BasicIterator::BasicIterator(MagicalContainer &magicalContainer) : magicalContainer(&magicalContainer), pos(0){};

// BasicIterator copy constructor
MagicalContainer::BasicIterator::BasicIterator(const BasicIterator &other) : magicalContainer(other.magicalContainer), pos(other.pos){};

// BasicIterator equality comparison operator
bool MagicalContainer::BasicIterator::operator==(const BasicIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos == other.pos;
}

// BasicIterator inequality comparison operator
bool MagicalContainer::BasicIterator::operator!=(const BasicIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos != other.pos;
}

// BasicIterator less than comparison operator
bool MagicalContainer::BasicIterator::operator<(const BasicIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos < other.pos;
}

// BasicIterator greater than comparison operator
bool MagicalContainer::BasicIterator::operator>(const BasicIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos > other.pos;
}

// BasicIterator destructor
MagicalContainer::BasicIterator::~BasicIterator() = default;

// BasicIterator move constructor
MagicalContainer::BasicIterator::BasicIterator(BasicIterator &&other) noexcept
    : magicalContainer(other.magicalContainer), pos(other.pos), it(std::move(other.it)) {}

// AscendingIterator constructor
MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &magicalContainer) : BasicIterator(magicalContainer)
{
    it = magicalContainer.sort.begin();
};

// AscendingIterator copy constructor
MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : BasicIterator(other){};

// AscendingIterator copy assignment operator
MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::runtime_error("Cant copy from another container");
    magicalContainer = other.magicalContainer;
    pos = other.pos;
    it = other.it;
    return *this;
}

// Dereference operator for AscendingIterator
int MagicalContainer::AscendingIterator::operator*() const
{
    if (it == magicalContainer->sort.end())
        throw std::runtime_error("Iterator is out of range");
    return **it;
}

// Pre-increment operator for AscendingIterator
MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
{
    if (it == magicalContainer->sort.end())
    {
        throw std::runtime_error("Iterator is out of range");
        return *this;
    }
    ++it;
    ++pos;
    return *this;
}

// Begin function for AscendingIterator
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
{
    AscendingIterator temp(*this);
    temp.it = magicalContainer->sort.begin();
    temp.pos = 0;
    return temp;
}

// End function for AscendingIterator
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
{
    AscendingIterator temp(*this);
    temp.it = magicalContainer->sort.end();
    temp.pos = magicalContainer->sort.size();
    return temp;
}

// SideCrossIterator constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &magicalContainer) : BasicIterator(magicalContainer)
{
    it = magicalContainer.cross.begin();
};

// SideCrossIterator copy constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : BasicIterator(other){};

// SideCrossIterator copy assignment operator
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
{
    // Check if both iterators belong to the same container
    if (this->magicalContainer != other.magicalContainer)
    {
        throw std::runtime_error("Can't assign iterator from different container");
    }

    // Check for self-assignment
    if (this != &other)
    {
        // Assign each data member from the source object to this object
        // Assuming that magicalContainer should be the same for both, so no need to copy
        pos = other.pos;
        it = other.it;
    }

    // Return a reference to this object
    return *this;
}

// Dereference operator for SideCrossIterator
int MagicalContainer::SideCrossIterator::operator*() const
{
    if (it == magicalContainer->cross.end())
        throw std::runtime_error("Iterator is out of range");
    return **it;
}

// Pre-increment operator for SideCrossIterator
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
{
    // Check if iterator is at the end
    if (it == magicalContainer->cross.end())
    {
        throw std::runtime_error("Iterator is out of range");
    }

    // Increment the iterator and position
    ++it;
    ++pos;

    // Return a reference to this object
    return *this;
}

// Begin function for SideCrossIterator
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
{
    SideCrossIterator temp(*this);
    temp.it = magicalContainer->cross.begin();
    temp.pos = 0;
    return temp;
}

// End function for SideCrossIterator
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
{
    // Create a new iterator that points to the end of the cross vector
    SideCrossIterator endIterator(*magicalContainer);
    endIterator.it = magicalContainer->cross.end();
    endIterator.pos = magicalContainer->cross.size();

    return endIterator;
}

// PrimeIterator constructor
MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &magicalContainer) : BasicIterator(magicalContainer)
{
    it = magicalContainer.prime.begin();
};

// PrimeIterator copy constructor
MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : BasicIterator(other){};

// PrimeIterator copy assignment operator
MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
{
    if (&other == this)
    {
        // self-assignment, do nothing
        return *this;
    }

    // Check if the iterator is from the same container
    if (this->magicalContainer != other.magicalContainer)
    {
        throw std::runtime_error("Can't copy from another container");
    }

    // Copy-and-swap idiom
    PrimeIterator temp(other);
    std::swap(magicalContainer, temp.magicalContainer);
    std::swap(pos, temp.pos);
    std::swap(it, temp.it);

    return *this;
}

// Dereference operator for PrimeIterator
int MagicalContainer::PrimeIterator::operator*() const
{
    if (it == magicalContainer->prime.end())
        throw std::runtime_error("Iterator is out of range");
    return **it;
}

// Pre-increment operator for PrimeIterator
MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
{
    if (it == magicalContainer->prime.end())
    {
        throw std::runtime_error("Iterator is out of range");
        return *this;
    }
    ++it;
    ++pos;
    return *this;
}
bool MagicalContainer::PrimeIterator::is_self_assignment(const PrimeIterator &other) const
{
    if (&other == this)
    {
        return true;
    }

    // Check if the iterator is from the same container
    if (this->magicalContainer != other.magicalContainer)
    {
        throw std::runtime_error("Can't copy from another container");
    }
    return false;
}

void MagicalContainer::PrimeIterator::swap_with_temp(PrimeIterator &temp)
{
    std::swap(magicalContainer, temp.magicalContainer);
    std::swap(pos, temp.pos);
    std::swap(it, temp.it);
}

// PrimeIterator copy assignment operator
MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
{
    if (!is_self_assignment(other))
    {
        // Copy-and-swap idiom
        PrimeIterator temp(other);
        swap_with_temp(temp);
    }
    return *this;
}

// Begin function for PrimeIterator
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
{
    PrimeIterator temp(*this);
    temp.it = magicalContainer->prime.begin();
    temp.pos = 0;
    return temp;
}

// End function for PrimeIterator
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
{
    PrimeIterator temp(*this);
    temp.it = magicalContainer->prime.end();
    temp.pos = magicalContainer->prime.size();
    return temp;
}
