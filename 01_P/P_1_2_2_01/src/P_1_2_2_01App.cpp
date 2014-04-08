#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include <algorithm>

using namespace ci;
using namespace ci::app;
using namespace std;

class P_1_2_2_01App : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
    void keyUp( KeyEvent event);
	void update();
	void draw();
    
private:
    enum SortOrder {NONE, HUE, SATURATION, BRIGHTNESS, LUMINANCE};
    Vec2i mMousePos;
    SortOrder mSortOrder;
    Surface32f mImage;
    vector<Color> mColors;
    int mTileCount;
    float mTileSize;
    
    static bool sortByHue(Color a, Color b);
    static bool sortBySaturation(Color a, Color b);
    static bool sortByBrightness(Color a, Color b);
    static bool sortByLuminance(Color a, Color b);
};

void P_1_2_2_01App::setup()
{
    setWindowSize(600, 600);
    mImage = Surface32f(loadImage(loadAsset("pic1.jpg")));
    mSortOrder = NONE;
}

void P_1_2_2_01App::update()
{
    mTileCount = getWindowWidth() / max(mMousePos.x, 5);
    mTileSize = getWindowWidth() / float(mTileCount);
    
    mColors.clear();
    
    for (int col = 0; col < mTileCount; col++)
    {
        for (int row = 0; row < mTileCount; row++)
        {
            mColors.push_back(mImage.getPixel(Vec2i(row * mTileSize, col * mTileSize)));
        }
    }
    
    switch (mSortOrder) {
        case HUE:
        std::sort(mColors.begin(), mColors.end(), sortByHue);
        break;
        case SATURATION:
        std::sort(mColors.begin(), mColors.end(), sortBySaturation);
        break;
        case BRIGHTNESS:
        std::sort(mColors.begin(), mColors.end(), sortByBrightness);
        break;
        case LUMINANCE:
        std::sort(mColors.begin(), mColors.end(), sortByLuminance);
        break;
        
        default:
        break;
    }
}

bool P_1_2_2_01App::sortByHue(Color a, Color b)
{
    return a.get(ColorModel::CM_HSV)[0] > b.get(ColorModel::CM_HSV)[0];
}
bool P_1_2_2_01App::sortBySaturation(Color a, Color b)
{
    return a.get(ColorModel::CM_HSV)[1] > b.get(ColorModel::CM_HSV)[1];
}
bool P_1_2_2_01App::sortByBrightness(Color a, Color b)
{
    return a.get(ColorModel::CM_HSV)[2] > b.get(ColorModel::CM_HSV)[2];
}
bool P_1_2_2_01App::sortByLuminance(Color a, Color b)
{
    Vec3f aVec = a.get(ColorModel::CM_RGB);
    Vec3f bVec = b.get(ColorModel::CM_RGB);
    // see http://en.wikipedia.org/wiki/Luminance_(relative)
    float aLuminance = 0.2126 * aVec[0] + 0.7152 * aVec[1] + 0.0722 * aVec[2];
    float bLuminance = 0.2126 * bVec[0] + 0.7152 * bVec[1] + 0.0722 * bVec[2];
    
    return aLuminance > bLuminance;
}

void P_1_2_2_01App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    for (int col = 0; col < mTileCount; col++)
    {
        for (int row = 0; row < mTileCount; row++)
        {
            gl::color(mColors[col * mTileCount + row]);
            gl::drawSolidRect(Rectf(row * mTileSize, col * mTileSize,
                                    (row + 1) * mTileSize, (col + 1) * mTileSize));
        }
    }
}

void P_1_2_2_01App::mouseDown( MouseEvent event )
{
}

void P_1_2_2_01App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

void P_1_2_2_01App::keyUp( KeyEvent event )
{
    switch (event.getChar()) {
        case '1':
        mImage = Surface32f(loadImage(loadAsset("pic1.jpg")));
        break;
        
        case '2':
        mImage = Surface32f(loadImage(loadAsset("pic2.jpg")));
        break;
        
        case '3':
        mImage = Surface32f(loadImage(loadAsset("pic3.jpg")));
        break;
        
        case '4':
        mSortOrder = NONE;
        break;
        
        case '5':
        mSortOrder = HUE;
        break;
        
        case '6':
        mSortOrder = SATURATION;
        break;
        
        case '7':
        mSortOrder = BRIGHTNESS;
        break;
        
        case '8':
        mSortOrder = LUMINANCE;
        break;
        
        default:
        break;
    }
}

CINDER_APP_NATIVE( P_1_2_2_01App, RendererGl )
