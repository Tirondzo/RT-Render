#ifndef RENDERSETTINGS_H
#define RENDERSETTINGS_H

#include "scene.h"
#include "camera.h"

class RenderSettings
{
protected:
    int width;
    int height;
    bool idealThreadsCount;
    int threadsCount;
    int samplesPerPixel;
    int maxReflections;
    Scene *scene;
    Camera *camera;

public:
    RenderSettings(int width = 512, int height = 512,
                   bool idealThreadsCount = true,
                   int threadsCount = 4,
                   int samplesPerPixel = 512,
                   int maxReflections = 32) :
        width(width), height(height),
        idealThreadsCount(idealThreadsCount),
        threadsCount(threadsCount),
        samplesPerPixel(samplesPerPixel),
        maxReflections(maxReflections),
        scene(), camera() {}
    int& getWidth();
    void setWidth(int value);
    int& getHeight();
    void setHeight(int value);
    bool& getIsIdealThreadsCount();
    void setIsIdealThreadsCount(bool value);
    int& getThreadsCount();
    void setThreadsCount(int value);
    int& getSamplesPerPixel();
    void setSamplesPerPixel(int value);
    int& getMaxReflections();
    void setMaxReflections(int value);
    Scene *&getScene();
    void setScene(Scene *value);
    Camera *&getCamera();
    void setCamera(Camera *value);
};

#endif // RENDERSETTINGS_H
