#ifndef __SQLMXDriver__
#define __SQLMXDriver__

#include <string>
#ifdef __cplusplus
extern "C" {
#endif
namespace interface{

int DriverInitialize(std::string language, int nowaitOn, std::string moduleCaching, std::string compiledModuleLocation);
void SetDefaultEncoding(std::string encoding);

}

#ifdef __cplusplus
}
#endif
#endif
