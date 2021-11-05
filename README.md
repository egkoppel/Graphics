# Graphics
My attempt at OpenGL graphics.

I have no idea what this will end up as, but it's a bit of fun and something to do.

Also, the added requirement that it must all be in C, with no C++ code. Partly because that would be cheating, but also because keeping it in C makes it compatiable with both C and C++ projects.

Previous goals include:

  - To condense all the information needed to draw a textured rectangle (composed of 2 triangles) into a single structure.
  
  - To make a single function, drawStruct(), that takes a structure as its sole argument and then draw it onto the screen.

  - To make an array of the structures and a function that takes this array and draws all of them in one go.

  - To prevent structs from overwriting each other when drawn.

  -To have an imgui implementation.

  -To do that thing with the colours on the corners of objects that makes it look trippy.


Future goals:

  -There is a projection matrix - the next step is to enter the third dimension (putting it like that makes it sound significantly more dramatic than it actually is).

Apparently including \*.c files instead of \*.h files is not good.
But it works, so it stays.
