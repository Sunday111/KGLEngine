#ifndef KGL_CORE_CORE_MODULE_H_INCLUDED
#define KGL_CORE_CORE_MODULE_H_INCLUDED

#include <KGL_Core/Module.h>

namespace KGL { namespace Core {

class KGL_CORE_API CoreModule : public Module
{
    DECLARE_CLASS_RTTI(CoreModule, Module)

public:
    ~CoreModule();

    /* Returns next module id and increments it */
    virtual int GetNextModuleId();
    int GetModuleId() override;

    static CoreModule* GetInstance();

protected:
    explicit CoreModule();

private:
    class Impl;
    Impl* m_d;
};

} }

#endif