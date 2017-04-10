#include <cassert>
#include <KGL_Base/Marco.h>
#include <KGL_Graphics/Scene/Model3d.h>

namespace KGL { namespace Graphics {

using namespace Geom;

class Model3dImpl
{
public:

    explicit Model3dImpl(
        const std::shared_ptr<IndexBlob>& indexBlob,
        const std::shared_ptr<VertexBlob>& vertexBlob) :
        m_indexBlob(indexBlob),
        m_vertexBlob(vertexBlob)
    {}

    const std::shared_ptr<Geom::IndexBlob>& GetIndexBlob() const
    {
        return m_indexBlob;
    }

    const std::shared_ptr<Geom::VertexBlob>& GetVertexBlob() const
    {
        return m_vertexBlob;
    }

private:
    std::shared_ptr<IndexBlob> m_indexBlob;
    std::shared_ptr<VertexBlob> m_vertexBlob;
};

Model3d::Model3d(
    const std::shared_ptr<IndexBlob>& indexBlob,
    const std::shared_ptr<VertexBlob>& vertexBlob) :
    m_d(new Model3dImpl(indexBlob, vertexBlob))
{}

Model3d::Model3d(Model3d&& uref) :
    m_d(uref.m_d)
{
    uref.m_d = nullptr;
}

Model3d::~Model3d()
{
    SafeDelete(m_d);
}

Model3dImpl* Model3d::GetImpl()
{
    assert(m_d != nullptr);
    return m_d;
}
const std::shared_ptr<IndexBlob>& Model3d::GetIndexBlob() const
{
    assert(m_d != nullptr);
    return m_d->GetIndexBlob();
}

const std::shared_ptr<VertexBlob>& Model3d::GetVertexBlob() const
{
    assert(m_d != nullptr);
    return m_d->GetVertexBlob();
}

Model3d& Model3d::operator=(Model3d&& uref)
{
    SafeDelete(m_d);
    m_d = uref.m_d;
    uref.m_d = nullptr;
    return *this;
}

} }