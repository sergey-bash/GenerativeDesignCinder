#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class P_1_2_1_01App : public AppNative {
public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
    void keyUp( KeyEvent event );
	void update();
	void draw();
    
private:
    Rand mRand;
    Vec2i mMousePos;
    vector<Colorf> mColorsLeft;
    vector<Colorf> mColorsRight;
    bool mInterpolateShortest;
    int mTileCountX, mTileCountY; // 2-100, 2-10
    const int MAX_TILES_Y = 10;
    
    void generateColors();
};

void P_1_2_1_01App::setup()
{
    mInterpolateShortest = true;
    mTileCountX = 2;
    mTileCountY = 10;
    generateColors();
}

void P_1_2_1_01App::update()
{
    mTileCountX = int(lmap(float(mMousePos.x), 0.0f, float(getWindowWidth()), 2.0f, 100.0f));
    mTileCountY = int(lmap(float(mMousePos.y), 0.0f, float(getWindowHeight()), 2.0f, 10.0f));
}

void P_1_2_1_01App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    float tileWidth = float(getWindowWidth()) / float(mTileCountX);
    float tileHeight = float(getWindowHeight()) / float(mTileCountY);
    for (int col = 0; col < mTileCountY; col++ )
    {
        Colorf leftColor = mColorsLeft[col];
        Colorf rightColor = mColorsRight[col];
        ColorModel colorModel = mInterpolateShortest ? ColorModel::CM_HSV : ColorModel::CM_RGB;
        for (int row = 0; row < mTileCountX; row++)
        {
            Vec3f leftColorVector = leftColor.get(colorModel);
            Vec3f rightColorVector = rightColor.get(colorModel);
            gl::color(Colorf(colorModel, leftColorVector.lerp(float(row) / float(mTileCountX), rightColorVector)));
            gl::drawSolidRect(Rectf(row * tileWidth, col * tileHeight,
                                    (row + 1) * tileWidth, (col + 1) * tileHeight));
        }
    }
}

void P_1_2_1_01App::generateColors()
{
    mColorsLeft.clear();
    mColorsRight.clear();
    for (int i = 0; i < MAX_TILES_Y; i++) {
        mColorsLeft.push_back(Colorf(ColorModel::CM_HSV,
                                     mRand.nextFloat(0, 60.0f / 360.0f), mRand.nextFloat(), 1.0));
        mColorsRight.push_back(Colorf(ColorModel::CM_HSV,
                                      mRand.nextFloat(160.0f / 360.0f, 190.0f / 360.0f), 1.0,  mRand.nextFloat()));
    }
}

void P_1_2_1_01App::mouseDown( MouseEvent event )
{
    generateColors();
}

void P_1_2_1_01App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

void P_1_2_1_01App::keyUp( KeyEvent event )
{
    if (event.getChar() == '1') mInterpolateShortest = !mInterpolateShortest;
}



CINDER_APP_NATIVE( P_1_2_1_01App, RendererGl )
