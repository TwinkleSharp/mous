#ifndef MOUS_PLUGINAGENT_H
#define MOUS_PLUGINAGENT_H

#include <string>
#include <dlfcn.h>
#include <mous/ErrorCode.h>
#include <mous/PluginHelper.h>

namespace mous {

class PluginAgent
{
    typedef const PluginInfo* (*FnPluginInfo)(void);
    typedef void* (*FnCreatePlugin)(void);
    typedef void (*FnReleasePlugin)(void*);

public:
    explicit PluginAgent(EmPluginType type):
        m_Type(type),
        m_pHandle(NULL),
        m_fnInfo(NULL),
        m_fnCreate(NULL),
        m_fnRelease(NULL)
    {

    }

    ~PluginAgent()
    {
        Close();
    }

    EmPluginType Type() const
    {
        return m_Type;
    }

    EmErrorCode Open(const std::string& path)
    {
        m_pHandle = dlopen(path.c_str(), RTLD_LAZY | RTLD_GLOBAL);
        if (m_pHandle == NULL)
            return ErrorCode::MgrBadFormat;

        m_fnInfo = (FnPluginInfo)dlsym(m_pHandle, StrPluginInfo);
        if (m_fnInfo == NULL)
            return ErrorCode::MgrBadFormat;

        m_fnCreate = (FnCreatePlugin)dlsym(m_pHandle, StrCreatePlugin);
        if (m_fnCreate == NULL)
            return ErrorCode::MgrBadFormat;

        m_fnRelease = (FnReleasePlugin)dlsym(m_pHandle, StrReleasePlugin);
        if (m_fnCreate == NULL)
            return ErrorCode::MgrBadFormat;

        return ErrorCode::Ok;
    }

    void Close()
    {
        m_fnInfo = NULL;
        m_fnCreate = NULL;
        m_fnRelease = NULL;

        if (m_pHandle != NULL) {
            dlclose(m_pHandle);
            m_pHandle = NULL;
        }
    }

    const PluginInfo* Info() const
    {
        return (m_fnInfo != NULL) ? m_fnInfo() : NULL;
    }

    void* CreateObject() const
    {
        return m_fnCreate();
    }

    void ReleaseObject(void* inf) const
    {
        m_fnRelease(inf);
    }

private:
    const EmPluginType m_Type;

    void* m_pHandle;

    FnPluginInfo m_fnInfo;
    FnCreatePlugin m_fnCreate;
    FnReleasePlugin m_fnRelease;
};

}
#endif
