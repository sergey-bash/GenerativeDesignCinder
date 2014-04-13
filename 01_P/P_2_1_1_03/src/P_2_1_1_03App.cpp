#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

/**
 * changing number, color and strokeweight on diagonals in a grid
 *
 * MOUSE
 * position x          : diagonal strokeweight
 * position y          : number diagonals
 * left click          : new random layout
 *
 * KEYS
 * 1                   : color left diagonal
 * 2                   : color right diagonal
 * 3                   : switch transparency left diagonal on/off
 * 4                   : switch transparency right diagonal on/off
 * 0                   : default
 */

// (sergey) I had to employ some heavy trickery here to compensate
// for Cinder not having stroke cap setting, limited lineWidth setting,
// and not being able to draw rotated rectangle

class P_2_1_1_03App : public AppNative {
public:
	void setup();
	void mouseUp( MouseEvent event );
    void mouseMove( MouseEvent event );
    void keyUp( KeyEvent event );
	void update();
	void draw();
private:
    const Colorf LEFT_COLOR_1 = Colorf(ColorModel::CM_HSV, 323.0f / 360.0f, 100.0f / 100.0f, 77.0f / 100.0f);
    const Colorf LEFT_COLOR_2 = Colorf(ColorModel::CM_HSV, 273.0f / 360.0f, 73.0f / 100.0f, 51.0f / 100.0f);
    const Colorf RIGHT_COLOR_1 = Colorf::black();
    const Colorf RIGHT_COLOR_2 = Colorf(ColorModel::CM_HSV, 192.0f / 360.0f, 100.0f / 100.0f, 64.0f / 100.0f);
    
    int mTileCount = 1;
    Colorf mColorLeft = LEFT_COLOR_1;
    Colorf mColorRight = RIGHT_COLOR_1;
    Colorf mColorBack = Colorf::white();
    bool mTransparentLeft = false;
    bool mTransparentRight = false;
    unsigned long mRandomSeed = 1;
    Rand mRand;
    Vec2i mMousePos;
    static float calculateAngleDeg(float cellWidth, float cellHeight);
};

void P_2_1_1_03App::setup()
{
    setWindowSize(600, 600);
    gl::enableAlphaBlending();
}

void P_2_1_1_03App::update()
{
}

void P_2_1_1_03App::draw()
{
	gl::clear( mColorBack );
    
    mRand.seed(mRandomSeed);
    
    mTileCount = mMousePos.y / 15.0f;
    
    float cellWidth = float(getWindowWidth()) / mTileCount;
    float cellHeight = float(getWindowHeight()) / mTileCount;
    float angleDeg = calculateAngleDeg(cellWidth, cellHeight);
    float lineLenght = sqrt(cellWidth * cellWidth / 4.0f + cellHeight * cellHeight);
    
    for (int gridY = 0; gridY < mTileCount; gridY++)
    {
        for (int gridX = 0; gridX < mTileCount; gridX++)
        {
            
            int posX = cellWidth * gridX;
            int posY = cellHeight * gridY;
            float delta = float(mMousePos.x) / 15.0f / 2.0f;
            
            int toggle = mRand.nextInt(2);
            
            gl::pushMatrices();
            if (toggle == 0) {
                gl::color(ColorAf(mColorLeft, mTransparentLeft ? gridY * 0.1f : 1.0f));
                gl::translate(posX , posY );
                gl::rotate(Vec3f(0.0f, 0.0f, angleDeg));
                gl::drawSolidRoundedRect(Rectf(-delta, -delta, lineLenght + delta, delta), delta);
                gl::popMatrices();
                gl::pushMatrices();
                gl::translate(posX + cellWidth / 2.0f, posY);
                gl::rotate(Vec3f(0.0f, 0.0f, angleDeg));
                gl::drawSolidRoundedRect(Rectf(-delta, -delta, lineLenght + delta, delta), delta);
                gl::popMatrices();
            }
            else
            {
                gl::color(ColorAf(mColorRight, mTransparentRight ? 1.0 - gridY * 0.1f : 1.0f));
                gl::translate(posX + cellWidth / 2.0f, posY );
                gl::rotate(Vec3f(0.0f, 0.0f, (180 - angleDeg)));
                gl::drawSolidRoundedRect(Rectf(-delta, -delta, lineLenght + delta, delta), delta);
                gl::popMatrices();
                gl::pushMatrices();
                gl::translate(posX + cellWidth, posY);
                gl::rotate(Vec3f(0.0f, 0.0f, (180 - angleDeg)));
                gl::drawSolidRoundedRect(Rectf(-delta, -delta, lineLenght + delta, delta), delta);
                gl::popMatrices();
            }
        }
    }
}

float P_2_1_1_03App::calculateAngleDeg(float cellWidth, float cellHeight)
{
    float cosAlpha = cellWidth / sqrt(4*cellHeight*cellHeight + cellWidth * cellWidth);
    return acos(cosAlpha) / (2.0f * M_PI) * 360.0f;
}

void P_2_1_1_03App::mouseUp( MouseEvent event )
{
    mRandomSeed = mRand.nextUint();
}

void P_2_1_1_03App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

void P_2_1_1_03App::keyUp( KeyEvent event )
{
    switch (event.getChar()) {
        case '1':
        mColorLeft = mColorLeft == LEFT_COLOR_1 ? LEFT_COLOR_2 : LEFT_COLOR_1;
        break;
        case '2':
        mColorRight = mColorRight == RIGHT_COLOR_1 ? RIGHT_COLOR_2 : RIGHT_COLOR_1;
        break;
        case '3':
        mTransparentLeft = !mTransparentLeft;
        break;
        case '4':
        mTransparentRight = !mTransparentRight;
        break;
        case '0':
        mTransparentLeft = false;
        mTransparentRight = false;
        mColorLeft = LEFT_COLOR_1;
        mColorRight = RIGHT_COLOR_1;
        break;
        default:
        break;
    }
}

CINDER_APP_NATIVE( P_2_1_1_03App, RendererGl )
