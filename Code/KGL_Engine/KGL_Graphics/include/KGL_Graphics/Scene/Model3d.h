#ifndef KGL_GRAPHICS_MODEL_3D_H_INCLUDED
#define KGL_GRAPHICS_MODEL_3D_H_INCLUDED

#include <KGL_Base/Geom/IndexBlob.h>
#include <KGL_Base/Geom/VertexBlob.h>
#include <KGL_Graphics/Common.h>
#include <memory>

namespace KGL { namespace Graphics {

class Model3dImpl;

class Model3d
{
public:
    explicit Model3d(
        const std::shared_ptr<Geom::IndexBlob>& indexBlob,
        const std::shared_ptr<Geom::VertexBlob>& vertexBlob);
    Model3d(const Model3d&) = delete;
    Model3d(Model3d&& uref);
    ~Model3d();

    Model3dImpl* GetImpl();

    const std::shared_ptr<Geom::IndexBlob>& GetIndexBlob() const;
    const std::shared_ptr<Geom::VertexBlob>& GetVertexBlob() const;

    Model3d& operator=(const Model3d&) = delete;
    Model3d& operator=(Model3d&& uref);
private:
    Model3dImpl* m_d;
};

} }

#endif