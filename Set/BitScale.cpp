#include <iostream>
#include <stdexcept>
#include <bitset>
#include "BitScale.h"
using namespace std;

const int BitScale::WordBitSize_ = 16;

BitScale::BitScale(int numBits)
{
	numBits_ = numBits;
	numWords_ = (numBits_ + WordBitSize_ - 1) / WordBitSize_;
	words_ = new Word[numWords_];
	memset(words_, 0, numWords_ * sizeof(Word));
}

BitScale::BitScale(const BitScale& arg)
{
	numBits_ = arg.numBits_;
	numWords_ = arg.numWords_;
	words_ = new Word[numWords_];
	memcpy(words_, arg.words_, numWords_ * sizeof(Word));
}

BitScale::~BitScale()
{
	delete[] words_;
}

void BitScale::print()
{
	for (int i = 0; i < numWords_; i++) {
		printf("%-3d) ", i);
		cout << std::bitset<WordBitSize_>(words_[i]) << endl;
	}
}

bool BitScale::hasBit(int bit)
{
	if (bit < 0 || bit >= numBits_) 
		return false;
	return (words_[bit / WordBitSize_] &
		(1 << bit % WordBitSize_)) != 0;
}

BitScale& BitScale::setBit(int bit)
{
	if (bit < 0)
		throw runtime_error("Signed bit.");
	while (bit >= numBits_)
		resize();
	words_[bit / WordBitSize_] |= (1 << bit % WordBitSize_);
	return *this;
}

BitScale& BitScale::clearBit(int bit)
{
	if (bit < 0 || bit >= numBits_)
		return *this;
	words_[bit / WordBitSize_] &= ~(1 << bit % WordBitSize_);
	return *this;
}

BitScale& BitScale::operator=(const BitScale& arg)
{
	numBits_ = arg.numBits_;
	numWords_ = arg.numWords_;
	words_ = new Word[numWords_];
	memcpy(words_, arg.words_, numWords_ * sizeof(Word));
	return *this;
}

BitScale& BitScale::operator |=(const BitScale& arg)
{
	while (numBits_ < arg.numBits_) {
		resize();
	}
	for (int i = 0; i < arg.numWords_; i++)
		words_[i] |= arg.words_[i];
	return *this;
}

BitScale& BitScale::operator &=(const BitScale& arg)
{
	for (int i = 0; i < numWords_; i++)
		words_[i] &= arg.words_[i];
	return *this;
}

BitScale& BitScale::operator -=(const BitScale& arg)
{
	for (int i = 0; i < numWords_; i++)
		words_[i] &= ~arg.words_[i];
	return *this;
}

void BitScale::resize() {
	numBits_ *= 2;
	int lastNum = numWords_;
	numWords_ = (numBits_ + WordBitSize_ - 1) / WordBitSize_;
	Word *bufWords = new Word[numWords_];
	memset(bufWords, 0, numWords_ * sizeof(Word));
	memcpy(bufWords, words_, lastNum * sizeof(Word));
	delete[] words_;
	words_ = bufWords;
}