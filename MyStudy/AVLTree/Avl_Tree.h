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

// ���� Ű�� ����
// ���� left �� right �� �̵� �Ҽ� ���� parent ���� �̵��� ������� ����
// Ű�� ����ũ�� (�ߺ��� ���� ������� ����) 
// �뷱�� ������ ���Ǵ� ���� ����Ʈ���� lhs ������ ����Ʈ���� rhs �� �Ҷ�
// factor = lhs - rhs ��.

// Case #1 ���� ����Ʈ���� ���� ����Ʈ������ ���� ������ ���
// LR ȸ���� �뷱�� ���Ͱ� 1���� ũ�� ������ ����� Ű�� ���� �ڽ��� Ű���� Ŭ�� ����
//        
// RR ȸ����     ""                           �ݴ��� ���
// Case #2 ���� ����Ʈ���� ���� ����Ʈ������ ������ ���

template<typename key_type,
    typename value_type, typename compare_type = less<key_type>
    /*�ߺ� Ű�� ������� �ʱ� ������ ���� ���� �ʿ�� ����*/>
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
        // ������ ���Ǵ� leaf ������ ���� �� ����� ����
        Node_ptr left = nullptr;
        Node_ptr right = nullptr;
        // Node_ptr parent = nullptr; �ʿ䰡 ����..
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
    // ���� ���� �Լ� 
    // ���� ����Ʈ���� �� ������ ����
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
        // ���� ���� ����Ʈ�� ���� �μ��� ���� �ٽ� �����
        // ȸ���ؾ��ϴ� ���̽� �����ϰ� ����
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
        // ���� ���� ����Ʈ�� ���� �μ��� ���� �ٽ� �����
        // ȸ���ؾ��ϴ� ���̽� �����ϰ� ����
        root = Balancing(balanced_case(root), root);
        return root;
    }
    // LR ������ ����
    // ��Ʈ ���� lhs - rhs > 1 && ���� �ڽĳ�� ���� ������ ���� > ���� ����
    Node_ptr LR_Rotate(Node_ptr root) {
        // ��Ʈ���� ���� �ڽĿ� ���ؼ� RR ȸ�� ����
        root->left = RR_Rotate(root->left);
        // ��Ʈ�� LL ȸ�� ����
        return LL_Rotate(root);
    }
    Node_ptr RL_Rotate(Node_ptr root) {
        // ��Ʈ���� ������ �ڽĿ� ���ؼ� LL ȸ�� ����
        root->right = LL_Rotate(root->right);
        // ��Ʈ�� RR ȸ�� ����
        return   RR_Rotate(root);
    }
    Node_ptr RR_Rotate(Node_ptr root) {
        // �θ����� ������ �ڽĳ�带 �ڽĳ�带   ������ ������ �ڽĳ���� 
        // ���� �ڽĳ��� ��ü
        auto prev_root_right = root->right;
        root->right = root->right->left;
        (prev_root_right)->left = root;
        return prev_root_right;
    };

    // ������ ����Ʈ���� �� ������ ����
    Node_ptr LL_Rotate(Node_ptr root) {
        // ��Ʈ �������� ������Ʈ ����
        // �θ����� ���� �ڽĳ�带  �θ����� ���� �ڽĳ���� ������ �ڽĳ��� ��ü
        auto prev_root_left = root->left;
        root->left = root->left->right;
        // �θ����� ���� �ڽĳ�忴�� ����� ������ �ڽĳ�带 ��Ʈ ���� ��ü
        (prev_root_left)->right = root;
        return prev_root_left;
    }
    // leaf �� NULL �� �ڽ� ���� -1�� ������
              // Height = max(leftchild.height(),rightchild.height()+1; 
    int32_t calc_Height(const Node_ptr const  target) const {
        if (target == nullptr) return 0;
        return (max(calc_Height(target->left), calc_Height(target->right)) + 1);
    };
    int32_t balance_factor(const Node_ptr const  target)const {
        if (target == nullptr)return 0; 
        return calc_Height(target->left) - calc_Height(target->right);
    }
    // calc ����ؼ� ���� ������
    // calc �ΰ� �޾Ƽ� ���밪 ����غ�;
    // 1�ʰ��ϸ� �ұ�����
    // 

    // ���� ���� ����Ʈ���� �������̰� 1 �ʰ� �Ұ�� �ұ������� �����Ѵ�.
    // ABS(leftsubtree.height () - rightsubtree.height() ) > 1  �ұ��� !!
    // ������ �ȸ´´ٸ� False �����Ѵ�.
    // �˻��ϱ��� �ݵ�� ���� ������ �����ؾ��Ѵ� calc_Height
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



