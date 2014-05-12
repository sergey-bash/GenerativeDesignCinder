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
 * arrow left/right    : number of tiles horizontally
 * arrow up/down       : number of tiles vertically
 */

class P_2_1_3_03App : public AppNative {
public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
    void keyUp( KeyEvent event );
	void update();
	void draw();
private:
    Vec2i mMousePos;
    float mTileCountX = 6;
    float mTileCountY = 6;
    
    int mCount = 0;
    
    int mDrawMode = 1;
};

void P_2_1_3_03App::setup()
{
    setWindowSize(600, 600);
}

void P_2_1_3_03App::update()
{
}

void P_2_1_3_03App::draw()
{
	gl::clear( Color(1, 1, 1) );
    gl::color(0, 0, 0);
    
    mCount = mMousePos.x / 20 + 5;
    float para = float(mMousePos.y) / float(getWindowHeight()) - 0.5;
    
    for (int gridY = 0; gridY < mTileCountY; gridY++)
    {
        for (int gridX = 0; gridX < mTileCountX; gridX++)
        {
            float tileWidth = getWindowWidth() / mTileCountX;
            float tileHeight = getWindowHeight() / mTileCountY;
            Vec2f pos = Vec2f(gridX * tileWidth, gridY * tileHeight);
            
            gl::pushMatrices();
            gl::translate(pos);
            if (mDrawMode == 1)
            {
                //gl::translate(-tileWidth / 2.0f, -tileHeight / 2.0f);
                for (int i = 0; i <= mCount; i++)
                {
                    gl::drawLine(Vec2f(0, (para + 0.5f) * tileHeight), Vec2f(tileWidth, i * tileHeight / mCount));
                    gl::drawLine(Vec2f(0, i*tileHeight / mCount), Vec2f(tileWidth, tileHeight - (para + 0.5) * tileHeight));
                }
            }
            else if (mDrawMode == 2)
            {
                
            }
            else if (mDrawMode == 3)
            {
                
            }
            
            gl::popMatrices();
        }
    }
}

void P_2_1_3_03App::mouseDown( MouseEvent event )
{
}

void P_2_1_3_03App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

void P_2_1_3_03App::keyUp( KeyEvent event )
{
    if (event.getChar() == '1') mDrawMode = 1;
    if (event.getChar() == '2') mDrawMode = 2;
    if (event.getChar() == '3') mDrawMode = 3;
    
}

CINDER_APP_NATIVE( P_2_1_3_03App, RendererGl )
