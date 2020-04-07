print('..Building App')

defaultLinuxPathToBoostHeaders = '/usr/include/boost/'

pathToBoostHeaders = '#libraries/boost_1_72_0/boost/'
pathToBox2DHeaders = '#libraries/box2d-master/include/'
pathToBox2DLibrary = '#libraries/box2d-master/build/src/'

env_base = Environment(
    CC = 'g++',
    CCFLAGS = '-O2 -Wall',
    SCONS_CXX_STANDARD='c++11',
    CPPPATH = [
        '#include',
        '#include/main/utility',
        pathToBoostHeaders,
        pathToBox2DHeaders
        ]
)

binFolder = '#bin/'
pathToUtility = '#include/main/utility/'
libraryPath = binFolder + 'libs/'
programName = 'hello'
programPath = '#'


#check for essential libraries
import sys
import subprocess
conf = Configure(env_base)

#TODO: start scripts in their ow directory
print 'Checking for libraries'

if sys.platform.startswith('linux'):
    if not conf.CheckCXXHeader(defaultLinuxPathToBoostHeaders + 'shared_ptr.hpp') and not conf.CheckCXXHeader('shared_ptr.hpp'):
        print 'Boost not found'
        subprocess.call(['scripts/BoostLinux.sh'], shell=True)
    else:
        print 'Boost found'

    #if not 
elif sys.platform.startswith('win'):
    print 'Win'

else:
    print 'Unsupported OS. Exiting.'
    Exit(1)


Exit(1)


#build in separate directories
SConscript(
    'source/graphic_library_facade/SConscript', 
    exports=['env_base', 'binFolder', 'pathToUtility', 'libraryPath'], 
    variant_dir = binFolder + 'graphic_library_facade', 
    duplicate=0
    )

SConscript(
    'source/main/program_events/SConscript', 
    exports=['env_base', 'binFolder', 'pathToUtility', 'libraryPath'], 
    variant_dir = binFolder + 'main/program_events', 
    duplicate=0
    )

SConscript(
    'source/main/screen/SConscript', 
    exports=['env_base', 'binFolder', 'pathToUtility', 'libraryPath'], 
    variant_dir = binFolder + 'main/screen', 
    duplicate=0
    )

SConscript(
    'source/main/drawing/SConscript', 
    exports=['env_base', 'binFolder', 'pathToUtility', 'libraryPath'], 
    variant_dir = binFolder + 'main/drawing', 
    duplicate=0
    )


#print(Glob(['*.cpp', '../graphic_library_facade/*.o', 'program_events/*.o']))

#env.Program('hello', Glob(['*.cpp', '../graphic_library_facade/*.o', 'program_events/*.o']))
#env.Program(target = 'hello', source = ['main.cpp', 'renderLoop.cpp', '../graphic_library_facade/graphicLibraryFacade.o', 'program_events/basicEvents.o', 'program_events/eventManager.o', 'program_events/eventInterface.h'])
#['main.cpp', 'renderLoop.cpp', '../graphic_library_facade/graphicLibraryFacade.o']

#hello = env.Program(target = 'hello', source = ['source/main/main.cpp', 'source/main/renderLoop.cpp', 'build/graphic_library_facade/graphicLibraryFacade.o'])

SConscript(
    'source/main/SConscript', 
    exports = ['env_base', 'libraryPath', 'programName', 'programPath', 'binFolder', 'pathToBox2DLibrary', 'pathToBox2DHeaders'], 
    variant_dir= binFolder + 'main', 
    duplicate=0
    )

#the install option
#env.Install('usr/bin/scontest', hello)
#env.Alias('install', 'usr/bin/scontest')
