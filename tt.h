#include "ttnode.h"
#ifndef TT_H
#define TT_H
class TT{
	public:
        void buildTree(ifstream &input);
        vector<int> findhelp(TTNode* root, string key);
	private:
		TTNode* root;
};
#endif
