#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;


/**
 * draw a module made of lines in a grid
 *
 * MOUSE
 * position x          : number of tiles horizontally
 * position y          : number of tiles vertically
 *
 * KEYS
 * 1-3                 : draw mode
 */

class P_2_1_3_02App : public AppNative {
public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
    void keyUp( KeyEvent event );
	void update();
	void draw();
private:
    Vec2i mMousePos;
    float mTileCountX = 5;
    float mTileCountY = 5;
    
    int mCount = 10;
    float mColorStep = 20.0f / 360.0f;
    
    float mLineWeight = 0;
    float mStrokeColor = 0;
    
    Color mBackgroundColor = Color::white();
    
    int mDrawMode = 1;
};

void P_2_1_3_02App::setup()
{
    setWindowSize(600, 600);
}

void P_2_1_3_02App::update()
{
}

void P_2_1_3_02App::draw()
{
	gl::clear( mBackgroundColor );
    
    mTileCountX = mMousePos.x / 30 + 1.0f;
    mTileCountY = mMousePos.y / 30 + 1.0f;
    
    for (int gridY = 0; gridY < mTileCountY; gridY++)
    {
        for (int gridX = 0; gridX < mTileCountX; gridX++)
        {
            float tileWidth = getWindowWidth() / mTileCountX;
            float tileHeight = getWindowHeight() / mTileCountY;
            Vec2f pos = Vec2f(gridX * tileWidth, gridY * tileHeight);
            
            Vec2f v1 = Vec2f(tileWidth / 2.0f, tileHeight / 2.0f);
            Vec2f v2 = Vec2f::zero();
            
            gl::pushMatrices();
            gl::translate(pos);
            for (int side = 0; side < 4; side++) {
                for (int i = 0; i < mCount; i++) {
                    if (side == 0) {
                        v2 = Vec2f(v2.x + tileWidth / mCount, 0);
                    }
                    if (side == 1) {
                        v2 = Vec2f(tileWidth, v2.y + tileHeight / mCount);
                    }
                    if (side == 2) {
                        v2 = Vec2f(v2.x - tileWidth / mCount, tileHeight);
                    }
                    if (side == 3) {
                        v2 = Vec2f(0, v2.y - tileHeight / mCount);
                    }
                    
                    if (i < mCount / 2.0f)
                    {
                        mLineWeight += 1.0f;
                        mStrokeColor += 60.0f / 360.0f;
                    }
                    else
                    {
                        mLineWeight -= 1.0f;
                        mStrokeColor -= 60.0f / 360.0f;
                    }
                    
                    if (mDrawMode == 1)
                    {
                        mBackgroundColor = Color::white();
                        gl::color(Color::black());
                    }
                    else if (mDrawMode == 2)
                    {
                        mBackgroundColor = Color::white();
                        gl::color(Color::black());
                        gl::lineWidth(mLineWeight);
                    }
                    else
                    {
                        mBackgroundColor = Color::black();
                        gl::color(Color::gray(mStrokeColor));
                        gl::lineWidth(mMousePos.x / 100.0f);
                    }
                    
                    
                    gl::drawLine(v1, v2);
                }
            }
            gl::popMatrices();
        }
    }
}

void P_2_1_3_02App::mouseDown( MouseEvent event )
{
}

void P_2_1_3_02App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

void P_2_1_3_02App::keyUp( KeyEvent event )
{
    if (event.getChar() == '1') mDrawMode = 1;
    if (event.getChar() == '2') mDrawMode = 2;
    if (event.getChar() == '3') mDrawMode = 3;
    
}

CINDER_APP_NATIVE( P_2_1_3_02App, RendererGl )
