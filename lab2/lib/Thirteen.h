#pragma once

#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <stdint.h>
#include <ostream>

using ull = uint64_t;

class Thirteen {
    private:
        unsigned char* val_ {nullptr};
        ull cap_{0u};
        void resize(ull new_capacity);

    public:

        const std::string ALPHABET = "0123456789ABC";
        const std::map<unsigned char, ull> REV_ALPHABET = {
            {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
            {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
            {'A', 10}, {'B', 11}, {'C', 12}
        };
        // Constructors
        Thirteen() : cap_(2u), val_(new unsigned char[this->cap_]) {
            this->val_[0] = '0';
            this->val_[1] = '\0';
        }
        Thirteen(const size_t &n, unsigned char v = 0);
        Thirteen(const std::initializer_list<unsigned char>& l);
        Thirteen(const std::string& s);

        // Copy constructor
        Thirteen(const Thirteen& other);
        // Move constructor
        Thirteen(Thirteen&& other) noexcept;

        // Destructors
        virtual ~Thirteen() noexcept;

        // Operators
        // Copy assignment
        Thirteen& operator=(const Thirteen& other);
        // Move assignment
        Thirteen& operator=(Thirteen&& other) noexcept;

        bool operator==(Thirteen& other) noexcept;
        bool operator!=(Thirteen& other) noexcept;
        bool operator>(Thirteen& other) noexcept;
        bool operator<(Thirteen& other) noexcept;

        Thirteen operator+(Thirteen& other);
        Thirteen operator-(Thirteen& other);

        friend std::ostream& operator<<(std::ostream& os, const Thirteen& t);

        // Methods
        bool is_empty() noexcept;

};
