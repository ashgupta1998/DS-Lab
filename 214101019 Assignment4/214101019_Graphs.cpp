#include <bits/stdc++.h>
#include <iostream>
//#include <stdio.h>

using namespace std;

//------------------------------------------------- Node Graph -------------------------------------------------------------------------------------------------
class Node{
    private:
        int value;                               //to store the key value of node
        int start;                               //to store start time of the node
        int finish;                              //to store finish time of the node
        int pred;                                //to store predecessor of the node
        vector <int> adjacent;
        Node(int k)
        {
            this->value = k;
            this->start = 0;
            this->finish = 0;
            this->pred = 0;
            

        }
    public:
        friend class Graph;
};

class Graph{

public:
    vector <Node*> adjList;
    int vertices;
    int edges;
    int time;
    vector <char>color;                              //to store color of each node ('w'->white,'b'->black,'g'->gray)
    Graph(int n,int m);
    void Read_Graph(const char *filename);
    void DFS();
    void DFS_visit(int u);
    void DFS_Print();
};

//-------------------------------------------------------------DFS-------------------------------------------------------------------------------------------------


Graph :: Graph(int n,int m)
{
    this->vertices = n;
    this->edges = m;
    this->time =0;
    vector <int> v;
    v.push_back(0);
    for(int i=0;i<=n;i++)
    {
        Node *node = new Node(i);
        adjList.push_back(node);
        color.push_back('w');                               //initializing each node with black color
        
    }

}

void Graph :: Read_Graph(const char *filename)
{
    FILE *fptr = fopen(filename,"r");
    char line [30] ="";
    fgets(line,30,fptr);
    int v1,v2,w;
    for(int i=1;i<=edges;i++)
    {
        fscanf(fptr, "%d %d %d",&v1,&v2,&w);
        adjList[v1]->adjacent.push_back(v2);                        //for u-v edge adding v to the adjacency list of u
        
    }
    fclose(fptr);
}

void Graph :: DFS()
{
    time = 0;
    for(int u = 1;u<=vertices;u++)
    {
        if(color[u] == 'w')
        {
            DFS_visit(u);                                              //calling dfs_visit on node u if its color is white i.e. not explored yet
        }
            
    }
    //DFS Finished
    cout<<"\n";
}

void Graph :: DFS_visit(int u)
{
    
    time = time +1;
    adjList[u]->start = time;                                           //setting start time
    color[u] = 'g';
    for(int v = 0;v < adjList[u]->adjacent.size();v++)
    {
        
         if(color[adjList[u]->adjacent[v]] == 'w')
         {
              adjList[adjList[u]->adjacent[v]]->pred = adjList[u]->value ;                     //setting predecessor of v = u
              DFS_visit(adjList[u]->adjacent[v]) ;                      //calling dfs_visit on node v
         }
         
    }
    color[u] = 'b';                                                     //setting color to black
    time = time + 1;                            
    adjList[u]->finish = time;                                          //setting finish time

}

void Graph :: DFS_Print()
{
    FILE *filename = fopen("dfs.dot","w");
	fprintf(filename, "digraph DFS {\n");
    fprintf(filename, "    node [fontname=Arial , shape = circle];\n");
    if(vertices == 0)
    {
        cout<<"Empty Graph\n";
    }
    else
    {
        
        for(int v = 1;v<=vertices;v++)
        {
                fprintf(filename,"%d[label = \"%d | s: %d | f: %d\"];\n",v,v,adjList[v]->start,adjList[v]->finish);
                
        }
        for(int u = 1;u<=vertices;u++)
        {
            for(int v = 0;v<adjList[u]->adjacent.size();v++)
            {
                string type;
                if( adjList[u]->start < adjList[adjList[u]->adjacent[v]]->start  &&  adjList[adjList[u]->adjacent[v]]->finish < adjList[u]->finish)
                   {
                       type = "forward/tree";
                       if(adjList[adjList[u]->adjacent[v]]->pred == u)
                            fprintf(filename,"%d -> %d[label = tree color =\"red\"];",u,adjList[u]->adjacent[v]);					//if pred = u then tree edge
                        else 
                            fprintf(filename,"%d -> %d[label = forward color =\"yellow\"];",u,adjList[u]->adjacent[v]);				//if pred != u then forward edge
                   } 
                   else if(adjList[u]->start >= adjList[adjList[u]->adjacent[v]]->start  &&  adjList[adjList[u]->adjacent[v]]->finish >= adjList[u]->finish)
                   {
                        type = "back";
                        fprintf(filename,"%d -> %d[label = back color = \"blue\"];",u,adjList[u]->adjacent[v]);
                   }
                   
                   else{
                       type = "cross";
                       fprintf(filename,"%d -> %d[label = cross color = \"green\"];",u,adjList[u]->adjacent[v]);
                   }
            }
        }
            
    }
    fprintf(filename, "}\n");
    fclose(filename);
    cout<<"** Printing Graph Please close the dfs.svg window to continue furhter **\n\n";
	system("dot -Tsvg dfs.dot -o dfs.svg");
   	system("dfs.svg");
} 

//------------------------------------------------------------TARJAN----------------------------------------------------------------------------------

class Node_tarjan{
    private:
        int key;                                //to store the key value of the node
        int id;                                 //assigned while performing dfs 
        int low;                                //stores minimum id of the node reachable from the node 
        vector <int> adjacent;
        Node_tarjan(int k)
        {
            this->key = k;
            this->id = 0;
            this->low = 0;
        }
    public:
        friend class Graph_tarjan;
};

class Graph_tarjan
{

public:
    vector <Node_tarjan*> adjList;
    int vertices;
    int edges;
    int id_value;
    int SCC;

    vector <bool>in_seen;                               //denotes node present in stack or not
    vector <bool> processed;                            //denotes node visited/processed or not
    stack <int> st;

    Graph_tarjan(int n,int m);
    void Read_Graph(const char *filename);
    void Compute_SCC();
    void SCC_DFS(int u);
    void SCC_Print();
};

Graph_tarjan :: Graph_tarjan(int n,int m)
{
    this->vertices = n;
    this->edges = m;
    this->id_value = 0;
    this->SCC = 0;
    for(int i=0;i<=n;i++)
    {
        Node_tarjan *node = new Node_tarjan(i);                                 //initiliasing required arrays
        adjList.push_back(node);
        in_seen.push_back(false);
        processed.push_back(false);
    }

}

void Graph_tarjan :: Read_Graph(const char *filename)
{
    FILE *fptr = fopen(filename,"r");
    char line [30] ="";
    fgets(line,30,fptr);
    int v1,v2,w;
    
    for(int i=1;i<=edges;i++)
    {
        fscanf(fptr, "%d %d %d",&v1,&v2,&w);
        adjList[v1]->adjacent.push_back(v2);
    }
    fclose(fptr);
    cout<<"\n";
}

void Graph_tarjan :: Compute_SCC()
{
    for(int i =1;i<=vertices;i++)
    {
        if(processed[i] == false)
        {
            SCC_DFS(i);                                             //Call to SCC_DFS
        }
    }
    cout<<"Total number of SCC = "<<SCC<<"\n\n";
}

void Graph_tarjan :: SCC_DFS(int u)
{
    in_seen[u] = true;                                              //as node pushed in stack so in_seen is set to true
    st.push(u);
    id_value++;
    adjList[u]->id = adjList[u]->low = id_value;
    processed[u] = true;                                            //set processed of node to true as it is now being processed
    
    for(int v =0;v<adjList[u]->adjacent.size();v++)
    {
        if(processed[adjList[u]->adjacent[v]] == false)
        {
            SCC_DFS(adjList[u]->adjacent[v]);                               // call to SCC_DFS on its neighbour if not processed 
        }
        if(in_seen[adjList[u]->adjacent[v]] == true)
        {
            adjList[u]->low = min(adjList[u]->low , adjList[adjList[u]->adjacent[v]]->low);     //update low value to min of previous and its neighboured just explored
        }
    }
    
    if(adjList[u]->id == adjList[u]->low)                           //id = low indicates that one SCC is found 
    {
        int node ;
        cout<<"Node(s) in SCC "<<SCC+1<<" are : ";
        do
        {
            
            node = st.top();
            cout<<adjList[node]->key<<" ";
            st.pop();
            in_seen[node] = false;                              //as node popped off stack thus in_seen is set to false
            adjList[node]->low = adjList[u]->id;                //set low to id of the u node
            
        }while(node != u);
        cout<<"\n\n";
        SCC++;
    }
    
   
}

void Graph_tarjan :: SCC_Print()
{
    FILE *filename = fopen("scc.dot","w");
	fprintf(filename, "digraph TARJAN {\n");
    fprintf(filename, "    node [fontname=Arial , shape = circle];\n");
    if(vertices == 0)
    {
        cout<<"Empty Graph\n";
    }
    else
    {
        
        for(int v = 1;v<=vertices;v++)
        {
                fprintf(filename,"%d[label = \"%d |  low: %d\"];\n",v,v,adjList[v]->low);
                
        }
        for(int u = 1;u<=vertices;u++)
        {
            for(int v = 0;v<adjList[u]->adjacent.size();v++)
            {
                fprintf(filename,"%d -> %d;",adjList[u]->key,adjList[u]->adjacent[v]);
            }
        }
    }
    fprintf(filename, "}\n");
    fclose(filename);
    cout<<"** Printing Graph Please close the scc.svg window to continue furhter **\n\n";
	system("dot -Tsvg scc.dot -o scc.svg");
   	system("scc.svg");
}

//--------------------------------------------------------COMPONENT--------------------------------------------------------------------------------

class Node_comp{
    private:
        int key;
        int id;
        int low;
        vector <int> adjacent;
        Node_comp(int k)
        {
            this->key = k;
            this->id = 0;
            this->low = 0;
        }
    public:
        friend class Graph_comp;
};

class Graph_comp
{

public:
    vector <Node_comp*> adjList;
    vector <Node_comp*> adjList_Rev;
    int vertices;
    int edges;
    int id_value;
    int SCC;

    vector <bool>in_seen;                               //denotes node present in stack or not
    vector <bool> processed;                            //denotes node visited/processed or not
    stack <int> st;
    vector<vector<int>>scc_nodes;
    vector<int>belongs_to;
    vector<int>indegree;
    vector<vector<int>>a;
    vector<vector<int>>b;
    

    Graph_comp(int n,int m);
    void Read_Graph(const char *filename);
    void Compute_SCC();
    void SCC_DFS(int u);
    void SCC_Print();
    void Revised_Adjacency(Graph_comp *g);
    void Component_Print();
    void revise(Graph_comp *g);
    void incomponent();
    bool reachable(int u,int v);
    void New_Print();
};

Graph_comp :: Graph_comp(int n,int m)
{
    this->vertices = n;
    this->edges = m;
    this->id_value = 0;
    this->SCC = 0;
    for(int i=0;i<=n;i++)
    {
        Node_comp *node = new Node_comp(i);                                      //initializing arrays
        adjList.push_back(node);
        adjList_Rev.push_back(node);
        in_seen.push_back(false);
        processed.push_back(false);
        belongs_to.push_back(0);
    }
    for(int i=0;i<=n;i++)
    {
        vector<int>h;
        for(int j=0;j<=n;j++)
        {
            h.push_back(0);
        }
        b.push_back(h);
    }

}

void Graph_comp :: Read_Graph(const char *filename)
{
    FILE *fptr = fopen(filename,"r");
    char line [30] ="";
    fgets(line,30,fptr);
    int v1,v2,w;
    
    for(int i=1;i<=edges;i++)
    {
        fscanf(fptr, "%d %d %d",&v1,&v2,&w);
        
        adjList[v1]->adjacent.push_back(v2);
    }
    fclose(fptr);
    cout<<"\n\n";
}

void Graph_comp ::  Revised_Adjacency(Graph_comp *g)
{
    for(int i=0;i<=g->SCC;i++)
    {
        indegree.push_back(0);
    }

    //"Checking if graph is semi connected or not"
    //cout<<"Edges in condensation graph are: \n\n";
    


    for(int i=1;i<=g->SCC;i++)
    {
        
        set <int> ad;
        for (int j = 1; j<g->scc_nodes[i].size();j++)
        {
            
            int n = g->scc_nodes[i][j];
            
            
            for(int k=0;k<g->adjList[n]->adjacent.size();k++)
            {
                
                if(g->belongs_to[g->adjList[n]->adjacent[k]] != g->belongs_to[n])        //edge from onde component to another
                {
                    
                    ad.insert(g->belongs_to[g->adjList[n]->adjacent[k]]);
                    indegree[g->belongs_to[g->adjList[n]->adjacent[k]]] += 1;           //increment indegree of the node component
                }

            }
        }
        
        for(auto y:ad)
            {
                
                adjList[i]->adjacent.push_back(y);
                //cout<<"edge : "<<i<<" -> "<<y<<"\n";

            }

    }
        
    cout<<"\n\n";

}




void Graph_comp :: revise(Graph_comp *g)
{
    
    //initialising is_edge array 

    vector<vector<bool>>is_edge;
    
    
    for(int i=0;i<=g->SCC;i++)
    {
        
        vector<bool>ed;
        for(int j=0;j<=g->SCC;j++)
        {
            ed.push_back(false);
            
        }
            is_edge.push_back(ed);
    }

    
    //copying belongs_to array
    for(int i=0;i<=vertices;i++)
    {
        belongs_to[i] = g->belongs_to[i];
    }
    
    //  initializing a matrix to store the edges going between two components

    //"\ninitialising a of g3

    for(int i=0;i<=vertices;i++)
    {
        vector<int>h;
        for(int j=0;j<=vertices;j++)
        {
            h.push_back(0);  
        }
        a.push_back(h);
        
    }


    //adding intercomponenet edges
    //for each node u  checking its adjacent v
    //if node u belongs to component a and node v to component b
    //then if no edge has been added from a to b compoenent then this edge is included  else not


    
    for(int i=1;i<=vertices;i++)
    {
        for(int j=0;j<adjList[i]->adjacent.size();j++)
        {
            
            if(belongs_to[adjList[i]->key] != belongs_to[adjList[i]->adjacent[j]])
            {
                if(is_edge[belongs_to[adjList[i]->key]][belongs_to[adjList[i]->adjacent[j]]] == false )
                {
                        a[adjList[i]->key][adjList[i]->adjacent[j]] = 1;
                        is_edge[belongs_to[adjList[i]->key]][belongs_to[adjList[i]->adjacent[j]]] = true;
                }
            }
        }
    }

    

    SCC = g->SCC;
    scc_nodes = g->scc_nodes;
  
}


bool Graph_comp :: reachable(int u,int v)
{
  //performing bfs

    bool flag = false;
    vector<bool>in_q;
    
    for(int i=0;i<=vertices;i++)
    {
        in_q.push_back(false);
    }
    queue <int> q;
    q.push(u);
    in_q[u] = true;
    while(!q.empty() && flag == false)
    {
        int n = q.front();
        q.pop();
        if(n == v)                                      //if n = v that means another path exists from u to v
        {
            flag = true;                    
            return flag;                                //return flag = true
        }
        else
        {
            for(int i=1;i<=vertices;i++)
            {
                if(b[n][i] == 1 && in_q[i] == false)                //if n is not equal to v then push it into the queue and iterate again
                {
                    q.push(i);
                    in_q[i] = true;
                }
            }
            
        }
    }

    return flag;

}

void Graph_comp :: incomponent()
{
    
    //initialising b matrix
    //if edge exists then set bit as 1
    for(int i=1;i<=vertices;i++)
    {
        for(int j=0;j<adjList[i]->adjacent.size();j++)
        {
            b[i][adjList[i]->adjacent[j]] = 1;
        }
    }
    

   //removing edges between two distinct components
    for(int i=1;i<=SCC;i++)
    {
        for(int j=1;j<scc_nodes[i].size();j++)
        {
            int n = scc_nodes[i][j];
            for(int k=0;k<adjList[n]->adjacent.size();k++)
            {
                if(belongs_to[n] != belongs_to[adjList[n]->adjacent[k]])
                    b[n][adjList[n]->adjacent[k]] = 0;
            }
            
        }
        
    }

//checking if a particular edge in a SCC is a stron bridge or not
//An Edge is a strong bridge if its removal increases the number of Strongly Connected Components
//For each SCC each node u and its adjacent node v
//edge (u,v) is removed 
//then reachable function is called from u to v and from v to u
//if output of any reachble is false then it means no another path exists between u and v 
//so we need to compulsorily consider (u,v) edge 



    for(int i=1;i<=SCC;i++)
    {
        for(int j=1;j<scc_nodes[i].size();j++)
        {
            int n = scc_nodes[i][j];
            for(int k=0;k<adjList[n]->adjacent.size();k++)
            {
                if(b[n][adjList[n]->adjacent[k]] == 1)
                {
                    b[n][adjList[n]->adjacent[k]] = 0;

                    bool flag1 = reachable(n,adjList[n]->adjacent[k]);      //flag1 = true indicates that another path exists
                    bool flag2 = reachable(adjList[n]->adjacent[k],n);      //flag2 = true indicates that another path exists

                    if(flag1 == false || flag2 == false)                    //if either of them is false then SCC condition is voilated on removal of edge u,v
                    {
                            b[n][adjList[n]->adjacent[k]] = 1;              //add edge u,v again
                    }

                }
            }
        }

    }

    cout<<"\n";

}



void Graph_comp :: Compute_SCC()
{
    
    for(int i =1;i<=vertices;i++)
    {
        if(processed[i] == false)
        {
            SCC_DFS(i);
        }
    }
    cout<<"Total number of SCC = "<<SCC<<"\n\n"; 
      
    
}

void Graph_comp :: SCC_DFS(int u)
{
    vector <int> v;
    v.push_back(0);
    scc_nodes.push_back(v);
    in_seen[u] = true;
    st.push(u);
    id_value++;
    adjList[u]->id = adjList[u]->low = id_value;
    processed[u] = true;
    
    for(int v =0;v<adjList[u]->adjacent.size();v++)
    {
        if(processed[adjList[u]->adjacent[v]] == false)
        {
            SCC_DFS(adjList[u]->adjacent[v]);                               // call to SCC_DFS on its neighbour if not processed 
        }
        if(in_seen[adjList[u]->adjacent[v]] == true)
        {
            adjList[u]->low = min(adjList[u]->low , adjList[adjList[u]->adjacent[v]]->low);
        }
    }
    
    if(adjList[u]->id == adjList[u]->low)
    {
        int node ;
        cout<<"Node(s) in SCC "<<SCC+1<<" are : ";
        do
        {
            node = st.top();
            cout<<adjList[node]->key<<" ";
            scc_nodes[SCC+1].push_back(adjList[node]->key);
            st.pop();
            in_seen[node] = false;
            adjList[node]->low = adjList[u]->id;
            belongs_to[adjList[node]->key] = SCC+1;
            
            
        }while(node != u);
        cout<<"\n\n";
        SCC++;
    }
    
   
   
}



void Graph_comp :: Component_Print()
{
    //to print component graph
    FILE *filename = fopen("semiconnected.dot","w");
	fprintf(filename, "digraph SEMI_CONNECTED {\n");
    fprintf(filename, "    node [fontname=Arial , shape = circle];\n");
    if(vertices == 0)
    {
        cout<<"Empty Graph\n";
    }
    else
    {
        
        for(int v = 1;v<=vertices;v++)
        {
                fprintf(filename,"%d[label = \" component %d\"];\n",v,v);
                
        }
        for(int u = 1;u<=vertices;u++)
        {
            for(int v = 0;v<adjList[u]->adjacent.size();v++)
            {
                fprintf(filename,"%d -> %d;",adjList[u]->key,adjList[u]->adjacent[v]);
            }
        }
    }
    fprintf(filename, "}\n");
    fclose(filename);
    cout<<"** Please close the semiconnected.svg window to continue furhter **\n";
	system("dot -Tsvg semiconnected.dot -o semiconnected.svg");
   	system("semiconnected.svg");
}


void Graph_comp :: New_Print()
{
    //to print minimised graph

    FILE *filename = fopen("comp.dot","w");
	fprintf(filename, "digraph MINI_GRAPH {\n");
    fprintf(filename, "    node [fontname=Arial , shape = circle];\n");
    if(vertices == 0)
    {
        cout<<"Empty Graph\n";
    }
    else
    {
        
        for(int v = 1;v<=vertices;v++)
        {
                fprintf(filename,"%d[label = \"%d\"];\n",v,v);
                
        }
        for(int u = 1;u<=vertices;u++)
        {
            for(int v = 1;v<=vertices;v++)
            {
                    if(a[u][v] == 1)
                    {
                        fprintf(filename,"%d->%d;\n",u,v);
                    }
                    else if(b[u][v] == 1)
                    {
                        fprintf(filename,"%d->%d;\n",u,v);
                    }
            }
        }
    }
            
fprintf(filename, "}\n");
    fclose(filename);
    cout<<"** Please close the comp.svg window to continue furhter **\n";
	system("dot -Tsvg comp.dot -o comp.svg");
   	system("comp.svg");

    

}


//---------------------------------------------------------SEMI-CONNECTED--------------------------------------------------------------------------

class Node_semi{
    private:
        int key;
        int id;
        int low;
        vector <int> adjacent;
        Node_semi(int k)
        {
            this->key = k;
            this->id = 0;
            this->low = 0;
        }
    public:
        friend class Graph_semi;
};

class Graph_semi
{

public:
    vector <Node_semi*> adjList;
    vector <Node_semi*> adjList_Rev;
    int vertices;
    int edges;
    int id_value;
    int SCC;

    vector <bool>in_seen;                               //denotes node present in stack or not
    vector <bool> processed;                            //denotes node visited/processed or not
    stack <int> st;
    vector<vector<int>>scc_nodes;
    vector<int>belongs_to;                              //denotes the SCC to which node belongs
    vector<int>indegree;                                //to maintain the the number of incoming edges in a component

    Graph_semi(int n,int m);
    void Read_Graph(const char *filename);
    void Compute_SCC();
    void SCC_DFS(int u);
    void SCC_Print();
    void Revised_Adjacency(Graph_semi *g);
    void Component_Print();
};

Graph_semi :: Graph_semi(int n,int m)
{
    this->vertices = n;
    this->edges = m;
    this->id_value = 0;
    this->SCC = 0;
    for(int i=0;i<=n;i++)
    {
        Node_semi *node = new Node_semi(i);                 //initialising arrays
        adjList.push_back(node);
        in_seen.push_back(false);
        processed.push_back(false);
        belongs_to.push_back(0);
    }

}

void Graph_semi :: Read_Graph(const char *filename)         //reading graph
{
    FILE *fptr = fopen(filename,"r");
    char line [30] ="";
    fgets(line,30,fptr);
    int v1,v2,w;
    
    for(int i=1;i<=edges;i++)
    {
        fscanf(fptr, "%d %d %d",&v1,&v2,&w);
        adjList[v1]->adjacent.push_back(v2);
    }
    fclose(fptr);
    cout<<"\n\n";
}

void Graph_semi ::  Revised_Adjacency(Graph_semi *g)
{
    //this function generates the new adjacency list for the component graph and prints the edges

    for(int i=0;i<=g->SCC;i++)
    {
        indegree.push_back(0);
    }

    cout<<"Checking if graph is semi connected or not \n"<<endl;
    cout<<"Edges in condensation graph are: \n\n";
    


    for(int i=1;i<=g->SCC;i++)
    {
        set <int> ad;
        for (int j = 1; j<g->scc_nodes[i].size();j++)
        {
            
            int n = g->scc_nodes[i][j];
            
            
            for(int k=0;k<g->adjList[n]->adjacent.size();k++)
            {
                
                if(g->belongs_to[g->adjList[n]->adjacent[k]] != g->belongs_to[n])
                {
                    ad.insert(g->belongs_to[g->adjList[n]->adjacent[k]]);                       //add edge between component
                    indegree[g->belongs_to[g->adjList[n]->adjacent[k]]] += 1;                   //incrementing indegree
                }

            }
        }
        
        for(auto y:ad)
            {
                
                adjList[i]->adjacent.push_back(y);
                cout<<"edge : "<<i<<" -> "<<y<<"\n";

            }

    }
    
    

    //the component graph (where nodes are the components) will not contain any cycle
    //so if more than one component node has indegree = 0 i.e. no incoming edge 
    //then it means that there are atleast two component a and b which are not reachable a->b or b->a
    //hence the nodes belonging to these components are also not reachable 
    //hence graph is not semi connected
    
    int count = 0;
    
    for(int i=1;i<indegree.size();i++)
    {
        if(indegree[i] == 0)
        {
            count++;
        }
    }
    cout<<"-------------------------------------------------------------------------------------------------------------------------------------------\n";
    if(count == 1)
    {
        cout<<"\nTHE INPUTTED GRAPH IS SEMI CONNECTED";
    }
    else{
        cout<<"\nTHE INPUTTED GRAPH IS NOT SEMI CONNECTED";
    }
        
    cout<<"\n\n";

}

void Graph_semi :: Compute_SCC()
{
    
    for(int i =1;i<=vertices;i++)
    {
        if(processed[i] == false)
        {
            SCC_DFS(i);
        }
    }
    cout<<"Total number of SCC = "<<SCC<<"\n\n";   
    
}

void Graph_semi :: SCC_DFS(int u)
{
    vector <int> v;
    v.push_back(0);
    scc_nodes.push_back(v);
    in_seen[u] = true;
    st.push(u);
    id_value++;
    adjList[u]->id = adjList[u]->low = id_value;
    processed[u] = true;
    
    for(int v =0;v<adjList[u]->adjacent.size();v++)
    {
        if(processed[adjList[u]->adjacent[v]] == false)
        {
            SCC_DFS(adjList[u]->adjacent[v]);                               // call to SCC_DFS on its neighbour if not processed 
        }
        if(in_seen[adjList[u]->adjacent[v]] == true)
        {
            adjList[u]->low = min(adjList[u]->low , adjList[adjList[u]->adjacent[v]]->low);
        }
    }
    
    if(adjList[u]->id == adjList[u]->low)
    {
        int node ;
        cout<<"Node(s) in SCC "<<SCC+1<<" are : ";
        do
        {
            node = st.top();
            cout<<adjList[node]->key<<" ";
            scc_nodes[SCC+1].push_back(adjList[node]->key);
            st.pop();
            in_seen[node] = false;
            adjList[node]->low = adjList[u]->id;
            belongs_to[adjList[node]->key] = SCC+1;
            
            
        }while(node != u);
        cout<<"\n\n";
        SCC++;
    }
    
   
   
}



void Graph_semi :: Component_Print()
{
    //to print component graph
    FILE *filename = fopen("semiconnected.dot","w");
	fprintf(filename, "digraph SEMI_CONNECTED {\n");
    fprintf(filename, "    node [fontname=Arial , shape = circle];\n");
    if(vertices == 0)
    {
        cout<<"Empty Graph\n";
    }
    else
    {
        
        for(int v = 1;v<=vertices;v++)
        {
                fprintf(filename,"%d[label = \" component %d\"];\n",v,v);
                
        }
        for(int u = 1;u<=vertices;u++)
        {
            for(int v = 0;v<adjList[u]->adjacent.size();v++)
            {
                fprintf(filename,"%d -> %d;",adjList[u]->key,adjList[u]->adjacent[v]);
            }
        }
    }
    fprintf(filename, "}\n");
    fclose(filename);
    cout<<"** Please close the semiconnected.svg window to continue furhter **\n";
	system("dot -Tsvg semiconnected.dot -o semiconnected.svg");
   	system("semiconnected.svg");
}


//---------------------------------------------------------DIJKSTRA---------------------------------------------------------------------------------

class Node_dijkstra{
    private:
        int key;                                  //to store key value of the node
        int dis;                                  //to store distance of the node from source vertex
        int pred;                                 //to store predecessor of the node
        vector <int> adjacent;
        Node_dijkstra(int k)
        {
            this->key = k;
            this->dis = 100000000;
            this->pred = 0;
        }
    public:
        friend class Graph_dijkstra;
};

class Graph_dijkstra
{

public:
    vector <Node_dijkstra*> adjList;
    int vertices;
    int edges;
    int s;
    vector<vector<int>> weight;                     //to store weights
    vector<bool>in_queue;                           //to know whether the node is present in the queue or not                              
    vector<int>processed;                           //to know if the node is processed or not
    vector <Node_dijkstra*> nodes;
    bool great(Node_dijkstra node1,Node_dijkstra node2);              //comparator function
    Graph_dijkstra(int n,int m);
    void Read_Graph(const char *filename);
    void Dijkstra();
    void relax(int u,int v);
    void Print();
};

Graph_dijkstra :: Graph_dijkstra(int n,int m)
{
    this->vertices = n;
    this->edges = m;

    for(int i=0;i<=n;i++)
    {
        Node_dijkstra *node = new Node_dijkstra(i);
        nodes.push_back(node);
        adjList.push_back(node);
        weight.push_back(node->adjacent);
        in_queue.push_back(false);                      //initializing in queue with false
        
    }
}

void Graph_dijkstra :: Read_Graph(const char *filename)
{
    FILE *fptr = fopen(filename,"r");
    char line [30] ="";
    fgets(line,30,fptr);
    int v1,v2,w;
    char c;
    for(int i=1;i<=edges;i++)
    {
        
        fscanf(fptr, "%d %d %d" ,&v1,&v2,&w);
        //cout<<"\nEdge "<<i<<" : "<<v1<<" -> "<<v2<<" weight : "<<w<<"\n\n";
        adjList[v1]->adjacent.push_back(v2);
        weight[v1].push_back(w);
    }
    
    cout<<"\n\n";
    fclose(fptr);
    
}

void Graph_dijkstra :: relax(int u,int v)
{
    if(adjList[v]->dis > (adjList[u]->dis + weight[u][v]))                  //checking if the  current distance is greater or not            
    {
        adjList[v]->dis = adjList[u]->dis + weight[u][v];                   //update distance if current distance is greater
        adjList[v]->pred = u;                                               //set predecessor if v to u
    }
}



void Graph_dijkstra :: Dijkstra()
{
    
    cout<<"Enter the source vertex: ";
    cin>>s;
    adjList[s]->dis=0;
    
    processed.push_back(0);
    processed.push_back(s);
    in_queue[s] = true;

    auto comp = [](Node_dijkstra node1, Node_dijkstra node2) {                                //comparator lambda function for comparison function in priority queue
        if (node1.dis > node2.dis)                                          //for each node comparison done using distance value
            return true;
        else
        { 
            return false;
        }
    };
    
    
    priority_queue<Node_dijkstra,vector<Node_dijkstra>,decltype(comp)> q(comp);

    q.push(*nodes[s]);
    /*for(int i=1;i<=vertices;i++)
    {
        q.push(*nodes[i]);
    }*/
    while(q.size()>0)
    {
        int  node = q.top().key;
        processed.push_back(node);                                          //extracting node with min dis value
        in_queue[node] = true;                                              //as node present in the queue so set in_queue of the node to true
        q.pop();
        int u = node;
        for(int i =0;i<adjList[u]->adjacent.size();i++)
        {
            int v = adjList[u]->adjacent[i];
            if(adjList[v]->dis > (adjList[u]->dis + weight[u][i]))          //for each node adjacent to node u check if relaxation is possible or not
            {
            Node_dijkstra *temp = nodes[adjList[u]->adjacent[i]];
            adjList[v]->dis = adjList[u]->dis + weight[u][i];
            adjList[v]->pred = u;
            if(in_queue[temp->key] == false)                                //if node is not present in the queue then add it to the queue
               {
                   q.push(*temp);
                   in_queue[temp->key] = true;
               } 
            //cout<<"node "<<v<<" pred is "<<u<<" dis is : "<<adjList[v]->dis<<" weight: "<<weight[u][i]<<endl;
            
    }

            
        }
    }

}

void Graph_dijkstra :: Print()
{
    FILE *filename = fopen("dijkstra.dot","w");
	fprintf(filename, "digraph Dijkstra {\n");
    fprintf(filename, "    node [fontname=Arial , shape = circle];\n");
    if(vertices == 0)
    {
        cout<<"Empty Graph\n";
    }
    else
    {
        
        for(int v = 1;v<=vertices;v++)
        {
                fprintf(filename,"%d[label = \"%d |  dis: %d | pred: %d \"];\n",v,v,adjList[v]->dis,adjList[v]->pred);
        }
        for(int i = 1;i<=vertices;i++)
       {
           if(i!=s && adjList[i]->pred!=0 )
    	    fprintf(filename,"%d -> %d [label = %d];\n",adjList[i]->pred,i,adjList[i]->dis-adjList[adjList[i]->pred]->dis);

	   }
        
    }
    fprintf(filename, "}\n");
    fclose(filename);
    cout<<"** Printing Graph Please close the dijkstra.svg window to continue furhter **\n\n";
	system("dot -Tsvg dijkstra.dot -o dijkstra.svg");
   	system("dijkstra.svg");

}








//------------------------------------------------------------MAIN FUNCTION--------------------------------------------------------------------------



int main()
{
    cout<<endl;
    int n,e;
    //const char *filename = "input_graph.txt";
    string str;
    cout<<"Enter the filename (eg. input.txt) : ";
    cin>>str;
    cout<<"\n";
    const char *filename = str.c_str();                             //reading the graph
    FILE *fptr = fopen(filename,"r");
    fscanf(fptr, "%d ",&n);
    cout<<"Number of vertices are : "<<n<<"\n";
    fscanf(fptr," %d ",&e);
    cout<<"\nNumber of edges are : "<<e<<"\n";
    fclose(fptr);
    
    int choice;
    
    do
    {
        cout<<"\n___________________________________________________________________________________________________________________________________\n";
        cout<<"\nEnter a choice: \n";
        cout<<"1. DFS 2. Tarjan 3. Component 4. Semi-Connected 5. Dijkstra 6. Exit => ";
        cin>>choice;
        cout<<"Entered choice is : "<<choice<<endl;
        switch (choice)
        {
        case 1:
            {
            cout<<"\nImplementing DFS\n";
            Graph * dfsg = new Graph(n,e);
             dfsg->Read_Graph(filename);
             dfsg->DFS();                                           //call to obtain dfs traversasl
             dfsg->DFS_Print();                                     //printing dfs traversal
             cout<<"\nDfs Done\n";
            break;
            }
        case 2:
        {
            cout<<"\nImplementing Tarjan\n";
            Graph_tarjan *gtarjan = new Graph_tarjan(n,e);
            gtarjan->Read_Graph(filename);                            
            gtarjan->Compute_SCC();                                   //call to compute the SCCs
            gtarjan->SCC_Print();                                     //printing the graph with low id of each node 
            cout<<"\nTarjan Done\n";
            break;
        }
        case 3:
        {
            cout<<"\nImplementing Component Graph and Minimisation\n";
            Graph_comp *gcomp = new Graph_comp(n,e);
            gcomp->Read_Graph(filename);
            gcomp->Compute_SCC();
            //cout<<"-------------------------------------------------------------------------------------------------------------------------------------------\n";
            
            Graph_comp *gccomp = new Graph_comp(gcomp->SCC,gcomp->SCC-1);
            gccomp->Revised_Adjacency(gcomp); 
            //cout<<"-------------------------------------------------------------------------------------------------------------------------------------------\n";
            gccomp->Component_Print();                                  //printing component graph

            Graph_comp *g3comp = new Graph_comp(n,e);
            g3comp->Read_Graph(filename);
            g3comp->revise(gcomp);
            g3comp->incomponent();                                          //calling incomponent
            g3comp->New_Print();
            

            cout<<"Component Graph and Minimised Graph Done\n";
            break;
        }
        case 4:
        {
            cout<<"\nImplementing Semi Connected\n";
            Graph_semi *gsemi = new Graph_semi(n,e);
            gsemi->Read_Graph(filename);                                        
            gsemi->Compute_SCC();                                               //call to compute SCC
            cout<<"-------------------------------------------------------------------------------------------------------------------------------------------\n";
            Graph_semi *gcsemi = new Graph_semi(gsemi->SCC,gsemi->SCC-1);
            gcsemi->Revised_Adjacency(gsemi); 
            cout<<"-------------------------------------------------------------------------------------------------------------------------------------------\n";
            gcsemi->Component_Print();                                          //printing component graph
            cout<<"\nSemiConnected Done\n";
            break;
        }
        case 5:
        {
            cout<<"\nImplementing Dijkstra\n";
            Graph_dijkstra *gdijkstra = new Graph_dijkstra(n,e);
            gdijkstra->Read_Graph(filename);                                    
            gdijkstra->Dijkstra();                                              //call to dijkstra function
            gdijkstra->Print();                                                 //printing shortest paths of each node from source s
            cout<<"\nDijkstra Done\n";
            break;
        }
        case 6:
        {
            cout<<"Exiting...\n";                                               //exit
            exit;
            break;
        }
        
        default:
            {
                cout<<"Incorrect Choice"<<endl;
                break;
            }
        
    }
    }while(choice!=6);
    

}









