#pragma once

#include <iostream>
#include <cassert>
#include "allocator.h"

template <typename T, typename Alloc = allocator<T>>
class Vector {
    private:
        T* arr_;
        size_t sz_ {0u};
        size_t cap_ {0u};
        Alloc alloc_;

        template <bool isConst>
        class base_iterator {
            public:
                using ptr_type = std::conditional_t<isConst, const T*, T*>;
                using ref_type = std::conditional_t<isConst, const T&, T&>;
                using val_type = T;
            
            private:
                ptr_type ptr;

            public:
                base_iterator(ptr_type ptr): ptr(ptr) {}
                base_iterator(const base_iterator& other) : ptr(other.ptr) {}
                base_iterator(base_iterator&& other) noexcept : ptr(other.ptr) {
                    other.ptr = nullptr;
                }
                
                base_iterator& operator=(const base_iterator& other) {
                    ptr = other.ptr;
                    return *this;
                }

                base_iterator& operator=(base_iterator&& other) {
                    ptr = other.ptr;
                    return *this;
                }
                
                ref_type operator*() const {
                    return *ptr;
                }

                ptr_type operator->() const {
                    return ptr;
                }

                base_iterator& operator++() {
                    ++ptr;
                    return *this;
                }

                base_iterator operator++(int) {
                    base_iterator copy = *this;
                    ++ptr;
                    return copy;
                }

                base_iterator operator--() {
                    --ptr;
                    return *this;
                }

                base_iterator operator--(int) {
                    base_iterator copy = *this;
                    --ptr;
                    return copy;
                }

                bool operator==(const base_iterator& other) const {
                    return this->ptr == other.ptr;
                }

                bool operator!=(const base_iterator& other) const {
                    return !(this->ptr == other.ptr);
                }
        };
    public:
        // Constructors
        Vector() : sz_(0u), cap_(0u), arr_(nullptr) {}
        Vector(size_t n) : sz_(n), cap_(n) {
            arr_ = alloc_.allocate(n);
            for (size_t i {0}; i < n; ++i) {
                alloc_.construct(arr_ + i, T());
            }
        }
        Vector(size_t n, T value) : sz_(n), cap_(n) {
            arr_ = alloc_.allocate(n);
            for (size_t i {0}; i < n; ++i) {
                alloc_.construct(arr_ + i, value);
            }
        }

        // Destructor
        ~Vector() {
            clear();
            alloc_.deallocate(arr_, cap_);
        }

        // Element access
        T& operator[](size_t index) noexcept {
            assert(index < cap_);
            return arr_[index];
        }

        const T& operator[](size_t index) const noexcept {
            assert(index < cap_);
            return arr_[index];
        }

        T& at(size_t index) {
            if (index >= sz_) {
                throw std::out_of_range("out_of_range");
            }
            return arr_[index];
        }

        const T& at(size_t index) const {
            if (index >= sz_) {
                throw std::out_of_range("out_of_range");
            }
            return arr_[index];
        }

        T& front() {
            assert(sz_ > 0);
            return *(begin());
        }
        
        const T& front() const { 
            assert(sz_ > 0);
            return *(cbegin());
        }
        
        T& back() {
            assert(sz_ > 0);
            return (sz_ > 1 ? *(--end()) : *begin());
        }

        const T& back() const {
            assert(sz_ > 0);
            return (sz_ > 1 ? *(--cend()) : *cbegin());
        }

        T* data() noexcept {
            return (sz_ > 0 ? arr_ : nullptr);
        }

        // Iterators
        using iterator = base_iterator<false>;
        using const_iterator = base_iterator<true>;

        iterator begin() {
            return {arr_};
        }

        iterator end() {
            return {arr_ + sz_};
        }

        const_iterator begin() const {
            return {arr_};
        }

        const_iterator end() const {
            return {arr_ + sz_};
        }

        const_iterator cbegin() const {
            return {arr_};
        }

        const_iterator cend() const {
            return {arr_ + sz_};
        }

        // Capacity
        size_t size() const noexcept {
            return sz_;
        }

        size_t capacity() const noexcept {
            return cap_;
        }

        bool empty() const noexcept {
            return sz_ == 0u;
        }

        // Modifiers
        void reserve(size_t newcap) {
            if (newcap <= cap_) {
                return;
            }
            T* newarr = alloc_.allocate(newcap);
            size_t index {0};
            try {
                for (; index < sz_; ++index) {
                    alloc_.construct(newarr + index, arr_[index]);
                }
            } catch (...) {
                for (size_t new_index {0}; new_index < index; ++new_index){
                    alloc_.destroy(newarr + new_index);
                }
                alloc_.deallocate(newarr, newcap);
                throw;
            }
            for (size_t index {0}; index < sz_; ++index) {
                alloc_.destroy(arr_ + index);
            }
            alloc_.deallocate(arr_, cap_);

            arr_ = newarr;
            cap_ = newcap;
        }

        void resize(size_t newcap) {
            if (newcap > cap_) {
                reserve(newcap);
                cap_ = newcap;
                sz_ = newcap;
            } else {
                for (size_t i {0}; i < sz_; ++i) {
                    alloc_.destroy(arr_ + i);
                }
                sz_ = newcap;
            }
        }

        void push_back(const T& value) {
            if (sz_ == cap_) {
                reserve(cap_ > 0 ? cap_ * 2 : 1);
            }
            alloc_.construct(arr_ + sz_, value);
            ++sz_;
        }

        void clear() {
            for (size_t i {0}; i < sz_; ++i) {
                arr_[i] = T();
            }
            sz_ = 0u;
        }
};