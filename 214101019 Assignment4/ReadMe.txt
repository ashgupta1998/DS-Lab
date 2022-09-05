				214101019
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

IMPORTANT: **Auto is not supported in dev cpp sometimes so please follow the following steps before running the code file
	   In DevCpp 
	   	1. Go to Tools -> Compiler Options
	   	2. Check the checkbox labelled, "Add the following commands when calling the compiler" And add in the text entry box, "-std=c++11" or if that doesn't work "-std=c++0x"
	   	3. Donot include " " example only type -std=c++11 in the text entry box 
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Steps to execute:

	1. Open the 214101019_Graphs.cpp 
	2. Run the code
	3. You will be prompted to enter the file name
	4. Enter the filename like input.txt (**INCLUDE .txt IN THE FILE NAME)
	5. Now you will get a Menu consiting of 6 choices 
	6. Enter the anyone choice and view the result
	7. Select choice 6 to exit

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
NOTE:   **If using DevCpp for evaluation then please perform the steps mentioned in IMPORTANT previously or else if using some other
		 IDE then please ensure that it supports auto variable usage  
	**After selecting any particular choice from the menu its corresponding output graph will by default get printed
        **After .svg window opens Please close the window to continue the code further as sometimes window os does not allow the execution of 
		the code if .svg file generated from the code is still open
	**ALL GRAPHS ARE CONSIDERED TO BE SIMPLE GRAPH 
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      
INPUT OUTPUT FORMAT:

5 test case files are provided in the folder namely graph1.txt,graph2.txt,graph3.txt,graph4.txt,graph5.txt

1. For Dfs 
	Graphviz output will be printed; each node has s: as start time and f:as finish time; edges are classified using colors and labels

2. For Tarjan
	All SCCs with corresponding nodes in it will be printed in the console
	Total number of SCCs will be printed will be printed in the console
	Graphviz output will be printed; each node has its key value and low value; Those nodes with same low value are in same SCC

3. For Component and Minimised Graph
	All SCCs with corresponding nodes in it will be printed in the console
	Total number of SCCs will be printed in the console
	Component Graph will be printed where each node corresponds to a component 
	** When the above .svg window is closed then Minimised Graph .svg window will be opened

4. SemiConnected
	All SCCs with corresponding nodes in it will be printed in the console
	Total number of SCCs will be printed will be printed in the console
	Whether the inputted graph is semiconnected or not will be printed in the console
	Component Graph will be printed where each node corresponds to a component 

5. Dijkstra
	You will be prompted to enter the source vertex
	After entering the source vertex the graphviz output will be generated
	Each node in the graphviz will contain its key value,its distance from the source,its predecessor
	Default predecessor of the source node and that of the nodes not reachable from the source nodes is 0 
	Distance of the nodes not reachable from the source node is some large value (here 10000000)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	

	 
      
      
      
      