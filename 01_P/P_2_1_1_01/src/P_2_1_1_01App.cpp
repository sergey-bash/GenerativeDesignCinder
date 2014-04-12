#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

/**
 * changing strokeweight and strokecaps on diagonals in a grid
 *
 * MOUSE
 * position x          : left diagonal strokeweight
 * position y          : right diagonal strokeweight
 * left click          : new random layout
 *
 * KEYS
 * 1                   : round strokecap
 * 2                   : square strokecap
 * 3                   : project strokecap
 */

// (sergey) I had to employ some heavy trickery here to compensate
// for Cinder not having stroke cap setting, limited lineWidth setting,
// and not being able to draw rotated rectangle

class P_2_1_1_01App : public AppNative {
  public:
	void setup();
	void mouseUp( MouseEvent event );
    void mouseMove( MouseEvent event );
    void keyUp( KeyEvent event );
	void update();
	void draw();
private:
    enum StrokeCap {ROUND, SQUARE, PROJECT};
    int mTileCount = 20;
    unsigned long mRandomSeed = 1;
    StrokeCap mStrokeCap = ROUND;
    Rand mRand;
    Vec2i mMousePos;
};

void P_2_1_1_01App::setup()
{
    setWindowSize(600, 600);
}

void P_2_1_1_01App::update()
{
}

void P_2_1_1_01App::draw()
{
	gl::clear( Color( 1, 1, 1 ) );
    
    mRand.seed(mRandomSeed);
    gl::color(0, 0, 0);
    
    for (int gridY = 0; gridY < mTileCount; gridY++)
    {
        for (int gridX = 0; gridX < mTileCount; gridX++)
        {
            int cellWidth = getWindowWidth() / mTileCount;
            int cellHeight = getWindowHeight() / mTileCount;
            int posX = cellWidth * gridX;
            int posY = cellHeight * gridY;
            float lineLenght = sqrt(cellWidth * cellWidth + cellHeight * cellHeight);
            
            int toggle = mRand.nextInt(2);
            
            float delta = float(toggle == 0 ? mMousePos.x : mMousePos.y) / 20.0f / 2.0f;
            gl::pushMatrices();
            gl::translate(posX , posY );
            gl::rotate(Vec3f(0.0f, 0.0f, toggle == 0 ? 45.0f : -45.0f));
            
            if (mStrokeCap == ROUND)
            {
                gl::drawSolidRoundedRect(Rectf(-delta, -delta, lineLenght + delta, delta), delta);
            }
            else if (mStrokeCap == SQUARE)
            {
                gl::drawSolidRect(Rectf(0, -delta, lineLenght, delta));
            }
            else // PROJECT
            {
                gl::drawSolidRect(Rectf(-delta, -delta, lineLenght + delta, delta));
            }
            gl::popMatrices();
            

        }
    }
}

void P_2_1_1_01App::mouseUp( MouseEvent event )
{
    mRandomSeed = mRand.nextUint();
}

void P_2_1_1_01App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

void P_2_1_1_01App::keyUp( KeyEvent event )
{
    switch (event.getChar()) {
        case '1':
        mStrokeCap = ROUND;
        break;
        case '2':
        mStrokeCap = SQUARE;
        break;
        case '3':
        mStrokeCap = PROJECT;
        break;
        default:
        break;
    }
}

CINDER_APP_NATIVE( P_2_1_1_01App, RendererGl )
