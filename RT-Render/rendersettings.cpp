#include "rendersettings.h"

int& RenderSettings::getHeight()
{
    return height;
}

void RenderSettings::setHeight(int value)
{
    height = value;
}

bool& RenderSettings::getIsIdealThreadsCount()
{
    return idealThreadsCount;
}

void RenderSettings::setIsIdealThreadsCount(bool value)
{
    idealThreadsCount = value;
}

int& RenderSettings::getThreadsCount()
{
    return threadsCount;
}

void RenderSettings::setThreadsCount(int value)
{
    threadsCount = value;
}

int& RenderSettings::getSamplesPerPixel()
{
    return samplesPerPixel;
}

void RenderSettings::setSamplesPerPixel(int value)
{
    samplesPerPixel = value;
}

int& RenderSettings::getMaxReflections()
{
    return maxReflections;
}

void RenderSettings::setMaxReflections(int value)
{
    maxReflections = value;
}

Scene *&RenderSettings::getScene()
{
    return scene;
}

void RenderSettings::setScene(Scene *value)
{
    scene = value;
}

Camera *&RenderSettings::getCamera()
{
    return camera;
}

void RenderSettings::setCamera(Camera *value)
{
    camera = value;
}

int& RenderSettings::getWidth()
{
    return width;
}

void RenderSettings::setWidth(int value)
{
    width = value;
}
