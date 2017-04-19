#glfw
cc -o myprog ./source/*.c -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lSOIL /usr/local/lib/libglfw3.a /usr/local/lib/libGLEW.a ./libft.a ../SimpleOpenGLImageLibrary/lib/libSOIL.a
