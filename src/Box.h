#pragma once
class Box
{
	int value;
	bool isDefault;

public:
	Box();
	Box(int v);

	int getValue();
	bool isEmpty();
	void setValue(int v);
	void clear();
};

