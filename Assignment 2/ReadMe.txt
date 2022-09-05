Steps:
 1. Open the cpp file in Dev C++
 2. Run the cpp file
 3. You will be prompted with message "Enter 1.Search 2. Insert 3.Delete 4.Print "
 4. Enter the key accordingly and perform the respective opertion
 5. You will then be prompted with message Start (y/n):
 6. Enter y to contiue and n to end.

How to print Tree:
 1. When you select operation 4 i.e. Print then avl1.dot file be generated.
 2. Locate the file location (say Location_file) of avl1.dot in your system. 
 3. Also locate the location where dot.exe is located in your pc(say Location_graphviz).
 4. Run the following command with given format in command prompt.
 5. "Location_graphviz" -Tpng Location_file -o Location_file\avl1.png
 6. Eg. "C:\Program Files\Graphviz\bin\dot.exe" -Tpng C:\Users\aishw\OneDrive\Desktop\avl1.dot -o C:\Users\aishw\OneDrive\Desktop\avl1.png
 7. avl1.png Png file will be generated open it to view the tree.   