// Copyright Davydov Nikolay 2021

#ifndef INCLUDE_UNIQUE_PTR_HPP_
#define INCLUDE_UNIQUE_PTR_HPP_

#include <iostream>

namespace my_unique_ptr {
    template<class T>
    class unique_ptr {
    private:
        T *data_;

    public:
        unique_ptr(const unique_ptr &copy) = delete;

        unique_ptr &operator=(const unique_ptr &copy) = delete;

        unique_ptr() : data_(nullptr) {}

        explicit unique_ptr(T *data) : data_(data) {}

        unique_ptr(unique_ptr &&moved) noexcept: data_(std::move(moved.data_)) {
            moved.data_ = nullptr;
        }

        ~unique_ptr() noexcept {
            delete data_;
        }

        unique_ptr &operator=(unique_ptr &&moved) noexcept {
            if (this == &moved) return *this;

            delete data_;
            data_ = std::move(moved.data_);
            moved.data_ = nullptr;
            return *this;
        }

        void reset(T *ptr = nullptr) {
            delete data_;
            data_ = ptr;
        }

        T *release() {
            T *ptr = data_;
            data_ = nullptr;
            return ptr;
        }

        void swap(unique_ptr &other) noexcept {
            std::swap(data_, other.data_);
        }

        T *operator->() const noexcept {
            return data_;
        }

        T &operator*() const noexcept {
            return *data_;
        }

        explicit operator bool() const noexcept {
            return data_;
        }

        T *get() const noexcept {
            return data_;
        }
    };

    template<typename T, typename... Args>
    unique_ptr<T> make_unique(Args &&... args) {
        return unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}

#endif //INCLUDE_UNIQUE_PTR_HPP_
