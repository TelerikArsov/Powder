# Powder
## Instalation Guide
**SFML**

First, you must download the SFML SDK.

The version used in the code is 2.5.1 Visual C++ 15 (2017) - 32-bit, which can be found [here](https://www.sfml-dev.org/download/sfml/2.5.1/).

**Configuring the project**

The first thing to do is to copy the SFML folder (located in `<sfml-install-path>`/include)  of the downloaded SDK, to the lib folder of the project.

The next step is to copy the lib folder of the SDK (Which can be found here `<sfml-install-path>`/lib) into the newly copied SFML folder.

The final result should look like this.

![INCLUDE FOLDER](http://imgs.fyi/img/8336.png)

**Adding the dll files**

Since the project uses the dynamic version of SFML, you need to copy the SFML DLLs (they are in `<sfml-install-path>`/bin) to the folder where the executables are located. In our case its the Release and Debug folders after the first build (Note, the project currently is set up to only work for x86 platforms). Keep in mind that for the Debug folder you need to copy only the DLLs that have the "-d-2" suffix, while for Release only the DLLs with the "-2".

In the end it should look like this (Release on the left, Debug on the right).

![RELEASE DLLS](http://imgs.fyi/img/833c.png) ![DEBUG DLLS](http://imgs.fyi/img/833a.png)
