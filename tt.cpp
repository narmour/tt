#include "ttnode.h"
#include "tt.h"


TTNode::TTNode(string lk, vector<int> lv, string rk, vector<int> rv,
                TTNode* p1, TTNode* p2,
                TTNode* p3) {
    	_lkey = lk; _rkey = rk;
    	_lval = lv; _rval = rv;
    	_left = p1; _center = p2; _right = p3;
  		};


vector<int>  TT::findhelp(TTNode* root, string k) {
  if (root == nullptr) return vector<int>();          // val not found
  if (k == root->lkey()) return root->lval();
  if ((!root->rkey().empty()) && (k == root->rkey()) )
    return root->rval();
  if (k < root->lkey() )       // Search left
    return findhelp(root->lchild(), k);
  else if (root->rkey().empty())           // Search center
    return findhelp(root->cchild(), k);
  else if (k < root->rkey())  // Search center
    return findhelp(root->cchild(), k);
  else return findhelp(root->rchild(), k); // Search right
}

// Add a new key/value pair to the node. There might be a subtree
// associated with the record being added. This information comes
// in the form of a 2-3 tree node with one key and a (possibly null)
// subtree through the center pointer field.
TTNode* TTNode::add(TTNode* it) {
  if (_rkey.empty()) { // Only one key, add here
    if (_lkey  < it->lkey()) {
        //cout << "ADD 1\n";
      _rkey = it->lkey(); _rval = it->lval();
      _center = it->lchild(); _right = it->cchild();
    }
    else {
        //cout << "ADD 2\n";
      _rkey = _lkey; _rval = _lval; _right = _center;
      _lkey = it->lkey(); _lval = it->lval();
      _center = it->cchild();
    }
    return this;
  }
  else if (_lkey >= it->lkey()) { // Add left
    //cout << "ADD    left\n";
    TTNode *N1 = new TTNode(_lkey, _lval, "", vector<int>() , it, this, nullptr);
    it->setLeftChild(_left);
    _left = _center; _center = _right; _right = nullptr;
    _lkey = _rkey; _lval = _rval; _rkey = ""; _rval = vector<int>();
    return N1;
  }
  else if (_rkey >= it->lkey()) { // Add center
    //cout << "ADD    center\n";
    //TTNode* temp = new TTNode(it);
    //cout << "temp->lkey:" << temp->lkey() << endl;
    //temp->setCenterChild(new TTNode (_rkey, _rval, "", vector<int>(), it->cchild(), _right, nullptr));
    //temp->setLeftChild(this);
    //_rkey = "";
    //_rval = vector<int>();
    //_right = nullptr;
    it->setCenterChild(new TTNode (_rkey, _rval, "", vector<int>(), it->cchild(), _right, nullptr));
    it->setLeftChild(this);
    _rkey = "";
    _rval = vector<int>();
    _right = nullptr;
    return it;  //TODO: this might be a problem
  }
  else { // Add right
    //cout << "ADD    right\n";
    TTNode *N1 = new TTNode (_rkey, _rval, "", vector<int>(), this, it, nullptr);
    it->setLeftChild(_right);
    _right = nullptr; _rkey = ""; _rval = vector<int>();
    return N1;
  }
}

// add  line to key k's line vector
TTNode *inserthelp(TTNode* rt, string k,int line,int &distinctWords) {
  TTNode* retval;
  if (rt == nullptr){ // Empty tree: create a leaf node for root
      //cout << "INSERTHELP making empty tree:\n";
    distinctWords++;
    vector<int> v;
    v.push_back(line);
    return new TTNode(k, v, "", vector<int>(), nullptr, nullptr, nullptr);
    
  }
  // check for duplicates?
  if(k == rt->lkey()){
      rt->add_lval(line);
      return rt;
  }
  if(k == rt->rkey()){
      rt->add_rval(line);
      return rt;
  }
  if (rt->isLeaf()){ // At leaf node: insert here
      //cout << "INSERTHELP inserting at leaf node:\n";
      //TTNode* temp = new TTNode(k, vector<int>(), "", vector<int>(), nullptr, nullptr, nullptr);
      //temp->add_lval(line);
    distinctWords++;
    //retval = rt->add(temp);
    //cout << "got back from add\n";
    //return retval;
    vector<int> v;
    v.push_back(line);
    return rt->add(new TTNode(k, v, "", vector<int>(), nullptr, nullptr, nullptr));
  }

  // Add to internal node
  if (k < rt->lkey()) { // Insert left
      //cout << "INSERTHELP insert left\n";
    retval = inserthelp(rt->lchild(), k,line,distinctWords);
    if (retval == rt->lchild()) return rt;
    else{ 
        //cout << "doing the addd?\n";
        return rt->add(retval);
    }

  }
  else if((rt->rkey().empty()) || (k < rt->rkey())) {
      //cout << "INSERTHELP insert center child\n";
    retval = inserthelp(rt->cchild(), k,line,distinctWords);
    if (retval == rt->cchild()) return rt;
    else return rt->add(retval);
  }
  else { // Insert right
      //cout << "INSERTHELP insert right child\n";
    retval = inserthelp(rt->rchild(), k,line,distinctWords);
    if (retval == rt->rchild()) return rt;
    else return rt->add(retval);
  }
}

void TT::buildTree(ifstream & input){
	int line = 1, numWords = 0, distWords = 0, treeHeight = 0;
	stringstream tempWord;
	double totalTime, finishTime, startTime = clock();
	while (!input.eof()) {
		string tempLine, tempWord;

		//Read a whole line of text from the file
		getline(input, tempLine);
		for (int i = 0; i < tempLine.length(); i++) {
		    //Insert valid chars into tempWord until a delimiter( newline or space) is found
		    while (tempLine[i] != ' '&& tempLine[i] != '\n' && i < tempLine.length() ) {
			tempWord.insert(tempWord.end(), tempLine[i]);
			i++;
		    }
		   
            //Trim any punctuation off end of word. Will leave things like apostrophes
            //and decimal points
            while(tempWord.length() > 0 && !isalnum(tempWord[tempWord.length() - 1]))
			    tempWord.resize(tempWord.size() -1);   
			
            if (tempWord.length() > 0)
            {
                //Once word is formatted,call insert with the word, the line of the input
                //file it came from, the root of our tree, and the distinct word counter
                //TODO

                //cout << "inserting: " << tempWord << endl;
                //if(findhelp(root,tempWord).size()==0)
                root = inserthelp(root, tempWord,line, distWords);
                //Increment our total number of words inserted
                numWords++;
                //Clear out tempWord so we can use it again
                tempWord.clear();
		    }
			
		}
		line++;
	}

	//Do time and height calculation
	finishTime = clock();
	totalTime = (double) (finishTime - startTime)/CLOCKS_PER_SEC;
	treeHeight = findHeight(root);

	//Print output
	cout << setw(40) << std::left;
	cout << "Total number of words: " << numWords<< endl;

	cout << setw(40) << std::left 
	<< "Total number of distinct words: " << distWords << endl;

	cout << setw(40) << std::left 
	<<"Total time spent building index: " << totalTime << endl;

	cout << setw(40) << std::left
	<<"Height of TT is : " << treeHeight << endl;
}


int TT::findHeight(TTNode* root){
    TTNode* temp = root;
    int h = 0;
    while(!temp->isLeaf()){
        h++;
        temp = temp->lchild();
    }

    return h;


}

void TT::printTree(ostream &outs){
    outs << "-----printing out TT-----\n";
    printTreeHelper(root,outs);
}


void TT::contains(){
    string input;
    cout << "Search word: ";
    cin >> input;

    vector<int> res = findhelp(this->root,input);
    if(res.size() >0){
        cout << "Line Numbers: ";
        for(int l:res)
            cout <<l << ", ";
        cout << endl;
    }
    else{
        cout << input << " is not in the document\n";

    }

     

}


// http://pages.cs.wisc.edu/~paton/readings/Old/fall01/2-3Tree.html
void TT::printTreeHelper(TTNode* root,ostream &outs){
    if(root ==nullptr)
        return;
    else if (root->isLeaf()){
        if(!root->lkey().empty()){
        outs << root->lkey() << "\t";
        for (int l :root->lval())
            outs << l << "   ";
        outs << endl;
        }
        if(!root->rkey().empty()){
        outs << root->rkey() << "\t";
        for (int l :root->rval())
            outs << l << "   ";
        outs << endl;
        }
    }
    else if (root->rchild() == nullptr){ // 2 node
        printTreeHelper(root->lchild(),outs);
        //outs  << root->lkey() << "\t" << root->rkey() << endl;
        if(!root->lkey().empty()){
        outs << root->lkey() << "\t";
        for (int l :root->lval())
            outs << l << "   ";
        outs << endl;
        }

        if(!root->rkey().empty()){
        outs << root->rkey() << "\t";
        for (int l :root->rval())
            outs << l << "   ";
        outs << endl;
        }
        printTreeHelper(root->cchild(),outs);
    }
    else{// 3 node
        printTreeHelper(root->lchild(),outs);
        //outs  << root->lkey() << endl;
        if(!root->lkey().empty()){
        outs << root->lkey() << "\t";
        for (int l :root->lval())
            outs << l << "   ";
        outs << endl;
        }
        printTreeHelper(root->cchild(),outs);
        //outs  << root->rkey() << endl;
        if(!root->rkey().empty()){
        outs << root->rkey() << "\t";
        for (int l :root->rval())
            outs << l << "   ";
        outs << endl;
        }
        printTreeHelper(root->rchild(),outs);
    }

}



