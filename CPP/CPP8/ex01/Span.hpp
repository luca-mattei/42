#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <stdexcept>

class Span
{
private:
    unsigned int        _maxSize;
    std::vector<int>    _numbers;

public:
    Span();
    Span(unsigned int n);
    Span(const Span& other);
    Span& operator=(const Span& other);
    ~Span();

    void addNumber(int number);
    int  shortestSpan() const;
    int  longestSpan() const;
    template <typename Iterator>
    void addRange(Iterator begin, Iterator end)
    {
        for (Iterator it = begin; it != end; ++it)
        {
            if (_numbers.size() >= _maxSize)
                throw std::out_of_range("Span is full");
            _numbers.push_back(*it);
        }
    }
};

#endif