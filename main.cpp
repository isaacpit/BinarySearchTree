//#include "BTree.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

#include "BTree.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

template <typename T>
Fl_Window* fltk_print (BTree<T> tree) {
    const char* title = {"Tree"};
    Fl_Window* win = new Fl_Window(800, 400, title);
    int size = 30;
    int start_x = win->w() / 2;
    int start_y = win->h() / 16;
    win->begin();

    string* s = new string(to_string('x'));
    Fl_Box* box = new Fl_Box(start_x, start_y, size, size, s->c_str());
    box->box(FL_UP_BOX);
    fltk_print_helper(box, tree.get_root(), 'x');
    win->end();
    win->show();

    return win;
}

template<typename T> 
Fl_Box* fltk_print_helper (Fl_Box* inbox, Node<T> *node, char c = 'x') {
    if (node != NULL) {
        int size = 30;
        string* s = new string(to_string(node->value));
        Fl_Box *box = NULL;
        // if (node == node->parent->left) {
        //     Fl_Box *box = new Fl_Box(inbox->x() - i * size,  
        //         inbox->y() + i * size, size, size, s->c_str());
        // }
        cout << "called on : " << node->value << endl;

        // fltk_print_helper(inbox, node->right, i + 1, 'r');
        if (c == 'l') {
            box = new Fl_Box( inbox->x() - 2.5 * size,  
                inbox->y() + 2 * size, size, size, s->c_str());
            box->box(FL_UP_BOX);        
        //     fltk_print_helper(inbox, node->left, i + 1, 'l');
        // fltk_print_helper(inbox, node->right, i + 1, 'r');
        }
        else if (c == 'r') {
            box = new Fl_Box(inbox->x() + 2.5 * size, 
                inbox->y() + 2 *  size, size, size, s->c_str());
            box->box(FL_UP_BOX);
        //             fltk_print_helper(inbox, node->left, i + 1, 'l');
        // fltk_print_helper(inbox, node->right, i + 1, 'r');
        }
        else if (c == 'x') {
            box = new Fl_Box(inbox->x(), inbox->y(), size, size, s->c_str());
            box->box(FL_UP_BOX);

        }
        fltk_print_helper(box, node->left, 'l');
        fltk_print_helper(box, node->right, 'r');



        // fltk_print_helper(inbox, node->left, i + 1, 'l');

        // int size = 30;
        // int start_x = win->w() / 2;
        // int start_y = win->h() / 16;

        // Fl_Box *box = new Fl_Box(start_x, start_y, size, size, s->c_str());
        // box->box(FL_UP_BOX);
        return box;
    }

    return NULL;
}

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



    string outFileName = file + ".tree";
    ofstream outf(outFileName);

    // cout << "print_val test: " << endl;
    // bt.print_val(bt.get_root());
    cout << "\nprint_ref test: " << endl;
    int lvl = 0;
    bt.print_ref(bt.get_root(), lvl);
    // bt.print_level_by_level(cout);

    if (bt.getSize() < pow(2,4)) {
        cout << bt << endl;
        outf << bt;
        // bt.print_level_by_level(outputFile);
    }
    else {
        // do nothing
    }
    
    fltk_print(bt);
    // const char* title = {"Tree"};
    // Fl_Window mywindow(800, 400, title);
    // int size = 30;
    // int start_x = mywindow.w() / 2;
    // int start_y = mywindow.h() / 16;

    // mywindow.begin();
    // string s = to_string(4);
    // Fl_Box box(start_x, start_y, size, size, s.c_str());
    // box.box(FL_UP_BOX);



    // mywindow.end();
    // mywindow.show();


    // cout << bt << endl;

    return Fl::run();
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