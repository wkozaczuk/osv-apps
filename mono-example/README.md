This demonstrates running Mono C# apps on OSv.
Mono is a Cross platform, open source .NET framework that allows
running C# apps on Linux. For more details please
read here - https://www.mono-project.com/

To build this app you need to install Mono development
framework (mono-devel) proper for your Linux distribution
- follow https://www.mono-project.com/download/stable/#download-lin.

WARNING: Please note that at this point this app crashes on OSv due to
unimplemented pthread_getschedparam() family calls.
