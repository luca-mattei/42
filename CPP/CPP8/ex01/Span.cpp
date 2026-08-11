#include "Span.hpp"
#include <algorithm>    // sort, min_element, max_element
#include <numeric> // adjacent_difference

Span::Span() : _maxSize(0) {}

Span::Span(unsigned int n) : _maxSize(n) {}

Span::Span(const Span& other) : _maxSize(other._maxSize), _numbers(other._numbers) {}

Span& Span::operator=(const Span& other)
{
    if (this != &other)
    {
        _maxSize = other._maxSize;
        _numbers = other._numbers;
    }
    return *this;
}

Span::~Span() {}

void Span::addNumber(int number)
{
    if (_numbers.size() >= _maxSize)
        throw std::out_of_range("Span is full");
    _numbers.push_back(number);
}

int Span::longestSpan() const
{
    if (_numbers.size() < 2)
        throw std::runtime_error("Not enough numbers to find a span");

    std::vector<int>::const_iterator min = std::min_element(_numbers.begin(), _numbers.end());
    std::vector<int>::const_iterator max = std::max_element(_numbers.begin(), _numbers.end());
    return *max - *min;
}

int Span::shortestSpan() const
{
    if (_numbers.size() < 2)
        throw std::runtime_error("Not enough numbers to find a span");

    std::vector<int> sorted(_numbers);          // copie pour ne pas altérer l'original
    std::sort(sorted.begin(), sorted.end());    // tri croissant

    std::vector<int> diffs(sorted.size());
    std::adjacent_difference(sorted.begin(), sorted.end(), diffs.begin());

    // diffs[0] est une copie de sorted[0], pas une vrai diff donc je fais diffs.begin() + 1
    return *std::min_element(diffs.begin() + 1, diffs.end());
}