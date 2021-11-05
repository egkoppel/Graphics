# Graphics
My attempt at OpenGL graphics.

I have no idea what this will end up as, but it's a bit of fun and something to do.

Formerly subject to a C-only requirement (without C++) until I decided that was simply too hard. It was the glm library that finally broke my resolve.

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
