#include <bits/stdc++.h>
using namespace std;

class Graph{
	public:
		int graph[50][50] ;
		int weight[50][50] ;
		int pred[50];
		int vertices[50];
		int dis[50];
		char color[50];
		int n,e;
		void construct_graph();
		void initialize_source(int s);
		void relax(int u,int v);
		void sp_dfs(int u);
		bool neg_cycle(int u);
		void print();	
};

void Graph :: construct_graph()
{
	
	cout<<"Enter number of vertices: ";
	cin>>n;
	cout<<"\nEnter number of edges: ";
	cin>>e;
	int v1,v2,w;
	int i=0,j=0;
	/*for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			graph[i][j] = 0;
			weight[i][j] = INT_MAX;
		}
		cout<<endl;
	}*/
	cout<<"\n\n";
	for(i=0;i<e;i++)
	{
		cout<<"Enter v1 v2 w(v1,v2) : ";
		cin>>v1>>v2>>w;
		graph[v1][v2] = 1;
		weight[v1][v2] = w;
	}
	/*
	cout<<"Graph matrix is : \n";
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cout<<graph[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	cout<<"Weight matrix is : \n";
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cout<<weight[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	*/
}


void Graph :: initialize_source(int s)
{
	int i=0;
	for(i=0;i<n;i++)
	{
		color[i] = 'w';
		dis[i] = INT_MAX;
		pred[i] = NULL;	
	}
	pred[0] = 0;
	dis[0] = 0;
	/*cout<<"dis is :";
	for(i=0;i<n;i++)
	{
		
		cout<<dis[i] <<" ";	
	}
	cout<<endl;
	
	cout<<"color is :";
	for(i=0;i<n;i++)
	{
		
		cout<<color[i] <<" ";	
	}
	cout<<endl;
	cout<<"pred is :";
	for(i=0;i<n;i++)
	{
		
		cout<<pred[i] <<" ";	
	}
	cout<<endl;
	*/
	
}

void Graph :: relax(int u,int v)
{
	if(dis[v] > (dis[u] + weight[u][v]))
	{
		dis[v] = dis[u] + weight[u][v];
		pred[v] = u;
	}
}

void Graph :: sp_dfs(int u)
{
	color[u] = 'g';
	int i =0;
	for(i=0;i<n;i++)
	{
		if(graph[u][i] == 1 && color[i] == 'w')
		{
			pred[i] = u;
			relax(u,i);
			sp_dfs(i);
		}
		else if(graph[u][i] == 1 && color[i] == 'b' && dis[i] > (dis[u] + weight[u][i]))
		{
			relax(u,i);
			sp_dfs(i);
		}
	}
	color[u] = 'b';
}

bool Graph :: neg_cycle(int u)
{
	int i=0,j=0;
	for(i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(graph[i][j] == 1) 
			{
				if(dis[j] > dis[i] + weight[i][j])
					return false;
			}
		}
	}
	return true;
}

void Graph :: print()
{
	FILE *filename = fopen("graph.dot","w");
	fprintf(filename, "digraph SSSP {\n");
    fprintf(filename, "    node [fontname=Arial , shape = circle];\n");
    int i=1;
    for(i = 1;i<n;i++)
    {
    	fprintf(filename,"%d -> %d [label = %d];\n",pred[i],i,dis[i]-dis[pred[i]]);
	}
	fprintf(filename, "}\n");
    fclose(filename);
	system("dot -Tsvg graph.dot -o graph.svg");
   	system("graph.svg");
}


	
	
int main()
{
	Graph g;
	g.construct_graph();
	g.initialize_source(0);
	g.sp_dfs(0);
	bool flag = g.neg_cycle(0);
	if(flag)
	{
		cout<<"\nPrinting graph"<<endl;
		g.print();
		
	}
	else
	{
		cout<<"\nNegative Cycle exists";
		g.print();
	}
	cout<<"\nexecuted";
	return 0;
	
}









