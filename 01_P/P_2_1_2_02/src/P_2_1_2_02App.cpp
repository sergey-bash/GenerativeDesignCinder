#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;


/**
 * changing module color and positions in a grid
 *
 * MOUSE
 * position x          : offset x
 * position y          : offset y
 * left click          : random position
 *
 * KEYS
 * 1-3                 : different sets of colors
 * 0                   : default
 * arrow up/down       : background module size
 * arrow left/right    : foreground module size
 */

class P_2_1_2_02App : public AppNative {
public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
    void mouseUp( MouseEvent event );
    void keyUp( KeyEvent event );
	void update();
	void draw();
private:
    Vec2i mMousePos;
    Colorf mModuleColorBg = Colorf::black();
    Colorf mModuleColorFg = Colorf::white();
    float mModuleAlphaBg = 1.0f;
    float mModuleAlphaFg = 1.0f;
    float mModuleRadiusBg = 30.0f / 2.0f;
    float mModuleRadiusFg = 15.0f / 2.0f;
    Colorf mClearColor = Colorf::white();
    float mTileCount = 20.0f;
    unsigned long mRandomSeed = 0;
    Rand mRand;
};

void P_2_1_2_02App::setup()
{
    setWindowSize(600, 600);
    gl::enableAlphaBlending();
}

void P_2_1_2_02App::update()
{
}

void P_2_1_2_02App::draw()
{
	gl::clear( mClearColor );
    
    gl::pushMatrices();
    float gridStepX = getWindowWidth() / mTileCount;
    float gridStepY = getWindowHeight() / mTileCount;
    gl::translate(gridStepX / 2.0f, gridStepY / 2.0f);
    
    mRand.seed(mRandomSeed);
    
    for (int gridY = 0; gridY < mTileCount; gridY++)
    {
        for (int gridX = 0; gridX < mTileCount; gridX++)
        {
            float posX = gridStepX * gridX;
            float posY = gridStepY * gridY;
            
            float shiftX = mRand.nextFloat(-1, 1) * mMousePos.x / 20.0f;
            float shiftY = mRand.nextFloat(-1, 1) * mMousePos.y / 20.0f;
            
            gl::color(ColorA(mModuleColorBg, mModuleAlphaBg));
            gl::drawSolidCircle(Vec2f(posX + shiftX, posY + shiftY), mModuleRadiusBg);
        }
    }
    
    for (int gridY = 0; gridY < mTileCount; gridY++)
    {
        for (int gridX = 0; gridX < mTileCount; gridX++)
        {
            float posX = gridStepX * gridX;
            float posY = gridStepY * gridY;
            
            gl::color(ColorA(mModuleColorFg, mModuleAlphaFg));
            gl::drawSolidCircle(Vec2f(posX, posY), mModuleRadiusFg);
        }
    }
    
    gl::popMatrices();
}

void P_2_1_2_02App::mouseDown( MouseEvent event )
{
}

void P_2_1_2_02App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

void P_2_1_2_02App::mouseUp( MouseEvent event )
{
    mRandomSeed = mRand.nextUint();
}

void P_2_1_2_02App::keyUp( KeyEvent event )
{
    if (event.getChar() == '1')
    {
        mModuleColorBg = mModuleColorBg == Color::black()
        ? Colorf(ColorModel::CM_HSV, 273.0f / 360.0f, 0.73f, 0.51f) : Color::black();
    }
    if (event.getChar() == '2')
    {
        mModuleColorFg = mModuleColorFg == Color::white()
        ? Colorf(ColorModel::CM_HSV, 323.0f / 360.0f, 1.0f, 0.77f) : Color::white();
    }
    if (event.getChar() == '3') {
        if (mModuleAlphaBg == 1.0f)
        {
            mModuleAlphaBg = 0.5f;
            mModuleAlphaFg = 0.5f;
        }
        else
        {
            mModuleAlphaBg = 1.0f;
            mModuleAlphaFg = 1.0f;
        }
    }
    
    if (event.getChar() == '0')
    {
        mModuleColorBg = Color::black();
        mModuleColorFg = Color::white();
        mModuleAlphaBg = 1.0f;
        mModuleAlphaFg = 1.0f;
        mModuleRadiusBg = 30.0f / 2.0f;
        mModuleRadiusFg = 15.0f / 2.0f;
    }
    
    if (event.getCode() == KeyEvent::KEY_UP) mModuleRadiusBg += 1;
    if (event.getCode() == KeyEvent::KEY_DOWN) mModuleRadiusBg = max(mModuleRadiusBg - 1, 5.0f);
    if (event.getCode() == KeyEvent::KEY_LEFT) mModuleRadiusFg += max(mModuleRadiusFg - 1, 2.5f);
    if (event.getCode() == KeyEvent::KEY_RIGHT) mModuleRadiusFg += 1;
}

CINDER_APP_NATIVE( P_2_1_2_02App, RendererGl )
