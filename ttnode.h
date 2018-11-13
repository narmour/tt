#ifndef TTNODE_H
#define TTNODE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>


using namespace std;

// 2-3 tree node implementation
class TTNode{
	public:
  		TTNode() { _center = _left = _right = nullptr; }
    	TTNode(string lk, vector<int> lv, string rk, vector<int> rv,
                TTNode* p1, TTNode* p2,
                TTNode* p3);
        TTNode(TTNode* t){_center = t->_center;_left=t->_left;_right=t->_right;
                         _lval=t->_lval;_lkey=t->_lkey;_rval=t->_rval;_rkey=t->_rkey;}
                         
  		bool isLeaf() { return _left == nullptr; }
  		TTNode* lchild() { return _left; }
  		TTNode* rchild() { return _right; }
  		TTNode* cchild() { return _center; }
  		string lkey() { return _lkey; }  // Left key
  		vector<int> lval() { return _lval; }  // Left value
        void add_lval(int l){_lval.push_back(l);}
        void add_rval(int l){_rval.push_back(l);}
  		string rkey() { return _rkey; }  // Right key
  		vector<int> rval() { return _rval; }  // Right value
  		void setLeft(string k, vector<int> e) { _lkey = k; _lval = e; }
  		void setRight(string k, vector<int> e) { _rkey = k; _rval = e; }
  		void setLeftChild(TTNode* it) { _left = it; }
  		void setCenterChild(TTNode* it){ _center = it; }
  		void setRightChild(TTNode* it) { _right = it; }
		TTNode* add(TTNode* it);
	private:
   		vector<int>  _lval;        // The left record
   		string _lkey;        // The node's left key
   		vector<int> _rval;        // The right record
   		string _rkey;        // The node's right key
   		TTNode* _left;   // Pointer to left child
   		TTNode* _center; // Pointer to middle child
   		TTNode* _right;  // Pointer to right child
};
#endif


