#include "object.h"


Object::Object(const Material material) : material(material)
{

}

Material Object::getMaterial() const
{
    return material;
}

void Object::setMaterial(const Material &value)
{
    material = value;
}
