#include <iostream>
#include <link.h>
#include <fstream>
#include <iostream>
#include <fstream>
#include <link.h>
using namespace std;

typedef long long __int64;

typedef void* (*t_mono_get_root_domain)();
typedef void* (*t_mono_thread_attach)(void *monoDomain);
typedef void* (*t_mono_assembly_open)(char *filename, void *status);
typedef void* (*t_mono_assembly_get_image)(void *assembly);
typedef void* (*t_mono_class_from_name)(void *monoImage, char *namespacee, char *name);
typedef void* (*t_mono_class_get_method_from_name)(void *klass, char *name, int paramCount);
typedef void* (*t_mono_runtime_invoke)(void *monoMethod, void *obj, void **params, void **exc);

t_mono_get_root_domain mono_get_root_domain;
t_mono_thread_attach mono_thread_attach;
t_mono_assembly_open mono_assembly_open;
t_mono_assembly_get_image mono_assembly_get_image;
t_mono_class_from_name mono_class_from_name;
t_mono_class_get_method_from_name mono_class_get_method_from_name;
t_mono_runtime_invoke mono_runtime_invoke;

__int64 backup = 0;

void disableAssemblyLoadCallback(void *library)
{
    void *f = (dlsym(library, "mono_assembly_invoke_load_hook"));
    int offset = *(int*)(f + 6 + 3);
    __int64 *raxRef = (__int64*) (offset + f + 7 + 6);
    __int64 *rax = *((__int64**) raxRef);
    backup = *rax;
    *rax = 0;
}

void enableAssemblyLoadCallback(void *library)
{
    void *f = (dlsym(library, "mono_assembly_invoke_load_hook"));
    int offset = *(int*)(f + 6 + 3);
    __int64 *raxRef = (__int64*) (offset + f + 7 + 6);
    __int64 *rax = *((__int64**) raxRef);
    *rax = backup;
}

int __attribute__((constructor)) load()
{
    void *library = dlopen("YOUR_GAME/Mono/x86_64/libmono.so", RTLD_NOLOAD | RTLD_NOW);

    mono_get_root_domain = (t_mono_get_root_domain) (dlsym(library, "mono_get_root_domain"));
    mono_thread_attach = (t_mono_thread_attach) (dlsym(library, "mono_thread_attach"));
    mono_assembly_open = (t_mono_assembly_open) (dlsym(library, "mono_assembly_open"));
    mono_assembly_get_image = (t_mono_assembly_get_image) (dlsym(library, "mono_assembly_get_image"));
    mono_class_from_name = (t_mono_class_from_name) (dlsym(library, "mono_class_from_name"));
    mono_class_get_method_from_name = (t_mono_class_get_method_from_name) (dlsym(library, "mono_class_get_method_from_name"));
    mono_runtime_invoke = (t_mono_runtime_invoke) (dlsym(library, "mono_runtime_invoke"));

    disableAssemblyLoadCallback(library);

    mono_thread_attach(mono_get_root_domain());
    void* assembly = mono_assembly_open((char*)"ASSEMBLY_LOCATION", NULL);
    void* monoImage = mono_assembly_get_image(assembly);
    void* monoClass = mono_class_from_name(monoImage, (char*)"YOUR_NAMESPACE", (char*)"YOUR_CLASS");
    void* monoClassMethod = mono_class_get_method_from_name(monoClass, (char*)"YOUR_METHOD", 0);
    mono_runtime_invoke(monoClassMethod, NULL, NULL, NULL);

    enableAssemblyLoadCallback(library);
}

void __attribute__((destructor)) unload()
{

};