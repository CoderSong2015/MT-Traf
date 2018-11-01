#ifndef __SQLMXDriver__
#define __SQLMXDriver__

#include <string>
#ifdef __cplusplus
extern "C" {
#endif
int DriverInitialize(std::string language, int nowaitOn, std::string moduleCaching, std::string compiledModuleLocation);
#ifdef __cplusplus
}
#endif
#endif
