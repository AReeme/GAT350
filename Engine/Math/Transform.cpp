#include "Transform.h"

bool neu::Transform::Write(const rapidjson::Value& value) const
{
    return true;
}

bool neu::Transform::Read(const rapidjson::Value& value)
{
    READ_DATA(value, position);
    READ_DATA(value, scale);

    glm::vec3 euler;
    READ_NAME_DATA(value, "rotation", euler);
    rotation = math::EulerToQuaternion(euler);

    return true;
}
