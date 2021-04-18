#pragma once
class Stat
{

public:
    Stat(std::string Name, double Value)
    {
        _name = Name;
        _value = Value;
    }

    std::string Name() const {
        return this->_name;
    };
    double Value() const {
        return _value;
    }
private:
    std::string _name;
    double _value;
};


// This class is to define what a certain stat on an item could be.
// Usage:
// For example, using an array of PossibleStat,
// we can generate the numbers for the resulting item.
// PossibleStat("strength", 500, 750) will be used to generate a strength stat
// with a value between 500 and 750.

class PossibleStat {

public:
    PossibleStat(std::string Name, double RangeMin, double RangeMax, double Step)
    {
        _name = Name;
        _rangeMin = RangeMin;
        _rangeMax = RangeMax;
        _step = Step;
    }

    std::string Name() { return _name; }
    double RangeMin() { return _rangeMin; }
    double RangeMax() { return _rangeMax; }
    double Step() { return _step; }

private:
    std::string _name;
    double _rangeMax;
    double _rangeMin;
    double _step;
};