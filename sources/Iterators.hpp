#pragma once
#include <iostream>
#include <map>
#include <set>
#include "BinaryTree.hpp"
namespace ariel
{
    template<typename T>
    class PreOrderIt 
    {
        private:
            Node<T>* curr;
            Node<T>* begin_node;
            set<Node<T>&>visited;
        public:
            PreOrderIt<T>(Node<T>* node = nullptr) : curr(node) begin_node(node)
            {}
            PreOrderIt begin()
            {
                return PreOrderIt{curr};
            }
            PreOrderIt end()
            {
                return PreOrderIt{nullptr};
            }

            PreOrderIt&  operator++() {
                check_children();
                return *this;
            }
            const PreOrderIt operator++(int) {
                
                PreOrderIt tmp= *this;
                visited.insert(curr);
                check_children();
                return tmp;
		    }
            
            const PreOrderIt check_children()
            {
                if(curr->left!=nullptr && !is_visited(curr->left))
                {
                    curr=curr->left
                }
                else if(curr->right!=nullptr && !is_visited(curr->right))
                {
                    curr=curr->right;
                }
                else
                {
                    Node<T>* temp=curr->parent;
                    while (temp!=nullptr)
                    {
                       if(temp->left!=nullptr && !is_visited(temp->left))
                        {
                            curr = temp->left;
                        } 
                        else if(temp->right!=nullptr && !is_visited(temp->right))
                        {
                            curr= curr->right;
                        }

                        temp=curr->parent;
                    }
                }
            }
            bool is_visited(Node<T>& n)
            {
                if(visited.find(n)==visited.end())
                    retrurn false;
                return true;
            }


    };


    template<typename T>
    class InOrderIt
    {
        private:
             Node<T>* curr;
        public:
            InOrderIt<T>(Node<T>* node = nullptr) : curr(node)
            {}
            InOrderIt begin()
            {
                Node<T>* node=curr;
                while(node->left!=NULL)
                {
                    node=node->left;
                }
                return InOrderIt{node};
            }
            InOrderIt end()
            {
                return InOrderIt{nullptr};
            }         

    };

    template<typename T>
    class PostOrderIt
    {
        private:
            Node<T>* curr;
        public:
            PostOrderIt<T>(Node<T>* node = nullptr) : curr(node)
            {}
            PostOrderIt begin()
            {
                Node<T>* node=curr;
                while(node->left!=NULL)
                {
                    node=node->left;
                }
                if(node->right!=NULL){
                    return PostOrderIt{node->right};
                }
                return PostOrderIt{node};
            }
            PostOrderIt end()
            {
                return PostOrderIt{nullptr};
            }         

    };

}