This was me messing around with graphics in the windows command console.

Low resolution BMP images can be loaded and displayed.

Main branch shows a moving object.
Adding-HECS branch shows moving objects in a parent-child relationship.

ANSI terminal commands are used to get a full range colors however there are hard performance limitations with this method.
Writing directly to the console buffer is a much faster method however you are limited to 8 or so colors this way so proper rgb images can't be displayed.

Unfortunately with windows console host graphics you are limited to extremely slow rendering or extremely limited colors.

It's important you use the old windows console host not the new windows 11 version. There is a secondary project in the solution that launches the old conhost (can't debug this way), or you can change the default in your windows 11 settings and run the main project directly.
