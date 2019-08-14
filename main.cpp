#include <iostream>

using namespace std;


struct MedianPosition
{
    uint position;
    bool even;
};

class ArrayManager
{
public:
    ArrayManager(int * arr, size_t len):
        index_(0), maxIndex_(len - 1), arr_(arr)
    {

    }

    bool getItem(int & _value)
    {
        bool res = false;
        if (index_ <= maxIndex_)
        {
            _value = arr_[index_];
            res = true;
        }
        return res;
    }


    void incInd()
    {
        index_++;
    }
private:
    uint index_;
    uint maxIndex_;
    int * arr_;
};


MedianPosition getPosition(size_t _lenArr1, size_t _lenArr2)
{
    MedianPosition mp;
    mp.even = (((_lenArr1 + _lenArr2) % 2) == 0);
    mp.position = ((_lenArr1 + _lenArr2) / 2) + 1;

    return mp;
}

float avg(float value1_, float value2_)
{
    return ((value1_ + value2_)/2);
}

float getMediana(ArrayManager &am1, ArrayManager &am2, int _stepsToMediana, bool even_)
{
    int value1;
    int value2;
    int result;

    if (!am1.getItem(value1))
    {
        if (am2.getItem(value1))
            am2.incInd();
        else
            return -1; //error
    };

    if (!am2.getItem(value2))
    {
        if (am1.getItem(value2))
            am1.incInd();
        else
            return -1; //error
    };

    if (value1 > value2)
    {
        am2.incInd();
        result = value2;
    }
    else if (value1 < value2)
    {
        am1.incInd();
        result = value1;
    }
    else if (value1 == value2)
    {
        am1.incInd();
        am2.incInd();
        result = value1;
    }

    if (_stepsToMediana == 0)
    {
        return result;
    }
    else if (_stepsToMediana == 1)
    {
        if (even_)
        {
            float a = getMediana(am1, am2, _stepsToMediana - 1, even_);
            return avg(result, a);
        }
    }
    else
    {
        return getMediana(am1, am2, _stepsToMediana - 1, even_);
    }
}

int main()
{
    int arr1[] = {1, 5, 7, 9, 10, 12, 13, 19};
    int arr2[] = {1, 2, 6, 11, 22, 24};

    MedianPosition mp;
    mp = getPosition(sizeof(arr1)/sizeof(int), sizeof(arr2)/sizeof(int));

    ArrayManager am1(arr1, sizeof(arr1)/sizeof(int));
    ArrayManager am2(arr2, sizeof(arr2)/sizeof(int));

    std::cout << getMediana(am1, am2, mp.position, mp.even) << std::endl;
    return 0;
}
