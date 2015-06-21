#ifndef BLOCK_H
#define BLOCK_H

#include <allegro.h>
#include <string>
#include <time.h>

#include <sstream>

#include "tools.h"

using namespace std;

class Block{

public:
  Block();
  ~Block();

  void SetImages( string image1, string image2);
  void SetImages( string image1);

  int GetY();
  int GetX();

  int GetHeight();
  int GetWidth();

  int GetType();

  bool GetSelected();
  bool GetFlaged();

  bool GetDead();

  BITMAP* GetImage();

  void draw(BITMAP* tempBitmap, float stretchWidth, float stretchHeight);
  void DrawNewSprite( BITMAP* tempBitmap, BITMAP* spriteToDraw, float stretchWidth, float stretchHeight);

  void SetX( int newValue);
  void SetY( int newValue);

  void SetWidth(int newValue);
  void SetHeight(int newValue);

  void SetType(int newType);
  void SetValue(int newValue);


  void SetSelected(bool newSelected);
  void SetFlaged(bool newFlag);

  void Change();

private:

  int x;
  int y;

  int width;
  int height;

  int frame;
  int type;
  int value;

  bool selected;

  bool flaged;

  bool animated;

  BITMAP *images[2][2];

  BITMAP *flag;
};

#endif

