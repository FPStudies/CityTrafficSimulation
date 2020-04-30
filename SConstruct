#
#      Authors: Kordowski Mateusz, Przybysz Filip
#
#add build tests option
AddOption(
    '--build',
    dest='build_option',
    type='string',
    nargs=1,
    action='store',
    help='choosing to build <program> or <tests>',
    default='program'
    )
#wrong --build value
if (GetOption('build_option') != 'program') and (GetOption('build_option') != 'tests'):
    print('Error: Unknown --build option\n')
    Exit(1)


print('..Scons Environment Setup\n')

import sys
import subprocess
import os

#needed paths
pathToBoostHeaders = '#libraries/boost_1_72_0/'
pathToSFMLHeaders = '#libraries/SFML-2.5.1/include/'
pathToSFMLLibraries = '#libraries/SFML-2.5.1/lib/'
pathToBox2DHeaders = '#libraries/box2d-master/include/'
pathToBox2DLibrary = '#libraries/box2d-master/build/src/'

binFolder = '#bin/'
testsFolder = '#tests/bin'
pathToUtility = '#include/main/utility/'
libraryPath = binFolder + 'libs/'
programName = 'hello'
programPath = '#'



#environment variable setup
if sys.platform.startswith('linux'):

    env_base = Environment(
        CC = 'g++',
        CCFLAGS = '-O2 -Wall -g',
        SCONS_CXX_STANDARD='c++11',
        CPPPATH = [
            '#include',
            '#include/main/utility',
            pathToSFMLHeaders,
            pathToBoostHeaders,
            pathToBox2DHeaders
            ],
        LIBPATH = [
            pathToSFMLLibraries,
            pathToBox2DLibrary
            ]
    )
    env_base.PrependENVPath('PATH', os.environ['PATH'])

elif sys.platform.startswith('win'):

    env_base = Environment(
        CC = 'CL.exe',
        CCFLAGS = '-O2 -EHsc -MD',
        SCONS_CXX_STANDARD='c++11',
        CPPPATH = [
            '#include',
            '#include/main/utility',
            pathToSFMLHeaders,
            pathToBoostHeaders,
            pathToBox2DHeaders
            ],
        LIBPATH = [
            pathToSFMLLibraries,
            pathToBox2DLibrary,
            pathToBox2DLibrary + 'Release'
            ]
    )
    env_base.PrependENVPath('PATH', os.environ['PATH'])

else:
    print 'Unsupported OS. Exiting.'
    Exit(1)



if not env_base.GetOption('clean'):

    print('..Building App\n')

#check for essential libraries

    conf = Configure(env_base)

    print ('..Checking for libraries:\n')

#TODO: exit on installation error

    if sys.platform.startswith('linux'):

        if not conf.CheckCXXHeader('boost/shared_ptr.hpp'):
            print 'Boost not found\n'
            subprocess.call(['./BoostLinux.sh'], shell=True, cwd = 'scripts')
        else:
            print 'Boost found\n'

        if not conf.CheckCXXHeader('SFML/Graphics.hpp'):
            print 'SFML not found\n'
            subprocess.call(['./SFMLLinux.sh'], shell=True, cwd = 'scripts')
        else:
            print 'SFML found\n'

        if not conf.CheckLib('box2d'):
            print 'Box2D not found\n'
            subprocess.call(['./Box2DLinux.sh'], shell=True, cwd = 'scripts')
        else:
            print 'Box2D found\n'
    

    elif sys.platform.startswith('win'):
        
        if not conf.CheckCXXHeader('boost/shared_ptr.hpp'):
            print 'Boost not found\n'
            subprocess.call(['powershell.exe', '.\BoostWin.ps1'], shell=True, cwd = 'scripts')
        else:
            print 'Boost found\n'

        if not conf.CheckCXXHeader('SFML/Graphics.hpp'):
            print 'SFML not found\n'
            subprocess.call(['powershell.exe', '.\SFMLWin.ps1'], shell=True, cwd = 'scripts')
        else:
            print 'SFML found\n'
        
        if not conf.CheckLib('box2d'):
            print 'Box2D not found\n'
            subprocess.call(['powershell.exe', '.\Box2DWin.ps1'], shell=True, cwd = 'scripts')
        else:
            print 'Box2D found\n'


    else:
        print 'Unsupported OS. Exiting.'
        Exit(1)

else:
    print('..Cleaning App\n')

#Exit(1)

if not env_base.GetOption('clean'):
    print('..Building Targets\n')

#build in separate directories
SConscript(
    'source/graphic_library_facade/SConscript', 
    exports=['env_base', 'binFolder', 'pathToUtility', 'libraryPath'], 
    variant_dir = binFolder + 'graphic_library_facade', 
    duplicate=0
    )

SConscript(
    'source/main/collision/SConscript', 
    exports=['env_base', 'binFolder', 'pathToUtility', 'libraryPath'], 
    variant_dir = binFolder + 'main/collision', 
    duplicate=0
    )

SConscript(
    'source/main/program_events/SConscript', 
    exports=['env_base', 'binFolder', 'pathToUtility', 'libraryPath'], 
    variant_dir = binFolder + 'main/program_events', 
    duplicate=0
    )

 
SConscript(
    'source/main/drawing/SConscript', 
    exports=['env_base', 'binFolder', 'pathToUtility', 'libraryPath'], 
    variant_dir = binFolder + 'main/drawing', 
    duplicate=0
    )   

SConscript(
    'source/main/screen/SConscript', 
    exports=['env_base', 'binFolder', 'pathToUtility', 'libraryPath'], 
    variant_dir = binFolder + 'main/screen', 
    duplicate=0
    )


#print(Glob(['*.cpp', '../graphic_library_facade/*.o', 'program_events/*.o']))

#env.Program('hello', Glob(['*.cpp', '../graphic_library_facade/*.o', 'program_events/*.o']))
#env.Program(target = 'hello', source = ['main.cpp', 'renderLoop.cpp', '../graphic_library_facade/graphicLibraryFacade.o', 'program_events/basicEvents.o', 'program_events/eventManager.o', 'program_events/eventInterface.h'])
#['main.cpp', 'renderLoop.cpp', '../graphic_library_facade/graphicLibraryFacade.o']

#hello = env.Program(target = 'hello', source = ['source/main/main.cpp', 'source/main/renderLoop.cpp', 'build/graphic_library_facade/graphicLibraryFacade.o'])

if (GetOption('build_option') == 'program'):
    SConscript(
        'source/main/SConscript', 
        exports = ['env_base', 'libraryPath', 'programName', 'programPath', 'binFolder', 'pathToBox2DHeaders', 'sys'], 
        variant_dir= binFolder + 'main', 
        duplicate=0
        )
elif (GetOption('build_option') == 'tests'):
    SConscript(
        'tests/SConscript', 
        exports = ['env_base', 'libraryPath', 'testsFolder', 'pathToBox2DHeaders', 'sys'], 
        variant_dir= testsFolder, 
        duplicate=0
        )

#the install option
#env.Install('usr/bin/scontest', hello)
#env.Alias('install', 'usr/bin/scontest')
