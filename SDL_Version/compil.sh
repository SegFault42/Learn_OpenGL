#SDL2
gcc source/*.c -lGLEW -lSDL2 -framework OpenGL `sdl2-config --cflags --libs` -o OpenGL ./libft.a
#glfw
#cc -o myprog glsf.c -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo /usr/local/lib/libglfw3.a /usr/local/lib/libGLEW.a
