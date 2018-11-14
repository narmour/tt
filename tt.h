#include "ttnode.h"
#ifndef TT_H
#define TT_H
class TT{
	public:
        TT() { root = nullptr ; }
        void buildTree(ifstream &input);
        void printTree(ostream &outs);
        vector<int> findhelp(TTNode* root, string key);
        void contains();
        int findHeight(TTNode* root);

	private:
        void printTreeHelper(TTNode* root,ostream &outs);
		TTNode* root;
};
#endif
