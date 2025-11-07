#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>
#include <type_traits>

template<typename T>
concept Scalar = std::is_scalar_v<T>;

#endif