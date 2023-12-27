#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <array>



using namespace std;

class graph{
public:
    int vertices;
    vector<vector<int> > edges;

    graph(){};
    graph(int s){
        vertices = 6;
        edges.resize(vertices);
        for(int i=0;i<vertices;i++){
            edges[i].resize(vertices);
        }
    }

   void set(int r, int c, int d) {
       edges[r][c] = d;
       return;
       }
   int get(int r, int c) {
       return edges[r][c];
       }

   void set_size(int s) {
       vertices = s;
       edges.resize(vertices * vertices);
       return;
       }
   int get_size(){
       return vertices;
       }
   int count_vertices() {
        int v=0;
        for(int i=0;i<vertices;i++){
             for(int j=0;j<vertices;j++){
                if(get(i,j)>0){  
                v++; break;
                }
            }
        }
        return v;
   }
   int count_edges(){
        int e=0;
        for(int i=0;i<vertices;i++){
            for(int j=0;j<vertices;j++){
                e+=get(i,j);
            }
        }
        return e/2;
   }

   graph& remove_self_loops(){
        for(int i=0;i<vertices;i++){
        set(i,i,0);
        }
        return *this;
   }

   graph& merge_vertices(int u, int v){
   if(u< vertices && v<vertices){
        for(int i=0;i<vertices;i++){
            set(i,v,get(i,u)+get(i,v));
            set(i,u,0);
            set(v,i,get(u,i)+get(v,i));
            set(u,i,0);
          }
   }
   return *this;
   }

   void print(){
        for(int i=0;i<vertices;i++){
            for(int j=0;j<vertices;j++){
                cout<<get(i,j)<<" ";
            }
            cout<<endl;
        }
   }
};

void kargers_algorithm(graph& g)
{
   g.remove_self_loops();
   while (g.count_vertices() > 2)
   {
      int u = 0, v = 0;
      do
      {
         u = rand() % g.get_size();
         v = rand() % g.get_size();
      }
      while (g.get(u, v) == 0);
   // Merge both vertices
      g.merge_vertices(u, v);
   //Remove self-loops
      g.remove_self_loops();
   }
   return;
}

int main()
{
     graph g(6);
     int edgeset[11][2] = {{0,1},{0,2},{0,4},{1,2},{1,3},{2,3},{2,4},{2,5},{3,4},{3,5},{4,5}};
    for(auto &e : edgeset){
        g.set(e[0],e[1],1);
        g.set(e[1],e[0],1);
    }
     /*
     g.edges={{0 ,1 ,0, 1, 1, 0},
              {1, 0, 1, 0, 1, 0},
              {0, 1, 0, 0, 1, 1},
              {1, 0, 0, 0, 1, 0},
              {1, 1, 1, 1, 0, 1},
              {0, 0, 1, 0, 1, 0}};
              */
      graph ming; ming.set_size(0);

      cout << "Input vertex count: " << g.count_vertices() << endl;
      cout << "Input edge count: " << (g.count_edges()) << endl;

      int n = g.count_vertices();
      float ln = log((float) n);
      float runs = n * n * ln, mincut = INT_MAX;

      for (int i = 0; i < runs; ++i)
      {
         graph copy = g;
         kargers_algorithm(copy);
         cout << "--" << endl;
         copy.print();
         int cut = copy.count_edges();
         if (cut < mincut)
         {
            mincut = cut;
            ming = copy;
         }
      }
      cout << "Output vertex count: " << ming.count_vertices() << endl;
      cout << "Output edge count: " << ming.count_edges()<< endl;
    cout<< "Minimum cut for the graph is "<< mincut<<endl;
    return 0;
}