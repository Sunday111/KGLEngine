#include "ApplicationImpl.h"
#include <KGL_Core/SystemsManager.h>

namespace KGL { namespace Core {

ApplicationImpl::ApplicationImpl() :
    m_systemsManager(std::make_unique<SystemsManager>())
{}

ApplicationImpl::~ApplicationImpl() = default;

SystemsManager* ApplicationImpl::GetSystemsManager()
{
    return m_systemsManager.get();
}

} }