#include "HCTree.hpp"


/* Deletes all nodes in HCTree, used in decontructor
 */

void deleteALL(HCNode* node)
{
  if(node)
  {
    deleteALL(node->c0);
    deleteALL(node->c1);
    delete node;
  }
}

HCTree::~HCTree()
{
  deleteALL(root);
  root=0;
}

void HCTree::build(const vector<unsigned int>& freqs)
{
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> mypq;
  HCNode* parent; 

  for(int i=0;i<freqs.size();i++)      
  {
    if(freqs.at(i)!=0) //initailize leaves with freqs vector
    {
      leaves[i] = new HCNode(freqs.at(i),i);
      mypq.push(leaves[i]);
    }
  }
  if(mypq.size()==1)  //corner case with only one element
  {
    HCNode* top = new HCNode(0,mypq.top()->symbol);

    mypq.push(top);
  }
  while(mypq.size()>1)  //Create HCTree by poping priority queue 
  {
    HCNode* c0 = mypq.top();
    mypq.pop();

    HCNode* c1 = mypq.top();
    mypq.pop();

    //Make parent node and then insert in to mypq
    int totalcount = (*c0).count + (*c1).count;
    
    parent = new HCNode(totalcount,(*c0).symbol,c0,c1);  
    c0->p = parent;
    c1->p = parent;
    
    mypq.push(parent);
  }

  if(mypq.size()==1)
  {
    root = mypq.top();
  }
  else
    root = parent;

}
void HCTree::encode(byte symbol, BitOutputStream& out) const
{
  HCNode* cursor = leaves[symbol];
  stack<int> code;
  while(cursor != 0 && cursor != root) // traverse until root and keep values in stack
  {
    if(cursor->p->c0 == cursor)
      code.push(0);
    else if(cursor->p->c1 == cursor)
      code.push(1);
    cursor=cursor->p;
  }

  int realsize=code.size();

  for(int i=0;i<realsize;i++) //pop stack adn write
  {
    out.bitwrite(code.top());
    code.pop();
  }
}
byte HCTree::decode(BitInputStream& in) const
{
  HCNode* cursor = root;
  int bit;

  while(cursor->c0!=0 && cursor->c1!=0)//traverse until null then return symbol
  {
    bit = in.bitread();
    if(bit == 0)
      cursor=cursor->c0;
    if(bit == 1)
      cursor=cursor->c1;
  }
  return cursor->symbol;
}


