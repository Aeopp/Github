#include <iostream>
#include <string>
using namespace std;

template<typename t>
struct node
{
	t data;
	node* next = nullptr;
	node* prev = nullptr;
	node(const t& pdata) : data(pdata) {}; 
};
template<typename t>
class List
{
public:
	node<t>* head = nullptr;
	node<t>* tail = nullptr;
	bool isEmpty()
	{
		return (!(head&&tail));
	};
	List<t>() = default; 
	int32_t  erase(int32_t offset)
	{
		if (head==nullptr)
			return 0;
		node<t>* deleter = head;
		node<t>* left = head->prev;
		node<t>* right =head->next ;

		while (--offset>0)
		{
			deleter = deleter->next;
			left = deleter->prev;
			right = deleter->next;
		};
		if (deleter&&left&&right)
		{
			left->next = deleter->next;
			right->prev = deleter->prev;
			cout << "Delete : " << deleter->data << endl;
			delete deleter;
			
			head = left;
			tail = right;
		};
	};
	void Insert(const t& data)
	{
		node<t>* adder = new node<t>(data); 
		if (!head)
			head = adder;
		else if (!tail)
		{
			tail = adder;
			head->next = tail;
			head->prev = tail;
			tail->next = head;
			tail->prev = head;
		}
		else 
		{
			tail->next = adder;
			adder->next = head;
			adder->prev = tail;
			tail = adder;
		};
	};
	void print()
	{
		if (head==nullptr)
			return;

		node<t>* cur = head; 
		while (cur!=nullptr)
		{
			std::cout << cur->data << endl;
			cur = cur->next;
		};
	};
	t getdata(size_t offset)
	{
		node<t>* cur = head;

		while (offset--)
			cur = cur->next;

		return cur->data; 
	};
	/*virtual */~List()
	{
		/*node<t>* cur = head;
		while (cur)
		{
			node<t>* deleter = cur;
			cur = cur->next;
			delete deleter;
		};*/
	};
private:
};

int main()
{
	constexpr size_t dice = 3;

	List<std::string> LList;
	LList.Insert("A");
	LList.Insert("B");
	LList.Insert("C");
	LList.Insert("D");
	LList.Insert("E");
	LList.Insert("F");
	LList.Insert("G");
	LList.Insert("H");
	LList.Insert("I");
	LList.Insert("J");

	LList.erase(1);
	LList.erase(1);
	LList.erase(1);
	LList.erase(1);
				
	LList.erase(1);
	LList.erase(1);
	LList.erase(1);
	LList.erase(1);
	LList.erase(1);
	LList.erase(1);
	/*LList.erase(7);*/
//	LList.erase(7);
	


	//LList.print();
};