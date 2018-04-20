#include "object.h"


Object::Object(Material *material) : material(material)
{

}

Material* Object::getMaterial() const
{
    return material;
}

void Object::setMaterial(Material *value)
{
    material = value;
}
