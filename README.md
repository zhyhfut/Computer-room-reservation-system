This code is a computer room reservation system code based on the Dark Horse Programmer course, which is developed by VS2022.

By studying the source code, the following shortcomes are found:
1. The three types of submenus are accessed using global functions, with C language type forced conversions in between.
2. The work numbers and names of teachers and students are not properly protected.
3. There is too much duplication of code for extracting and splitting appointment information.

To address the above issues, this code makes the following optimizations:
1. Encapsulate the global function of loading the submenu into a pure virtual member function in the Identity class, and use polymorphism to implement it in the subclasses one by one.
2. Change the name and work number of the teacher and student to private type and access them using friend.
3. In orderFile.cpp, encapsulate the string segmentation into a function that returns a pair type and call it in the parameterized constructor.

The system functions will be expanded based on this in the future.
