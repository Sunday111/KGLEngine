#include <limits>
#include <KGL_Base/Geom/BoundingBox.h>

namespace KGL { namespace Geom {

const BoundingBox3f BoundingBox3f::kInvalid(
    Vector3f(
        std::numeric_limits<float>::max(),
        std::numeric_limits<float>::max(),
        std::numeric_limits<float>::max()),
    Vector3f(
        std::numeric_limits<float>::lowest(),
        std::numeric_limits<float>::lowest(),
        std::numeric_limits<float>::lowest()),
    true);

} }