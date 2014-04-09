#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class P_1_2_3_01App : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
    void keyUp( KeyEvent event );
	void update();
	void draw();
    
private:
    Rand mRand;
    int mTileCountX;
    int mTileCountY;
    vector<Colorf> mColors;
    Vec2i mMousePos;
    
    void generateColors(float minHue, float maxHue, float minSat, float maxSat, float minVal, float maxVal);
};

void P_1_2_3_01App::setup()
{
    setWindowSize(800, 800);
    mTileCountX = 50;
    mTileCountY = 10;
    
    generateColors(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
}

void P_1_2_3_01App::generateColors(float minHue, float maxHue, float minSat, float maxSat, float minVal, float maxVal)
{
    mColors.clear();
    for (int i = 0; i < mTileCountX; i++)
    {
        mColors.push_back(Colorf(ColorModel::CM_HSV,
                                 mRand.nextFloat(minHue, maxHue),
                                 mRand.nextFloat(minSat, maxSat),
                                 mRand.nextFloat(minVal, maxVal)));
    }
}

void P_1_2_3_01App::update()
{
    
}

void P_1_2_3_01App::draw()
{
	gl::clear( Color( 1, 1, 1 ) );
    
    int counter = 0;
    int currentTileCountX = (int) lmap(float(mMousePos.x), 0.0f, float(getWindowWidth()),
                                       1.0f, float(mTileCountX));
    int currentTileCountY = (int) lmap(float(mMousePos.y), 0.0f, float(getWindowHeight()),
                                       1.0f, float(mTileCountY));
    currentTileCountX = max(1, min(currentTileCountX, mTileCountX));
    currentTileCountY = max(1, min(currentTileCountY, mTileCountY));
    
    console() << "currentTileCountX: " << currentTileCountX << endl;
    console() << "currentTileCountY: " << currentTileCountY << endl;
    
    float tileWidth = float(getWindowWidth()) / currentTileCountX;
    float tileHeight = float(getWindowHeight()) / currentTileCountY;
    
    for (int col = 0; col < mTileCountY; col++)
    {
        for (int row = 0; row < mTileCountX; row++)
        {
            float posX = tileWidth * row;
            float posY = tileHeight * col;
            int index = counter % currentTileCountX;
            
            gl::color(mColors[index]);
            gl::drawSolidRect(Rectf(posX, posY, posX + tileWidth, posY + tileHeight));
            
            counter++;
        }
    }
    
}

void P_1_2_3_01App::mouseDown( MouseEvent event )
{
}

void P_1_2_3_01App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

void P_1_2_3_01App::keyUp(KeyEvent event)
{
    float defaultHue = 195.0f/360.0f;
    switch (event.getChar()) {
        case '1':
        generateColors(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
        break;
        case '2':
        generateColors(0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f);
        break;
        case '3':
        generateColors(0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
        break;
        case '4':
        generateColors(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
        break;
        case '5':
        generateColors(defaultHue, defaultHue, 1.0f, 1.0f, 0.0f, 1.0f);
        break;
        case '6':
        generateColors(defaultHue, defaultHue, 0.0f, 1.0f, 1.0f, 1.0f);
        break;
        case '7':
        generateColors(0.0f, 0.5f, 0.8f, 1.0f, 0.5f, 0.9f);
        break;
        case '8':
        generateColors(0.5f, 1.0f, 0.8f, 1.0f, 0.5f, 0.9f);
        break;
        case '9':
        mColors.clear();
        for (int i = 0; i < mTileCountX; i++)
        {
            if (i % 2 == 0)
            {
                mColors.push_back(Colorf(ColorModel::CM_HSV,
                                         mRand.nextFloat(),
                                         1.0f,
                                         mRand.nextFloat()));
            }
            else
            {
                mColors.push_back(Colorf(ColorModel::CM_HSV,
                                         defaultHue,
                                         mRand.nextFloat(),
                                         1.0f));
            }
            
        }
        break;
        case '0':
        mColors.clear();
        for (int i = 0; i < mTileCountX; i++)
        {
            if (i % 2 == 0)
            {
                mColors.push_back(Colorf(ColorModel::CM_HSV,
                                         192.0f / 360.0f,
                                         mRand.nextFloat(),
                                         mRand.nextFloat(0.1f, 1.0f)));
            }
            else
            {
                mColors.push_back(Colorf(ColorModel::CM_HSV,
                                         273.0f / 360.0f,
                                         mRand.nextFloat(),
                                         mRand.nextFloat(0.1f, 0.9f)));
            }
            
        }
        break;
        
        default:
        break;
    }
}

CINDER_APP_NATIVE( P_1_2_3_01App, RendererGl )
