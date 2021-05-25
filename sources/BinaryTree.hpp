/*
sources:
https://github.com/mission-peace/interview/blob/master/src/com/interview/tree/TreeTraversals.java#L105
https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html
https://www.geeksforgeeks.org/iterative-postorder-traversal-using-stack/
*/
#pragma once
#include <iostream>
#include <unordered_map>
#include <queue>
#include <deque>
#include <stack>
using namespace std;
namespace ariel
{
    
    template <typename T>
    class BinaryTree
    {
    
        private:
            struct Node
            {
                T data;
                Node *right,* left;
                Node() : data(nullptr), right(nullptr),left(nullptr)
                {}
                Node(T data) : data(data), right(nullptr),left(nullptr)
                {}

            };

            Node* root;

        public:
        
            BinaryTree():root(nullptr){}
            ~BinaryTree()
            {
                delete_nodes(root);
            }

            void delete_nodes(Node* node)
            {
                if(node != nullptr)
                {
                    if(node->left == nullptr && node->right ==nullptr)
                    {
                        //node->data=da;
                        delete(node);
                    }
                    else if(node->left==nullptr && node->right!=nullptr)
                    {
                        delete_nodes(node->right);
                    }
                    else if (node->left!=nullptr && node->right==nullptr)
                    {
                        delete_nodes(node->left);
                    }
                    else
                    { 
                        delete_nodes(node->left);
                        delete_nodes(node->right);
                    }
                }
            }

            Node* find_node(Node* node,T data)
            {
                if(node != nullptr )
                {
                    if( node->data == data)
                    {
                        return node;
                    }
                    if(node->left != nullptr && node->right !=nullptr)
                    {
                        Node *temp = find_node(node->left,data);
                        if(temp==nullptr)
                            return find_node(node->right,data);
                        return temp;
                    }
                    if(node->left==nullptr && node->right!=nullptr)
                    {
                        return find_node(node->right,data);
                    }
                    if (node->left!=nullptr && node->right==nullptr)
                    {
                        return find_node(node->left,data);
                    }
                }
                return nullptr;
            }

            void change_data(Node* node,T new_data)
            {
                node->data=new_data;
            }

            /*add root to the tree*/
            BinaryTree<T>& add_root(T data)
            {
                if (root==nullptr){
                    root= new Node(data);
                    return *this;
                }
                
                change_data(root,data);
                return *this;
            }

            /*add left son to the parent*/
            BinaryTree<T>& add_left(T parent, T left)
            {
                Node* p=find_node(root,parent);
                if(p==nullptr)
                {
                    throw invalid_argument{"the node doesn't exist"};
                }
                if(p->left!=nullptr){
                    change_data(p->left,left);
                    return *this;
                }
                p->left=new Node(left);
                return *this;
            }
            /*add right son to the parent*/
            BinaryTree<T>& add_right(T parent, T right){
                Node* p=find_node(root,parent);
                if(p==nullptr)
                {
                    throw invalid_argument{"the node doesn't exist"};
                }
                if(p->right!=nullptr){
                    change_data(p->right,right);
                    return *this;
                }
                p->right=new Node(right);
                return *this;
            }
            
            friend ostream& operator<<(ostream& os,BinaryTree<T>& bt)
            {
                if(bt.root==nullptr)
                {
                    return os<<"The tree is empty"<<endl;
                }
                for (auto it=bt.begin_preorder(); it!=bt.end_preorder(); ++it) {
                    os << (*it) << "," ;
                }
                return os<<endl;
            }

        private:
            class iterator
            {
                protected:
                    Node* curr;
                    queue<Node*>nodes_order;

                    void init(Node* node)
                    {
                       if(node!=nullptr){
                        order(node);
                        curr=nodes_order.front();
                        nodes_order.pop();
                        } 
                        else
                        {
                            curr=nullptr;
                        }

                    }
                    virtual void order(Node* node){}

                public:
                    
                    iterator& operator++() {
                        if(nodes_order.empty())
                        {
                            curr=nullptr;
                            return *this;
                        }
                        curr=nodes_order.front();
                        nodes_order.pop();
                        return *this;
                    }
                    const iterator operator++(int) {
                        
                        iterator tmp= *this;
                        if(nodes_order.empty())
                        {
                            curr=nullptr;
                            return tmp;
                        }
                        curr=nodes_order.front();
                        nodes_order.pop();
                        return tmp;
                    }
                    
                    const T& operator*() const {
			        return curr->data;
                    }

                    const T* operator->() const {
			            return &(curr->data);
		            }

                    bool operator==(const iterator& other) const {
			            return curr == (other.curr);
		            }

		            bool operator!=(const iterator& other) const {
                         return curr != (other.curr);
		            }

            };

        public:
            class PreOrderIt:public iterator
            {
                public:
                PreOrderIt(Node* node = nullptr) {
                    iterator::init(node);
                }

                private:
                virtual void order(Node* node){
                    deque<Node*>stack;
                    stack.push_front(node);
                    while(!stack.empty()){
                        node = stack.front();
                        stack.pop_front();
                        iterator::nodes_order.push(node);
                        if(node->right != nullptr){
                            stack.push_front(node->right);
                        }
                        if(node->left!= nullptr){
                            stack.push_front(node->left);
                        }
                    }
                }
               
            };
            
            class InOrderIt : public iterator
            {
                public:
                    InOrderIt(Node* node = nullptr) {
                        iterator::init(node);
                    }

                private:
                    virtual void order(Node* node){
                        deque<Node*>stack;
                        while(true){
                            if(node != nullptr){
                                stack.push_front(node);
                                node = node->left;
                            }
                            else{
                                if(stack.empty()){
                                    break;
                                }
                                node = stack.front();
                                stack.pop_front();
                                iterator::nodes_order.push(node);
                                node = node->right;
                            }
                        }
                    }
                
            };

            class PostOrderIt : public iterator
            {
                public:
                    PostOrderIt(Node* node = nullptr) {
                        iterator::init(node);
                    }

                private:
                    virtual void order(Node* node){
                        deque<Node*>stack;
                        while(node != nullptr || !stack.empty()){
                            if(node != nullptr){
                                stack.push_front(node);
                                node = node->left;
                            }
                            else{
                                Node* temp = stack.front()->right;
                                if (temp == nullptr) {
                                    temp = stack.front();
                                    stack.pop_front();
                                    iterator::nodes_order.push(temp);
                                    while (!stack.empty() && temp == stack.front()->right) {
                                        temp = stack.front(); 
                                        stack.pop_front();
                                        iterator::nodes_order.push(temp);
                                    }
                                } 
                                else {
                                    node = temp;
                                }
                            }
                        }
                    }
               
            };

            PreOrderIt begin_preorder()
            {
                return PreOrderIt{root};
            }
            PreOrderIt end_preorder()
            {
                return PreOrderIt{nullptr};
            }

            InOrderIt begin_inorder()
            {
                return InOrderIt{root};
            }
            InOrderIt end_inorder()
            {
                return InOrderIt{nullptr};
            }

            PostOrderIt begin_postorder()
            {
                return PostOrderIt{root};
            }
            PostOrderIt end_postorder()
            {
                return PostOrderIt{nullptr};
            }

            InOrderIt begin()
            {
                return begin_inorder();
            }
            InOrderIt end()
            {
                return end_inorder();
            }

            

};
}