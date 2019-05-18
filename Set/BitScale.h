#pragma once
class BitScale
{
private:
	using Word = unsigned short;
	static const int WordBitSize_;
	Word *words_;
	int numWords_;
	int numBits_;

public:
	BitScale(int numBits = 256);
	BitScale(const BitScale&);
	~BitScale();
	bool hasBit(int bit);
	BitScale& setBit(int bit);
	BitScale& clearBit(int bit);
	void print();
	void resize();
	BitScale& operator=(const BitScale& arg);
	BitScale& operator |=(int bit)
	{
		return setBit(bit);
	}
	BitScale& operator -=(int bit)
	{
		return clearBit(bit);
	}
	BitScale& operator |=(const BitScale& arg);
	BitScale& operator &=(const BitScale& arg);
	BitScale& operator -=(const BitScale& arg);
	template <class T>
	friend class Set;
};