#pragma once
#include "Type.h"
#include <functional>
#include <iostream>
template<class T>
class Super
{
private:
	template<class T >
	struct Sub
	{
		friend class Super;
		T* Element;
		Sub* Ptr = nullptr;
		Sub(const T& Param): Element(new T()) {};
		Sub() {};
		~Sub() {};
	};
public:
	template<class Y>
	Y fuinwe(const Y& qwe)const;
	void QWE();

	Super();
	~Super();
	inline void Function();
	using fptr = std::function<bool(const T& Lhs, const T& Rhs)>;
	fptr MPtr = nullptr;

	template<class Y>
	Sub<T>* TestFun(const Y& Temp,std::function<bool(const T& Lhs,const Y& Rhs)> Fp,
		const T& Tp)const; 

};
template<class T>
void Super<T>::QWE()
{};

template<class T>
template<class Y>
Y Super<T>::fuinwe(const Y& qwe)const
{
	std::cout << qwe << std::endl;
	return Y(12);
};

template<class T>
inline Super<T>::Super()
{
	int EWQE = 11;
	int& EQWRQWR = EWQE;

	fptr Ptr = [ = ](const T& Lhs, const T& Rhs)->bool {
	
		std::cout << Lhs + Rhs << std::endl;

		std::cout << EWQE << std::endl;
		std::cout << EQWRQWR << std::endl;

		return true;  
	
	};
	MPtr = Ptr;
	Sub<T>();
}

template<class T>
inline Super<T>::~Super()
{
}

template<class T>
inline void Super<T>::Function()
{
}

//template<class T>
//template<class Y>
//inline void Super<T>::TestFun(const Y& Temp, fptr Fp, const T& Tp) const
//{
//	
//	
//	
//	
//	
//
//}

template<class T>
template<class Y>
inline Super<T>::Sub<T>*Super<T>::TestFun(const Y& Temp, 

	std::function<bool(const T& Lhs, const Y& Rhs) >

Fp, 
const T& Tp) const
{
	int qqq = 2;
	int qweqwe = 523523;

	this->MPtr(qqq,qweqwe);


	int a = 2;
	float c = 3;
	Fp(a, c);
	std::cout << Tp;
	std::cout << Temp;
	return new Sub<T>();

}
