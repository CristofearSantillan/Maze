//Cristofear Santillan

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <fstream>

using namespace std;

class Grid{
  public:
    int size, v1, v2, c, x, y, z;
    map<int,string> vertices;
    vector<int> visited;
    map<double,string> edges;

  void display(){
    // for (auto itr = edges.begin(); itr != edges.end(); ++itr) {
    //   cout << itr->first << " " << itr->second << endl;
    // }
    // for (auto itr = vertices.begin(); itr != vertices.end(); ++itr) {
    //   cout << itr->first << " " << itr->second << endl;
    // }
    for(auto& i: visited){ cout << i << endl;}
    // cout << endl;
  }

  void createMap(int s){
    for(int i = 0; i < s*s; i++){
      vertices[i] = to_string(x) + " " + to_string(y);
      y++;
      if(y%s == 0){
        y = 0;
        x++;
      }
    }
    x = 1, y = 0;
  }

  Grid(int s): vertices(),visited(),edges(){
    size = s;
    x = 0,y = 0,v1 = 0,v2 = size,c = 0,z = size*size;
    createMap(s);
  }

  void addVerticalEdge(double e){
    edges[e] = to_string(x-1) + " " + to_string(y+1);
    x++;
    y++;
    if(x%size == 0){
      y = x++;
    }
  }

  void addHorizontalEdge(double e){
    edges[e] = to_string(v1) + " " + to_string(v2);
    v1+=size;
    v2+=size;
    if(v2 == z){
      z++;
      v1 = ++c;
      v2 = size + c;
    }
  }

  bool cycleCheck(int s1, int s2){

    int count1 = count(visited.begin(), visited.end(), s1), count2 = count(visited.begin(), visited.end(), s2);

    if(visited.size() <= 6 || ( count1 == 0 && count2 == 0 ) || ( count1 > 0 && count2 == 0) ||( count1 == 0 && count2 > 0)){
      return false;
    }
    
    //cout << "s1: " << s1 << " s2: " << s2 << endl;

    int vertex = s1, mainIndex = 0;
    vector<int> temp(visited);
    vector<int> holder{vertex};
    auto it = temp.begin();
    bool cycle = false;

    while(true){

      // cout << "temp: " << endl;
      // for(int i = 0; i < temp.size(); i+=2){ cout << temp[i] << " " << temp[i+1] << endl;}
      // cout << endl;
      // cout << "holder: " << endl;
      // for(int i = 0; i < holder.size(); i++){ cout << holder[i] << " ";}
      // cout << endl << endl;
      // cout << "vertex: " << vertex << endl;

      it = find(temp.begin(), temp.end(), vertex);
      mainIndex = (it - temp.begin()) + 1;
      //cout << "mainIndex: " << mainIndex << endl;

      if(mainIndex % 2 == 0){
        holder.push_back(temp[mainIndex-2]);
        //cout << "temp[mainIndex-2]: " << temp[mainIndex-2] << endl;
        temp.erase(temp.begin()+(mainIndex-2),temp.begin()+(mainIndex));
      }else{
        holder.push_back(temp[mainIndex]);
        //cout << "temp[mainIndex]: " << temp[mainIndex] << endl;
        temp.erase(temp.begin()+(mainIndex-1),temp.begin()+(mainIndex+1));
      }
      //cout << endl;

      if(holder[holder.size()-1] == s2){
        cycle = true;
        break;
      }

      if(find(temp.begin(), temp.end(), vertex) == temp.end()){
        if(holder.size() == 0){
          break;
        }
        holder.erase(holder.begin());
        vertex = holder[0];
        while(find(temp.begin(), temp.end(), vertex) == temp.end() && holder.size() != 0){
          holder.erase(holder.begin());
          vertex = holder[0];
        }
        if(holder.size() == 0 && find(temp.begin(), temp.end(), vertex) == temp.end()){
          break;
        }
      }

    }


    // vector<int> temp(visited);
    // vector<int> holder;

    // if(mainIndex % 2 == 0){
    //   holder.insert(holder.end(),temp.begin()+(mainIndex-2),temp.begin()+(mainIndex));
    //   preVertex = temp[mainIndex-2];
    //   temp.erase(temp.begin()+(mainIndex-2),temp.begin()+(mainIndex));
    // }else{
    //   holder.insert(holder.end(),temp.begin()+(mainIndex-1),temp.begin()+(mainIndex+1));
    //   preVertex = temp[mainIndex];
    //   temp.erase(temp.begin()+(mainIndex-1),temp.begin()+(mainIndex+1));
    // }

    // int index = mainIndex, vertex = preVertex;
    // bool cycle = false;

    // cout << "vertex: " << vertex << endl;
    // cout << "index: " << index << endl;
    // cout << "temp: " << endl;
    // for(int i = 0; i < temp.size(); i+=2){ cout << temp[i] << " " << temp[i+1] << endl;}
    // cout << endl;
    // cout << "holder: " << endl;
    // for(int i = 0; i < holder.size(); i+=2){ cout << holder[i] << " " << holder[i+1] << endl;}
    // cout << endl;

    // while(find(temp.begin(), temp.end(),s1) != temp.end() || holder.size() > 0){
      
    //   if (vertex == s2){
    //     cout << "end" << endl;
    //     cycle = true;
    //     break;
    //   }else if(count(temp.begin(), temp.end(),vertex) == 0){
    //     //cout << "temp[index-2]: " << temp[index-2] << " temp[index-1]: " << temp[index-1] << endl;
    //     // if(index % 2 == 0){
    //     //   temp.erase(temp.begin()+(index-2),temp.begin()+(index));
    //     // }else{
    //     //   temp.erase(temp.begin()+(index-1),temp.begin()+(index+1));
    //     // }
    //     // for(int i = 0; i < temp.size(); i+=2){ cout << temp[i] << " " << temp[i+1] << endl;}
    //     // cout << endl;

    //     if(count(temp.begin(), temp.end(), preVertex) == 0){
    //       // if(mainIndex % 2 == 0){
    //       //   temp.erase(temp.begin()+(mainIndex-2),temp.begin()+(mainIndex));
    //       // }else{
    //       //   temp.erase(temp.begin()+(mainIndex-1),temp.begin()+(mainIndex+1));
    //       // }
    //       holder.clear();
    //       if(find(temp.begin(), temp.end(),s1) == temp.end()){
    //         break;
    //       }else{
    //         it = find(temp.begin(), temp.end(),s1);
    //         mainIndex = (it - visited.begin()) + 1;
    //         if(mainIndex % 2 == 0){
    //           holder.insert(holder.end(),temp.begin()+(mainIndex-2),temp.begin()+(mainIndex));
    //           preVertex = temp[mainIndex-2];
    //           temp.erase(temp.begin()+(mainIndex-2),temp.begin()+(mainIndex));
    //         }else{
    //           holder.insert(holder.end(),temp.begin()+(mainIndex-1),temp.begin()+(mainIndex+1));
    //           preVertex = temp[mainIndex];
    //           temp.erase(temp.begin()+(mainIndex-1),temp.begin()+(mainIndex+1));
    //         }
    //       }
    //     }else if(count(temp.begin(), temp.end(),vertex) > 0){
          
    //     }

    //     vertex = preVertex;

    //     // it = find(temp.begin(), temp.end(),s1);
    //     // mainIndex = (it - temp.begin()) + 1;
    //     // if(mainIndex % 2 == 0){
    //     //   preVertex = visited[mainIndex-2];
    //     // }else{
    //     //   preVertex = visited[mainIndex];
    //     // }
    //     // vertex = preVertex;
    //     //iocontinue;
    //   }

    //   it = find(temp.begin(), temp.end(),vertex);
    //   index = (it - temp.begin()) + 1;

    //   if(index % 2 == 0){
    //     vertex = temp[index - 2];
    //     temp.erase(temp.begin()+(index-2),temp.begin()+(index));
    //   }else{
    //     vertex = temp[index];
    //     temp.erase(temp.begin()+(index-1),temp.begin()+(index+1));
    //   }

    //   // auto it = find(temp.begin(), temp.end(),vertex);
    //   // index = (it - temp.begin()) + 1;

    //   // if(index % 2 == 0){
    //   //   vertex = temp[index - 2];
    //   // }else{
    //   //   vertex = temp[index];
    //   // }
    // cout << "vertex: " << vertex << endl;
    // cout << "index: " << index << endl;
    // cout << "temp: " << endl;
    // for(int i = 0; i < temp.size(); i+=2){ cout << temp[i] << " " << temp[i+1] << endl;}
    // cout << endl;
    // cout << "holder: " << endl;
    // for(int i = 0; i < holder.size(); i+=2){ cout << holder[i] << " " << holder[i+1] << endl;}
    // cout << endl;

    // }
    // cout << endl;
    return cycle;
  }

  vector<int> nextEdge(){

    double max = 0.0;
    bool run = true;
    vector<string> result;
    vector<int> temp;

    while(run){

      max = edges.rbegin()->first;
      istringstream iss(edges[max]);
      result = {istream_iterator<std::string>(iss), {}};

      if(!(cycleCheck(stoi(result[0]),stoi(result[1])))){
        visited.push_back(stoi(result[0]));
        visited.push_back(stoi(result[1]));
        temp.push_back(stoi(result[1]));
        temp.push_back(stoi(result[0]));
        run = false;
      }

      edges.erase(max);

    }

    return temp;

  }

};

void readData(Grid*& g){
  ifstream fin("input.txt");

  int size;
  fin >> size;

  g = new Grid(size);

  double e = 0.0;
  int c = 0;
  while(fin >> e){
    c++;
    if(c >= ((size-1)*size)+1){
      g->addHorizontalEdge(e);
    }else{
      g->addVerticalEdge(e);
    }
  }

  fin.close();
}

vector<int> createMaze(Grid*& g){

  vector<int> knockDowns;
  int end = 2 * ((g->size*g->size) - 1);
  vector<int> temp;

  while(knockDowns.size() != end){
    temp = g->nextEdge();
    knockDowns.insert(knockDowns.end(), temp.begin(), temp.end());
  }

  return knockDowns;
}

void outputData(vector<int> result, Grid*& g){
  ofstream fout("output.txt");
  for(int i = 0; i < result.size(); i+=2){ 
    fout << g->vertices[result[i]] << " " << g->vertices[result[i+1]] << endl;
  }
  fout.close();
}

int main() {

  cout.precision(17);
  Grid* grid;
  readData(grid);
  // for (auto itr = grid->edges.begin(); itr != grid->edges.end(); ++itr) {
  //   cout << itr->first << " " << itr->second << endl;
  // }
  //cout << endl;
  outputData(createMaze(grid), grid);
  // cout << endl;
  // for(int i = 0; i < grid->visited.size(); i+=2){ cout << grid->visited[i] << " " << grid->visited[i+1] << endl;}
}