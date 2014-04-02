#include "HCNode.hpp"


bool HCNode::operator<(const HCNode& other){
  if(count != other.count) 
    return count > other.count;
  
  return symbol > other.symbol;  
}

