#include "ttnode.h"
#ifndef TT_H
#define TT_H
class TT{
	public:
        TT() { root = nullptr ; }
        void buildTree(ifstream &input);
        void printTree(ostream &outs);
        vector<int> findhelp(TTNode* root, string key);
	private:
        void printTreeHelper(TTNode* root,ostream &outs);
		TTNode* root;
};
#endif
