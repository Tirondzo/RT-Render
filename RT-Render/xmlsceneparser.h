#ifndef XMLSCENEPARSER_H
#define XMLSCENEPARSER_H

#include "scene.h"
#include "object.h"
#include "material.h"
#include "sphere.h"
#include "plane.h"
#include "camera.h"

#include "rendersettings.h"

#include <iostream>
#include <QFile>
#include <QDomDocument>
#include <QMap>

#include <locale>

class XMLSceneParser
{
public:
    XMLSceneParser();

    RenderSettings* loadScene(const QString &filePath) const{
        QFile sceneFile(filePath);

        sceneFile.open(QIODevice::ReadOnly);
        if (!sceneFile.isOpen()) {
            std::cerr << "Unable to open file at path '" << filePath.toUtf8().constData() << "'" << std::endl;
            return nullptr;
        }

        std::locale::global( std::locale( "C" ) );

        QDomDocument document;
        QString errorMessge;
        int errorLine, errorColumn;

        if (!document.setContent(&sceneFile, &errorMessge, &errorLine, &errorColumn)) {
            std::cerr << "XML parsing error at line " << errorLine << ", column " << errorColumn << ": " << errorMessge.toUtf8().constData() << std::endl;
            return nullptr;
        }

        QDomElement rootElement = document.documentElement();
        RenderSettings* settings = readScene(rootElement);

        return settings;
    }

private:
    Color parseColor(const QString &str) const{
        int r{}, g{}, b{}, a = 255;
        sscanf(str.toStdString().c_str(), "%d , %d , %d , %d", &r, &g, &b, &a);
        return Color(r,g,b,a);
    }
    Vector3D parseVector(const QString &str) const{
        double x{},y{},z{};
        sscanf(str.toStdString().c_str(), "%lf , %lf , %lf", &x, &y, &z);
        return Vector3D(x,y,z);
    }

    RenderSettings* readScene(const QDomElement &rootElement) const{
        if (rootElement.toElement().tagName() != "scene") {
            std::cerr << "Scene parsing error: invalid root tag name, 'scene' expected" << std::endl;
            return nullptr;
        }
        Scene* scene = new Scene();
        Camera *camera;
        RenderSettings *settings;
        QMap<QString, Material*> materials;

        bool isCameraIntialized = false;
        bool isSettingsInitialized = false;

        if(rootElement.hasAttribute("ambient")){
            scene->setAmbient(parseColor(rootElement.attribute("ambient")));
        }
        if(rootElement.hasAttribute("gamma")){
            scene->setGamma(rootElement.attribute("gamma").toFloat());
        }

        QDomElement element = rootElement.firstChildElement();
        while (!element.isNull()) {
            QString elementTagName = element.tagName();

            if (elementTagName == "camera") {
                if (isCameraIntialized) {
                    std::cerr << "Scene parsing error: 'camera' tag occurred twice, only one camera is allowed" << std::endl;
                    return nullptr;
                }
                camera = readCamera(element);
                if (camera == nullptr) {
                    std::cerr << "Scene parsing error: failed camera parameters reading" << std::endl;
                    return nullptr;
                }

                isCameraIntialized = true;
            }else if(elementTagName == "object"){
                Object *object = readObject(element, materials);
                if(object == nullptr){
                    std::cerr << "Scene parsing error: failed object parameters reading" << std::endl;
                    return nullptr;
                }
                scene->addObject(object);
            }else if(elementTagName == "material"){
                Material* material = readMaterial(element, materials);
                if(material == nullptr){
                    std::cerr << "Scene parsing error: failed object parameters reading" << std::endl;
                    return nullptr;
                }
            }else if(elementTagName == "settings"){
                if (isSettingsInitialized) {
                    std::cerr << "Scene parsing error: 'settings' tag occurred twice, only one settings are allowed" << std::endl;
                    return nullptr;
                }
                settings = readSettings(element);
                if(settings == nullptr){
                    std::cerr << "Scene parsing error: failed settings parameters reading" << std::endl;
                    return nullptr;
                }
                isSettingsInitialized = true;
            }
            element = element.nextSiblingElement();
        }
        if (!isCameraIntialized) {
            std::cerr << "Scene parsing error: camera parameters are not specified" << std::endl;
            return nullptr;
        }
        if (!isSettingsInitialized){
            settings = new RenderSettings();
        }

        settings->setScene(scene);
        settings->setCamera(camera);
        return settings;
    }

    RenderSettings* readSettings(const QDomElement &element) const{
        QDomElement childElement;
        RenderSettings *settings = new RenderSettings();
        if(!(childElement = element.firstChildElement("size")).isNull()){
            readAttributeAsInt(childElement, settings->getWidth(), "width");
            readAttributeAsInt(childElement, settings->getHeight(), "height");
        }
        if(!(childElement = element.firstChildElement("threads")).isNull()){
            settings->setIsIdealThreadsCount(childElement.hasAttribute("ideal"));
            readAttributeAsInt(childElement, settings->getThreadsCount(), "n");
        }
        if(!(childElement = element.firstChildElement("samples")).isNull()){
            readAttributeAsInt(childElement, settings->getSamplesPerPixel(), "n");
        }
        if(!(childElement = element.firstChildElement("reflections")).isNull()){
            readAttributeAsInt(childElement, settings->getMaxReflections(), "n");
        }
        return settings;
    }

    Camera* readCamera(const QDomElement &element) const{
        QDomElement childElement;
        Vector3D position, lookAt;
        float fov = 1.f;
        float focus = 3.8f;
        float focal = 7.5f;
        if(!(childElement = element.firstChildElement("position")).isNull()
                && readAttributeAsVector(childElement, position, "val")){
        }else return nullptr;
        if(!(childElement = element.firstChildElement("lookAt")).isNull()
                && readAttributeAsVector(childElement, lookAt, "val")){
        }else return nullptr;
        if(!(childElement = element.firstChildElement("fov")).isNull()){
            readAttributeAsFloat(childElement, fov, "val");
        }
        if(!(childElement = element.firstChildElement("focus")).isNull()){
            readAttributeAsFloat(childElement, focus, "val");
        }
        if(!(childElement = element.firstChildElement("focal")).isNull()){
            readAttributeAsFloat(childElement, focal, "val");
        }
        return new Camera(position, lookAt, fov, focus, focal);
    }

    Object* readObject(const QDomElement &element, const QMap<QString, Material*> &materials) const{
        QDomElement childElement;
        if(element.hasAttribute("type")){
            QString type = element.attribute("type");
            QString materialId;
            if(!(childElement = element.firstChildElement("material")).isNull()
                    && readAttributeAsString(childElement, materialId, "id")){
            }else return nullptr;

            Material *mat;
            if(materials.contains(materialId)){
                mat = materials[materialId];
            }else return nullptr;

            if(type == "plane"){
                Vector3D center, normal;
                int w = -1, l = -1;
                if(!(childElement = element.firstChildElement("center")).isNull()
                        && readAttributeAsVector(childElement, center, "val")){
                }else return nullptr;
                if(!(childElement = element.firstChildElement("normal")).isNull()
                        && readAttributeAsVector(childElement, normal, "val")){
                }else return nullptr;
                if(!(childElement = element.firstChildElement("size")).isNull()){
                    readAttributeAsInt(childElement, w, "width");
                    readAttributeAsInt(childElement, l, "length");
                }
                return new Plane(mat, center, normal, w, l);
            }else if(type == "sphere"){
                Vector3D center;
                float radius;
                if(!(childElement = element.firstChildElement("center")).isNull()
                        && readAttributeAsVector(childElement, center, "val")){
                }else return nullptr;
                if(!(childElement = element.firstChildElement("radius")).isNull()
                        && readAttributeAsFloat(childElement, radius, "val")){
                }else return nullptr;
                return new Sphere(mat, center, radius);
            }
        }
        return nullptr;
    }

    Material* readMaterial(const QDomElement &element, QMap<QString, Material*> &materials) const{
        QDomElement childElement;
        QString id;
        if(!readAttributeAsString(element, id, "id")){
            return nullptr;
        }
        Color color;
        float kd = 1, ks = 0, kt = 0;
        float reflectivity = .9f;
        if(!(childElement = element.firstChildElement("color")).isNull()
                && readAttributeAsColor(childElement, color, "val")){
        }else return nullptr;
        if(!(childElement = element.firstChildElement("mix")).isNull()
                && readAttributeAsFloat(childElement, kd, "kd")
                && readAttributeAsFloat(childElement, ks, "ks")
                && readAttributeAsFloat(childElement, kt, "kt")){
        };
        if(!(childElement = element.firstChildElement("reflectivity")).isNull()){
            readAttributeAsFloat(childElement, reflectivity);
        }
        Material *new_one = new Material(color, kd, ks, kt, reflectivity);
        if(element.hasAttribute(QString("light"))){
            new_one->setIsLight(true);
        }
        materials.insert(id, new_one);
        return new_one;
    }

    bool readAttributeAsFloat(const QDomElement &element, float &val, const QString &attr = "val") const{
        if(element.hasAttribute(attr)){
            val = element.attribute(attr).toFloat();
        }else return false;
        return true;
    }
    bool readAttributeAsInt(const QDomElement &element, int &val, const QString &attr = "val") const{
        if(element.hasAttribute(attr)){
            val = element.attribute(attr).toInt();
        }else return false;
        return true;
    }
    bool readAttributeAsVector(const QDomElement &element, Vector3D &val, const QString &attr = "val") const{
        if(element.hasAttribute(attr)){
            val = parseVector(element.attribute(attr));
        }else return false;
        return true;
    }
    bool readAttributeAsColor(const QDomElement &element, Color &val, const QString &attr = "val") const{
        if(element.hasAttribute(attr)){
            val = parseColor(element.attribute(attr));
        }else return false;
        return true;
    }
    bool readAttributeAsString(const QDomElement &element, QString &val, const QString &attr = "val") const{
        if(element.hasAttribute(attr)){
            val = element.attribute(attr);
        }else return false;
        return true;
    }
};

#endif // XMLSCENEPARSER_H
