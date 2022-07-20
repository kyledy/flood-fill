/*
*  File: negativeColorPicker.cpp
*  Implements the negative color picker for CPSC 221 PA2.
*
*/

#include <iostream>
#include "negativeColorPicker.h"

NegativeColorPicker::NegativeColorPicker(PNG& inputimg)
{
  // complete your implementation below 
  img = inputimg;
}

HSLAPixel NegativeColorPicker::operator()(PixelPoint p)
{
  HSLAPixel *px = img.getPixel(p.x, p.y);
  double negatedHue = getNegatedHue(px->h);
  double negatedLuminance = 1 - px->l;

  px->h = negatedHue; 
  px->l = negatedLuminance;
  return *px;
}

// helper function for negative color picker
double NegativeColorPicker::getNegatedHue(int hue) 
{
  return (hue + 180) % 360;
}

