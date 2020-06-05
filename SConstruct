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
pathToBoostLibraries = '#libraries/boost_1_72_0/stage/lib/'
pathToSFMLHeaders = '#libraries/SFML-2.5.1/include/'
pathToSFMLLibraries = '#libraries/SFML-2.5.1/lib/'
pathToBox2DHeaders = '#libraries/box2d-master/'
pathToBox2DLibrary = '#libraries/box2d-master/Build/bin/'

binFolder = '#bin/'
testsFolder = '#tests/bin/'
pathToUtility = '#include/main/utility/'
pathToControls = '#include/main/controls/'
libraryPath = binFolder + 'libs/'
programName = 'hello'
programPath = '#'

pathTo_drawing = '#include/main/draw/'
pathTo_trigger = "#include/main/trigger/"
pathTo_UI_button = "#include/main/UI/button/"
pathTo_controls = '#include/main/controls/'



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
            pathToBox2DLibrary + 'x86_64/Debug',
            pathToBoostLibraries
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
            pathToBox2DLibrary + 'x86_64/Release',
            pathToBoostLibraries
            ]
        #tools = [
        #    'msvc',
        #    'mslink',
        #    'mslib'
        #]
    )
    env_base.PrependENVPath('PATH', os.environ['PATH'])

else:
    print( 'Unsupported OS. Exiting.')
    Exit(1)



if not env_base.GetOption('clean'):

    print('..Building App\n')

#check for essential libraries

    conf = Configure(env_base)

    print ('..Checking for libraries:\n')

#TODO: exit on installation error

    if sys.platform.startswith('linux'):

        if not conf.CheckCXXHeader('boost/shared_ptr.hpp'):
            print( 'Boost not found\n')
            subprocess.call(['./BoostLinux.sh'], shell=True, cwd = 'scripts')
        else:
            print( 'Boost found\n')

        if not conf.CheckCXXHeader('SFML/Graphics.hpp'):
            print( 'SFML not found\n')
            subprocess.call(['./SFMLLinux.sh'], shell=True, cwd = 'scripts')
        else:
            print( 'SFML found\n')

        if not conf.CheckCXXHeader('Box2D/Box2D.h'):
            print( 'Box2D not found\n')
            subprocess.call(['./Box2DLinux.sh'], shell=True, cwd = 'scripts')
        else:
            print( 'Box2D found\n')
    

    elif sys.platform.startswith('win'):
        
        if not conf.CheckCXXHeader('boost\shared_ptr.hpp'):
            print('Boost not found\n')
            subprocess.call(['powershell.exe', '.\BoostWin.ps1'], shell=True, cwd = 'scripts')
        else:
            print( 'Boost found\n')

        if not conf.CheckCXXHeader('SFML/Graphics.hpp'):
            print( 'SFML not found\n')
            subprocess.call(['powershell.exe', '.\SFMLWin.ps1'], shell=True, cwd = 'scripts')
        else:
            print( 'SFML found\n')
        
        if not conf.CheckCXXHeader('Box2D/Box2D.h'):
            print( 'Box2D not found\n')
            subprocess.call(['powershell.exe', '.\Box2DWin.ps1'], shell=True, cwd = 'scripts')
        else:
            print( 'Box2D found\n')


    else:
        print( 'Unsupported OS. Exiting.')
        Exit(1)

else:
    print('..Cleaning App\n')

#Exit(1)

if not env_base.GetOption('clean'):
    print('..Building Targets\n')

#build in separate directories

# library facade
SConscript(
    'source/graphic_library_facade/SConscript', 
    exports=['env_base', 'binFolder', 'pathToUtility', 'libraryPath'], 
    variant_dir = binFolder + 'graphic_library_facade', 
    duplicate=0
    )

# controls
SConscript(
    '#source/main/controls/SConscript', 
    exports=['env_base', 'binFolder', 'pathToUtility', 'libraryPath'], 
    variant_dir = binFolder + 'main/controls', 
    duplicate=0
    )

# collision
SConscript(
    'source/main/collision/SConscript', 
    exports=['env_base', 'binFolder', 'pathToUtility', 'libraryPath'], 
    variant_dir = binFolder + 'main/collision', 
    duplicate=0
    )

# event
SConscript(
    'source/main/event/SConscript', 
    exports=['env_base', 'binFolder', 'pathToUtility', 'pathToControls', 'libraryPath'], 
    variant_dir = binFolder + 'main/event', 
    duplicate=0
    )

 
# draw
SConscript(
    'source/main/draw/SConscript', 
    exports=['env_base', 'binFolder', 'pathToUtility', 'libraryPath'], 
    variant_dir = binFolder + 'main/draw', 
    duplicate=0
    )   

# UI / button
SConscript(
    'source/main/UI/button/SConscript', 
    exports=['env_base', 'pathTo_drawing', 'pathTo_trigger', 'pathTo_UI_button', 'libraryPath'], 
    variant_dir = binFolder + 'main/UI/button', 
    duplicate=0
    )   

# trigger
SConscript(
    'source/main/trigger/SConscript', 
    exports=['env_base', 'pathTo_drawing', 'pathTo_trigger', 'pathTo_UI_button', 'pathTo_controls', 'libraryPath'], 
    variant_dir = binFolder + 'main/trigger', 
    duplicate=0
    )   

# UI / elements
SConscript(
    'source/main/UI/elements/SConscript', 
    exports=['env_base', 'binFolder', 'pathToUtility', 'libraryPath'], 
    variant_dir = binFolder + 'main/elements', 
    duplicate=0
    )

# graph
#SConscript(
#    'source/main/graph/SConscript', 
#    exports=['env_base', 'binFolder', 'pathToUtility', 'libraryPath'], 
#    variant_dir = binFolder + 'main/graph', 
#    duplicate=0
#    )

# screen
SConscript(
    'source/main/screen/SConscript', 
    exports=['env_base', 'binFolder', 'pathToUtility', 'libraryPath'], 
    variant_dir = binFolder + 'main/screen', 
    duplicate=0
    )

#print(Glob(['*.cpp', '../graphic_library_facade/*.o', 'event/*.o']))

#env.Program('hello', Glob(['*.cpp', '../graphic_library_facade/*.o', 'event/*.o']))
#env.Program(target = 'hello', source = ['main.cpp', 'renderLoop.cpp', '../graphic_library_facade/graphicLibraryFacade.o', 'event/basicEvents.o', 'event/eventManager.o', 'event/eventInterface.h'])
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

    #check for libboost_test installation
    if not env_base.GetOption('clean'):
        if sys.platform.startswith('linux'):

            if not conf.CheckLib('libboost_test_exec_monitor'):
                print( 'libboost not installed\n')
                subprocess.call(['./BoostInstallLinux.sh'], shell=True, cwd = 'scripts')

        else:

            if not conf.CheckLib('libboost_test_exec_monitor-vc142-mt-x64-1_72'):
                print( 'libboost not installed\n')
                subprocess.call(['powershell.exe', '.\BoostInstallWin.ps1'], shell=True, cwd = 'scripts')


    SConscript(
        '#tests/SConscript', 
        exports = ['env_base', 'libraryPath', 'binFolder', 'sys'], 
        variant_dir= testsFolder, 
        duplicate=0
        )

#the install option
#env.Install('usr/bin/scontest', hello)
#env.Alias('install', 'usr/bin/scontest')
