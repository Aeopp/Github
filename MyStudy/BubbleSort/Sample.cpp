#include <iostream>
#include <utility>
#include <xutility>
#include <random>
#include <array>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

namespace util
{
    template <class Ty,int64_t size,
        typename = 
        enable_if_t<is_move_constructible_v<Ty>&& is_move_assignable_v<Ty>>>

        constexpr void swap(Ty(& Left)[size],Ty(& Right)[size]) noexcept
        (is_nothrow_move_constructible_v<Ty>&& is_nothrow_move_assignable_v<Ty>)
    {
        std::remove_reference_t<Ty> Tmp = std::move(Left);
        Left = std::move(Right);
        Right = std::move(Tmp);
    };
}

//template<typename Ty,int64_t N>
//constexpr void bubble_sort(Ty(&arr)[N])noexcept
//{
//    for (int32_t i = 0; i < N-1; ++i)
//    {
//        for (int32_t j = 0; j < N-i; ++j)
//        {
//            if (arr[j] < arr[j + 1])
//            {
//                std::remove_reference_t<Ty> temp = arr[j];
//                arr[j] = arr[j + 1];
//                arr[j + 1] = temp; 
//            }
//        }
//    }
//}
template<typename Ty,size_t N>
constexpr void bubble_sort(std::array<Ty, N>& arr)noexcept
{
    bool flag = false;
    int32_t count = 0;
    for (int32_t i = 0; i < N - 1; ++i)
    {
        flag = true;
        for (int32_t j = 0; j < N - i - 1; ++j)
        {
            ++count;
            if (arr[j] < arr[j + 1])
            {
                flag = false;
                std::remove_reference_t<Ty> temp = std::move(arr[j]);
                arr[j] = std::move(arr[j + 1]);
                arr[j + 1] = std::move(temp);
            }
        }
        if (flag)
            break;
    }
    std::cout << " Count ? : " << count << std::endl;
};

template<typename Ty, size_t N>
constexpr void selection_sort(std::array<Ty, N>& arr)noexcept
{
    bool flag = false;
    int32_t count = 0;
    for (int32_t i = 0; i < N - 1; ++i)
    {
        flag = true;
        std::remove_reference_t<Ty> temp =
        std::numeric_limits<Ty>::min(); 
        int32_t swap_index;
        for (int32_t j = 1; j < N - i; ++j)
        {
            ++count;
            if (temp < arr[j])
            {
                flag = false;
                temp = arr[j];
                swap_index = j;
            }
        };
        if (flag)
            break;
        else {
            arr[swap_index] = std::move(arr[N - i - 1]);
            arr[N - i - 1] = std::move(temp);
        }
    }
    std::cout << " Count ? : " << count << std::endl;
};
template<typename Ty, size_t N>
constexpr void insert_sort(std::array<Ty, N>& arr)noexcept
{
    int32_t count = 0;
    for (int32_t i = 1; i < N; ++i)
    {
        std::remove_reference_t<Ty> target = arr[i];
        int32_t swap_index = -1; 
        for (int32_t j = 0; j < i; ++j)
        {
            count++;
            if (target < arr[j])
            {
                swap_index = j; 
                break; 
            };
        }
        if(swap_index != -1)
        {
            for (int32_t right = i; right > swap_index; --right)
            {
                arr[right] = std::move(arr[right - 1]);
            };
            arr[swap_index] = std::move(target);
        }
    }
    std::cout << " Count ? : " << count << std::endl;
};
//template<typename Ty, size_t N>
//constexpr void quick_sort(std::array<Ty, N>& arr,int32_t left,int32_t right)noexcept
//{
//    if (left >= right) return; 
//    int32_t count = 0; 
//    int32_t pivot = left; 
//    int32_t end = right; 
//
//    while (left < right)
//    {
//        while (arr[pivot] < arr[right])
//            right--; 
//        while (left < right && arr[pivot] >= arr[left])
//            left++; 
//        
//        std::remove_reference_t<Ty> temp = arr[left];
//        arr[left] = arr[right];
//        arr[right] = temp;
//
//    }
//};
//template<typename Ty>
//constexpr void quick_sort(std::vector<Ty>& arr,int32_t left, int32_t right)noexcept
//{
//    if (left >= right)return; 
//    int32_t pivot = (left + right) / 2; 
//    const int32_t begin = left;
//    const int32_t end = right;  
//
//    while (left <= right)
//    {
//        while ( arr[left] < arr[pivot])
//            ++left;
//        while ( arr[right] > arr[pivot])
//            --right;
//
//        if (left <= right)
//        {
//            int temp = arr[left];
//            arr[left] = arr[right];
//            arr[right] = temp;
//            left++; right--;
//        }
//    };
//    quick_sort(arr,begin , right); 
//    quick_sort(arr, left,end);
//}
template<typename Ty,size_t N>
void quick_sort(std::array<Ty,N>& arr,int32_t left, int32_t right)
{
    if (left >= right) return;
    int32_t pivot = arr[(left + right) / 2];
    int32_t begin = left;
    int32_t end = right;

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
    quick_sort(arr,left, end);
}



int main()
{
    std::array<int32_t,100> arr;

    std::random_device rand_device;
    std::mt19937 gen(rand_device());
    std::uniform_int_distribution<int32_t> distribution(0,100);

    auto rand_replace = [&distribution,&gen]
    (auto& element) {element = distribution(gen); };

    std::for_each(std::begin(arr), std::end(arr),rand_replace);

    std::cout << "Before \n";
    std::copy(std::begin(arr), std::end(arr),
        std::ostream_iterator<decltype(arr[0])>(std::cout, " "));
    
   
    std::cout << "\nAfter \n";
    quick_sort(arr,0,99);
 
    for (int32_t a : arr)
    {
        std::cout << a << " ";
    }
}