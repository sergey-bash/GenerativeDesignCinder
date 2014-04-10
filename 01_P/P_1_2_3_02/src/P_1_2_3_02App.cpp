#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class P_1_2_3_02App : public AppNative {
public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
    void mouseUp( MouseEvent event );
    void keyUp( KeyEvent event );
	void update();
	void draw();
    
private:
    Rand mRand;
    const int sColorsCount = 20;
    vector<Colorf> mColors;
    Vec2i mMousePos;
    bool mIsDirty;
    
    void generateColors();
};

void P_1_2_3_02App::setup()
{
    setWindowSize(800, 800);
    mIsDirty = true;
}

void P_1_2_3_02App::generateColors()
{
    mColors.clear();
    for (int i = 0; i < sColorsCount; i++)
    {
        if (i % 2 == 0)
        {
            mColors.push_back(Colorf(ColorModel::CM_HSV,
                                     mRand.nextFloat(),
                                     1.0,
                                     mRand.nextFloat()));
        }
        else
        {
            mColors.push_back(Colorf(ColorModel::CM_HSV,
                                     195.0f / 360.0f,
                                     mRand.nextFloat(),
                                     1.0));
        }
        
    }

}

void P_1_2_3_02App::update()
{
    if (!mIsDirty) return;
    generateColors();
}

void P_1_2_3_02App::draw()
{
    if (!mIsDirty) return;
    
	gl::clear( Color( 1, 1, 1 ) );
    
    int counter = 0;
    int rowCount = mRand.nextInt(5, 40);
    float rowHeight = float(getWindowHeight()) / float(rowCount);
    
    for (int i = 0; i < rowCount; i++)
    {
        int partCount = i + 1;
        vector<float> parts;
        
        for (int ii = 0; ii < partCount; ii++)
        {
            if (mRand.nextFloat() < 0.075)
            {
                int fragments = mRand.nextInt(2, 20);
                partCount += fragments;
                for (int iii = 0; iii < fragments; iii++)
                {
                    parts.push_back(mRand.nextFloat(2.0));
                }
            }
            else
            {
                parts.push_back(mRand.nextFloat(2, 20));
            }
        }
        
        float sumPartsTotal = 0.0f;
        for (int ii = 0; ii < partCount; ii++) sumPartsTotal += parts[ii];
        
        float sumPartsNow = 0.0f;
        for (int ii = 0; ii < parts.size(); ii++) {
            int index = counter % sColorsCount;
            gl::color(mColors[index]);
            
            
            float rectLeft = lmap(sumPartsNow, 0.0f, sumPartsTotal, 0.0f, float(getWindowWidth()));
            float rectWidth = lmap(parts[ii], 0.0f, sumPartsTotal, 0.0f, float(getWindowWidth()));
            gl::drawSolidRect(Rectf(rectLeft,
                              rowHeight * i,
                              rectLeft + rectWidth,
                              rowHeight * (i + 1)));
            
            sumPartsNow += parts[ii];
            counter++;
        }
    }
    
    mIsDirty = false;
}

void P_1_2_3_02App::mouseDown( MouseEvent event )
{
}

void P_1_2_3_02App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

void P_1_2_3_02App::mouseUp( MouseEvent event )
{
    mIsDirty = true;
}

void P_1_2_3_02App::keyUp(KeyEvent event)
{

}

CINDER_APP_NATIVE( P_1_2_3_02App, RendererGl )
