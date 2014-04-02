#include "BitOutputStream.hpp"

void BitOutputStream::flush()
{
  out.put(buffer); // Print out what is currently in buffer
  out.flush();    //Clear and reset values
  buffer=numbits=0;
}

void BitOutputStream::bitwrite(int i)
{
  if(numbits == 8) //if we reach 8 we need to flush
  {
    flush();
  }

  buffer = buffer | (i<<(7-numbits)); //Change buffer with current writebit

  numbits++;
}
