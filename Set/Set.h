#pragma once
#include "BitScale.h"

template <class T>
class Set
{
	int reserve_;
	int capacity_;
	BitScale bitScale_;
	T **array_;
public:
	Set(int reserve = 256) :
		reserve_(reserve)
		, capacity_(0)
		, bitScale_(reserve)
		, array_(new T*[reserve_])
	{}

	Set(const Set& arg) : reserve_(arg.reserve_)
		, capacity_(arg.capacity_)
		, bitScale_(arg.bitScale_)
	{
		array_ = new T*[reserve_];
		memcpy(array_, arg.array_, reserve_ * sizeof(T*));
	}

	Set& operator =(const Set& arg)
	{
		reserve_ = arg.reserve_;
		capacity_ = arg.capacity_;
		bitScale_ = arg.bitScale_;
		array_ = new T*[reserve_];
		memcpy(array_, arg.array_, reserve_ * sizeof(T*));
		return *this;
	}

	~Set() {
		delete[] array_;
	}

	int capacity() {
		return capacity_;
	}

	void print() {
		bitScale_.print();
	}

	void resize() {
		reserve_ *= 2;
		T **buf = new T*[reserve_];
		memcpy(buf, array_, (reserve_ / 2) * sizeof(T*));
		delete[] array_;
		array_ = buf;
		bitScale_.resize();
	}

	bool hasItem(const T& item)
	{
		return bitScale_.hasBit(item.id);
	}

	Set& operator |=(T& item)
	{
		while (item.id >= reserve_)
			resize();
		if (!hasItem(item)) capacity_++;
		bitScale_.setBit(item.id);
		array_[item.id] = &item;
		return *this;
	}

	Set& operator |=(Set& set)
	{
		while (set.reserve_ > reserve_)
			resize();
		addItems(set);
		bitScale_ |= set.bitScale_;
		capacity_ = countCapacity(bitScale_);
		return *this;
	}

	Set& operator -=(T& item)
	{
		if (hasItem(item)) capacity_--;
		bitScale_.clearBit(item.id);
		return *this;
	}

	Set& operator -=(const Set& set)
	{
		BitScale bufBitScale;
		bufBitScale = set.bitScale_;
		bufBitScale &= bitScale_;
		capacity_ -= countCapacity(bufBitScale);
		bitScale_ -= set.bitScale_;
		return *this;
	}

	Set& operator &=(const Set & set) {
		bitScale_ &= set.bitScale_;
		capacity_ = countCapacity(bitScale_);
		return *this;
	}

	bool operator<=(const Set& set) {
		BitScale bufBitScale;
		bufBitScale = set.bitScale_;
		bufBitScale &= bitScale_;
		return capacity_ == countCapacity(bufBitScale);
	}

	bool operator>=(const Set& set) {
		BitScale bufBitScale;
		bufBitScale = set.bitScale_;
		bufBitScale &= bitScale_;
		return set.capacity_ == countCapacity(bufBitScale);
	}

	bool operator==(const Set& set) {
		return ((*this >= set) && (*this <= set));
	}

	bool operator!=(const Set& set) {
		return !(*this == set);
	}
	
	template <class T2>
	Set<T2>* map(T2*(*f)(T *item)) {
		Set<T2> *bufSet = new Set<T2>;
		BitScale buf = bitScale_;
		int id;
		using Word = unsigned short;
		Word bufWord;
		for (int i = 0; i < buf.numWords_; i++) {
			bufWord = buf.words_[i];
			for (int j = 0; j < buf.WordBitSize_ - 1; j++) {
				if (bufWord & 1 == 1) {
					id = i * buf.WordBitSize_ + j;
					*(bufSet) |= *(f(array_[id]));
				}
				bufWord >>= 1;
			}
		}
		return bufSet;
	}

	Set* where(bool(*f)(T *item)) {
		Set *bufSet = new Set;
		BitScale buf = bitScale_;
		int id;
		using Word = unsigned short;
		Word bufWord;
		for (int i = 0; i < buf.numWords_; i++) {
			bufWord = buf.words_[i];
			for (int j = 0; j < buf.WordBitSize_ - 1; j++) {
				if (bufWord & 1 == 1) {
					id = i * buf.WordBitSize_ + j;
					if(f(array_[id]))
						*(bufSet) |= *(array_[id]);
				}
				bufWord >>= 1;
			}
		}
		return bufSet;
	}
	
private:
	int countCapacity(const BitScale& arg) {
		using Word = unsigned short;
		int count = 0;
		Word buf;
		for (int i = 0; i < arg.numWords_; i++) {
			buf = arg.words_[i];
			for (int j = 0; j < arg.WordBitSize_ - 1; j++) {
				if (buf & 1 == 1)
					count++;
				buf >>= 1;
			}
		}
		return count;
	}

	void addItems(const Set& set) {
		BitScale buf = set.bitScale_;
		buf -= bitScale_;
		int id;
		using Word = unsigned short;
		Word bufWord;
		for (int i = 0; i < buf.numWords_; i++) {
			bufWord = buf.words_[i];
			for (int j = 0; j < buf.WordBitSize_ - 1; j++) {
				if (bufWord & 1 == 1) {
					id = i * buf.WordBitSize_ + j;
					array_[id] = set.array_[id];
				}
				bufWord >>= 1;
			}
		}
	}
};