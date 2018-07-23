//#include "BTree.h"
#include "BTree.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


template<typename T> 
BTree<T> read_file(string file_name, BTree<T>& bt);
// vector<int> read_file(string file_name);

int main()
{
    vector<int> nums;
    string file;
    cout << "what is name of file?\n";
    cin >> file;


    BTree<int> bt;
    bt = read_file(file, bt);
    BTree<int> bt_copy(bt);
    BTree<int> bt_copy2;
    bt_copy2 = bt;

    // cout << "binary tree original: " << endl;
    // bt.inorder(cout) << endl;

    // cout << "binary tree copy constructor: " << endl;
    // bt_copy.inorder(cout) << endl;

    // cout << "binary tree copy assignment: " << endl;
    // bt_copy2.inorder(cout) << endl;

    // int item = 1;
    // Node<int>* foundItem;
    // foundItem = bt.search(item);
    // cout << *foundItem << endl;

    float avgTime = 0;
    avgTime = bt.get_average_search_time();
    cout << "average search time: " << avgTime << endl;


    ofstream out;
    string outFileName = file + ".tree";
    out.open(outFileName);

    cout << "print_val test: " << endl;
    bt.print_val(bt.get_root());
    cout << "\nprint_ref test: " << endl;
    int lvl = 0;
    bt.print_ref(bt.get_root(), lvl);
    // bt.print_level_by_level(cout);

    if (bt.getSize() < pow(2,4)) {
        cout << bt << endl;
        out << bt;
        // bt.print_level_by_level(outputFile);
    }
    else {
        // do nothing
    }
    // cout << bt << endl;


}

template<typename T> 
BTree<T> read_file(string file_name, BTree<T>& bt) {

    bt.deleteTree(bt.root);

    // BTree<int> bt; 
    ifstream ifs;
    ifs.open(file_name);
    
    stringstream ss;
    string s;
    int i = 0; 
    ifs >> s;

    while (!ifs.eof()) {
        // cout << s << " ";
        bt.insert(stoi(s));
        // cout << "i: " << i << endl;
        // ++i;
        ifs >> s;

    }
    cout << endl;

    return bt;
}