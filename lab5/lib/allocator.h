#pragma once

template <class T>
class allocator {
    private:
        //T* memory_;
    public:
        T* allocate(size_t count) {
            return reinterpret_cast<T*>(new char[count * sizeof(T)]);
        }
        
        void deallocate(T* ptr, size_t) {
            delete[] reinterpret_cast<char*>(ptr);
        }

        template <typename U, typename... Args>
        void construct(U* ptr, const Args&... args) {
            new (ptr) U(args...);
        }

        template <typename U>
        void destroy(U* ptr) {
            ptr->~U();
        }

        template <typename U>
        struct rebind {
            using other = allocator<U>;
        };
};

template<typename T, typename U>
constexpr bool operator==(allocator<T>& lhs, allocator<U>& rhs) {
    return true;
}