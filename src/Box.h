#pragma once
class Box
{
public:
    Box();
    Box(int v);

    int getValue();
    bool isEmpty();
    void setValue(int v);
    void clear();

private:
    int value;
    bool isDefault;
};

