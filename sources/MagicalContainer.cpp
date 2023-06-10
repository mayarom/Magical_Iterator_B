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
    : originalElements(other.originalElements),
      crossElements(other.crossElements),
      sortedElements(other.sortedElements),
      primeElements(other.primeElements) {}

// Copy assignment operator
MagicalContainer &MagicalContainer::operator=(const MagicalContainer &other)
{
    if (this == &other)
        return *this;

    originalElements = other.originalElements;
    crossElements = other.crossElements;
    sortedElements = other.sortedElements;
    primeElements = other.primeElements;

    return *this;
}

// Move constructor
MagicalContainer::MagicalContainer(MagicalContainer &&other) noexcept
    : originalElements(std::move(other.originalElements)),
      crossElements(std::move(other.crossElements)),
      sortedElements(std::move(other.sortedElements)),
      primeElements(std::move(other.primeElements)) {}

// Move assignment operator
MagicalContainer &MagicalContainer::operator=(MagicalContainer &&other) noexcept
{
    if (this == &other)
        return *this;

    originalElements = std::move(other.originalElements);
    crossElements = std::move(other.crossElements);
    sortedElements = std::move(other.sortedElements);
    primeElements = std::move(other.primeElements);

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

// Update the crossElements vector
void MagicalContainer::updateCrossElements()
{
    crossElements.clear();
    auto start_it = sortedElements.begin();
    auto end_it = sortedElements.rbegin();

    bool add_from_start = true;

    for (int i = 0; i < sortedElements.size(); i++)
    {
        if (add_from_start)
        {
            crossElements.push_back(*start_it);
            ++start_it;
        }
        else
        {
            crossElements.push_back(*end_it);
            ++end_it;
        }
        add_from_start = !add_from_start;
    }
}

// Update the sortedElements vector
void MagicalContainer::updateSortedElements()
{
    sortedElements.clear();

    for (auto it = originalElements.begin(); it != originalElements.end(); ++it)
    {
        sortedElements.push_back(&(*it));
    }

    std::sort(sortedElements.begin(), sortedElements.end(), [](int *a, int *b)
              { return *a < *b; });
}

// Update the primeElements vector
void MagicalContainer::updatePrimeElements()
{
    primeElements.clear();

    for (auto it = originalElements.begin(); it != originalElements.end(); ++it)
    {
        if (isPrime(*it))
        {
            primeElements.push_back(&(*it));
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
    originalElements.push_back(element);
    updatePrimeElements();
    updateSortedElements();
    updateCrossElements();
}

// Remove an element from the container
void MagicalContainer::removeElement(int element)
{
    auto it = std::find(originalElements.begin(), originalElements.end(), element);

    if (it == originalElements.end())
    {
        throw std::runtime_error("Element not found in container");
        return;
    }

    int *p = &(*it);

    originalElements.erase(it);

    sortedElements.erase(std::find(sortedElements.begin(), sortedElements.end(), p));

    if (isPrime(element))
    {
        primeElements.erase(std::find(primeElements.begin(), primeElements.end(), p));
    }
    updatePrimeElements();
    updateCrossElements();
    updateSortedElements();
}

// Get the size of the container
size_t MagicalContainer::size() const
{
    return originalElements.size();
}

// Equality comparison operator
bool MagicalContainer::operator==(const MagicalContainer &other) const
{
    return originalElements == other.originalElements;
}

// Inequality comparison operator
bool MagicalContainer::operator!=(const MagicalContainer &other) const
{
    return originalElements != other.originalElements;
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
    it = magicalContainer.sortedElements.begin();
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
    if (it == magicalContainer->sortedElements.end())
        throw std::runtime_error("Iterator is out of range");
    return **it;
}

// Pre-increment operator for AscendingIterator
MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
{
    if (it == magicalContainer->sortedElements.end())
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
    temp.it = magicalContainer->sortedElements.begin();
    temp.pos = 0;
    return temp;
}

// End function for AscendingIterator
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
{
    AscendingIterator temp(*this);
    temp.it = magicalContainer->sortedElements.end();
    temp.pos = magicalContainer->sortedElements.size();
    return temp;
}

// SideCrossIterator constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &magicalContainer) : BasicIterator(magicalContainer)
{
    it = magicalContainer.crossElements.begin();
};

// SideCrossIterator copy constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : BasicIterator(other){};

// SideCrossIterator copy assignment operator
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::runtime_error("Cant copy from another container");
    magicalContainer = other.magicalContainer;
    pos = other.pos;
    it = other.it;
    return *this;
}

// Dereference operator for SideCrossIterator
int MagicalContainer::SideCrossIterator::operator*() const
{
    if (it == magicalContainer->crossElements.end())
        throw std::runtime_error("Iterator is out of range");
    return **it;
}

// Pre-increment operator for SideCrossIterator
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
{
    if (it == magicalContainer->crossElements.end())
    {
        throw std::runtime_error("Iterator is out of range");
        return *this;
    }
    ++it;
    ++pos;
    return *this;
}

// Begin function for SideCrossIterator
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
{
    SideCrossIterator temp(*this);
    temp.it = magicalContainer->crossElements.begin();
    temp.pos = 0;
    return temp;
}

// End function for SideCrossIterator
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
{
    SideCrossIterator temp(*this);
    temp.it = magicalContainer->crossElements.end();
    temp.pos = magicalContainer->crossElements.size();
    return temp;
}

// PrimeIterator constructor
MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &magicalContainer) : BasicIterator(magicalContainer)
{
    it = magicalContainer.primeElements.begin();
};

// PrimeIterator copy constructor
MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : BasicIterator(other){};

// PrimeIterator copy assignment operator
MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::runtime_error("Cant copy from another container");
    magicalContainer = other.magicalContainer;
    pos = other.pos;
    it = other.it;
    return *this;
}

// Dereference operator for PrimeIterator
int MagicalContainer::PrimeIterator::operator*() const
{
    if (it == magicalContainer->primeElements.end())
        throw std::runtime_error("Iterator is out of range");
    return **it;
}

// Pre-increment operator for PrimeIterator
MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
{
    if (it == magicalContainer->primeElements.end())
    {
        throw std::runtime_error("Iterator is out of range");
        return *this;
    }
    ++it;
    ++pos;
    return *this;
}

// Begin function for PrimeIterator
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
{
    PrimeIterator temp(*this);
    temp.it = magicalContainer->primeElements.begin();
    temp.pos = 0;
    return temp;
}

// End function for PrimeIterator
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
{
    PrimeIterator temp(*this);
    temp.it = magicalContainer->primeElements.end();
    temp.pos = magicalContainer->primeElements.size();
    return temp;
}
