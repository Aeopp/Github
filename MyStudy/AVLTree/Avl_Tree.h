#pragma once
#include <iostream>
#include <string> 
#include <utility>
#include <functional>
#include <cmath>
#include <algorithm>
#include <tuple>
#include <map>
using namespace std;

// 노드는 키로 정렬
// 노드는 left 와 right 로 이동 할수 있음 parent 로의 이동은 허용하지 않음
// 키는 유니크함 (중복을 절대 허용하지 않음) 
// 밸런스 팩터의 정의는 왼쪽 서브트리를 lhs 오른쪽 서브트리를 rhs 라 할때
// factor = lhs - rhs 임.

// Case #1 좌측 서브트리가 우측 서브트리보다 많이 성장한 경우
// LR 회전은 밸런스 팩터가 1보다 크고 삽입한 노드의 키가 왼쪽 자식의 키보다 클때 시행
//        
// RR 회전은     ""                           반대의 경우
// Case #2 우측 서브트리가 좌측 서브트리보다 성장한 경우

template<typename key_type,
    typename value_type, typename compare_type = less<key_type>
    /*중복 키를 허용하지 않기 때문에 값을 비교할 필요는 없음*/>
    class Avl_Tree
{
private:
    template<typename _Ty>
    struct node
    {
        friend class Avl_Tree<key_type, value_type, compare_type>;
    private:
        using Node = node<_Ty>;
        using Node_ptr = Node*;
        
        node<_Ty>() = delete;
        node<_Ty>(node<_Ty>&&) noexcept = default;

        node<_Ty>& operator=(node<_Ty>&&) noexcept = default;
        node<_Ty>& operator=(const node<_Ty>&) = default;
        node<_Ty>(const node<_Ty>&) = default;

        node<_Ty>(const _Ty& p_Element) : Element{ p_Element } {};
        node<_Ty>(_Ty&& p_Element) : Element{ move(p_Element) } {};

        _Ty Element;
        int32_t height = 0;
        // 높이의 정의는 leaf 노드까지 가장 긴 경로의 길이
        Node_ptr left = nullptr;
        Node_ptr right = nullptr;
        // Node_ptr parent = nullptr; 필요가 없네..
    };
    using pair_type = pair</*const*/ key_type, value_type>;
    using Node = node<pair_type>;
    using Node_ptr = Node*;
    
    compare_type compare;
public:
    
    /*private*/  Node_ptr Root = nullptr;
    void inline insert(pair_type Element)& {
        Root = _insert(Root, Element);
    }
    void inline erase(pair_type Element)& {
        Root = _erase(Root, Element);
    }
    /* valuepair_typepe&*/
    value_type operator[](const key_type& p_key) {
        if (auto is_find = find(p_key);
            is_find != nullptr)
            is_find->Element.first;

        else return value_type();
    };
    void Print(const Node_ptr const root=nullptr) const {
        if (root == nullptr)return;

        Print(root->left);
        cout << root->Element.first << " ";
        Print(root->right);
    };
    template<typename key_type, typename value_type, typename compare_type> friend
    ostream& operator<<(ostream& out, const Avl_Tree<key_type, value_type, compare_type>&);
private:
    enum class ERotate_Case :int32_t {
        E_Balanced = -1,
        E_RR_Rotate,
        E_LL_Rotate,
        E_LR_Rotate,
        E_RL_Rotate,
    };
    // 구현 편의 함수 
    // 좌측 서브트리가 더 성장한 상태
    Node_ptr find(const key_type& p_key, Node_ptr root = Root) const& {
        if (Root == nullptr)
            return nullptr;
        /*throw bad_exception("Root does not exist");*/

        if (p_key < root->Element.first)
            return find(p_key, root->left);

        else if (root->Element.first < p_key)
            return  find(p_key, root->right);

        else return root;
    };
    Node_ptr Balancing(ERotate_Case Case, Node_ptr root) {
        switch (Case)
        {
        case ERotate_Case::E_RR_Rotate:
            return  RR_Rotate(root);
            break;
        case ERotate_Case::E_LL_Rotate:
            return LL_Rotate(root);
            break;
        case ERotate_Case::E_LR_Rotate:
            return  LR_Rotate(root);
            break;
        case ERotate_Case::E_RL_Rotate:
            return RL_Rotate(root);
            break;

        case ERotate_Case::E_Balanced:
            return root;
            /*break;*/
        default:
            return root;
            break;
        }
    }
    Node_ptr _insert(Node_ptr root, pair_type p_Element) {
        const auto& Key = p_Element.first;
        const auto& root_Key = root->Element.first;
        if (root == nullptr) {
            return new Node(p_Element);
        }
        else if (root_Key < Key) {
            root->right = _insert(root->right, p_Element);
        }
        else if (Key < root_Key) {
            root->left = _insert(root->left, p_Element);
        };
        // 좌측 우측 서브트리 균형 인수를 전부 다시 계산함
        // 회전해야하는 케이스 조사하고 실행
        return Balancing(balanced_case(root), root);
    }

    Node_ptr _erase(Node_ptr root, pair_type target) {
        if (root == nullptr) return nullptr;
     
        const auto& Key = target.first;
        const auto& root_Key = root->Element.first;

        if ((root_Key < Key) == false &&
            (Key < root_Key) == false) {

            if (root->left ==nullptr && root->right ==nullptr) {
                delete root; return nullptr;
            }
            else if (root->left && root->right) {
                auto Parent = root;
                auto Deleter = root->right;
                bool flag = false;
                while (Deleter->left) {
                    flag = true;
                    Parent = Deleter;
                    Deleter = Deleter->left;
                }
                 swap(root->Element, Deleter->Element);
                /*auto&& temp = move(root->Element);
                root->Element = move(Deleter->Element);
                Deleter->Element = move(temp);*/
                delete Deleter;

                if (flag)
                    Parent->left = nullptr;
                else
                    Parent->right = nullptr;
            }
            else if (root->left) {
                auto prev_root_left = root->left; 
                delete root; 
                return prev_root_left; 
            }
            else {
                auto prev_root_right = root->right;
                delete root;
                return prev_root_right; 
            }
        }
        else if (root_Key < Key) {
            root->right = _erase(root->right, target);
            return root; 
        }
        else if (Key < root_Key) {
            root->left = _erase(root->left, target);
            return root; 
        };
        // 좌측 우측 서브트리 균형 인수를 전부 다시 계산함
        // 회전해야하는 케이스 조사하고 실행
        root = Balancing(balanced_case(root), root);
        return root;
    }
    // LR 상태의 정의
    // 루트 기준 lhs - rhs > 1 && 왼쪽 자식노드 기준 오른쪽 높이 > 왼쪽 높이
    Node_ptr LR_Rotate(Node_ptr root) {
        // 루트기준 왼쪽 자식에 대해서 RR 회전 시행
        root->left = RR_Rotate(root->left);
        // 루트는 LL 회전 시행
        return LL_Rotate(root);
    }
    Node_ptr RL_Rotate(Node_ptr root) {
        // 루트기준 오른쪽 자식에 대해서 LL 회전 시행
        root->right = LL_Rotate(root->right);
        // 루트는 RR 회전 시행
        return   RR_Rotate(root);
    }
    Node_ptr RR_Rotate(Node_ptr root) {
        // 부모노드의 오른쪽 자식노드를 자식노드를   원래의 오른쪽 자식노드의 
        // 왼쪽 자식노드로 교체
        auto prev_root_right = root->right;
        root->right = root->right->left;
        (prev_root_right)->left = root;
        return prev_root_right;
    };

    // 오른쪽 서브트리가 더 성장한 상태
    Node_ptr LL_Rotate(Node_ptr root) {
        // 루트 기준으로 로테이트 수행
        // 부모노드의 왼쪽 자식노드를  부모노드의 왼쪽 자식노드의 오른쪽 자식노드로 교체
        auto prev_root_left = root->left;
        root->left = root->left->right;
        // 부모노드의 왼쪽 자식노드였던 노드의 오른쪽 자식노드를 루트 노드로 교체
        (prev_root_left)->right = root;
        return prev_root_left;
    }
    // leaf 의 NULL 인 자식 노드는 -1로 간주함
              // Height = max(leftchild.height(),rightchild.height()+1; 
    int32_t calc_Height(const Node_ptr const  target) const {
        if (target == nullptr) return 0;
        return (max(calc_Height(target->left), calc_Height(target->right)) + 1);
    };
    int32_t balance_factor(const Node_ptr const  target)const {
        if (target == nullptr)return 0; 
        return calc_Height(target->left) - calc_Height(target->right);
    }
    // calc 계산해서 위로 보내줌
    // calc 두개 받아서 절대값 계산해봄;
    // 1초과하면 불균형임
    // 

    // 좌측 우측 서브트리의 높이차이가 1 초과 할경우 불균형으로 간주한다.
    // ABS(leftsubtree.height () - rightsubtree.height() ) > 1  불균형 !!
    // 균형이 안맞는다면 False 리턴한다.
    // 검사하기전 반드시 높이 변수를 갱신해야한다 calc_Height
    /*int32_t inline balance_factor(Node_ptr target) const {
        int32_t left_height = target->left == nullptr ? -1 : target->left->height;
        int32_t right_height = target->right == nullptr ? -1 : target->right->height;
        return left_height - right_height;
    }*/
    ERotate_Case balanced_case(Node_ptr target) const {

        ERotate_Case Result = ERotate_Case::E_Balanced;
        int32_t factor = balance_factor(target); 
       
        if (factor > 1) {
            if (balance_factor(target->left) > 0)
                Result = ERotate_Case::E_LL_Rotate;
            else
                Result = ERotate_Case::E_LR_Rotate; 
        }
        else if(factor<-1){
            if (balance_factor(target->right) < 0)
                Result = ERotate_Case::E_RR_Rotate;
            else
                Result = ERotate_Case::E_RL_Rotate; 
        }

        return  Result;
    };
};

template<typename key_type, typename value_type, typename compare_type>
ostream& operator<<(ostream& out, const Avl_Tree<key_type, value_type, compare_type>& Avl_Tree)
{
    Avl_Tree.Print(Avl_Tree.Root);
    return out;
}



