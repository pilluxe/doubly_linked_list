#include "doublyLinkedList.h"


int main()
{
    linkedList<int>* ll = new linkedList<int>(false);       //ture/false doesnt matter here because value is inside node therefore its being destoryed along with node
    linkedList<someObject*>* ll2 = new linkedList<someObject*>(true);   //true/false matter if true list is destroying value and then node, if false list is destroying only node so then we need manually destroy value
    linkedList<someObject>* ll3 = new linkedList<someObject>(false);    //true/false same as ll

    cout << "---List with objects---\n" << endl;
    someObject so(14, 'k');
    someObject so2(183, 'x');
    someObject so3(23, 'j');
    ll3->addInOrder(so);
    ll3->addInOrder(so2);
    cout << "\n---Before change---\n" << endl;
    ll3->showFromBegin();
    cout << "\n---After change---\n" << endl;
    ll3->findAndChange(so, so3);
    ll3->showFromBegin();
    ll3->findIter(0);
    cout << ll3->listToString();
    someObject* so_ptr = new someObject(5, 'a');
    someObject* so2_ptr = new someObject(10, 'b');
    someObject* so3_ptr = new someObject(50, 'd');
    someObject* so4_ptr = new someObject(100, 'f');
    someObject* so5_ptr = new someObject(1, 'x');
    cout << "\n\n---List with pointers on objects---\n" << endl;
    ll2->addInOrder(so2_ptr);
    ll2->addInOrder(so_ptr);
    cout << "\n---Before change---\n" << endl;
    ll2->showFromBegin();
    ll2->findAndChange(so_ptr, so3_ptr);
    delete so3_ptr;
    cout << "\n---After change---\n" << endl;
    ll2->showFromBegin();
    ll2->findIter(1);       //second item
    ll2->addInOrder(so5_ptr);
    ll2->addInOrder(so4_ptr);
    ll2->showFromBegin();
    ll2->findIter(5);       //out of order
    ll2->findAndRemove(so4_ptr, true);
    cout << ll2->listToString();
    cout << "\n\n---List with integers or float or something(template)---\n" << endl;
    ll->addInOrder(8);
    ll->addInOrder(2);
    ll->addInOrder(4);
    ll->showFromBegin();
    ll->findIter(0);
    ll->addInOrder(2);
    ll->addInOrder(4);
    ll->addInOrder(8);
    cout << ll->listToString() << '\n';
    ll->findAndChange(2, 500);
    ll->findAndRemove(4, false);
    cout << ll->listToString();
    cout << "\nll is being removed" << endl;
    delete ll;
    cout << "\nll2 is being removed" << endl;
    delete ll2;
    cout << "\nll3 is being removed" << endl;
    delete ll3;
    return 0;
}