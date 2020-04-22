#include <iterator>
#include <vector>
#include <iostream> 
using namespace std; 
template<typename Ty>
void quick_sort(std::vector<Ty>& arr, int32_t left, int32_t right)
{
    if (left >= right) return;
    const int32_t pivot = arr[(left + right) / 2];
    const int32_t begin = left;
    const int32_t end = right;

    while (left <= right)
    {
        while (arr[left] < pivot) left++;
        while (arr[right] > pivot) right--;
        if (left <= right)
        {
            std::swap(arr[left], arr[right]);
            left++; right--;
        }
    }
    quick_sort(arr, begin, right);
    quick_sort(arr, left, end);
};
template<typename _Ty>
struct it
{
    using difference_type = typename _Ty::difference_type; 
    
};
int main()
{
    std::advance
    
    int32_t arrsize; 
    std::cin >> arrsize;
    std::vector<int32_t> arr(arrsize); 
    
    iterator_traits<decltype(arr.begin())>::value_type abc = 455;
    std::cout << abc << std::endl;
  /*  using _type = decltype(arr); 
    _type arwqeqw;*/

    std::copy(std::istream_iterator<int32_t>(std::cin),
    std::istream_iterator<int32_t>(), std::begin(arr));

    quick_sort(arr, 0, arr.size() - 1);

    std::copy(std::begin(arr), std::end(arr), 
    std::ostream_iterator<int32_t>(cout,"\n"));

    

}
