// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8) // = 32 

TBitField::TBitField(int len)
{
	if (len > 0) {
		int BitLen = len;
		int MemLen = (BitLen + BITS_IN_ONE_MEM - 1) / BITS_IN_ONE_MEM;
		pMem = new TELEM[MemLen];

		for (int i = 0; i < MemLen; i++) {
			pMem[i] = TELEM(0);
		}
	} 
	else if (len == 0) {
		MemLen = 0;
	}
	else {
		throw 1; 
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	int BitLen = bf.BitLen; 
	int MemLen = bf.MemLen; 
	pMem = new TELEM[MemLen]; 
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete []pMem; 
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	
 return n / BITS_IN_ONE_MEM;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << BITS_IN_ONE_MEM;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen))
		throw 2;
	// pMem[GetMemIndex(n)] |= (GetMemMask(n));
	GetMemIndex(n) |= 
}

void TBitField::ClrBit(const int n) // очистить бит
{
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField & bf) // присваивание
{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	
	return *this;
}

int TBitField::operator==(const TBitField & bf) const // сравнение
{
	if (BitLen == bf.BitLen) {
		bool flag = true; 
		for (int i = 0; i < BitLen; i++) {
			if (bf.pMem[i] != pMem[i]) {
				flag = false; 
			}
		}
		if (flag == true) {
			return 1;
		}
	}

	return 0;
}

int TBitField::operator!=(const TBitField & bf) const // сравнение
{
	if (BitLen == bf.BitLen) {
		bool flag = false; 
		for (int i = 0; i < BitLen; i++) {
			if (bf.pMem[i] != pMem[i]) {
				flag = true; 
			}
		}
		if (flag == true) {
			return 1; 
		}
		else {
			return 0; 
		}
	}
	else {
		return 0;
	}
}

TBitField TBitField::operator|(const TBitField & bf) // операция "или"
{
	int len = BitLen; 
	int mn_len = bf.BitLen; 
	if (bf.BitLen > BitLen) {
		len = bf.BitLen; 
		mn_len = BitLen; 
	}
	TBitField a(len); 
	for (int i = 0; i < mn_len; i++) {
		a.pMem[i] = bf.pMem[i] | pMem[i]; 
	}
	for (int i = mn_len; i < len; i++) {
		a.pMem[i] = bf.pMem[i]; 
	}
	return a;
}

TBitField TBitField::operator&(const TBitField & bf) // операция "и"
{
	int len = BitLen;
	int mn_len = bf.BitLen;
	if (bf.BitLen > BitLen) {
		len = bf.BitLen;
		mn_len = BitLen;
	}
	TBitField a(len);
	for (int i = 0; i < mn_len; i++) {
		a.pMem[i] = bf.pMem[i] & pMem[i];
	}
	for (int i = mn_len; i < len; i++) {
		a.pMem[i] = bf.pMem[i];
	}
	return a;
}

TBitField TBitField::operator~(void) // отрицание
{
	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] == TELEM(0)) {
			pMem[i] = TELEM(1); 
		}
		else if (pMem[i] == TELEM(1)) {
			pMem[i] = TELEM(0); 
		}
	}

	return TBitField(0);
}

// ввод/вывод

istream& operator>>(istream & is, TBitField & bf) // ввод
{
	std::cout << "Vvedi kolichestvo elementov tboego mnojestva : "; 
	is >> bf.BitLen; 
	int a; 
	for (int i = 0; i < bf.BitLen; i++) {
		is >> a; 
		bf.pMem[a] = 1;
	}
  return is;
}

ostream& operator<<(ostream & os, const TBitField & bf) // вывод
{
	if (bf.BitLen == 0) {
		os << 0; 
		return os; 
	} 
	os << '[';
	for (int i = 0; i < bf.BitLen; i++) {
		if (bf.pMem[i] == 1) {
			os << i << ', '; 
		}
	}
	os << bf.pMem[bf.BitLen] << ']'; 
	return os;
}
