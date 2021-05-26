#include "doctest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <list>
using namespace std;
#include "BinaryTree.hpp"
using namespace ariel;

class person{
    public:
    string name;
    int age;
    person():name(""),age(0){}
    //~person(){}
    person(string name,int age) : name(name), age(age){}
    friend bool operator==(const person &p1,const person &p2)
    {
        return p1.name==p2.name && p1.age==p2.age;
    }

    friend bool operator!=(const person &p1,const person &p2)
    {
        return !(p1==p2);
    }
    friend ostream& operator<<(ostream& os,const person &p)
    {
        os<<"name: "<<p.name<<", age: "<<p.age<<endl;
        return os;
    } 
    friend ostream& operator<<(ostream& os,const list<person>l)
    {   os<<"[ ";
        for(person p: l)
        {
            os<<"{name: "<<p.name<<", age: "<<p.age<<"},";
        }
        return os<<" ]";
         
    }

    
};

TEST_CASE("int tree")
{

    BinaryTree<int>bt;
    bt.add_root(1); 
    bt.add_left(1,2);
    bt.add_left(2,3);
    bt.add_right(2,4);
    bt.add_right(4,5);
    bt.add_right(1,6);
    bt.add_left(6,7);
    bt.add_right(7,8);
    bt.add_right(6,9);
    bt.add_left(9,10);
    
    int count=1;
    for(auto it=bt.begin_preorder();it!=bt.end_preorder();it++) //10 checks
    {
        cout << (*it) << " " ;
        CHECK(count==*it);
        count++;
    }
}

TEST_CASE("string tree") {
    BinaryTree<string>bt;
    //CHECK_THROWS(cout<<bt);
    bt.add_root("10"); 
    bt.add_root("5"); // root=5
    CHECK_THROWS(bt.add_left("10","2"));
    bt.add_left("5","2");
    bt.add_left("2","1");
    bt.add_right("2","3");
    bt.add_right("3","4");

    bt.add_right("5","8");
    bt.add_left("8","6");
    bt.add_right("8","10");
    bt.add_right("6","7");
    bt.add_left("10","9");
    
    int count=1;
    for(auto it=bt.begin_inorder();it!=bt.end_inorder();it++) //10 checks
    {
        cout << (*it) << " " ;
        CHECK(to_string(count)==*it);
        count++;
    }

}


TEST_CASE("person tree")
{
    BinaryTree<person>bt;
    person dan{"Dan",81};
    person rachel{"Rachel",60};
    person gad{"Gad",56};
    person ben{"Ben",40};
    person avi{"Avi",38};
    person rivka{"Rivka",30};
    person gil{"Gil",10};
    person yael{"Yael",23};
    person noam{"Noam",15};
    person dor{"Dor",26};
    bt.add_root(dor);
    CHECK_NOTHROW(bt.add_root(dan)); //dan replaced dor as root
    CHECK_THROWS(bt.add_left(dor,gad)); //dor doesn't exist 
    bt.add_left(dan,gad);
    bt.add_right(gad,rivka);
    bt.add_left(rivka,gil);
    bt.add_right(dan,rachel);
    bt.add_left(rachel,ben);
    bt.add_right(rachel,avi);
    bt.add_left(ben,dor);
    CHECK_NOTHROW(bt.add_left(ben,yael));
    CHECK_THROWS(bt.add_left(dor,noam));
    bt.add_right(ben,noam);
    //cout<<bt<<endl;
    queue<person>family;
    family.emplace(gad);
    family.emplace(gil);
    family.emplace(rivka);
    family.emplace(dan);
    family.emplace(yael);
    family.emplace(ben);
    family.emplace(noam);
    family.emplace(rachel);
    family.emplace(avi);
    for(auto it=bt.begin();it!=bt.end();it++,family.pop())
    {
        CHECK(*it==family.front());
    }
    
}

TEST_CASE("set<person> tree")
{
    BinaryTree<list<person>>bt;
    person dan{"Dan",81};
    person rachel{"Rachel",60};
    person gad{"Gad",56};
    person ben{"Ben",40};
    person avi{"Avi",38};
    person rivka{"Rivka",30};
    person gil{"Gil",10};
    person yael{"Yael",23};
    person noam{"Noam",15};
    person dor{"Dor",26};
    list<person>age70_89={dan};
    list<person>age50_69={rachel,gad};
    list<person>age30_49={ben,avi,rivka};
    list<person>age10_29={gil,noam,yael,dor};
    bt.add_root(age70_89);
    bt.add_left(age70_89,age50_69);
    bt.add_right(age50_69,age30_49);
    bt.add_left(age30_49,age10_29);
    //cout<<bt<<endl;
    queue<list<person>>ages;
    ages.emplace(age10_29);
    ages.emplace(age30_49);
    ages.emplace(age50_69);
    ages.emplace(age70_89);
    for(auto it=bt.begin_postorder();it!=bt.end_postorder();it++,ages.pop())
    {
        CHECK(it->front()==ages.front().front());
    }
   
}