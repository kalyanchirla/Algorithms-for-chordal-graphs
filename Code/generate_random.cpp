#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <ctime>
#include <random>
#include <set>

using namespace std;

vector<int>graph[1000000]; // Declare a graph (adjacency list)

void printgraph(int vertices)
{
    /*
    Function to print the graph in the required format
    */
    int ed =0;
    for(int i=0;i<vertices;i++)
    {
        ed+=graph[i].size(); //Finding the number of edges
    }
    int edges = ed/2; // Edges/2 as undirected graph
    set<vector<int> >s; // To avoid repetitions
    for(int i=0;i<vertices;i++)
    {
        for(int j=0;j<graph[i].size();j++)
        {
            vector<int>v;
            v.push_back(i);
            v.push_back(graph[i][j]);
            sort(v.begin(),v.end());
            s.insert(v);
        }
    }
    // PRINTING THE GRAPH
    set<vector<int> >::iterator it;
    cout << vertices << " " << edges << "\n";
    for(it=s.begin();it!=s.end();it++)
    {
        vector<int> v = *it;
        for(int j=0;j<v.size();j++)
        {
            cout << v[j] << " ";
        }
        cout << "\n";
    }
}
void generate_graph(int vertices)
{
    /*
    FUNCTION TO GENERATE A RANDOM GRAPH WITH 'vertices' as INPUT PARAMETER
    */
    int num_vertices = vertices;
    random_device rd; // obtain a random number from device
    mt19937 gen(rd()); // seed the generator
    //vector<int>graph[vertices];
    if(vertices>=3) // Complete graph of size 3
    {
        graph[0].push_back(1);
        graph[1].push_back(0);
        graph[0].push_back(2);
        graph[2].push_back(0);
        graph[1].push_back(2);
        graph[2].push_back(1);
    }
    vertices = vertices-3; //Update the number of vertices
    map<int, set<vector<int> > >cliques; // Declare a map to store the cliques of each size
    set<vector<int> >::iterator it,it4;
    int vertex_number=3; // New vertex number to be added
    while(vertices>0)
    {
        // Finding cliques of size 2
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<graph[i].size();j++)
            {
                vector<int>v;
                v.push_back(i);
                v.push_back(graph[i][j]);
                sort(v.begin(),v.end());
                cliques[2].insert(v);  
            }
        }
        // Finding all the cliques of size from 3 to 5 (Range can be changed)
        for(int i=3;i<=5;i++)
        {
            for(it = cliques[i-1].begin();it!=cliques[i-1].end();it++) //Iterating the cliques of size i-1 to form cliques of size i
            {
                vector<int>temp = *it; // Store the vertices of the clique into a vector 'temp'
                map<int,int>freq; //Declare a map to update the count of adjacent vertices of each vertex in the clique
                for(int j=0;j<temp.size();j++)
                {
                    for(int k=0;k<graph[temp[j]].size();k++)
                    {
                        freq[graph[temp[j]][k]]++; // Updating the count of adjacent vertices in the map
                    }
                }
                map<int,int>::iterator it2; //Iterator to iterate through the adjacent vertices count map
                for(it2=freq.begin();it2!=freq.end();it2++)
                {
                    if((it2->second)==temp.size()) //Checking if any adjacent vertex is adjacent to all the vertices in the clique
                    {
                        vector<int> new_v = temp; 
                        new_v.push_back(it2->first); // Add the new adjacent vertex which common among all the vertices in the clique to form a new clique of size 'i'
                        sort(new_v.begin(),new_v.end()); // Sort the vector to avoid repetitions in edges
                        cliques[i].insert(new_v); // Insert the new set into the clique of size i
                    }
                }
            }
        }
        int clique_bound = 2; // Clique bound is set to randomly choose a clique size from (2,max_size_possible)
        for(int i=3;i<=3;i++)
        {
            if(cliques[i].size()>0)
            {
                clique_bound=i; //Set maximum clique bound to a clique size where there is atleast one clique of that size present
            }
            else
            {
                break;
            }
        }
        uniform_int_distribution<> distr2(2, clique_bound); 
        int clique_size = distr2(gen); //Get the randomly chosen clique size
        int set_bound = cliques[clique_size].size(); // Set bound is used to choose a clique of random index
        uniform_int_distribution<> distr3(0, (set_bound-1)); // Random index is chosen from (0,clique[chosen_size].size()-1)
        int select_clique_idx = distr3(gen); // Gernerate the clique index
        it4 = cliques[clique_size].begin(); // Iterator to traverse the clique
        advance(it4,select_clique_idx); 
        vector<int>selected_clique = *it4;
        uniform_int_distribution<> distr5(2, (((selected_clique.size())*(selected_clique.size()-1))/2)-1); // Chose random number of edges between (2,(n*n-1)/2)
        int edges = distr5(gen); // Number of edges to join is also chosen in random 
        vertices--;
        int i=0;
        while(i<selected_clique.size())
        {
            graph[selected_clique[i]].push_back(vertex_number); // Edges are joined
            graph[vertex_number].push_back(selected_clique[i]);
            edges--;
            i++;
        }
        vertex_number++;
    }
    printgraph(num_vertices); // Print the graph
}
int main()
{
    // Output to a text file
    // Comment the below line to output the graph into console
    freopen ("input.txt","w",stdout);
    // Number of vertices as the input
    int vertices;
    cin >> vertices; 
    // Generate 10 graphs of each input size vertices
    int t = 10;
    cout << t << "\n";
    while(t--)
    {
        generate_graph(vertices); // Generate the random graph for input 'vertices'
        for(int i=0;i<vertices;i++) // Clear all the vertices data as the graph is declared in global scope
        {
            graph[i].clear();
        }
    }
}