/*
*  File:        filler.cpp
*  Description: Implementation of functions in the filler namespace.
*
*/

/*
*  Performs a flood fill using breadth first search.
*
*  PARAM:  config - FillerConfig struct to setup the fill
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
animation filler::FillBFS(FillerConfig& config) {
  // complete your implementation below
  // You should replace the following line with a
  // correct call to fill.
  
  return Fill<Queue>(config);
}

/*
*  Performs a flood fill using depth first search.
*
*  PARAM:  config - FillerConfig struct to setup the fill
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
animation filler::FillDFS(FillerConfig& config) {
  // complete your implementation below
  // You should replace the following line with a
  // correct call to fill.
  
  return Fill<Stack>(config);
}

/*
*  Run a flood fill on an image starting at the seed point
*
*  PARAM:  config - FillerConfig struct with data for flood fill of image
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
template <template <class T> class OrderingStructure> animation filler::Fill(FillerConfig& config)
{
  /*
  * You need to implement this function!
  *
  * This is the basic description of a flood-fill algorithm: Every fill
  * algorithm requires an ordering structure, which is passed to this
  * function via its template parameter. For a breadth-first-search
  * fill, that structure is a Queue, for a depth-first-search, that
  * structure is a Stack. To begin the algorithm, you simply place the
  * given point in the ordering structure, marking it processed
  * (the way you mark it is a design decision you'll make yourself).
  * We have a choice to either change the color, if appropriate, when we
  * add the point to the OS, or when we take it off. In our test cases,
  * we have assumed that you will change the color when a point is added
  * to the structure.
  * Until the structure is empty, you do the following:
  *
  * 1.     Remove a point from the ordering structure, and then...
  *
  *        1.    add its unprocessed neighbors (up/down/left/right) whose color values are
  *              within (or equal to) tolerance distance from the center,
  *              to the ordering structure, and
  *              mark them as processed.
  *        2.    if it is an appropriate frame, send the current PNG to the
  *              animation (as described below).
  *
  * 2.     When implementing your breadth-first-search and
  *        depth-first-search fills, you will need to explore neighboring
  *        pixels (up/down/left/right) in some order.
  *
  *        While the order in which you examine neighbors does not matter
  *        for a proper fill, you must use the same order as we do for
  *        your animations to come out like ours! The order you should put
  *        neighboring pixels **ONTO** the queue or stack is based on the
  *        following priority condition:
  *        ** MINIMUM COLOR DISTANCE FROM THE CURRENT PIXEL **
  *        Ties are broken first by minimum y-coordinate, then by minimum x-coordinate.
  *        The HSLAPixel.dist() function will be useful, and you should
  *        take advantage of the functionality in your PriorityNeighbours class.
  * 
  *        If you process the neighbours in a different order, your fill may
  *        still work correctly, but your animations will be different
  *        from the grading scripts!
  *
  * 3.     For every k pixels filled, **starting at the kth pixel**, you
  *        must add a frame to the animation, where k = frameFreq.
  *
  *        For example, if frameFreq is 4, then after the 4th pixel has
  *        been filled you should add a frame to the animation, then again
  *        after the 8th pixel, etc.  You must only add frames for the
  *        number of pixels that have been filled, not the number that
  *        have been checked. So if frameFreq is set to 1, a pixel should
  *        be filled every frame.
  *
  * 4.     Finally, as you leave the function, send one last frame to the
  *        animation. This frame will be the final result of the fill, and
  *        it will be the one we test against.
  *
  */

  int framecount = 0; // increment after processing one pixel; used for producing animation frames (step 3 above)
  animation anim;
  OrderingStructure<PixelPoint> os;
  // complete your implementation below
  // HINT: you will likely want to declare some kind of structure to track
  //       which pixels have already been visited

  PNG img = config.img;
  int imgW = (int)img.width();
  int imgH = (int)img.height();

  anim.addFrame(img);

  // array to check if pixel has been processed
  bool **check = new bool *[imgW];

  for (int k = 0; k < imgW; k++) {
    check[k] = new bool[imgH];
  }

  for(int i = 0; i < imgW; i++) {
    for(int j = 0; j < imgH; j++) {
      check[i][j] = false;
    }
  }

  int left;
  int right;
  int up;
  int down;

  ColorPicker *cPicker = config.picker;
  PixelPoint pp = config.seedpoint;
  os.Add(pp);
  framecount++;

  *img.getPixel(pp.x,pp.y) = cPicker->operator()(pp);

  if (framecount % config.frameFreq == 0) {
    anim.addFrame(img);
  }


  while(!os.IsEmpty()) {

    //pop off next
    PixelPoint currPoint = os.Remove();
    left = currPoint.x - 1;
    right = currPoint.x + 1;
    up = currPoint.y - 1;
    down = currPoint.y + 1;

    // LEFT
    if(left < imgW && left >= 0) {
      PixelPoint newP = PixelPoint(left, currPoint.y, currPoint.color);
        
      // if pixel has not been processed and color distance is within tolerance
      HSLAPixel* impix = img.getPixel(left, currPoint.y);

      if(check[left][newP.y] == false && pp.color.dist(*impix) <= config.tolerance) {
        check[left][newP.y] = true;
        os.Add(newP);
            
        // send pixel to colorPicker
        *impix = cPicker->operator()(newP);
        framecount++;
            
        if(framecount % config.frameFreq == 0) {
          anim.addFrame(img);
        }
      }
    }
    // Down
    if(down < imgH && down >= 0) {
      PixelPoint newP = PixelPoint(currPoint.x, down, currPoint.color);
        
      // if pixel has not been processed and color distance is within tolerance
      HSLAPixel* impix = img.getPixel(currPoint.x, down);

      if(check[newP.x][down] == false && pp.color.dist(*impix) <= config.tolerance) {
        check[newP.x][down] = true;
        os.Add(newP);
            
        // send pixel to colorPicker
        *impix = cPicker->operator()(newP);
        framecount++;
            
        if(framecount % config.frameFreq == 0) {
          anim.addFrame(img);
        }
      }
    }

    // Right
    if(right < imgW && right >= 0) {
      PixelPoint newP = PixelPoint(right, currPoint.y, currPoint.color);
        
      // if pixel has not been processed and color distance is within tolerance
      HSLAPixel* impix = img.getPixel(right, currPoint.y);

      if(check[right][newP.y] == false && pp.color.dist(*impix) <= config.tolerance) {
        check[right][newP.y] = true;
        os.Add(newP);
            
        // send pixel to colorPicker
        *impix = cPicker->operator()(newP);
        framecount++;
            
        if(framecount % config.frameFreq == 0) {
          anim.addFrame(img);
        }
      }
    }

    // UP
    if(up < imgH && up >= 0) {
      PixelPoint newP = PixelPoint(currPoint.x, up, currPoint.color);
        
      // if pixel has not been processed and color distance is within tolerance
      HSLAPixel* impix = img.getPixel(currPoint.x, up);

      if(check[newP.x][up] == false && pp.color.dist(*impix) <= config.tolerance) {
        check[newP.x][up] = true;
        os.Add(newP);
            
        // send pixel to colorPicker
        *impix = cPicker->operator()(newP);
        framecount++;
            
        if(framecount % config.frameFreq == 0) {
          anim.addFrame(img);
        }
      }
    }

  }

  for(int i=0;i<imgW; i++) {
    delete check[i];
  }

  delete[] check;

  anim.addFrame(img);
  return anim;
}
