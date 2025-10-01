// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	if (mp < 0)
	{
		throw 1;
	}
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(0)
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(0)
{
	MaxPower = bf.GetLength();
	BitField = bf;
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return (BitField.GetBit(Elem));
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem < 0 || Elem > this->GetMaxPower())
	{
		throw 2;
	}
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem < 0 || Elem > this->GetMaxPower())
	{
		throw 3;
	}
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet &TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower == s.MaxPower && BitField == s.BitField)
	{
		return true;
	}
	return false;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return (!(this->operator==(s)));
}

TSet TSet::operator+(const TSet &s) // объединение
{
	// int len = max(s.MaxPower, MaxPower);
	// TSet a(len);
	// for (int i = 0; i < len; i++)
	// {
	// 	if ((i < MaxPower) && (BitField.GetBit(i) == 1) || (i < s.MaxPower && s.BitField.GetBit(i) == 1))
	// 	{
	// 		a.BitField.SetBit(i);
	// 	}
	// }
	return TSet(BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	int len = max(Elem, MaxPower);
	TSet a(len);
	a.BitField = BitField;
	a.InsElem(Elem);
	return a;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	int len = max(Elem, MaxPower);
	TSet a(len);
	a.BitField = BitField;
	a.DelElem(Elem);
	return a;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	// int len = max(s.MaxPower, MaxPower);
	// TSet a(len);
	// int mlen = min(s.MaxPower, MaxPower);
	// for (int i = 0; i < mlen; i++) {
	// 	if (BitField.GetBit(i) == 1	 && s.BitField.GetBit(i) == 1) {
	// 		a.BitField.SetBit(i);
	// 	}

	// }

	return TSet(BitField & s.BitField);
}

TSet TSet::operator~(void) // дополнение
{
	TSet a(MaxPower);
	for (int i = 0; i < MaxPower; i++)
	{
		if (BitField.GetBit(i) == 0)
		{
			a.BitField.SetBit(i);
		}
	}
	return a;
}

// перегрузка ввода/вывода

istream &operator>>(istream &is, TSet &s) // ввод
{
	is >> s.BitField;
	return is;
}

ostream &operator<<(ostream &os, const TSet &s) // вывод
{
	os << s.BitField;
	return os;
}