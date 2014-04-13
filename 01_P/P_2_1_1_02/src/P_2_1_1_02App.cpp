#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

/**
 * changing strokeweight on diagonals in a grid with colors
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
 * 4                   : color left diagonal
 * 5                   : color right diagonal
 * 6                   : transparency left diagonal
 * 7                   : transparency right diagonal
 * 0                   : default
 */

// (sergey) I had to employ some heavy trickery here to compensate
// for Cinder not having stroke cap setting, limited lineWidth setting,
// and not being able to draw rotated rectangle

class P_2_1_1_02App : public AppNative {
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
    ColorAf mColorLeft = Colorf(197.0f / 255.0f, 0.0f, 123.0f / 255.0f);
    ColorAf mColorRight = Colorf(87.0f / 255.0f, 35.0f / 255.0f, 129.0f / 255.0f);
    float mAlphaLeft = 1.0f;
    float mAlphaRight = 1.0f;
    unsigned long mRandomSeed = 1;
    StrokeCap mStrokeCap = ROUND;
    Rand mRand;
    Vec2i mMousePos;
};

void P_2_1_1_02App::setup()
{
    setWindowSize(600, 600);
    gl::enableAlphaBlending();
}

void P_2_1_1_02App::update()
{
}

void P_2_1_1_02App::draw()
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
            
            gl::color(toggle == 0 ? ColorAf(mColorLeft, mAlphaLeft) : ColorAf(mColorRight, mAlphaRight));
            float delta = float(toggle == 0 ? mMousePos.x : mMousePos.y) / 10.0f / 2.0f;
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

void P_2_1_1_02App::mouseUp( MouseEvent event )
{
    mRandomSeed = mRand.nextUint();
}

void P_2_1_1_02App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

void P_2_1_1_02App::keyUp( KeyEvent event )
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
        case '4':
        if (mColorLeft == Colorf::black())
        {
            mColorLeft = Colorf(197.0f / 255.0f, 0.0f, 123.0f / 255.0f);
        }
        else
        {
            mColorLeft = Colorf::black();
        }
        break;
        case '5':
        if (mColorRight == Colorf::black())
        {
            mColorRight = Colorf(87.0f / 255.0f, 35.0f / 255.0f, 129.0f / 255.0f);
        }
        else
        {
            mColorRight = Colorf::black();
        }
        break;
        case '6':
        mAlphaLeft = mAlphaLeft == 1.0f ? 0.5f : 1.0f;
        break;
        case '7':
        mAlphaRight = mAlphaRight == 1.0f ? 0.5f : 1.0f;;
        break;
        default:
        break;
    }
}

CINDER_APP_NATIVE( P_2_1_1_02App, RendererGl )
