/**
 * @file MagicalContainer.hpp
 * @brief Defines the MagicalContainer class and its nested iterator classes.
 * @details The MagicalContainer class is a container that stores a collection of integers
 * with various ordering options. It provides functionality to add and remove elements,
 * retrieve the size of the container, and compare containers for equality.
 * The container supports three iterator classes: AscendingIterator, SideCrossIterator,
 * and PrimeIterator, which allow iteration over the container in different orderings.
 *
 * @author Maya Rom
 * @ID 207485251
 */

#pragma once

#include <cstddef>
#include <vector>

namespace ariel
{
    /**
     * @class MagicalContainer
     * @brief A container that stores a collection of integers with various ordering options.
     */
    class MagicalContainer
    {
        std::vector<int> regular; // stores original insertion order
        std::vector<int *> cross; // stores element pointers in cross order
        std::vector<int *> sort;  // stores element pointers in ascending order
        std::vector<int *> prime; // stores element pointers that are prime numbers in original order

        /**
  * @brief Check if a number is prime.
  * @param number The number to check.
  * @return true if the number is prime, false otherwise.

  */
        bool isPrime(int number) const;

        /**
         * @brief Update the cross order elements.
         */
        void optimise_cross();

        /**
         * @brief Update the ascending order elements.
         */
        void optimise_sort();

        /**
         * @brief Update the prime elements.
         */
        void optimise_prime();

        /**
         * @class BasicIterator
         * @brief Base class for the iterator classes of MagicalContainer.
         * @note This is an abstract class and cannot be instantiated directly.
         */
        class BasicIterator
        {
        protected:
            MagicalContainer *magicalContainer;
            size_t pos;
            std::vector<int *>::iterator it;

        public:
            /**
             * @brief Constructs a new BasicIterator object.
             * @param magicalContainer The MagicalContainer to iterate over.
             */
            BasicIterator(MagicalContainer &magicalContainer);

            /**
             * @brief Copy constructor for BasicIterator.
             * @param other The BasicIterator object to copy.
             */
            BasicIterator(const BasicIterator &other);

            /**
             * @brief Destructor for BasicIterator.
             */
            ~BasicIterator();

            /**
             * @brief Move constructor for BasicIterator.
             * @param other The BasicIterator object to move.
             */
            BasicIterator(BasicIterator &&other) noexcept;

            /**
             * @brief Move assignment operator for BasicIterator.
             * @param other The BasicIterator object to move.
             * @return Reference to the moved BasicIterator object.
             */
            BasicIterator &operator=(BasicIterator &&other) noexcept;

            /**
             * @brief Copy assignment operator for BasicIterator.
             * @param other The BasicIterator object to copy.
             * @return Reference to the copied BasicIterator object.
             */
            BasicIterator &operator=(const BasicIterator &other);

            /**
             * @brief Equality operator for BasicIterator.
             * @param other The BasicIterator object to compare.
             * @return true if the iterators are equal, false otherwise.
             */
            bool operator==(const BasicIterator &other) const;

            /**
             * @brief Inequality operator for BasicIterator.
             * @param other The BasicIterator object to compare.
             * @return true if the iterators are not equal, false otherwise.
             */
            bool operator!=(const BasicIterator &other) const;

            /**
             * @brief Greater than operator for BasicIterator.
             * @param other The BasicIterator object to compare.
             * @return true if this iterator is greater than the other, false otherwise.
             */
            bool operator>(const BasicIterator &other) const;

            /**
             * @brief Less than operator for BasicIterator.
             * @param other The BasicIterator object to compare.
             * @return true if this iterator is less than the other, false otherwise.
             */
            bool operator<(const BasicIterator &other) const;

            // A helper function to compare the integers that the pointers point to
            static bool compareIntPointers(int *a, int *b);
        };

    public:
        /**
         * @brief Constructs a new MagicalContainer object.
         */
        MagicalContainer();

        /**
         * @brief Destructor for MagicalContainer.
         */
        ~MagicalContainer();

        /**
         * @brief Copy constructor for MagicalContainer.
         * @param other The MagicalContainer object to copy.
         */
        MagicalContainer(const MagicalContainer &other);

        /**
         * @brief Copy assignment operator for MagicalContainer.
         * @param other The MagicalContainer object to copy.
         * @return Reference to the copied MagicalContainer object.
         */
        MagicalContainer &operator=(const MagicalContainer &other);

        /**
         * @brief Move constructor for MagicalContainer.
         * @param other The MagicalContainer object to move.
         */
        MagicalContainer(MagicalContainer &&other) noexcept;

        /**
         * @brief Move assignment operator for MagicalContainer.
         * @param other The MagicalContainer object to move.
         * @return Reference to the moved MagicalContainer object.
         */
        MagicalContainer &operator=(MagicalContainer &&other) noexcept;

        /**
         * @brief Add an element to the container.
         * @param element The element to add.
         */
        void addElement(int element);

        /**
         * @brief Remove an element from the container.
         * @param element The element to remove.
         */
        void removeElement(int element);

        /**
         * @brief Get the size of the container.
         * @return The size of the container.
         */
        size_t size() const;

        /**
         * @brief Equality operator for MagicalContainer.
         * @param other The MagicalContainer object to compare.
         * @return true if the containers are equal, false otherwise.
         */
        bool operator==(const MagicalContainer &other) const;

        /**
         * @brief Inequality operator for MagicalContainer.
         * @param other The MagicalContainer object to compare.
         * @return true if the containers are not equal, false otherwise.
         */
        bool operator!=(const MagicalContainer &other) const;

        // Nested classes

        /**
         * @class AscendingIterator
         * @brief An iterator that traverses the container in ascending order.
         */
        class AscendingIterator : public BasicIterator
        {
        public:
            /**
             * @brief Constructs a new AscendingIterator object.
             * @param magicalContainer The MagicalContainer to iterate over.
             */
            AscendingIterator(MagicalContainer &magicalContainer);

            /**
             * @brief Copy constructor for AscendingIterator.
             * @param other The AscendingIterator object to copy.
             */
            AscendingIterator(const AscendingIterator &other);

            /**
             * @brief Copy assignment operator for AscendingIterator.
             * @param other The AscendingIterator object to copy.
             * @return Reference to the copied AscendingIterator object.
             */
            AscendingIterator &operator=(const AscendingIterator &other);

            /**
             * @brief Dereference operator for AscendingIterator.
             * @return The value pointed to by the iterator.
             */
            int operator*() const;

            /**
             * @brief Pre-increment operator for AscendingIterator.
             * @return Reference to the incremented AscendingIterator object.
             */
            AscendingIterator &operator++();

            /**
             * @brief Get the beginning iterator of the container.
             * @return An AscendingIterator object representing the beginning of the container.
             */
            AscendingIterator begin();

            /**
             * @brief Get the ending iterator of the container.
             * @return An AscendingIterator object representing the end of the container.
             */
            AscendingIterator end();
        };
        // Helper functions declarations
        void initCross(std::vector<int *> &cross);
        void updateFromStart(std::vector<int *>::iterator &start_it, std::vector<int *> &cross);
        void updateFromEnd(std::vector<int *>::reverse_iterator &end_it, std::vector<int *> &cross);

        /**
         * @class SideCrossIterator
         * @brief An iterator that traverses the container in a cross order.
         */
        class SideCrossIterator : public BasicIterator
        {
        public:
            void optimise_sort();
            void optimise_prime();
            /**
             * @brief Constructs a new SideCrossIterator object.
             * @param magicalContainer The MagicalContainer to iterate over.
             */
            SideCrossIterator(MagicalContainer &magicalContainer);

            /**
             * @brief Copy constructor for SideCrossIterator.
             * @param other The SideCrossIterator object to copy.
             */
            SideCrossIterator(const SideCrossIterator &other);

            /**
             * @brief Copy assignment operator for SideCrossIterator.
             * @param other The SideCrossIterator object to copy.
             * @return Reference to the copied SideCrossIterator object.
             */
            SideCrossIterator &operator=(const SideCrossIterator &other);

            /**
             * @brief Dereference operator for SideCrossIterator.
             * @return The value pointed to by the iterator.
             */
            int operator*() const;

            /**
             * @brief Pre-increment operator for SideCrossIterator.
             * @return Reference to the incremented SideCrossIterator object.
             */
            SideCrossIterator &operator++();

            /**
             * @brief Get the beginning iterator of the container.
             * @return A SideCrossIterator object representing the beginning of the container.
             */
            SideCrossIterator begin();

            /**
             * @brief Get the ending iterator of the container.
             * @return A SideCrossIterator object representing the end of the container.
             */
            SideCrossIterator end();
        };

        /**
         * @class PrimeIterator
         * @brief An iterator that traverses the container and only returns prime numbers.
         */
        class PrimeIterator : public BasicIterator
        {
        public:
            bool is_self_assignment(const PrimeIterator &other) const;
            void swap_with_temp(PrimeIterator &temp);

            /**
             * @brief Constructs a new PrimeIterator object.
             * @param magicalContainer The MagicalContainer to iterate over.
             */
            PrimeIterator(MagicalContainer &magicalContainer);

            /**
             * @brief Copy constructor for PrimeIterator.
             * @param other The PrimeIterator object to copy.
             */
            PrimeIterator(const PrimeIterator &other);

            /**
             * @brief Copy assignment operator for PrimeIterator.
             * @param other The PrimeIterator object to copy.
             * @return Reference to the copied PrimeIterator object.
             */
            PrimeIterator &operator=(const PrimeIterator &other);

            /**
             * @brief Dereference operator for PrimeIterator.
             * @return The value pointed to by the iterator.
             */
            int operator*() const;

            /**
             * @brief Pre-increment operator for PrimeIterator.
             * @return Reference to the incremented PrimeIterator object.
             */
            PrimeIterator &operator++();

            /**
             * @brief Get the beginning iterator of the container.
             * @return A PrimeIterator object representing the beginning of the container.
             */
            PrimeIterator begin();

            /**
             * @brief Get the ending iterator of the container.
             * @return A PrimeIterator object representing the end of the container.
             */
            PrimeIterator end();
        };
    };
}
