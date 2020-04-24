#include <iostream>
#include <chrono>
#include <random>
#include <iterator>
#include "Avl_Tree.h"

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    constexpr uint64_t Size = 30; 
    std::uniform_int_distribution<int32_t> dis(0, Size);

    Avl_Tree<int32_t, int32_t> Tree;

    vector<int32_t> inserter_arr;
    inserter_arr.reserve(Size);
    //auto inserter = back_inserter(inserter_arr);
    vector<int32_t> delete_arr;
    delete_arr.reserve(Size);

    for (int32_t i = Size; i > 0; --i) {
        int32_t random = dis(gen); 
        Tree.insert({ random,random });
        inserter_arr.push_back(random);
    }

    sort(begin(inserter_arr), end(inserter_arr));

    std::cout << " 삽입한 데이터들... " << endl << endl;

    copy(begin(inserter_arr),end(inserter_arr),ostream_iterator<int32_t>
        (cout, " ")); 

    std::cout  << endl;

    std::cout << " 삽입 이후 트리 " << Tree << endl;

    for (int32_t i = Size; i > 0; --i) {
        int32_t random = dis(gen);
        Tree.erase({ random,random });
        delete_arr.push_back(random); 
    };

    sort(begin(delete_arr), end(delete_arr));

    std::cout << " 삭제한 데이터들... " << endl << endl;

    copy(begin(delete_arr), end(delete_arr), ostream_iterator<int32_t>
        (cout, " "));

    std::cout << " 삭제 이후 트리 " << Tree << endl; 
    
    std::cout << endl << endl << endl;

    Avl_Tree<int32_t, int32_t> Tester;
    Tester.insert({ 5,1 });
    Tester.insert({ 4,1 });
    Tester.insert({ 7,1 });
    Tester.insert({ 2,1 });
    Tester.insert({ 9,1 });
    Tester.insert({ 2,1 });
    Tester.insert({ 9,1 });
    std::cout << Tester << endl;
    Tester.erase({ 5,1 });
    Tester.erase({ 4,1 });
    Tester.erase({ 7,1 });
    Tester.erase({ 2,1 });
    std::cout << Tester << endl;

};