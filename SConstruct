print('..Building App')

env = Environment(
    CC = 'g++',
    CCFLAGS = '-O2',
    SCONS_CXX_STANDARD='c++11',
    CPPPATH = '.'
)


#SConscript(['source/graphic_library_facade/SConscript', 'source/main/program_events/SConscript', 'source/main/screen/SConscript', 'source/main/drawing/SConscript'], exports='env')

#build in separate dir
SConscript('source/graphic_library_facade/SConscript', exports='env', variant_dir='build/graphic_library_facade', duplicate=0)
SConscript('source/main/program_events/SConscript', exports='env', variant_dir='build/main/program_events', duplicate=0)
SConscript('source/main/screen/SConscript', exports='env', variant_dir='build/main/screen', duplicate=0)
SConscript('source/main/drawing/SConscript', exports='env', variant_dir='build/main/drawing', duplicate=0)


env.AppendUnique(
    CCFLAGS = ' -Wall',
    CPPPATH = ['source/BD_FACADE', 'source/graphic_library_facade', 'libraries/boost_1_72_0'],
    LIBS = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system', 'events', 'screenLib', 'drawing'],
    LIBPATH = '../../build/libs'
)



#print(Glob(['*.cpp', '../graphic_library_facade/*.o', 'program_events/*.o']))

#env.Program('hello', Glob(['*.cpp', '../graphic_library_facade/*.o', 'program_events/*.o']))
#env.Program(target = 'hello', source = ['main.cpp', 'renderLoop.cpp', '../graphic_library_facade/graphicLibraryFacade.o', 'program_events/basicEvents.o', 'program_events/eventManager.o', 'program_events/eventInterface.h'])
#['main.cpp', 'renderLoop.cpp', '../graphic_library_facade/graphicLibraryFacade.o']

#hello = env.Program(target = 'hello', source = ['source/main/main.cpp', 'source/main/renderLoop.cpp', 'build/graphic_library_facade/graphicLibraryFacade.o'])

SConscript('source/main/SConscript', exports='env', variant_dir='build/main', duplicate=0)

#the install option
#env.Install('usr/bin/scontest', hello)
#env.Alias('install', 'usr/bin/scontest')
