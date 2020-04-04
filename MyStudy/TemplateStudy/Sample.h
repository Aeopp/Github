//#pragma once
//
//#include <functional>
//#include <iostream>
//using namespace std;
//
//template<class T>
//class Super
//{
//private:
//	template<class T >
//	struct Sub
//	{
//		friend class Super;
//		T* Element;
//		Sub* Ptr = nullptr;
//		Sub(const T& Param): Element(new T()) {};
//		Sub() {};
//		~Sub() {};
//	};
//public:
//	template<class Y>
//	Y fuinwe(const Y& qwe)const;
//	void QWE();
//
//	Super();
//	~Super();
//	 void Function();
//	using fptr = std::function<bool(const T& Lhs, const T& Rhs)>;
//	fptr MPtr = nullptr;
//
//	template<class Y>
//	Sub<T>* TestFun(const Y& Temp,std::function<bool(const T& Lhs,const Y& Rhs)> Fp,
//		const T& Tp)const; 
//
//	template<class T>
//	friend std::ostream& operator<<(std::ostream& Co,const Super<T>& Target);
//	//{
//	//	std::cout << "	friend ostream& operator<<(ostream& Co, Super<T>& Target) \n\n ";
//	//};
//};
//#include "Imple.hpp"
//
