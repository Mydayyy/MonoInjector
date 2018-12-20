# MonoInjector

This tool allows you to inject your own mono dlls into foreign processes and invokes a given method

## Compile

- Modify all constants at the top of main.cpp according to your needs. You can find a short explanation below with examples below below
- compile injector with `cmake . && make`
- run `load.sh` and pass the target processes pid as the first argument and the injector.so (compiled in the last step) as the second argument


## Constants

- `*libmono`: Path to the target processes libmono.so = "/tmp/unty/spaceshooter_Data/Mono/x86_64/libmono.so";
- `*dll`: Mono.dll which you want to inject
- `*namespacee`: Namespace of the method you want to invoke
- `*klass`: Class on the method you want to invoke
- `*method`: Name of the method you want to invoke. Needs to be static

## Example

### Constants

```
const char *libmono = "/tmp/unity/spaceshooter_Data/Mono/x86_64/libmono.so";
const char *dll = "/mnt/Programming/OS/Programming/Projects/C#/AlbionOnline/InjectionTests/InjectionTests/Test/bin/Debug/Test.dll";
const char *namespacee = "Test";
const char *klass = "Class1";
const char *method = "Load";
```

### Run load.sh

```
./load.sh $(pidof spaceshooter.x86_64) "$(pwd)"/libInjector.so
```