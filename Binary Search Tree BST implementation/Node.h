
using namespace std ;

class Node{

public:
    int value ;
    Node* right ;
    Node* left ;
    Node(int val);
    Node(int val,Node* l,Node* r);
    static Node* CreateNode(int val);
};
