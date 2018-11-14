//Description: Takes a text file supplied by the user
//             and turns it into a word index, implemented
//             through the use of a BST 

#include <iostream>
#include <fstream>
#include "bst.h"
#include "tt.h"
using namespace std;

int main(int argc, char* argv[]) {
	int choice;
	if (argc != 2) {
	    cout << "Incorrect input. Correct format: ./<exectuable.out> <inputtext.txt>\n";
	    return 1;
	}

	ifstream input(argv[1]);
	BST myBST;
	TT myTT;

	cout <<"Options: (a) BST, (b) 2-3 Tree, (c) Compare BST and 2-3 Tree\n";
    string opt;
    cin >> opt;

    bool use_bst = 0;
    if(opt == "a")
        use_bst=1;
    else if (opt == "b")
        use_bst=0;
    else if (opt == "c"){
            cout << " building BST...\n";
            myBST.buildTree(input);
			input.clear();
			input.seekg(0, ios::beg);
            cout << "building TT...\n";
            myTT.buildTree(input);

			// compare the time taken to search all words in index
			double totalTime, finishTime, startTime = clock();
			for(string w :myTT.words()){
				if(!myBST.search(w))
					cout << "ERROR\n";
			} 
			finishTime = clock() - startTime;
			cout << "Total time taken by BST: " << finishTime << endl;;
			totalTime, finishTime, startTime = clock();
			for(string w :myTT.words()){
				if(myTT.findhelp(myTT.getRoot(),w).size() <1)
					cout << "ERROR\n";
			} 
			finishTime = clock() - startTime;
			cout << "Total time taken by TT: " << finishTime << endl;;
			return 0;

    }
    else{
        cout << "error" << endl;
        return -1;
    }

	if(input.is_open()){
        if(use_bst)
            myBST.buildTree(input);
        else
            myTT.buildTree(input);
            //myTree.buildTree(input);
            //myTree.printTree(cout);

            //input.close();
            while(1){
	        choice = 0;
	        cout <<"Options: (1) display index, (2) search, (3) save index, (4) quit\n";
	        cin >> choice;

		//Print index
	        if(choice == 1){
                if(use_bst)
	                myBST.printTree(cout);
                else
                    myTT.printTree(cout);
            }
	       
		//Search index for a word
		else if(choice == 2){
            if(use_bst)
	            myBST.contains();
            else
                myTT.contains();
        }

		//Save index
	        else if(choice == 3){
		    string outputFile;
	            cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
		    cin >> outputFile;
		    ofstream output(outputFile.c_str());
            if(use_bst)
	            myBST.printTree(output);
            else
                myTT.printTree(output);
	            output.close();
		    cout << "Saved\n";
	        }

		//Quit	
	        else
		    break;
            }
        }
	else{
	    cout << "Invalid File Name. Restart Program.\n";
	    return 2;
        }
	return 0;
}
