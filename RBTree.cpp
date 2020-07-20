#include<iostream>
#include<utility>
#include<time.h>
using namespace std;
enum Color
{
   BLACK,RED
};
template <class T>
struct TreeNode
{
   T _val; 
   Color _color;
   TreeNode<T>* _left;
   TreeNode<T>* _right;
   TreeNode<T>* _parent;
   TreeNode(const T& val=T())
     :_val(val),
     _color(RED),
     _right(nullptr),
     _left(nullptr),
     _parent(nullptr)
   {}
};
template <class T>
class RBTree
{
public:
typedef TreeNode<T> Node;
RBTree()
  :_header(new Node)
{
  _header->_left=_header->_right=_header;
}
bool insert(const T& val)
{
   if(_header->_parent==nullptr)
   {
     Node* root=new Node(val);
     _header->_left=_header->_right=root;
     _header->_parent=root;
     root->_parent=_header;
     root->_color=BLACK;
     return true;
   }
   Node* cur=_header->_parent;
   Node* parent=cur->_parent;
   while(cur)
   {
     parent=cur;
     if(cur->_val==val)
     {
       return false;
     }
     else if(cur->_val<val)
     {
       cur=cur->_right;
     }
     else 
     {
       cur->_left;
     }
   }
   cur=new Node(val);
   if(val>parent->_val)
   {
     parent->_right=cur;
   }
   else 
   {
     parent->_left=cur;
   }
   cur->_parent=parent;
   while(cur!=_header->_parent&&cur->_parent->_color==RED)
   {
     Node* p=cur->_parent;
     Node* g=p->_parent;
     if(g->_left==p)
     {
       Node* u=g->_right;
       if(u&&u->_color==RED)
       {
         u->_color=p->_color=BLACK;
         g->_color=RED;
         cur=g;
       }
       else 
       {
         if(p->_right==cur)
         {
            rorateL(p) ;
            swap(p,cur);
         }
         rorateR(g);
         p->_color=BLACK;
         g->_color=RED;
         break;
       }
     }
     else 
     {
       Node* u=g->_left;
       if(u&&u->_color==RED)
       {
         u->_color=p->_color=BLACK;
         g->_color=RED;
         cur=g;
       }
       else 
       {
         if(p->_left==cur)
         {
           rorateR(p);
           swap(p,cur);
         }
         rorateL(g);
         g->_color=RED;
         p->_color=BLACK;
         break;
       }
     }
   }
   _header->_parent->_color=BLACK;
   _header->_left=MostLeft();
   _header->_right=MostRight();
}
Node* MostLeft()
{
  Node* root=_header->_parent;
  while(root&&root->_left)
  {
    root=root->_left;
  }
  return root;
}
Node* MostRight()
{
  Node* root=_header->_parent;
  while(root&&root->_right)
  {
    root=root->_right;
  }
  return root;
}
void rorateL(Node* parent)
{
  Node* SubR=parent->_right;
  Node* SubRL=SubR->_left;
  parent->_right=SubRL;
  SubR->_left=parent;
  if(SubRL)
  {
    SubRL->_parent=parent;
  }
  if(parent==_header->_parent)
  {
    _header->_parent=SubR;
    SubR->_parent=_header;
  }
  else 
  {
    Node* g=parent->_parent;
    SubR->_parent=g;
    if(g->_left==parent)
    {
         g->_left=SubR;
    }
    else if(g->_right==parent)
    {
      g->_right=SubR;
    }
  }
  parent->_parent=SubR;
}
void rorateR(Node* parent)
{
  Node* SubL=parent->_left;
  Node* SubLR=SubL->_right;
  parent->_left=SubLR;
  SubL->_right=parent;
  if(SubLR)
  {
    SubLR->_parent=parent;
  }
  if(parent->_parent==_header)
  {
     _header->_parent=SubL;
     SubL->_parent=_header;
  }
  else 
  {
    Node* g=parent->_parent;
    SubL->_parent=g;
    if(g->_left==parent)
    {
      g->_left=SubL;
    }
    else if(g->_right==parent)
    {
      g->_right=SubL;
    }
  }
  parent->_parent=SubL;
}
void inorder()
{
   _inorder(_header->_parent);
   cout<<endl;
}
void _inorder(Node* root)
{
  if(root==nullptr)
    return;
  _inorder(root->_left);
  cout<<root->_val<<" ";
  _inorder(root->_right);
}
bool isRBTree()
{
   if(_header->_parent==nullptr)
     return true;
   Node* root=_header->_parent;
   if(root->_color==RED)
     return false;
   int cnt=0;
   while(root&&root->_right)
   {
     if(root->_color==BLACK)
     {
       cnt++;
     }
     root=root->_right;
   }
   return _isRBTree(_header->_parent,cnt,0);
}
bool _isRBTree(Node* cur,int total,int curCount)
{
   if(cur==nullptr)
   {
     if(curCount==total)
     {
       return true;
     }
     else 
     {
       return false;
     }
   }
   Node* parent=cur->_parent;
   if(cur&&cur->_color==RED&&parent&&parent->_color==RED)
   {
     cout<<cur->_val<<"error"<<endl;
     return false;
   }
   if(cur->_color==BLACK)
     ++curCount;
   return _isRBTree(cur->_left,total,curCount)&&_isRBTree(cur->_right,total,curCount);
}
private:
   Node* _header; 
};
void test()
{
  RBTree<int> rbt;
  rbt.insert(1);
  rbt.insert(2);
  rbt.insert(3);
  rbt.insert(4);
  rbt.insert(5);
  rbt.insert(6);
  rbt.insert(7);
  rbt.insert(8);
  rbt.insert(9);
  rbt.insert(10);
  rbt.insert(100);
  rbt.inorder();
  bool judge=rbt.isRBTree();
  if(judge==true)
  {
    cout<<"right"<<",isRBTree"<<endl;
  }
  else 
  {
    cout<<"no,is not RBTree"<<endl;
  }
}
int main()
{
  test();
}
