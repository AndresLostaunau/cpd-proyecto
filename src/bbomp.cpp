#include "tsmp.cpp"
#include <omp.h>

double max_value = inf;
pile_elem min_route;

void ordered_insert(pile_elem ins, std::vector<pile_elem> &os){
    for(auto it = os.begin(); it != os.end(); it++){
        if(ins.reduced_value > it->reduced_value){
            os.insert(it, ins);
            return;
        }
    }
    os.push_back(ins);
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

bool branch_entry(pile_elem node, std::vector<pile_elem> &os){
    pile_elem working;
    for(int i = 0; i < N; i++){
        if(node.visited[i]) continue;
        working = pile_elem(node, i);
        reduce_graph(working);
        // if(working.reduced_value >= max_value) continue;
        if(working.is_complete()){
            #pragma omp critical
            {
                if(working.reduced_value < max_value){
                    max_value = working.reduced_value;
                    min_route = working;
                }
            }
            return true;
        }else{
            ordered_insert(working, os);
        }
    }
    return false;
}

void omp_start(int starting_point){
    pile_elem first(route_graph, starting_point), work_elem;
    int vi[N-1];
    for(int i = 0; i < N; i++){
        if(i < starting_point) vi[i] = i;
        else vi[i] = i+1;
    }
    reduce_graph(first);
    omp_set_num_threads(4);
    double start = omp_get_wtime();
    #pragma omp parallel shared(min_route, max_value) private(work_elem)
    {
        std::vector<pile_elem> ordered_stack;
        #pragma omp master
        printf("Número de hilos: %d\n", omp_get_num_threads());

        #pragma omp for schedule(static) 
        for(int i = 0; i < N-1; i++){
            pile_elem work(first, i);
            reduce_graph(work);
            ordered_insert(work, ordered_stack);
        }

        do{
            work_elem = ordered_stack.back();
            ordered_stack.pop_back();
        }while(!branch_entry(work_elem, ordered_stack));
    }
    printf("Tiempo: %.3f ms\n", (omp_get_wtime()-start)*1e3);   
}

int main(int argc, char **argv){
    // srand(2);
    // for(int i = 0; i < N; i++) for(int j = 0; j < N; j++){
    //     if(i == j) route_graph[i][j] = inf;
    //     else route_graph[i][j] = ((double)rand()/RAND_MAX);
    // }
    omp_start(0);
    std::cout<<min_route.reduced_value<<'\n';
    // for(int i = 0; i < N-1; i++){
    //     std::cout<<min_route.full_route[i]<<"->"<<min_route.full_route[i+1]<<": "<<route_graph[min_route.full_route[i]][min_route.full_route[i+1]]<<'\n';
    // }
    // std::cout<<min_route.full_route[N-1]<<"->"<<min_route.full_route[0]<<": "<<route_graph[min_route.full_route[N-1]][min_route.full_route[0]]<<'\n';
}