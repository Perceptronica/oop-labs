#include "../lib/Thirteen.h"

void Thirteen::resize(ull new_capacity) {
    if (new_capacity < this->cap_) {
        throw std::invalid_argument("New cap_ is smaller than the old one");
    } else if (new_capacity == this->cap_) {
        return;
    }

    unsigned char *new_val_ = new unsigned char[new_capacity];
    for (ull i {0}; i < this->cap_; ++i) {
        new_val_[i] = this->val_[i];
    }

    delete[] this->val_;
    this->val_ = new_val_;
    this->cap_ = new_capacity;
}

Thirteen::Thirteen(const size_t &n, unsigned char v) {
    if (n == 0) { 
        *this = Thirteen(); 
        return; 
    }

    this->cap_ = static_cast<ull>(n + 1);
    this->val_ = new unsigned char[this->cap_];

    std::fill_n(this->val_, this->cap_ - 1, v);
    this->val_[this->cap_ - 1] = '\0';
}

Thirteen::Thirteen(const std::initializer_list<unsigned char>& l) {
    ull len = l.size();
    if (len == 0) { 
        *this = Thirteen(); 
        return; 
    }

    this->cap_ = len + 1;
    this->val_ = new unsigned char[this->cap_];

    for (ull i = 0; i < len; ++i) {
        this->val_[i] = *(l.end() - 1 - i);
    }

    this->val_[this->cap_ - 1] = '\0';
}

Thirteen::Thirteen(const std::string& s) {
    ull len = s.size();
    if (len == 0) { *this = Thirteen(); return; }

    this->cap_ = len + 1;
    this->val_ = new unsigned char[this->cap_];

    for (ull i = 0; i < len; ++i) {
        this->val_[i] = s[len - 1 - i];
    }

    this->val_[this->cap_ - 1] = '\0';
}

// Copy constructor
Thirteen::Thirteen(const Thirteen& other) {
    *this = other;
}

// Move constructor
Thirteen::Thirteen(Thirteen&& other) noexcept {
    *this = std::move(other);
}


// Destructor
Thirteen::~Thirteen() noexcept {
    this->cap_ = 0;
    if (this->val_ != nullptr) delete[] this->val_;
    this->val_ = nullptr;
}


// Copy assignment
Thirteen& Thirteen::operator=(const Thirteen& other) {
    if (this == &other)
        return *this;

    if (this->cap_ != other.cap_) {
        unsigned char *temp = new unsigned char[other.cap_];
        if (this->val_ != nullptr) delete[] this->val_;

        this->val_ = temp;
        this->cap_ = other.cap_;
    }

    std::copy(other.val_, other.val_ + other.cap_, this->val_);
    return *this;
}

// Move assignment
Thirteen& Thirteen::operator=(Thirteen&& other) noexcept {
    if (this == &other)
        return *this;

    if (this->val_ != nullptr) delete[] this->val_;
    this->val_ = other.val_;
    other.val_ = nullptr;

    this->cap_ = other.cap_;
    other.cap_ = 0;

    return *this;
}

bool Thirteen::operator==(Thirteen& other) noexcept {
    if (*this > other || *this < other) return false;
    return true;
}

bool Thirteen::operator!=(Thirteen& other) noexcept {
    return !(*this == other);
}

bool Thirteen::operator>(Thirteen& other) noexcept {
    ull max = std::max(this->cap_, other.cap_);

    for (ull i = 0; i < max; ++i) {
        if (i < this->cap_ && i < other.cap_) {
            unsigned char c1 = this->val_[i], c2 = other.val_[i];
            if (c1 == '\0' && c2 != '\0') {
                return false;
            } else if (c1 != '\0' && c2 == '\0') {
                return true;
            } else if (c1 == '\0' && c2 == '\0') {
                for (ull j = i - 1; j >= 0; --j) {
                    if (this->val_[j] > other.val_[j]) return true;
                    else return false;
                }
            }
        } else if (i < this->cap_) {
            return true;
        } else {
            return false;
        }
    }

    return false;
}

bool Thirteen::operator<(Thirteen& other) noexcept {
    return other > *this;
}


Thirteen Thirteen::operator+(Thirteen& other) {
    Thirteen temp;

    ull max = std::max(this->cap_, other.cap_);
    ull a = 0, b = 0, remainder = 0;

    for (ull i = 0; i < max - 1; ++i) {
        a = b = 0;

        if (i < this->cap_ - 1) {
            a = REV_ALPHABET.at(this->val_[i]);
        }
        if (i < other.cap_ - 1) {
            b = REV_ALPHABET.at(other.val_[i]);
        }

        if (remainder == 1) {
            a += 1;
        }

        remainder = (a + b) / 13;

        if (temp.cap_ - 1 <= i) {
            temp.resize(temp.cap_ * 2);
        }

        ull num = a + b;

        temp.val_[i] = ALPHABET[num % 13];
        temp.val_[i + 1] = ALPHABET[remainder];
    }


    if (remainder) {
        temp.val_[max] = '\0';
    } else {
        temp.val_[max - 1] = '\0';
    }

    return temp;
}

Thirteen Thirteen::operator-(Thirteen& other) {
    ull max = std::max(this->cap_, other.cap_);

    Thirteen temp = Thirteen(max, '\0');

    ull a = 0, b = 0, remainder = 0;
    ull i = 0;

    for (i = 0; i < max - 1; ++i) {
        a = b = 0;

        if (i < this->cap_ - 1) {
            a = REV_ALPHABET.at(this->val_[i]);
        }
        if (i < other.cap_ - 1) {
            b = REV_ALPHABET.at(other.val_[i]);
        }
        
        if (remainder > 0) {
            a -= remainder;
        }

        ull num {a - b};

        if (num < 0) {
            if (this->val_[i + 1] == '\0') {
                temp.val_[0] = '0';
                temp.val_[1] = '\0';
                break;
            }
            remainder = 1;
            temp.val_[i] = ALPHABET[13 + num % 13];
        } else {
            remainder = 0;
            temp.val_[i] = ALPHABET[num % 13];
        }
    }

    for (; i > 1; --i) { // i > 2 because we are not touching the first zero if it is present
        if (temp.val_[i] == '\0' && temp.val_[i - 1] == '0') temp.val_[i - 1] = '\0';
    }

    return temp;
}

std::ostream& operator<<(std::ostream& os, const Thirteen& t) {
    for (ull i {0}; i < t.cap_; ++i) {
        if (t.val_[i] == '\0') {
            for (ull j {1}; j <= i; ++j) {
      	        os << t.val_[i - j];
            }
            break;
        }
    }
    return os;
}


bool Thirteen::is_empty() noexcept {
    return (this->cap_ > 0 ? this->val_[0] == '\0' : true);
}