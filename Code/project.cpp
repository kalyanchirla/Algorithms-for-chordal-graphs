#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <ctime>
#include <chrono>

using namespace std;

void maxWeightedClique(vector<int>&ordering,vector<int>graph[])
{
    /*
        Calculate the maximum weighted clique for a given graph and its vertices' ordering
    */

    srand(time(0)); //seed the generator
    map<int,int>weights; // declare a map to store weights for each vertex
    int vertices = ordering.size();
    for(int i=0;i<vertices;i++)
    {
        int wt = ((rand()%vertices)+1); // randomly generate weights for every vertex in a graph
        weights.insert(make_pair(i,wt)); // insert the (vertex,weight) pairs into a map
    }
    int max_weight_sum = 1; // Initialize a maximum weight sum variable
    vector<int>clique; // Declaring a vector to store the vertices in the maximum weighted clique
    vector<int>S(ordering.size(),0); 
    map<int,int>idx; // Declare a map to store the indices of every vertex in the 'ordering'
    for(int i=0;i<ordering.size();i++)
    {
        idx[ordering[i]]=i;
    }
    for(int i=0;i<ordering.size();i++)
    {
        int current_weight = 0;
        int v = ordering[i]; // Selected vertex 'v'
        vector<int>X; 
        for(int j=0;j<graph[v].size();j++) // Traversing the adjacent elements of 'v'
        {
            int adj_v = graph[v][j];
            if(idx[v]<idx[adj_v]) 
            {
                X.push_back(adj_v); // Adding the adjacent vertices of 'v' whose index in 'ordering' is greater than that of 'v' to 'X'
            }
        }
        if(graph[v].size()!=0)
        {
            if(X.size()>0)
            {
                int u = X[0]; 
                int index_u = idx[u];
                for(int j=1;j<X.size();j++) // Finding a vertex 'u' among vertices in 'X' whose index in 'ordering' is minimum 
                {
                    if(idx[X[j]]<index_u)
                    {
                        index_u = idx[X[j]];
                        u = X[j];
                    }
                }
                // Updating the current_weight 
                for(int j=0;j<X.size();j++)
                {
                    current_weight+=weights[X[j]];
                }
                // Initializing vertex_weight 
                int vertex_wt = weights[u];
                // Updating S[u]
                S[u] = max(S[u],(current_weight-vertex_wt));
                if(S[v]<current_weight)
                {
                    current_weight = current_weight +weights[v];

                    if(max_weight_sum<current_weight)
                    {
                        max_weight_sum = current_weight; //Updating the maximum clique weight sum
                        X.push_back(v); 
                        clique = X; //Updating the 'clique' set with vertices in the maximum weighted clique
                    }
                }   
            }
        }
    }
    // Output the maximum weight sum of the maximum weighted clique
    cout << "THE MAXIMUM WEIGHTED CLIQUE SUM: " << max_weight_sum << "\n";
    // Output the vertices in the maximum weighted cliques along with their weights
    cout << "THE MAXIMUM WEIGHTED CLIQUE CONSISTS OF THE FOLLOWING VERTICES: " << "\n";
    cout << "VERTEX : WEIGHT" << "\n";
    for(int i=0;i<clique.size();i++)
    {
        cout << clique[i] << "\t  " << weights[clique[i]] << "\n";
    }
}

void maxIndependentSet(vector<int>&ordering, vector<int>graph[])
{
    /*
        Calculate the maximum Independent set and minimum clique covering of an unweighted 'graph' with 'ordering'
    */
    vector<bool>visited(ordering.size(),false); // Iniatilize a visited vector 
    map<int,int>independentSet; // Declare a map to store the independent set
    vector<vector<int> >cliqueCover; // Declare a 2D vector to store all the cliques in the clique cover
    map<int,int>idx; // Declare a map to store the indices of every vertex in the 'ordering'
    for(int i=0;i<ordering.size();i++)
    {
        idx[ordering[i]]=i;
    }

    for(int i=0;i<ordering.size();i++)
    {
        int v = ordering[i]; // Selected vertex
        if(visited[v]==false) // If the selected vertex is not visited 
        {
            vector<int>X; 
            for(int j=0;j<graph[v].size();j++)
            {
                int adj_v = graph[v][j];
                if(idx[v]<idx[adj_v])
                {
                    X.push_back(adj_v); // Adding the adjacent vertices of 'v' whose index in 'ordering' is greater than that of 'v' to 'X'
                }
            }
            if(graph[v].size()==0)
            {
                vector<int> clique; // Declaring a clique to store the vertices in the current clique
                clique.push_back(v);
                cliqueCover.push_back(clique); // Update the cliqueCover by adding the current clique to it
                if(!(independentSet.find(v)!=independentSet.end()))
                {
                    independentSet[v]++; //Updating the independent set
                }
            }
            else
            {
                for(int j=0;j<X.size();j++)
                {
                    visited[X[j]]=true; // Mark all the elements in 'X' as visited
                }
                if(!(independentSet.find(v)!=independentSet.end())) //Add the vertex to the independent set only if has not been added earlier
                {
                    independentSet[v]++;
                }
                X.push_back(v); // Update the set 'X'
                vector<int> clique;
                for(int j=0;j<X.size();j++)
                {
                    clique.push_back(X[j]); //Updating the current clique
                }
                cliqueCover.push_back(clique); //Update the cliqueCover by adding the current clique into it
            }
        }
    }
    map<int,int>::iterator it; // Declaring an iterator to traverse the map to output all the vertices in the independentSet
    cout << "THE MAXIMUM INDEPENDENT SET CONSISTS OF THE FOLLOWING VERTICES: ";
    for(it= independentSet.begin();it!=independentSet.end();it++) //Output the independentSet
    {
        cout << it->first << " ";
    }
    cout << "\n";
    // Output the number of cliques in minimumCliqueCover set (All the cliques in the cliqueCover can also be printed)
    cout << "THE MINIMUM CLIQUE COVER: " << cliqueCover.size() << "\n"; 
}

void maxclique(vector<int>&ordering, vector<int>graph[])
{
    /*
        Calculate the maximum Clique and minimum vertex colouring of an unweighted 'graph' with 'ordering'
    */
    int chromatic_number = 1; // Initialize the chromatic number to 1 as atleast 1 colour is required to colour a graph
    vector<int>clique; //Declare a vector to store the vertices in the maximum clique
    vector<int>S(ordering.size(),0); 
    map<int,int>idx; // Declare a map to store the indices of every vertex in the 'ordering'
    for(int i=0;i<ordering.size();i++)
    {
        idx[ordering[i]]=i; //Update the idx with respective indices of each vertex
    }
    for(int i=0;i<ordering.size();i++)
    {
        int v = ordering[i]; // Selected vertex
        vector<int>X;
        for(int j=0;j<graph[v].size();j++)
        {
            int adj_v = graph[v][j];
            if(idx[v]<idx[adj_v])
            {
                X.push_back(adj_v); // Adding the adjacent vertices of 'v' whose index in 'ordering' is greater than that of 'v' to 'X'
            }
        }
        if(X.size()>0)
        {
            int u = X[0];
            int index_u = idx[u];
            // Finding a vertex 'u' among vertices in 'X' whose index in 'ordering' is minimum
            for(int j=1;j<X.size();j++)
            {
                if(idx[X[j]]<index_u)
                {
                    index_u = idx[X[j]];
                    u = X[j];
                }
            }
            int x_size = X.size();
            S[u] = max(S[u],(x_size-1)); // Updating the vector 'S'
            if(S[v]<X.size())
            {
                // Finding the new maximum clique size
                int new_chromatic_number = max(chromatic_number,(1+x_size));
                if(new_chromatic_number>chromatic_number)
                {
                    clique = X;
                    clique.push_back(v); // Updating the vertices in the maximum clique
                    chromatic_number = new_chromatic_number; // Updating the maximum clique size
                }
            }
        }
    }
    // Output the vertices in the maximum clique
    cout << "THE MAXIMUM CLIQUE CONSISTS OF THE FOLLOWING VERTICES: ";
    for(int i=0;i<clique.size();i++)
    {
        cout << clique[i] << " ";
    }
    cout << "\n";
    // Output the Chromatic Number i.e, minimum vertex colours to colour the given graph
    cout << "CHROMATIC NUMBER OF THE GRAPH: " << clique.size() << "\n";
}
bool DIFF(vector<int>&A2, vector<int>&Adj_v,int n)
{
    
    vector<int>freq(n+1,0); // Initialize a map to store all the vertices in Adj_v
    for(int i=0;i<Adj_v.size();i++)
    {
        freq[Adj_v[i]]=1; // Store all the vertices of Adj_v to the map 'freq'
    }
    for(int i=0;i<A2.size();i++)
    {
        if(freq[A2[i]]==0) // If any vertex in A2 is not present in Adj_v i.e, 'freq' then return false
        {
            return false;
        }
    }
    return true;
}

bool checkPerfectEliminationOrdering(vector<int>&ordering, vector<int>graph[])
{
    /*
        Verify whether a given 'ordering' of a 'graph' is a perfect-elimination ordering
    */
    map<int,vector<int> >A; // Declaring a map 'A'
    map<int,int>idx; // Declare a map to store the indices of every vertex in the 'ordering'
    for(int i=0;i<ordering.size();i++)
    {
        idx[ordering[i]]=i; //Update the idx with respective indices of each vertex
    }
    for(int i=0;i<ordering.size()-1;i++)
    {
        int v = ordering[i]; // Selected vertex
        vector<int>X;
        for(int j=0;j<graph[v].size();j++)
        {
            int adj_v = graph[v][j];
            if(idx[v]<idx[adj_v])
            {
                X.push_back(adj_v); // Adding the adjacent vertices of 'v' whose index in 'ordering' is greater than that of 'v' to 'X'
            }
        }
        if(X.size()>0)
        {
            int u = X[0];
            int index_u = idx[u];
            // Finding a vertex 'u' among vertices in 'X' whose index in 'ordering' is minimum
            for(int j=1;j<X.size();j++)
            {
                if(idx[X[j]]<index_u)
                {
                    index_u = idx[X[j]];
                    u = X[j];
                }
            }
            for(int j=0;j<X.size();j++)
            {
                if(X[j]!=u)
                {
                    A[u].push_back(X[j]); //Updating A[u] by adding all the vertices in 'X' except 'u'
                }
            }
        }
        vector<int>A2; // Declaring a vector to add all the elements in 'A[v]' for every vertex 'v' in 'graph'
        vector<int>Adj_v; // Declaring a vector to all the adjacent elements of 'v' for every vertex 'v' in 'graph'
        for(int j=0;j<A[v].size();j++)
        {
            A2.push_back(A[v][j]); // Update 'A2'
        }
        for(int j=0;j<graph[v].size();j++)
        {
            Adj_v.push_back(graph[v][j]); // Update Adj_v
        }
        if(!DIFF(A2,Adj_v,ordering.size())) // Check Difference of A2 and Adj_v
        {
            return false;
        }
    }
    return true;
}
vector<int> MCS(vector<int>graph[], int vertices, int edges)
{
    /*
        Find the ordering of vertices in a 'graph' using Maximum Cardinality Search
    */
    map<int, map<int,int> >node_store; // Declare a map to store all the vertices with a given label
    for(int i=0;i<vertices;i++)
    {
        node_store[0][i]++; //As the initial label is 0, update the count for all vertices at label=0
    }
    map<int,int>label_store; // Declare a map to store the label for all vertices in 'graph'
    for(int i=0;i<vertices;i++)
    {
        label_store[i]=0; // Initialize label=0 for all vertices
    }
    vector<int>ordering; // Declare a vector to store the final ordering of the vertices in 'graph'
    map<int,int>label_count; // Declare a map to store the count each label remaining
    map<int,int>visited; // Declare a visited map
    label_count[0]=vertices; // Initially, all vertices have a label=0
    map<int,int>::iterator it_labelcount,it_nodestore;
    for(int m=vertices-1;m>=0;m--)
    {
        it_labelcount = label_count.end(); // Take the maximum label from the end of the map
        --it_labelcount; 
        int current_label = (it_labelcount)->first; // Initialize the current_label with label taken above
        label_count[current_label]--; //Update label count
        if(label_count[current_label]==0)
        {
            label_count.erase(current_label); //Removing the label and its mapped data if its count=0
        }
        it_nodestore = node_store[current_label].begin(); 
        if(it_nodestore->second!=0&&it_nodestore!=node_store[current_label].end()) // Traversing the vertices in the 'current_label' from 'node_store'
        {
            int current_vertex = it_nodestore->first; // Current vertex is the first vertex in the 'node_store' with 'current_label'
            ordering.push_back(current_vertex); // Update the ordering vector
            visited[current_vertex]++; // Mark the 'current_vertex' as visited
            node_store[current_label].erase(it_nodestore); // Erase the 'current_vertex' from 'current_label' of 'node_store'
            vector<int>adjacent; // Declare a vector to store the adjacent vertices of the current_vertex
            for(int i=0;i<graph[current_vertex].size();i++)
            {
                adjacent.push_back(graph[current_vertex][i]); //Updating with adjacent vertices
            }
            for(int i=0;i<adjacent.size();i++)
            {
                if(!(visited.find(adjacent[i])!=visited.end())) // If the adjacent vertex is not visited
                {
                    int adjacent_label = label_store[adjacent[i]]; // Find the label of adjacent vertex
                    int new_label = adjacent_label+1; //  Make the new label by adding 1 to current label
                    label_store[adjacent[i]]=new_label; // Update the vertex's label with new label
                    it_nodestore = node_store[adjacent_label].find(adjacent[i]); // Find the adjacent vertex in its current label and delete it from 'node_store[adjacent_label]'
                    if(node_store[adjacent_label].find(adjacent[i])!=node_store[adjacent_label].end())
                    {
                        node_store[adjacent_label].erase(it_nodestore); //Update node_store
                        label_count[adjacent_label]--; //Update labelcount
                        if(label_count[adjacent_label]==0)
                        {
                            label_count.erase(adjacent_label); //Update labelcount
                        }
                    }
                    node_store[new_label][adjacent[i]]++; //Update node_store
                    label_count[new_label]++; //Update labelcount
                }
            }
        }
    }
    // Reverse the 'ordering' as the ordering obtained is in the reverse order
    reverse(ordering.begin(),ordering.end());
    return ordering;
}

vector<int> LEXBFS(vector<int>graph[], int vertices, int edges)
{
    /*
        Find the ordering of vertices in a 'graph' using Lexicographic Breadth-first search
    */
    map<string, map<int,int> >node_store; // Declare a map to store all the vertices with a given label
    for(int i=0;i<vertices;i++)
    {
        node_store[""][i]++; //As the initial label is "", update the count for all vertices at label=""
    }
    map<int,string>label_store; // Declare a map to store the label for all vertices in 'graph'
    for(int i=0;i<vertices;i++)
    {
        label_store[i]=""; // Initialize label="" for all vertices
    }
    vector<int>ordering; // Declare a vector to store the final ordering of the vertices in 'graph'
    map<int,int>::iterator it; // Iterator to traverse map in 'node_store'
    map<string,int>::iterator it2; // Iterator to traverse 'node_store'
    map<string,int>label_count; // Declare a map to store the count each label remaining
    map<int,int>visited; // Declare a visited map
    label_count[""]=vertices; // Initially, all vertices have a label=""

    for(int m=vertices-1;m>=0;m--)
    {
        it2 = label_count.end(); // Take the maximum label from the end of the map
        --it2;
        string current_label = it2->first; // Initialize the current_label with label taken above
        label_count[current_label]--; //Update label count
        if(label_count[current_label]==0)
        {
            label_count.erase(current_label);  //Removing the label and its mapped data if its count=0
        }
        it = node_store[current_label].begin();
        if(it->second!=0&&it!=node_store[current_label].end()) // Traversing the vertices in the 'current_label' from 'node_store'
        {
            int current_vertex = it->first; // Current vertex is the first vertex in the 'node_store' with 'current_label'
            ordering.push_back(current_vertex); // Update the ordering vector
            visited[current_vertex]++; // Mark the 'current_vertex' as visited
            node_store[current_label].erase(it); // Erase the 'current_vertex' from 'current_label' of 'node_store'
            vector<int>adjacent; // Declare a vector to store the adjacent vertices of the current_vertex
            for(int i=0;i<graph[current_vertex].size();i++)
            {
                adjacent.push_back(graph[current_vertex][i]); //Updating with adjacent vertices
            }
            for(int i=0;i<adjacent.size();i++)
            {
                if(!(visited.find(adjacent[i])!=visited.end())) // If the adjacent vertex is not visited
                {
                    string adjacent_label = label_store[adjacent[i]]; // Find the label of adjacent vertex
                    string addtn = to_string(1); 
                    string new_label = adjacent_label+addtn; // New_label = current_label + addtn
                    label_store[adjacent[i]]=new_label; // Update the vertex's label with new label
                    it = node_store[adjacent_label].find(adjacent[i]); // Find the adjacent vertex in its current label and delete it from 'node_store[adjacent_label]'
                    if(node_store[adjacent_label].find(adjacent[i])!=node_store[adjacent_label].end())
                    {
                        node_store[adjacent_label].erase(it); //Update node_store
                        label_count[adjacent_label]--; //Update label_count
                        if(label_count[adjacent_label]==0)
                        {
                            label_count.erase(adjacent_label); //Update label_count
                        }
                    }
                    node_store[new_label][adjacent[i]]++; //Update node_store
                    label_count[new_label]++; //Update label_count
                }
            }
        }
    }
    // Reverse the 'ordering' as the ordering obtained is in the reverse order
    reverse(ordering.begin(),ordering.end());
    return ordering;
}
int main()
{
    // Comment the below line if you want to customly provide graph input
    freopen("input.txt","r",stdin);
    
    //Taking the number of vertices and edges as input
    int vertices,edges;
    cout << "ENTER THE NUMBER OF VERTICES: " << "\n";
    cin >> vertices;
    cout << "ENTER THE NUMBER OF EDGES: " << "\n";
    cin >> edges;

    // Declaring an adjacency list
    vector<int>graph[vertices+1];

    // Taking the vertex pairs as input for edges
    cout << "ENTER ALL THE VERTEX PAIRS FOR EDGES: " << "\n";
    for(int i=0;i<edges;i++)
    {
        int v1,v2;
        cin >> v1 >> v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
    // Get the ordering of vertices using LEXBFS
    vector<int> ordering_lexbfs = LEXBFS(graph,vertices,edges);
    vector<int> ordering_mcs = MCS(graph,vertices,edges);
    
    //OUTPUT THE LEXBFS ORDERING
    cout << "LEXBFS ORDERING: ";
    for(int i=0;i<ordering_lexbfs.size();i++)
    {
        cout << ordering_lexbfs[i] << " ";
    }
    cout << "\n";

    //OUTPUT THE MCS ORDERING
    cout << "MCS ORDERING: ";
    for(int i=0;i<ordering_mcs.size();i++)
    {
        cout << ordering_mcs[i] << " ";
    }
    cout << "\n";
    if(checkPerfectEliminationOrdering(ordering_lexbfs,graph)) // CHECK IF THE GRAPH is Chordal
    {
        cout << "THE GIVEN INPUT GRAPH IS A CHORDAL GRAPH" << "\n";

        maxclique(ordering_lexbfs,graph); //Calculate the maximum Clique and minimum vertex colouring
        maxIndependentSet(ordering_lexbfs,graph); //Calculate the maximum independent set and minimum clique covering
        maxWeightedClique(ordering_lexbfs,graph); // Calculate the maximum weighted clique
    }
    else
    {
        cout << "THE INPUT GRAPH IS A CHORDAL GRAPH" << "\n";
    }
}