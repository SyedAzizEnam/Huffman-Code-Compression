#include "BitInputStream.hpp"

void BitInputStream::fill()
{
  buffer = in.get(); //fill buffer
  numbits = 0; //reset read count
}

int BitInputStream::bitread()
{
  int bit;
  if(numbits == 8)  // if we reach 8 we need to fill again
  {
    fill();
  }

  bit = 1 & (buffer >>(7-numbits)); //get current bit

  numbits++;

  return bit;
}
