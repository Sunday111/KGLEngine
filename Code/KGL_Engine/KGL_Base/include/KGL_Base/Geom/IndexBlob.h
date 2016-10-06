#ifndef KGL_BASE_INDEX_BLOB_H_INCLUDED
#define KGL_BASE_INDEX_BLOB_H_INCLUDED

#include <memory>
#include <vector>

namespace KGL { namespace Geom {

class IndexBlob
{
public:
    explicit IndexBlob(std::vector<int> indices) :
        m_indices(indices)
    {}

    const std::vector<int>& GetData() { return m_indices; }

private:
    const std::vector<int> m_indices;
};

using IndexBlobPtr = std::shared_ptr<IndexBlob>;
using IndexBlobConstPtr = std::shared_ptr<const IndexBlob>;

} }

#endif /* KGL_BASE_INDEX_BLOB_H_INCLUDED */