#include "tsmp.cpp"
#include <omp.h>

double min_graph[N][N];
double max_value = inf;
pile_elem min_route;
std::vector<pile_elem> ordered_pile;

void ordered_insert(pile_elem ins){
    for(auto it = ordered_pile.begin(); it != ordered_pile.end(); it++){
        if(ins.reduced_value > it->reduced_value){
            ordered_pile.insert(it, ins);
            return;
        }
    }
    ordered_pile.push_back(ins);
}

void reduce_graph(pile_elem &ins){
    int i, j;
    double min;
    for(i = 0; i < N; i++){
        min = inf;
        for(j = 0; j < N; j++){
            if(ins.graph[i][j] < min) min = ins.graph[i][j];
        }
        if(min == inf) continue;
        for(j = 0; j < N; j++) {
            if(ins.graph[i][j] != inf) ins.graph[i][j] = ins.graph[i][j] - min;
            else ins.graph[i][j] = inf;  
        }
        ins.reduced_value += min;
    }
    for(j = 0; j < N; j++){
        min = inf;
        for(i = 0; i < N; i++){
            if(ins.graph[i][j] < min) min = ins.graph[i][j];
        }
        if(min == inf) continue;
        for(i = 0; i < N; i++) {
            if(ins.graph[i][j] != inf) ins.graph[i][j] = ins.graph[i][j] - min;
            else ins.graph[i][j] = inf;  
        }
        ins.reduced_value += min;
    }
}

void print_graph(double graph[N][N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(graph[i][j] == inf) std::cout<<"  inf ";
            else std::cout<<std::setw(5)<<graph[i][j]<<' ';
        }
        std::cout<<'\n';
    }
    std::cout<<'\n';
}

bool branch_entry(pile_elem node){
    pile_elem working;
    for(int i = 0; i < N; i++){
        if(node.visited[i]) continue;
        working = pile_elem(node, i);
        reduce_graph(working);
        // if(working.reduced_value >= max_value) continue;
        if(working.is_complete()){
            max_value = working.reduced_value;
            min_route = working;
            return true;
        }else{
            ordered_insert(working);
        }
    }
    return false;
}

void start(int starting_point){
    pile_elem first(route_graph, starting_point), work_elem;
    reduce_graph(first);
    ordered_pile.push_back(first);
    int count = 0;
    auto start = (double)std::clock()/(double)CLOCKS_PER_SEC;
    while(!ordered_pile.empty()){
        work_elem = ordered_pile.back();
        ordered_pile.pop_back();
        // work_elem.print_route();
        count++;
        if(branch_entry(work_elem)) {
            std::cout<<count<<'\n';
            std::cout<<1e6*((double)std::clock()/(double)CLOCKS_PER_SEC - start)/(double) CLOCKS_PER_SEC<<"ns \n";
            return;
        }
    }
    std::cout<<count<<'\n';
}

void omp_start(int starting point){
    pile_elem first(route_graph, starting_point), work_elem;
    int vi[N-1];
    for(int i = 0; i < N; i++){
        if(i < starting_point) vi[i] = i;
        else vi[i] = i+1;
    }
    std::vector<double> ordered_stack;
    reduce_graph(first);
    ordered_stack.push_back(first);
    #pragma parallel for schedule(static) private(ordered_stack)
    for(int i = 0; i < N-1; i++){
        while(!ordered_stack.empty()){
            work_elem = ordered_stack.back();
            ordered_stack.pop_back();
            pile_elem work(work_elem, i);
            
        }
    }
}

int main(int argc, char **argv){
    // srand(2);
    // for(int i = 0; i < N; i++) for(int j = 0; j < N; j++){
    //     if(i == j) route_graph[i][j] = inf;
    //     else route_graph[i][j] = ((double)rand()/RAND_MAX);
    // }
    // print_graph(route_graph);
    // exit(0);
    start(0);
    std::cout<<min_route.reduced_value<<'\n';
    double sum = 0;
    for(int i = 0; i < N-1; i++){
        std::cout<<min_route.full_route[i]<<"->"<<min_route.full_route[i+1]<<": "<<route_graph[min_route.full_route[i]][min_route.full_route[i+1]]<<'\n';
    }
    std::cout<<min_route.full_route[N-1]<<"->"<<min_route.full_route[0]<<": "<<route_graph[min_route.full_route[N-1]][min_route.full_route[0]]<<'\n';
}