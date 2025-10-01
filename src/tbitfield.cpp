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
	if (len < 0){
		throw 1; 
	}
	else if (len == 0) {
		BitLen = 0; 
		MemLen = 0; 
	}
	else {
		BitLen = len;
		MemLen = (BitLen + BITS_IN_ONE_MEM - 1) / BITS_IN_ONE_MEM;
		pMem = new TELEM[MemLen];

		for (int i = 0; i < MemLen; i++) {
			pMem[i] = 0;
		}
	} 
} 

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen; 
	MemLen = bf.MemLen; 
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
	return 1 << (n % BITS_IN_ONE_MEM);
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
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n > BitLen) {
		throw 3;
	}
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));

}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n > BitLen) {
		throw 4;
	}
	
	return pMem[GetMemIndex(n)] & GetMemMask(n);

}

// битовые операции

TBitField& TBitField::operator=(const TBitField & bf) // присваивание
{
	if (this != &bf) { // проверка на самоприсваивание
		delete[] pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}

int TBitField::operator==(const TBitField & bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;

	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i])
			return false;
	}
	return true;
}

int TBitField::operator!=(const TBitField & bf) const // сравнение
{
	return(!(this->operator==(bf)));
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int len = std::max(BitLen, bf.BitLen);
	TBitField a(len);
	if (bf.BitLen > BitLen) {
		for (int i = 0; i < bf.MemLen; i++) {
			cout << a.pMem[i] << ", ";
			a.pMem[i] = bf.pMem[i];
			cout << a.pMem[i] << "\n";

		}
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";

		for (int i = 0; i < MemLen; i++) {
			a.pMem[i] |= pMem[i];
		}
	}
	else {
		for (int i = 0; i < MemLen; i++) {
			cout << a.pMem[i] << ", ";
			a.pMem[i] = pMem[i];
			cout << a.pMem[i] << "\n";
		}
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
		for (int i = 0; i < bf.MemLen; i++) {
			cout << a.pMem[i] << ", ";
			a.pMem[i] |= bf.pMem[i];
			cout << a.pMem[i] << "\n";

		}
	}
	return a;
}


TBitField TBitField::operator&(const TBitField & bf) // операция "и"
{
	int len = std::max(BitLen, bf.BitLen); 
	TBitField a(len); 
	if (bf.BitLen > BitLen) {
		for (int i = 0; i < MemLen; i++) {
			a.pMem[i] = pMem[i];
		}

		for (int i = 0; i < MemLen; i++) {

			a.pMem[i] &= bf.pMem[i];
		}
	}
	else {
		for (int i = 0; i < bf.MemLen; i++) {
			a.pMem[i] = bf.pMem[i];

		}
		for (int i = 0; i < bf.MemLen; i++) {
			a.pMem[i] &= pMem[i];
		}
	} 
	return a; 
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField a(*this); 
	for (int i = 0; i < MemLen - 1; i++) {
		a.pMem[i] = ~pMem[i]; 
	}
	for (int i = (MemLen - 1) * BITS_IN_ONE_MEM; i < a.BitLen; i++) {
		if (a.GetBit(i) == 0) {
			a.SetBit(i); 
		}
		else {
			a.ClrBit(i); 
		}
	}
	
	return a;
}

// ввод/вывод

istream& operator>>(istream & is, TBitField & bf) // ввод
{
	return is;
}

ostream& operator<<(ostream & os, const TBitField & bf) // вывод
{
	return os; 
}
