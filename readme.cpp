/** \mainpage %Numpp: C++ library for scientific computation
 *
 * \section intro_s Introduction
 * Warning: this library is still under heavy development and my be unusable
 * 
 * \section install_s Install instruction
 * These instructions work for unix-like systems only.
 *
 * \subsection build_install_s Build requirements
 * Linux distributions usually provide these dependencies as packages named cmake, gcc/clang and gsl. Depending on your distribution you may need the development version of gsl (gsl-dev)
 * + CMake version 3.0.0 or later
 * + A working c++ compiler, which supports c++17. The current CMake setup only supports gcc and clang, but changing only a few lines in the main CMakeLists.txt should be enough to add a compiler.
 * + The Gnu Scientific Library.
 *
 * \subsection make_install_s Compiling
 * You can build %Numpp with cmake: choose a directry to put the build files in.
 * Then:
 *
 *      cmake <path to source directory>
 *      make
 *
 * \subsection install_install_s Installing
 * Installing usually requires root permission, so you should run this command as root, or using sudo
 *
 *      make install
 *
 */
