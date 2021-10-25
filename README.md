# Graphics
My attempt at OpenGL graphics.

I have no idea what this will end up as, but it's a bit of fun and something to do.

Previous goals include:

  -To condense all the information needed to draw a textured rectangle (composed of 2 triangles) into a single structure.
  
  -To make a single function, drawStruct(), that takes a structure as its sole argument and then draw it onto the screen.

  -To make an array of the structures and a function that takes this array and draws all of them in one go.


The next goal is to prevent structs from overwriting each other when drawn. Currently, the new image of the second struct overwrites the previous image, instead of being drawn/superimposed over it.



Apparently including \*.c files instead of \*.h files is not good.
But it works, so it stays.
