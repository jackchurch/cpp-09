#pragma once

template<typename T>
class Optional
{
public:
    Optional() : has_value(false) {}
    Optional(const T& value) : has_value(true), value(value) {}

    bool hasValue() const { return has_value; }
    T getValue() const { return value; }

private:
    bool has_value;
    T value;
};