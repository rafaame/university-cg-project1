##### Variables

ifeq ($(OS),Windows_NT)
    
	SRCDIR = src
	OBJDIR = obj
	INCDIR = -Isrc -Iinclude -Ivendor/glfw-3.0.4/include -Ivendor/glew-1.10.0/include -Ivendor/glm
	LIBDIR = -Lvendor/glfw-3.0.4/src -Lvendor/glew-1.10.0/lib
	CPPFLAGS = -g -Wall $(INCDIR) -DGLM_FORCE_RADIANS -DGLFW_STATIC
	LFLAGS = -lglfw3 -lGLEW -lopengl32 -lglu32 -lgdi32
	CC = g++ -mwin32

else
    
	SRCDIR = src
	OBJDIR = obj
	INCDIR = -Isrc -Iinclude -Ivendor/glfw-3.0.4/include -I/usr/local/Cellar/glew/1.11.0/include -Ivendor/glm
	LIBDIR = -Lvendor/glfw-3.0.4/src -L/usr/local/Cellar/glew/1.11.0/lib
	CPPFLAGS = -g -Wall $(INCDIR) -DGLM_FORCE_RADIANS -DGLFW_STATIC
	LFLAGS = -framework IOKit -framework Cocoa -framework OpenGL -framework QuartzCore -lglfw3 -lGLEW
	CC = g++

endif

##### Files

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
SRCFILES = $(patsubst $(SRCDIR)/%,%,$(SOURCES))
DEPENDENCIES = $(patsubst %.cpp,%.o,$(SOURCES))
OBJTEMP = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES))
OBJECTS = $(patsubst %.cpp,%.o,$(OBJTEMP))
TARGET = bin/main

##### Build rules
all: depend $(DEPENDENCIES)
	$(CC) $(CPPFLAGS) $(LIBDIR) $(OBJECTS) $(LFLAGS) -o $(TARGET)

.cpp.o:
	$(CC) $(CPPFLAGS) -c -o $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$*).o $*.cpp

depend:
	gccmakedep -fMakefile $(INCDIR) $(SOURCES)

clean:
	@rm -rf $(TARGET) $(TARGET).exe $(OBJDIR)/*.o *.bak *~ *%

run: all
	cd bin && ./main
	
memtest:
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./main
	
# DO NOT DELETE
Camera.o: src/Camera.cpp include/Camera.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/fstream \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__config \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ostream \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ios \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/iosfwd \
  /usr/include/wchar.h /usr/include/_types.h /usr/include/sys/_types.h \
  /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h \
  /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h \
  /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h \
  /usr/include/Availability.h /usr/include/AvailabilityInternal.h \
  /usr/include/sys/_types/_null.h /usr/include/sys/_types/_size_t.h \
  /usr/include/sys/_types/_mbstate_t.h \
  /usr/include/sys/_types/_ct_rune_t.h /usr/include/sys/_types/_rune_t.h \
  /usr/include/sys/_types/_wchar_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stdarg.h \
  /usr/include/stdio.h /usr/include/sys/_types/_va_list.h \
  /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h \
  /usr/include/sys/_types/_ssize_t.h /usr/include/time.h \
  /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_time_t.h \
  /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h \
  /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h \
  /usr/include/ctype.h /usr/include/runetype.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__locale \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/string \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstring \
  /usr/include/string.h /usr/include/sys/_types/_rsize_t.h \
  /usr/include/sys/_types/_errno_t.h /usr/include/strings.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdio \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cwchar \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cwctype \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cctype \
  /usr/include/wctype.h /usr/include/_types/_wctrans_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/algorithm \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/initializer_list \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstddef \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stddef.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/type_traits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/utility \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__tuple \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__tuple_03 \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/memory \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/typeinfo \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/exception \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdint \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stdint.h \
  /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h \
  /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h \
  /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h \
  /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h \
  /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h \
  /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h \
  /usr/include/_types/_uintmax_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/new \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/limits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__undef_min_max \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/iterator \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_base \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_base_03 \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__debug \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/tuple \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/stdexcept \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/mutex \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__mutex_base \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/chrono \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ctime \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ratio \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/climits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/limits.h \
  /usr/include/limits.h /usr/include/machine/limits.h \
  /usr/include/i386/limits.h /usr/include/i386/_limits.h \
  /usr/include/sys/syslimits.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/system_error \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cerrno \
  /usr/include/errno.h /usr/include/sys/errno.h /usr/include/pthread.h \
  /usr/include/pthread/pthread_impl.h /usr/include/pthread/sched.h \
  /usr/include/sys/_pthread/_pthread_attr_t.h \
  /usr/include/sys/_pthread/_pthread_cond_t.h \
  /usr/include/sys/_pthread/_pthread_condattr_t.h \
  /usr/include/sys/_pthread/_pthread_key_t.h \
  /usr/include/sys/_pthread/_pthread_mutex_t.h \
  /usr/include/sys/_pthread/_pthread_mutexattr_t.h \
  /usr/include/sys/_pthread/_pthread_once_t.h \
  /usr/include/sys/_pthread/_pthread_rwlock_t.h \
  /usr/include/sys/_pthread/_pthread_rwlockattr_t.h \
  /usr/include/sys/_pthread/_pthread_t.h /usr/include/pthread/qos.h \
  /usr/include/sys/qos.h /usr/include/sys/_types/_mach_port_t.h \
  /usr/include/sys/_types/_sigset_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/functional \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_03 \
  /usr/include/locale.h /usr/include/_locale.h /usr/include/xlocale.h \
  /usr/include/_xlocale.h /usr/include/xlocale/_ctype.h \
  /usr/include/xlocale/__wctype.h /usr/include/xlocale/_stdio.h \
  /usr/include/xlocale/_string.h /usr/include/xlocale/_time.h \
  /usr/include/xlocale/_wchar.h /usr/include/xlocale/_wctype.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/streambuf \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/locale \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdlib \
  /usr/include/stdlib.h /usr/include/sys/wait.h \
  /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h \
  /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h \
  /usr/include/machine/signal.h /usr/include/i386/signal.h \
  /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h \
  /usr/include/mach/i386/_structs.h \
  /usr/include/sys/_types/_sigaltstack.h \
  /usr/include/sys/_types/_ucontext.h /usr/include/sys/_types/_uid_t.h \
  /usr/include/sys/resource.h /usr/include/sys/_types/_timeval.h \
  /usr/include/machine/endian.h /usr/include/i386/endian.h \
  /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h \
  /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h \
  /usr/include/machine/types.h /usr/include/i386/types.h \
  /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h \
  /usr/include/xlocale/_stdlib.h /usr/include/nl_types.h \
  /usr/include/sys/types.h /usr/include/sys/_types/_blkcnt_t.h \
  /usr/include/sys/_types/_blksize_t.h /usr/include/sys/_types/_gid_t.h \
  /usr/include/sys/_types/_in_addr_t.h \
  /usr/include/sys/_types/_in_port_t.h /usr/include/sys/_types/_ino_t.h \
  /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_key_t.h \
  /usr/include/sys/_types/_nlink_t.h \
  /usr/include/sys/_types/_useconds_t.h \
  /usr/include/sys/_types/_suseconds_t.h \
  /usr/include/sys/_types/_fd_def.h \
  /usr/include/sys/_types/_fd_setsize.h \
  /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h \
  /usr/include/sys/_types/_fd_zero.h /usr/include/sys/_types/_fd_isset.h \
  /usr/include/sys/_types/_fd_copy.h \
  /usr/include/sys/_types/_fsblkcnt_t.h \
  /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/_types/_nl_item.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/bitset \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__bit_reference \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/istream \
  vendor/glm/glm/glm.hpp vendor/glm/glm/detail/_fixes.hpp \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cmath \
  /usr/include/math.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cfloat \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/float.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cassert \
  /usr/include/assert.h vendor/glm/glm/fwd.hpp \
  vendor/glm/glm/detail/type_int.hpp vendor/glm/glm/detail/setup.hpp \
  vendor/glm/glm/detail/type_float.hpp \
  vendor/glm/glm/detail/type_vec.hpp vendor/glm/glm/detail/precision.hpp \
  vendor/glm/glm/detail/type_mat.hpp vendor/glm/glm/vec2.hpp \
  vendor/glm/glm/detail/type_vec2.hpp \
  vendor/glm/glm/detail/type_vec2.inl vendor/glm/glm/vec3.hpp \
  vendor/glm/glm/detail/type_vec3.hpp \
  vendor/glm/glm/detail/type_vec3.inl vendor/glm/glm/vec4.hpp \
  vendor/glm/glm/detail/type_vec4.hpp \
  vendor/glm/glm/detail/type_vec4.inl vendor/glm/glm/mat2x2.hpp \
  vendor/glm/glm/detail/type_mat2x2.hpp \
  vendor/glm/glm/detail/type_mat2x2.inl vendor/glm/glm/mat2x3.hpp \
  vendor/glm/glm/detail/type_mat2x3.hpp \
  vendor/glm/glm/detail/type_mat2x3.inl vendor/glm/glm/mat2x4.hpp \
  vendor/glm/glm/detail/type_mat2x4.hpp \
  vendor/glm/glm/detail/type_mat2x4.inl vendor/glm/glm/mat3x2.hpp \
  vendor/glm/glm/detail/type_mat3x2.hpp \
  vendor/glm/glm/detail/type_mat3x2.inl vendor/glm/glm/mat3x3.hpp \
  vendor/glm/glm/detail/type_mat3x3.hpp \
  vendor/glm/glm/detail/type_mat3x3.inl vendor/glm/glm/mat3x4.hpp \
  vendor/glm/glm/detail/type_mat3x4.hpp \
  vendor/glm/glm/detail/type_mat3x4.inl vendor/glm/glm/mat4x2.hpp \
  vendor/glm/glm/detail/type_mat4x2.hpp \
  vendor/glm/glm/detail/type_mat4x2.inl vendor/glm/glm/mat4x3.hpp \
  vendor/glm/glm/detail/type_mat4x3.hpp \
  vendor/glm/glm/detail/type_mat4x3.inl vendor/glm/glm/mat4x4.hpp \
  vendor/glm/glm/detail/type_mat4x4.hpp \
  vendor/glm/glm/detail/type_mat4x4.inl vendor/glm/glm/trigonometric.hpp \
  vendor/glm/glm/detail/func_trigonometric.hpp \
  vendor/glm/glm/detail/func_trigonometric.inl \
  vendor/glm/glm/detail/_vectorize.hpp \
  vendor/glm/glm/detail/type_vec1.hpp \
  vendor/glm/glm/detail/type_vec1.inl vendor/glm/glm/exponential.hpp \
  vendor/glm/glm/detail/func_exponential.hpp \
  vendor/glm/glm/detail/func_exponential.inl \
  vendor/glm/glm/detail/func_vector_relational.hpp \
  vendor/glm/glm/detail/func_vector_relational.inl \
  vendor/glm/glm/common.hpp vendor/glm/glm/detail/func_common.hpp \
  vendor/glm/glm/detail/func_common.inl vendor/glm/glm/packing.hpp \
  vendor/glm/glm/detail/func_packing.hpp \
  vendor/glm/glm/detail/func_packing.inl \
  vendor/glm/glm/detail/type_half.hpp \
  vendor/glm/glm/detail/type_half.inl vendor/glm/glm/geometric.hpp \
  vendor/glm/glm/detail/func_geometric.hpp \
  vendor/glm/glm/detail/func_geometric.inl vendor/glm/glm/matrix.hpp \
  vendor/glm/glm/detail/func_matrix.hpp \
  vendor/glm/glm/detail/func_matrix.inl \
  vendor/glm/glm/vector_relational.hpp vendor/glm/glm/integer.hpp \
  vendor/glm/glm/detail/func_integer.hpp \
  vendor/glm/glm/detail/func_integer.inl \
  vendor/glm/glm/gtc/matrix_transform.hpp \
  vendor/glm/glm/gtc/matrix_transform.inl \
  vendor/glm/glm/gtx/transform2.hpp vendor/glm/glm/gtx/../glm.hpp \
  vendor/glm/glm/gtx/../gtx/transform.hpp \
  vendor/glm/glm/gtx/transform.inl vendor/glm/glm/gtx/transform2.inl
GLFWManager.o: src/GLFWManager.cpp \
  /usr/local/Cellar/glew/1.11.0/include/GL/glew.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stddef.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stdint.h \
  /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h \
  /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h \
  /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h \
  /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h \
  /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h \
  /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h \
  /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h \
  /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h \
  /usr/include/sys/_types/_intptr_t.h \
  /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h \
  /usr/include/_types/_uintmax_t.h /usr/include/Availability.h \
  /usr/include/AvailabilityInternal.h \
  /System/Library/Frameworks/OpenGL.framework/Headers/glu.h \
  /System/Library/Frameworks/OpenGL.framework/Headers/OpenGLAvailability.h \
  /System/Library/Frameworks/OpenGL.framework/Headers/gl.h \
  include/GLFWManager.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/string \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__config \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/iosfwd \
  /usr/include/wchar.h /usr/include/_types.h \
  /usr/include/sys/_types/_null.h /usr/include/sys/_types/_size_t.h \
  /usr/include/sys/_types/_mbstate_t.h \
  /usr/include/sys/_types/_ct_rune_t.h /usr/include/sys/_types/_rune_t.h \
  /usr/include/sys/_types/_wchar_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stdarg.h \
  /usr/include/stdio.h /usr/include/sys/_types/_va_list.h \
  /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h \
  /usr/include/sys/_types/_ssize_t.h /usr/include/time.h \
  /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_time_t.h \
  /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h \
  /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h \
  /usr/include/ctype.h /usr/include/runetype.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstring \
  /usr/include/string.h /usr/include/sys/_types/_rsize_t.h \
  /usr/include/sys/_types/_errno_t.h /usr/include/strings.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdio \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cwchar \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cwctype \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cctype \
  /usr/include/wctype.h /usr/include/_types/_wctrans_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/algorithm \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/initializer_list \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstddef \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/type_traits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/utility \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__tuple \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__tuple_03 \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/memory \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/typeinfo \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/exception \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdint \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/new \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/limits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__undef_min_max \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/iterator \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_base \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_base_03 \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__debug \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/tuple \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/stdexcept \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/fstream \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ostream \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ios \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__locale \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/mutex \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__mutex_base \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/chrono \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ctime \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ratio \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/climits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/limits.h \
  /usr/include/limits.h /usr/include/machine/limits.h \
  /usr/include/i386/limits.h /usr/include/i386/_limits.h \
  /usr/include/sys/syslimits.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/system_error \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cerrno \
  /usr/include/errno.h /usr/include/sys/errno.h /usr/include/pthread.h \
  /usr/include/pthread/pthread_impl.h /usr/include/pthread/sched.h \
  /usr/include/sys/_pthread/_pthread_attr_t.h \
  /usr/include/sys/_pthread/_pthread_cond_t.h \
  /usr/include/sys/_pthread/_pthread_condattr_t.h \
  /usr/include/sys/_pthread/_pthread_key_t.h \
  /usr/include/sys/_pthread/_pthread_mutex_t.h \
  /usr/include/sys/_pthread/_pthread_mutexattr_t.h \
  /usr/include/sys/_pthread/_pthread_once_t.h \
  /usr/include/sys/_pthread/_pthread_rwlock_t.h \
  /usr/include/sys/_pthread/_pthread_rwlockattr_t.h \
  /usr/include/sys/_pthread/_pthread_t.h /usr/include/pthread/qos.h \
  /usr/include/sys/qos.h /usr/include/sys/_types/_mach_port_t.h \
  /usr/include/sys/_types/_sigset_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/functional \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_03 \
  /usr/include/locale.h /usr/include/_locale.h /usr/include/xlocale.h \
  /usr/include/_xlocale.h /usr/include/xlocale/_ctype.h \
  /usr/include/xlocale/__wctype.h /usr/include/xlocale/_stdio.h \
  /usr/include/xlocale/_string.h /usr/include/xlocale/_time.h \
  /usr/include/xlocale/_wchar.h /usr/include/xlocale/_wctype.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/streambuf \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/locale \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdlib \
  /usr/include/stdlib.h /usr/include/sys/wait.h \
  /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h \
  /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h \
  /usr/include/machine/signal.h /usr/include/i386/signal.h \
  /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h \
  /usr/include/mach/i386/_structs.h \
  /usr/include/sys/_types/_sigaltstack.h \
  /usr/include/sys/_types/_ucontext.h /usr/include/sys/_types/_uid_t.h \
  /usr/include/sys/resource.h /usr/include/sys/_types/_timeval.h \
  /usr/include/machine/endian.h /usr/include/i386/endian.h \
  /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h \
  /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h \
  /usr/include/machine/types.h /usr/include/i386/types.h \
  /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h \
  /usr/include/xlocale/_stdlib.h /usr/include/nl_types.h \
  /usr/include/sys/types.h /usr/include/sys/_types/_blkcnt_t.h \
  /usr/include/sys/_types/_blksize_t.h /usr/include/sys/_types/_gid_t.h \
  /usr/include/sys/_types/_in_addr_t.h \
  /usr/include/sys/_types/_in_port_t.h /usr/include/sys/_types/_ino_t.h \
  /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_key_t.h \
  /usr/include/sys/_types/_nlink_t.h \
  /usr/include/sys/_types/_useconds_t.h \
  /usr/include/sys/_types/_suseconds_t.h \
  /usr/include/sys/_types/_fd_def.h \
  /usr/include/sys/_types/_fd_setsize.h \
  /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h \
  /usr/include/sys/_types/_fd_zero.h /usr/include/sys/_types/_fd_isset.h \
  /usr/include/sys/_types/_fd_copy.h \
  /usr/include/sys/_types/_fsblkcnt_t.h \
  /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/_types/_nl_item.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/bitset \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__bit_reference \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/istream \
  vendor/glfw-3.0.4/include/GLFW/glfw3.h include/WindowManager.h \
  include/InputManager.h vendor/glm/glm/glm.hpp \
  vendor/glm/glm/detail/_fixes.hpp \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cmath \
  /usr/include/math.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cfloat \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/float.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cassert \
  /usr/include/assert.h vendor/glm/glm/fwd.hpp \
  vendor/glm/glm/detail/type_int.hpp vendor/glm/glm/detail/setup.hpp \
  vendor/glm/glm/detail/type_float.hpp \
  vendor/glm/glm/detail/type_vec.hpp vendor/glm/glm/detail/precision.hpp \
  vendor/glm/glm/detail/type_mat.hpp vendor/glm/glm/vec2.hpp \
  vendor/glm/glm/detail/type_vec2.hpp \
  vendor/glm/glm/detail/type_vec2.inl vendor/glm/glm/vec3.hpp \
  vendor/glm/glm/detail/type_vec3.hpp \
  vendor/glm/glm/detail/type_vec3.inl vendor/glm/glm/vec4.hpp \
  vendor/glm/glm/detail/type_vec4.hpp \
  vendor/glm/glm/detail/type_vec4.inl vendor/glm/glm/mat2x2.hpp \
  vendor/glm/glm/detail/type_mat2x2.hpp \
  vendor/glm/glm/detail/type_mat2x2.inl vendor/glm/glm/mat2x3.hpp \
  vendor/glm/glm/detail/type_mat2x3.hpp \
  vendor/glm/glm/detail/type_mat2x3.inl vendor/glm/glm/mat2x4.hpp \
  vendor/glm/glm/detail/type_mat2x4.hpp \
  vendor/glm/glm/detail/type_mat2x4.inl vendor/glm/glm/mat3x2.hpp \
  vendor/glm/glm/detail/type_mat3x2.hpp \
  vendor/glm/glm/detail/type_mat3x2.inl vendor/glm/glm/mat3x3.hpp \
  vendor/glm/glm/detail/type_mat3x3.hpp \
  vendor/glm/glm/detail/type_mat3x3.inl vendor/glm/glm/mat3x4.hpp \
  vendor/glm/glm/detail/type_mat3x4.hpp \
  vendor/glm/glm/detail/type_mat3x4.inl vendor/glm/glm/mat4x2.hpp \
  vendor/glm/glm/detail/type_mat4x2.hpp \
  vendor/glm/glm/detail/type_mat4x2.inl vendor/glm/glm/mat4x3.hpp \
  vendor/glm/glm/detail/type_mat4x3.hpp \
  vendor/glm/glm/detail/type_mat4x3.inl vendor/glm/glm/mat4x4.hpp \
  vendor/glm/glm/detail/type_mat4x4.hpp \
  vendor/glm/glm/detail/type_mat4x4.inl vendor/glm/glm/trigonometric.hpp \
  vendor/glm/glm/detail/func_trigonometric.hpp \
  vendor/glm/glm/detail/func_trigonometric.inl \
  vendor/glm/glm/detail/_vectorize.hpp \
  vendor/glm/glm/detail/type_vec1.hpp \
  vendor/glm/glm/detail/type_vec1.inl vendor/glm/glm/exponential.hpp \
  vendor/glm/glm/detail/func_exponential.hpp \
  vendor/glm/glm/detail/func_exponential.inl \
  vendor/glm/glm/detail/func_vector_relational.hpp \
  vendor/glm/glm/detail/func_vector_relational.inl \
  vendor/glm/glm/common.hpp vendor/glm/glm/detail/func_common.hpp \
  vendor/glm/glm/detail/func_common.inl vendor/glm/glm/packing.hpp \
  vendor/glm/glm/detail/func_packing.hpp \
  vendor/glm/glm/detail/func_packing.inl \
  vendor/glm/glm/detail/type_half.hpp \
  vendor/glm/glm/detail/type_half.inl vendor/glm/glm/geometric.hpp \
  vendor/glm/glm/detail/func_geometric.hpp \
  vendor/glm/glm/detail/func_geometric.inl vendor/glm/glm/matrix.hpp \
  vendor/glm/glm/detail/func_matrix.hpp \
  vendor/glm/glm/detail/func_matrix.inl \
  vendor/glm/glm/vector_relational.hpp vendor/glm/glm/integer.hpp \
  vendor/glm/glm/detail/func_integer.hpp \
  vendor/glm/glm/detail/func_integer.inl \
  vendor/glm/glm/gtc/matrix_transform.hpp \
  vendor/glm/glm/gtc/matrix_transform.inl \
  vendor/glm/glm/gtx/transform2.hpp vendor/glm/glm/gtx/../glm.hpp \
  vendor/glm/glm/gtx/../gtx/transform.hpp \
  vendor/glm/glm/gtx/transform.inl vendor/glm/glm/gtx/transform2.inl \
  include/Camera.h include/Main.h include/Model.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__split_buffer \
  include/Shader.h include/TimeManager.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/thread
InputManager.o: src/InputManager.cpp include/InputManager.h \
  vendor/glm/glm/glm.hpp vendor/glm/glm/detail/_fixes.hpp \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cmath \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__config \
  /usr/include/math.h /usr/include/sys/cdefs.h \
  /usr/include/sys/_symbol_aliasing.h \
  /usr/include/sys/_posix_availability.h /usr/include/Availability.h \
  /usr/include/AvailabilityInternal.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/type_traits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstddef \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stddef.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/climits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/limits.h \
  /usr/include/limits.h /usr/include/machine/limits.h \
  /usr/include/i386/limits.h /usr/include/i386/_limits.h \
  /usr/include/sys/syslimits.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cfloat \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/float.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/limits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__undef_min_max \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cassert \
  /usr/include/assert.h /usr/include/stdlib.h /usr/include/_types.h \
  /usr/include/sys/_types.h /usr/include/machine/_types.h \
  /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h \
  /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h \
  /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h \
  /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h \
  /usr/include/i386/signal.h /usr/include/machine/_mcontext.h \
  /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h \
  /usr/include/sys/_pthread/_pthread_attr_t.h \
  /usr/include/sys/_types/_sigaltstack.h \
  /usr/include/sys/_types/_ucontext.h \
  /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_size_t.h \
  /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stdint.h \
  /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h \
  /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h \
  /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h \
  /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h \
  /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h \
  /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h \
  /usr/include/_types/_uintmax_t.h /usr/include/sys/_types/_timeval.h \
  /usr/include/machine/endian.h /usr/include/i386/endian.h \
  /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h \
  /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h \
  /usr/include/sys/_types/_ct_rune_t.h /usr/include/sys/_types/_rune_t.h \
  /usr/include/sys/_types/_wchar_t.h /usr/include/sys/_types/_null.h \
  /usr/include/machine/types.h /usr/include/i386/types.h \
  /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h \
  vendor/glm/glm/fwd.hpp vendor/glm/glm/detail/type_int.hpp \
  vendor/glm/glm/detail/setup.hpp vendor/glm/glm/detail/type_float.hpp \
  vendor/glm/glm/detail/type_vec.hpp vendor/glm/glm/detail/precision.hpp \
  vendor/glm/glm/detail/type_mat.hpp vendor/glm/glm/vec2.hpp \
  vendor/glm/glm/detail/type_vec2.hpp \
  vendor/glm/glm/detail/type_vec2.inl vendor/glm/glm/vec3.hpp \
  vendor/glm/glm/detail/type_vec3.hpp \
  vendor/glm/glm/detail/type_vec3.inl vendor/glm/glm/vec4.hpp \
  vendor/glm/glm/detail/type_vec4.hpp \
  vendor/glm/glm/detail/type_vec4.inl vendor/glm/glm/mat2x2.hpp \
  vendor/glm/glm/detail/type_mat2x2.hpp \
  vendor/glm/glm/detail/type_mat2x2.inl vendor/glm/glm/mat2x3.hpp \
  vendor/glm/glm/detail/type_mat2x3.hpp \
  vendor/glm/glm/detail/type_mat2x3.inl vendor/glm/glm/mat2x4.hpp \
  vendor/glm/glm/detail/type_mat2x4.hpp \
  vendor/glm/glm/detail/type_mat2x4.inl vendor/glm/glm/mat3x2.hpp \
  vendor/glm/glm/detail/type_mat3x2.hpp \
  vendor/glm/glm/detail/type_mat3x2.inl vendor/glm/glm/mat3x3.hpp \
  vendor/glm/glm/detail/type_mat3x3.hpp \
  vendor/glm/glm/detail/type_mat3x3.inl vendor/glm/glm/mat3x4.hpp \
  vendor/glm/glm/detail/type_mat3x4.hpp \
  vendor/glm/glm/detail/type_mat3x4.inl vendor/glm/glm/mat4x2.hpp \
  vendor/glm/glm/detail/type_mat4x2.hpp \
  vendor/glm/glm/detail/type_mat4x2.inl vendor/glm/glm/mat4x3.hpp \
  vendor/glm/glm/detail/type_mat4x3.hpp \
  vendor/glm/glm/detail/type_mat4x3.inl vendor/glm/glm/mat4x4.hpp \
  vendor/glm/glm/detail/type_mat4x4.hpp \
  vendor/glm/glm/detail/type_mat4x4.inl vendor/glm/glm/trigonometric.hpp \
  vendor/glm/glm/detail/func_trigonometric.hpp \
  vendor/glm/glm/detail/func_trigonometric.inl \
  vendor/glm/glm/detail/_vectorize.hpp \
  vendor/glm/glm/detail/type_vec1.hpp \
  vendor/glm/glm/detail/type_vec1.inl vendor/glm/glm/exponential.hpp \
  vendor/glm/glm/detail/func_exponential.hpp \
  vendor/glm/glm/detail/func_exponential.inl \
  vendor/glm/glm/detail/func_vector_relational.hpp \
  vendor/glm/glm/detail/func_vector_relational.inl \
  vendor/glm/glm/common.hpp vendor/glm/glm/detail/func_common.hpp \
  vendor/glm/glm/detail/func_common.inl vendor/glm/glm/packing.hpp \
  vendor/glm/glm/detail/func_packing.hpp \
  vendor/glm/glm/detail/func_packing.inl \
  vendor/glm/glm/detail/type_half.hpp \
  vendor/glm/glm/detail/type_half.inl vendor/glm/glm/geometric.hpp \
  vendor/glm/glm/detail/func_geometric.hpp \
  vendor/glm/glm/detail/func_geometric.inl vendor/glm/glm/matrix.hpp \
  vendor/glm/glm/detail/func_matrix.hpp \
  vendor/glm/glm/detail/func_matrix.inl \
  vendor/glm/glm/vector_relational.hpp vendor/glm/glm/integer.hpp \
  vendor/glm/glm/detail/func_integer.hpp \
  vendor/glm/glm/detail/func_integer.inl \
  vendor/glm/glm/gtc/matrix_transform.hpp \
  vendor/glm/glm/gtc/matrix_transform.inl \
  vendor/glm/glm/gtx/transform2.hpp vendor/glm/glm/gtx/../glm.hpp \
  vendor/glm/glm/gtx/../gtx/transform.hpp \
  vendor/glm/glm/gtx/transform.inl vendor/glm/glm/gtx/transform2.inl \
  include/Camera.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/fstream \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ostream \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ios \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/iosfwd \
  /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stdarg.h \
  /usr/include/stdio.h /usr/include/sys/_types/_va_list.h \
  /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h \
  /usr/include/sys/_types/_ssize_t.h /usr/include/time.h \
  /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_time_t.h \
  /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h \
  /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h \
  /usr/include/ctype.h /usr/include/runetype.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__locale \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/string \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstring \
  /usr/include/string.h /usr/include/sys/_types/_rsize_t.h \
  /usr/include/sys/_types/_errno_t.h /usr/include/strings.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdio \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cwchar \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cwctype \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cctype \
  /usr/include/wctype.h /usr/include/_types/_wctrans_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/algorithm \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/initializer_list \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/utility \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__tuple \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__tuple_03 \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/memory \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/typeinfo \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/exception \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdint \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/new \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/iterator \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_base \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_base_03 \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__debug \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/tuple \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/stdexcept \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/mutex \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__mutex_base \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/chrono \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ctime \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ratio \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/system_error \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cerrno \
  /usr/include/errno.h /usr/include/sys/errno.h /usr/include/pthread.h \
  /usr/include/pthread/pthread_impl.h /usr/include/pthread/sched.h \
  /usr/include/sys/_pthread/_pthread_cond_t.h \
  /usr/include/sys/_pthread/_pthread_condattr_t.h \
  /usr/include/sys/_pthread/_pthread_key_t.h \
  /usr/include/sys/_pthread/_pthread_mutex_t.h \
  /usr/include/sys/_pthread/_pthread_mutexattr_t.h \
  /usr/include/sys/_pthread/_pthread_once_t.h \
  /usr/include/sys/_pthread/_pthread_rwlock_t.h \
  /usr/include/sys/_pthread/_pthread_rwlockattr_t.h \
  /usr/include/sys/_pthread/_pthread_t.h /usr/include/pthread/qos.h \
  /usr/include/sys/qos.h /usr/include/sys/_types/_mach_port_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/functional \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_03 \
  /usr/include/locale.h /usr/include/_locale.h /usr/include/xlocale.h \
  /usr/include/_xlocale.h /usr/include/xlocale/_ctype.h \
  /usr/include/xlocale/__wctype.h /usr/include/xlocale/_stdio.h \
  /usr/include/xlocale/_stdlib.h /usr/include/xlocale/_string.h \
  /usr/include/xlocale/_time.h /usr/include/xlocale/_wchar.h \
  /usr/include/xlocale/_wctype.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/streambuf \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/locale \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdlib \
  /usr/include/nl_types.h /usr/include/sys/types.h \
  /usr/include/sys/_types/_blkcnt_t.h \
  /usr/include/sys/_types/_blksize_t.h /usr/include/sys/_types/_gid_t.h \
  /usr/include/sys/_types/_in_addr_t.h \
  /usr/include/sys/_types/_in_port_t.h /usr/include/sys/_types/_ino_t.h \
  /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_key_t.h \
  /usr/include/sys/_types/_nlink_t.h \
  /usr/include/sys/_types/_useconds_t.h \
  /usr/include/sys/_types/_suseconds_t.h \
  /usr/include/sys/_types/_fd_def.h \
  /usr/include/sys/_types/_fd_setsize.h \
  /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h \
  /usr/include/sys/_types/_fd_zero.h /usr/include/sys/_types/_fd_isset.h \
  /usr/include/sys/_types/_fd_copy.h \
  /usr/include/sys/_types/_fsblkcnt_t.h \
  /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/_types/_nl_item.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/bitset \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__bit_reference \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/istream \
  include/TimeManager.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/thread
Main.o: src/Main.cpp /usr/local/Cellar/glew/1.11.0/include/GL/glew.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stddef.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stdint.h \
  /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h \
  /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h \
  /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h \
  /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h \
  /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h \
  /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h \
  /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h \
  /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h \
  /usr/include/sys/_types/_intptr_t.h \
  /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h \
  /usr/include/_types/_uintmax_t.h /usr/include/Availability.h \
  /usr/include/AvailabilityInternal.h \
  /System/Library/Frameworks/OpenGL.framework/Headers/glu.h \
  /System/Library/Frameworks/OpenGL.framework/Headers/OpenGLAvailability.h \
  /System/Library/Frameworks/OpenGL.framework/Headers/gl.h \
  include/Main.h include/WindowManager.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/string \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__config \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/iosfwd \
  /usr/include/wchar.h /usr/include/_types.h \
  /usr/include/sys/_types/_null.h /usr/include/sys/_types/_size_t.h \
  /usr/include/sys/_types/_mbstate_t.h \
  /usr/include/sys/_types/_ct_rune_t.h /usr/include/sys/_types/_rune_t.h \
  /usr/include/sys/_types/_wchar_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stdarg.h \
  /usr/include/stdio.h /usr/include/sys/_types/_va_list.h \
  /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h \
  /usr/include/sys/_types/_ssize_t.h /usr/include/time.h \
  /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_time_t.h \
  /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h \
  /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h \
  /usr/include/ctype.h /usr/include/runetype.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstring \
  /usr/include/string.h /usr/include/sys/_types/_rsize_t.h \
  /usr/include/sys/_types/_errno_t.h /usr/include/strings.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdio \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cwchar \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cwctype \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cctype \
  /usr/include/wctype.h /usr/include/_types/_wctrans_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/algorithm \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/initializer_list \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstddef \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/type_traits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/utility \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__tuple \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__tuple_03 \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/memory \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/typeinfo \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/exception \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdint \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/new \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/limits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__undef_min_max \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/iterator \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_base \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_base_03 \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__debug \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/tuple \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/stdexcept \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/fstream \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ostream \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ios \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__locale \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/mutex \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__mutex_base \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/chrono \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ctime \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ratio \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/climits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/limits.h \
  /usr/include/limits.h /usr/include/machine/limits.h \
  /usr/include/i386/limits.h /usr/include/i386/_limits.h \
  /usr/include/sys/syslimits.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/system_error \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cerrno \
  /usr/include/errno.h /usr/include/sys/errno.h /usr/include/pthread.h \
  /usr/include/pthread/pthread_impl.h /usr/include/pthread/sched.h \
  /usr/include/sys/_pthread/_pthread_attr_t.h \
  /usr/include/sys/_pthread/_pthread_cond_t.h \
  /usr/include/sys/_pthread/_pthread_condattr_t.h \
  /usr/include/sys/_pthread/_pthread_key_t.h \
  /usr/include/sys/_pthread/_pthread_mutex_t.h \
  /usr/include/sys/_pthread/_pthread_mutexattr_t.h \
  /usr/include/sys/_pthread/_pthread_once_t.h \
  /usr/include/sys/_pthread/_pthread_rwlock_t.h \
  /usr/include/sys/_pthread/_pthread_rwlockattr_t.h \
  /usr/include/sys/_pthread/_pthread_t.h /usr/include/pthread/qos.h \
  /usr/include/sys/qos.h /usr/include/sys/_types/_mach_port_t.h \
  /usr/include/sys/_types/_sigset_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/functional \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_03 \
  /usr/include/locale.h /usr/include/_locale.h /usr/include/xlocale.h \
  /usr/include/_xlocale.h /usr/include/xlocale/_ctype.h \
  /usr/include/xlocale/__wctype.h /usr/include/xlocale/_stdio.h \
  /usr/include/xlocale/_string.h /usr/include/xlocale/_time.h \
  /usr/include/xlocale/_wchar.h /usr/include/xlocale/_wctype.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/streambuf \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/locale \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdlib \
  /usr/include/stdlib.h /usr/include/sys/wait.h \
  /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h \
  /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h \
  /usr/include/machine/signal.h /usr/include/i386/signal.h \
  /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h \
  /usr/include/mach/i386/_structs.h \
  /usr/include/sys/_types/_sigaltstack.h \
  /usr/include/sys/_types/_ucontext.h /usr/include/sys/_types/_uid_t.h \
  /usr/include/sys/resource.h /usr/include/sys/_types/_timeval.h \
  /usr/include/machine/endian.h /usr/include/i386/endian.h \
  /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h \
  /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h \
  /usr/include/machine/types.h /usr/include/i386/types.h \
  /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h \
  /usr/include/xlocale/_stdlib.h /usr/include/nl_types.h \
  /usr/include/sys/types.h /usr/include/sys/_types/_blkcnt_t.h \
  /usr/include/sys/_types/_blksize_t.h /usr/include/sys/_types/_gid_t.h \
  /usr/include/sys/_types/_in_addr_t.h \
  /usr/include/sys/_types/_in_port_t.h /usr/include/sys/_types/_ino_t.h \
  /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_key_t.h \
  /usr/include/sys/_types/_nlink_t.h \
  /usr/include/sys/_types/_useconds_t.h \
  /usr/include/sys/_types/_suseconds_t.h \
  /usr/include/sys/_types/_fd_def.h \
  /usr/include/sys/_types/_fd_setsize.h \
  /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h \
  /usr/include/sys/_types/_fd_zero.h /usr/include/sys/_types/_fd_isset.h \
  /usr/include/sys/_types/_fd_copy.h \
  /usr/include/sys/_types/_fsblkcnt_t.h \
  /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/_types/_nl_item.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/bitset \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__bit_reference \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/istream \
  include/InputManager.h vendor/glm/glm/glm.hpp \
  vendor/glm/glm/detail/_fixes.hpp \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cmath \
  /usr/include/math.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cfloat \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/float.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cassert \
  /usr/include/assert.h vendor/glm/glm/fwd.hpp \
  vendor/glm/glm/detail/type_int.hpp vendor/glm/glm/detail/setup.hpp \
  vendor/glm/glm/detail/type_float.hpp \
  vendor/glm/glm/detail/type_vec.hpp vendor/glm/glm/detail/precision.hpp \
  vendor/glm/glm/detail/type_mat.hpp vendor/glm/glm/vec2.hpp \
  vendor/glm/glm/detail/type_vec2.hpp \
  vendor/glm/glm/detail/type_vec2.inl vendor/glm/glm/vec3.hpp \
  vendor/glm/glm/detail/type_vec3.hpp \
  vendor/glm/glm/detail/type_vec3.inl vendor/glm/glm/vec4.hpp \
  vendor/glm/glm/detail/type_vec4.hpp \
  vendor/glm/glm/detail/type_vec4.inl vendor/glm/glm/mat2x2.hpp \
  vendor/glm/glm/detail/type_mat2x2.hpp \
  vendor/glm/glm/detail/type_mat2x2.inl vendor/glm/glm/mat2x3.hpp \
  vendor/glm/glm/detail/type_mat2x3.hpp \
  vendor/glm/glm/detail/type_mat2x3.inl vendor/glm/glm/mat2x4.hpp \
  vendor/glm/glm/detail/type_mat2x4.hpp \
  vendor/glm/glm/detail/type_mat2x4.inl vendor/glm/glm/mat3x2.hpp \
  vendor/glm/glm/detail/type_mat3x2.hpp \
  vendor/glm/glm/detail/type_mat3x2.inl vendor/glm/glm/mat3x3.hpp \
  vendor/glm/glm/detail/type_mat3x3.hpp \
  vendor/glm/glm/detail/type_mat3x3.inl vendor/glm/glm/mat3x4.hpp \
  vendor/glm/glm/detail/type_mat3x4.hpp \
  vendor/glm/glm/detail/type_mat3x4.inl vendor/glm/glm/mat4x2.hpp \
  vendor/glm/glm/detail/type_mat4x2.hpp \
  vendor/glm/glm/detail/type_mat4x2.inl vendor/glm/glm/mat4x3.hpp \
  vendor/glm/glm/detail/type_mat4x3.hpp \
  vendor/glm/glm/detail/type_mat4x3.inl vendor/glm/glm/mat4x4.hpp \
  vendor/glm/glm/detail/type_mat4x4.hpp \
  vendor/glm/glm/detail/type_mat4x4.inl vendor/glm/glm/trigonometric.hpp \
  vendor/glm/glm/detail/func_trigonometric.hpp \
  vendor/glm/glm/detail/func_trigonometric.inl \
  vendor/glm/glm/detail/_vectorize.hpp \
  vendor/glm/glm/detail/type_vec1.hpp \
  vendor/glm/glm/detail/type_vec1.inl vendor/glm/glm/exponential.hpp \
  vendor/glm/glm/detail/func_exponential.hpp \
  vendor/glm/glm/detail/func_exponential.inl \
  vendor/glm/glm/detail/func_vector_relational.hpp \
  vendor/glm/glm/detail/func_vector_relational.inl \
  vendor/glm/glm/common.hpp vendor/glm/glm/detail/func_common.hpp \
  vendor/glm/glm/detail/func_common.inl vendor/glm/glm/packing.hpp \
  vendor/glm/glm/detail/func_packing.hpp \
  vendor/glm/glm/detail/func_packing.inl \
  vendor/glm/glm/detail/type_half.hpp \
  vendor/glm/glm/detail/type_half.inl vendor/glm/glm/geometric.hpp \
  vendor/glm/glm/detail/func_geometric.hpp \
  vendor/glm/glm/detail/func_geometric.inl vendor/glm/glm/matrix.hpp \
  vendor/glm/glm/detail/func_matrix.hpp \
  vendor/glm/glm/detail/func_matrix.inl \
  vendor/glm/glm/vector_relational.hpp vendor/glm/glm/integer.hpp \
  vendor/glm/glm/detail/func_integer.hpp \
  vendor/glm/glm/detail/func_integer.inl \
  vendor/glm/glm/gtc/matrix_transform.hpp \
  vendor/glm/glm/gtc/matrix_transform.inl \
  vendor/glm/glm/gtx/transform2.hpp vendor/glm/glm/gtx/../glm.hpp \
  vendor/glm/glm/gtx/../gtx/transform.hpp \
  vendor/glm/glm/gtx/transform.inl vendor/glm/glm/gtx/transform2.inl \
  include/Camera.h include/Model.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__split_buffer \
  include/Shader.h include/TimeManager.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/thread
Model.o: src/Model.cpp include/Model.h /usr/include/stdio.h \
  /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h \
  /usr/include/sys/_posix_availability.h /usr/include/Availability.h \
  /usr/include/AvailabilityInternal.h /usr/include/_types.h \
  /usr/include/sys/_types.h /usr/include/machine/_types.h \
  /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h \
  /usr/include/sys/_types/_va_list.h /usr/include/sys/_types/_size_t.h \
  /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h \
  /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h \
  /usr/include/stdlib.h /usr/include/sys/wait.h \
  /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h \
  /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h \
  /usr/include/machine/signal.h /usr/include/i386/signal.h \
  /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h \
  /usr/include/mach/i386/_structs.h \
  /usr/include/sys/_pthread/_pthread_attr_t.h \
  /usr/include/sys/_types/_sigaltstack.h \
  /usr/include/sys/_types/_ucontext.h \
  /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_uid_t.h \
  /usr/include/sys/resource.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stdint.h \
  /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h \
  /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h \
  /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h \
  /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h \
  /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h \
  /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h \
  /usr/include/_types/_uintmax_t.h /usr/include/sys/_types/_timeval.h \
  /usr/include/machine/endian.h /usr/include/i386/endian.h \
  /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h \
  /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h \
  /usr/include/sys/_types/_ct_rune_t.h /usr/include/sys/_types/_rune_t.h \
  /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h \
  /usr/include/i386/types.h /usr/include/sys/_types/_dev_t.h \
  /usr/include/sys/_types/_mode_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__config \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__bit_reference \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/algorithm \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/initializer_list \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstddef \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stddef.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/type_traits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstring \
  /usr/include/string.h /usr/include/sys/_types/_rsize_t.h \
  /usr/include/sys/_types/_errno_t.h /usr/include/strings.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/utility \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__tuple \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__tuple_03 \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/memory \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/typeinfo \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/exception \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdint \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/new \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/limits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__undef_min_max \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/iterator \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_base \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_base_03 \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/iosfwd \
  /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stdarg.h \
  /usr/include/time.h /usr/include/sys/_types/_clock_t.h \
  /usr/include/sys/_types/_time_t.h /usr/include/sys/_types/_timespec.h \
  /usr/include/_wctype.h /usr/include/sys/_types/_wint_t.h \
  /usr/include/_types/_wctype_t.h /usr/include/ctype.h \
  /usr/include/runetype.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__debug \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/tuple \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/climits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/limits.h \
  /usr/include/limits.h /usr/include/machine/limits.h \
  /usr/include/i386/limits.h /usr/include/i386/_limits.h \
  /usr/include/sys/syslimits.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/stdexcept \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__split_buffer \
  /usr/local/Cellar/glew/1.11.0/include/GL/glew.h \
  /System/Library/Frameworks/OpenGL.framework/Headers/glu.h \
  /System/Library/Frameworks/OpenGL.framework/Headers/OpenGLAvailability.h \
  /System/Library/Frameworks/OpenGL.framework/Headers/gl.h \
  vendor/glm/glm/glm.hpp vendor/glm/glm/detail/_fixes.hpp \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cmath \
  /usr/include/math.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cfloat \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/float.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cassert \
  /usr/include/assert.h vendor/glm/glm/fwd.hpp \
  vendor/glm/glm/detail/type_int.hpp vendor/glm/glm/detail/setup.hpp \
  vendor/glm/glm/detail/type_float.hpp \
  vendor/glm/glm/detail/type_vec.hpp vendor/glm/glm/detail/precision.hpp \
  vendor/glm/glm/detail/type_mat.hpp vendor/glm/glm/vec2.hpp \
  vendor/glm/glm/detail/type_vec2.hpp \
  vendor/glm/glm/detail/type_vec2.inl vendor/glm/glm/vec3.hpp \
  vendor/glm/glm/detail/type_vec3.hpp \
  vendor/glm/glm/detail/type_vec3.inl vendor/glm/glm/vec4.hpp \
  vendor/glm/glm/detail/type_vec4.hpp \
  vendor/glm/glm/detail/type_vec4.inl vendor/glm/glm/mat2x2.hpp \
  vendor/glm/glm/detail/type_mat2x2.hpp \
  vendor/glm/glm/detail/type_mat2x2.inl vendor/glm/glm/mat2x3.hpp \
  vendor/glm/glm/detail/type_mat2x3.hpp \
  vendor/glm/glm/detail/type_mat2x3.inl vendor/glm/glm/mat2x4.hpp \
  vendor/glm/glm/detail/type_mat2x4.hpp \
  vendor/glm/glm/detail/type_mat2x4.inl vendor/glm/glm/mat3x2.hpp \
  vendor/glm/glm/detail/type_mat3x2.hpp \
  vendor/glm/glm/detail/type_mat3x2.inl vendor/glm/glm/mat3x3.hpp \
  vendor/glm/glm/detail/type_mat3x3.hpp \
  vendor/glm/glm/detail/type_mat3x3.inl vendor/glm/glm/mat3x4.hpp \
  vendor/glm/glm/detail/type_mat3x4.hpp \
  vendor/glm/glm/detail/type_mat3x4.inl vendor/glm/glm/mat4x2.hpp \
  vendor/glm/glm/detail/type_mat4x2.hpp \
  vendor/glm/glm/detail/type_mat4x2.inl vendor/glm/glm/mat4x3.hpp \
  vendor/glm/glm/detail/type_mat4x3.hpp \
  vendor/glm/glm/detail/type_mat4x3.inl vendor/glm/glm/mat4x4.hpp \
  vendor/glm/glm/detail/type_mat4x4.hpp \
  vendor/glm/glm/detail/type_mat4x4.inl vendor/glm/glm/trigonometric.hpp \
  vendor/glm/glm/detail/func_trigonometric.hpp \
  vendor/glm/glm/detail/func_trigonometric.inl \
  vendor/glm/glm/detail/_vectorize.hpp \
  vendor/glm/glm/detail/type_vec1.hpp \
  vendor/glm/glm/detail/type_vec1.inl vendor/glm/glm/exponential.hpp \
  vendor/glm/glm/detail/func_exponential.hpp \
  vendor/glm/glm/detail/func_exponential.inl \
  vendor/glm/glm/detail/func_vector_relational.hpp \
  vendor/glm/glm/detail/func_vector_relational.inl \
  vendor/glm/glm/common.hpp vendor/glm/glm/detail/func_common.hpp \
  vendor/glm/glm/detail/func_common.inl vendor/glm/glm/packing.hpp \
  vendor/glm/glm/detail/func_packing.hpp \
  vendor/glm/glm/detail/func_packing.inl \
  vendor/glm/glm/detail/type_half.hpp \
  vendor/glm/glm/detail/type_half.inl vendor/glm/glm/geometric.hpp \
  vendor/glm/glm/detail/func_geometric.hpp \
  vendor/glm/glm/detail/func_geometric.inl vendor/glm/glm/matrix.hpp \
  vendor/glm/glm/detail/func_matrix.hpp \
  vendor/glm/glm/detail/func_matrix.inl \
  vendor/glm/glm/vector_relational.hpp vendor/glm/glm/integer.hpp \
  vendor/glm/glm/detail/func_integer.hpp \
  vendor/glm/glm/detail/func_integer.inl \
  vendor/glm/glm/gtc/matrix_transform.hpp \
  vendor/glm/glm/gtc/matrix_transform.inl \
  vendor/glm/glm/gtx/transform2.hpp vendor/glm/glm/gtx/../glm.hpp \
  vendor/glm/glm/gtx/../gtx/transform.hpp \
  vendor/glm/glm/gtx/transform.inl vendor/glm/glm/gtx/transform2.inl \
  include/Shader.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/string \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdio \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cwchar \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cwctype \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cctype \
  /usr/include/wctype.h /usr/include/_types/_wctrans_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/fstream \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ostream \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ios \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__locale \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/mutex \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__mutex_base \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/chrono \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ctime \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ratio \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/system_error \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cerrno \
  /usr/include/errno.h /usr/include/sys/errno.h /usr/include/pthread.h \
  /usr/include/pthread/pthread_impl.h /usr/include/pthread/sched.h \
  /usr/include/sys/_pthread/_pthread_cond_t.h \
  /usr/include/sys/_pthread/_pthread_condattr_t.h \
  /usr/include/sys/_pthread/_pthread_key_t.h \
  /usr/include/sys/_pthread/_pthread_mutex_t.h \
  /usr/include/sys/_pthread/_pthread_mutexattr_t.h \
  /usr/include/sys/_pthread/_pthread_once_t.h \
  /usr/include/sys/_pthread/_pthread_rwlock_t.h \
  /usr/include/sys/_pthread/_pthread_rwlockattr_t.h \
  /usr/include/sys/_pthread/_pthread_t.h /usr/include/pthread/qos.h \
  /usr/include/sys/qos.h /usr/include/sys/_types/_mach_port_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/functional \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_03 \
  /usr/include/locale.h /usr/include/_locale.h /usr/include/xlocale.h \
  /usr/include/_xlocale.h /usr/include/xlocale/_ctype.h \
  /usr/include/xlocale/__wctype.h /usr/include/xlocale/_stdio.h \
  /usr/include/xlocale/_stdlib.h /usr/include/xlocale/_string.h \
  /usr/include/xlocale/_time.h /usr/include/xlocale/_wchar.h \
  /usr/include/xlocale/_wctype.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/streambuf \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/locale \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdlib \
  /usr/include/nl_types.h /usr/include/sys/types.h \
  /usr/include/sys/_types/_blkcnt_t.h \
  /usr/include/sys/_types/_blksize_t.h /usr/include/sys/_types/_gid_t.h \
  /usr/include/sys/_types/_in_addr_t.h \
  /usr/include/sys/_types/_in_port_t.h /usr/include/sys/_types/_ino_t.h \
  /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_key_t.h \
  /usr/include/sys/_types/_nlink_t.h \
  /usr/include/sys/_types/_useconds_t.h \
  /usr/include/sys/_types/_suseconds_t.h \
  /usr/include/sys/_types/_fd_def.h \
  /usr/include/sys/_types/_fd_setsize.h \
  /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h \
  /usr/include/sys/_types/_fd_zero.h /usr/include/sys/_types/_fd_isset.h \
  /usr/include/sys/_types/_fd_copy.h \
  /usr/include/sys/_types/_fsblkcnt_t.h \
  /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/_types/_nl_item.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/bitset \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/istream \
  include/Camera.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/iostream \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/sstream
Shader.o: src/Shader.cpp include/Shader.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/string \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__config \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/iosfwd \
  /usr/include/wchar.h /usr/include/_types.h /usr/include/sys/_types.h \
  /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h \
  /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h \
  /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h \
  /usr/include/Availability.h /usr/include/AvailabilityInternal.h \
  /usr/include/sys/_types/_null.h /usr/include/sys/_types/_size_t.h \
  /usr/include/sys/_types/_mbstate_t.h \
  /usr/include/sys/_types/_ct_rune_t.h /usr/include/sys/_types/_rune_t.h \
  /usr/include/sys/_types/_wchar_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stdarg.h \
  /usr/include/stdio.h /usr/include/sys/_types/_va_list.h \
  /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h \
  /usr/include/sys/_types/_ssize_t.h /usr/include/time.h \
  /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_time_t.h \
  /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h \
  /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h \
  /usr/include/ctype.h /usr/include/runetype.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstring \
  /usr/include/string.h /usr/include/sys/_types/_rsize_t.h \
  /usr/include/sys/_types/_errno_t.h /usr/include/strings.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdio \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cwchar \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cwctype \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cctype \
  /usr/include/wctype.h /usr/include/_types/_wctrans_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/algorithm \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/initializer_list \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstddef \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stddef.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/type_traits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/utility \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__tuple \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__tuple_03 \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/memory \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/typeinfo \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/exception \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdint \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stdint.h \
  /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h \
  /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h \
  /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h \
  /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h \
  /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h \
  /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h \
  /usr/include/_types/_uintmax_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/new \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/limits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__undef_min_max \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/iterator \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_base \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_base_03 \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__debug \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/tuple \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/stdexcept \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/fstream \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ostream \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ios \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__locale \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/mutex \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__mutex_base \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/chrono \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ctime \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ratio \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/climits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/limits.h \
  /usr/include/limits.h /usr/include/machine/limits.h \
  /usr/include/i386/limits.h /usr/include/i386/_limits.h \
  /usr/include/sys/syslimits.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/system_error \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cerrno \
  /usr/include/errno.h /usr/include/sys/errno.h /usr/include/pthread.h \
  /usr/include/pthread/pthread_impl.h /usr/include/pthread/sched.h \
  /usr/include/sys/_pthread/_pthread_attr_t.h \
  /usr/include/sys/_pthread/_pthread_cond_t.h \
  /usr/include/sys/_pthread/_pthread_condattr_t.h \
  /usr/include/sys/_pthread/_pthread_key_t.h \
  /usr/include/sys/_pthread/_pthread_mutex_t.h \
  /usr/include/sys/_pthread/_pthread_mutexattr_t.h \
  /usr/include/sys/_pthread/_pthread_once_t.h \
  /usr/include/sys/_pthread/_pthread_rwlock_t.h \
  /usr/include/sys/_pthread/_pthread_rwlockattr_t.h \
  /usr/include/sys/_pthread/_pthread_t.h /usr/include/pthread/qos.h \
  /usr/include/sys/qos.h /usr/include/sys/_types/_mach_port_t.h \
  /usr/include/sys/_types/_sigset_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/functional \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_03 \
  /usr/include/locale.h /usr/include/_locale.h /usr/include/xlocale.h \
  /usr/include/_xlocale.h /usr/include/xlocale/_ctype.h \
  /usr/include/xlocale/__wctype.h /usr/include/xlocale/_stdio.h \
  /usr/include/xlocale/_string.h /usr/include/xlocale/_time.h \
  /usr/include/xlocale/_wchar.h /usr/include/xlocale/_wctype.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/streambuf \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/locale \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdlib \
  /usr/include/stdlib.h /usr/include/sys/wait.h \
  /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h \
  /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h \
  /usr/include/machine/signal.h /usr/include/i386/signal.h \
  /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h \
  /usr/include/mach/i386/_structs.h \
  /usr/include/sys/_types/_sigaltstack.h \
  /usr/include/sys/_types/_ucontext.h /usr/include/sys/_types/_uid_t.h \
  /usr/include/sys/resource.h /usr/include/sys/_types/_timeval.h \
  /usr/include/machine/endian.h /usr/include/i386/endian.h \
  /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h \
  /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h \
  /usr/include/machine/types.h /usr/include/i386/types.h \
  /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h \
  /usr/include/xlocale/_stdlib.h /usr/include/nl_types.h \
  /usr/include/sys/types.h /usr/include/sys/_types/_blkcnt_t.h \
  /usr/include/sys/_types/_blksize_t.h /usr/include/sys/_types/_gid_t.h \
  /usr/include/sys/_types/_in_addr_t.h \
  /usr/include/sys/_types/_in_port_t.h /usr/include/sys/_types/_ino_t.h \
  /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_key_t.h \
  /usr/include/sys/_types/_nlink_t.h \
  /usr/include/sys/_types/_useconds_t.h \
  /usr/include/sys/_types/_suseconds_t.h \
  /usr/include/sys/_types/_fd_def.h \
  /usr/include/sys/_types/_fd_setsize.h \
  /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h \
  /usr/include/sys/_types/_fd_zero.h /usr/include/sys/_types/_fd_isset.h \
  /usr/include/sys/_types/_fd_copy.h \
  /usr/include/sys/_types/_fsblkcnt_t.h \
  /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/_types/_nl_item.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/bitset \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__bit_reference \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/istream \
  /usr/local/Cellar/glew/1.11.0/include/GL/glew.h \
  /System/Library/Frameworks/OpenGL.framework/Headers/glu.h \
  /System/Library/Frameworks/OpenGL.framework/Headers/OpenGLAvailability.h \
  /System/Library/Frameworks/OpenGL.framework/Headers/gl.h
TimeManager.o: src/TimeManager.cpp include/TimeManager.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/chrono \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__config \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ctime \
  /usr/include/time.h /usr/include/_types.h /usr/include/sys/_types.h \
  /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h \
  /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h \
  /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h \
  /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_null.h \
  /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_time_t.h \
  /usr/include/sys/_types/_timespec.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/type_traits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstddef \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stddef.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/ratio \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstdint \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stdint.h \
  /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h \
  /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h \
  /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h \
  /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h \
  /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h \
  /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h \
  /usr/include/_types/_uintmax_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/climits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/limits.h \
  /usr/include/limits.h /usr/include/machine/limits.h \
  /usr/include/i386/limits.h /usr/include/i386/_limits.h \
  /usr/include/sys/syslimits.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__undef_min_max \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/limits \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/thread \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/iosfwd \
  /usr/include/wchar.h /usr/include/Availability.h \
  /usr/include/AvailabilityInternal.h \
  /usr/include/sys/_types/_mbstate_t.h \
  /usr/include/sys/_types/_ct_rune_t.h /usr/include/sys/_types/_rune_t.h \
  /usr/include/sys/_types/_wchar_t.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/6.1.0/include/stdarg.h \
  /usr/include/stdio.h /usr/include/sys/_types/_va_list.h \
  /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h \
  /usr/include/sys/_types/_ssize_t.h /usr/include/_wctype.h \
  /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h \
  /usr/include/ctype.h /usr/include/runetype.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_base \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/typeinfo \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/exception \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/new \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_base_03 \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/functional \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/memory \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/utility \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__tuple \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__tuple_03 \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/iterator \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/initializer_list \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__debug \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/tuple \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cstring \
  /usr/include/string.h /usr/include/sys/_types/_rsize_t.h \
  /usr/include/sys/_types/_errno_t.h /usr/include/strings.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__functional_03 \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/system_error \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/cerrno \
  /usr/include/errno.h /usr/include/sys/errno.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/stdexcept \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/__mutex_base \
  /usr/include/pthread.h /usr/include/pthread/pthread_impl.h \
  /usr/include/pthread/sched.h \
  /usr/include/sys/_pthread/_pthread_attr_t.h \
  /usr/include/sys/_pthread/_pthread_cond_t.h \
  /usr/include/sys/_pthread/_pthread_condattr_t.h \
  /usr/include/sys/_pthread/_pthread_key_t.h \
  /usr/include/sys/_pthread/_pthread_mutex_t.h \
  /usr/include/sys/_pthread/_pthread_mutexattr_t.h \
  /usr/include/sys/_pthread/_pthread_once_t.h \
  /usr/include/sys/_pthread/_pthread_rwlock_t.h \
  /usr/include/sys/_pthread/_pthread_rwlockattr_t.h \
  /usr/include/sys/_pthread/_pthread_t.h /usr/include/pthread/qos.h \
  /usr/include/sys/qos.h /usr/include/sys/_types/_mach_port_t.h \
  /usr/include/sys/_types/_sigset_t.h
