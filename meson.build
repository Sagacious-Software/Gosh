project('gosh',
        'c',
        version : '0.0.1',
        license : 'MIT',
        default_options : ['c_std=c89'])

# TODO: figure out best way to have default warnings / errors
# TODO: remove this test macro after getting rid of the x11 hack code
cargs = ['-Wall', '-Werror', '-Wpedantic', '-D_POSIX_C_SOURCE=199309L']

deps = []

inc_dir = include_directories('include')

headers = ['include/gosh/backend.h',
           'include/gosh/window.h',
           'include/gosh/mouse.h',
           'include/gosh/keyboard.h',
           'include/gosh/event.h',
           'include/gosh/util.h']

src_lib = ['src/backend.c',
           'src/window.c',
           'src/mouse.c',
           'src/keyboard.c',
           'src/util.c']

src_backend_x11 = ['src/backends/x11/backend.c',
                   'src/backends/x11/window.c',
                   'src/backends/x11/mouse.c',
                   'src/backends/x11/keyboard.c']

src_backend_windows = ['src/backends/windows/backend.c',
                       'src/backends/windows/window.c',
                       'src/backends/windows/mouse.c',
                       'src/backends/windows/keyboard.c',
                       'src/backends/windows/util.c']

if get_option('enable_backend_x11').enabled()
    src_lib += src_backend_x11
    cargs += ['-DENABLE_BACKEND_X11']
    deps += [dependency('x11')]
endif

if get_option('enable_backend_windows').enabled()
    src_lib += src_backend_windows
    cargs += ['-DENABLE_BACKEND_WINDOWS']
endif

install_headers(headers, subdir : 'gosh')

lib = library('gosh',
               sources : src_lib,
               include_directories : inc_dir,
               dependencies : deps,
               c_args : cargs,
               install : true)

demo1 = executable('gosh_demo1',
                   sources : 'demos/demo1.c',
                   link_with : lib,
                   include_directories : inc_dir,
                   c_args : cargs,
                   install : true)

test('demo1', demo1)
