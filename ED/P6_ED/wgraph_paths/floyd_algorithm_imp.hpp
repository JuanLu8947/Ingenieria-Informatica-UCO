/**
 * @file floyd_algorithm_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <utility>
#include <limits>
#include <stack>
#include <floyd_algorithm.hpp>

#ifdef __VERBOSE__
extern int Verbose_level;
#endif

inline std::ostream &
print_floyd_I(std::ostream &out,
              IMatrix const &I)
{
    std::string blanks = "          ";
    std::string unders = "__________";
    size_t field_width = 4;
    out << blanks.substr(0, field_width + 1);
    for (size_t i = 0; i < I.cols(); ++i)
        out << std::setw(field_width) << i;
    out << std::endl;
    out << blanks.substr(0, field_width + 1);
    for (size_t i = 0; i < I.cols(); ++i)
        out << std::setw(field_width) << unders.substr(0, field_width);
    out << std::endl;
    for (size_t r = 0; r < I.rows(); ++r)
    {
        out << std::setw(field_width) << r << '|';
        for (size_t c = 0; c < I.cols(); ++c)
        {
            if (I[r][c] == -1)
                out << std::setw(field_width) << '-';
            else
                out << std::setw(field_width) << I[r][c];
        }
        out << std::endl;
    }
    return out;
}

inline std::ostream &
print_floyd_D(std::ostream &out,
              FMatrix const &D)
{
    std::string blanks = "          ";
    std::string unders = "__________";
    size_t field_width = 4;
    out << blanks.substr(0, field_width + 1);
    for (size_t i = 0; i < D.cols(); ++i)
        out << std::setw(field_width) << i;
    out << std::endl;
    out << blanks.substr(0, field_width + 1);
    for (size_t i = 0; i < D.cols(); ++i)
        out << std::setw(field_width) << unders.substr(0, field_width);
    out << std::endl;
    for (size_t r = 0; r < D.rows(); ++r)
    {
        out << std::setw(field_width) << r << '|';
        for (size_t c = 0; c < D.cols(); ++c)
        {
            if (D[r][c] == std::numeric_limits<float>::infinity())
                out << std::setw(field_width) << '-';
            else
                out << std::setw(field_width) << D[r][c];
        }
        out << std::endl;
    }
    return out;
}

/**
 * @brief Compute the weight matrix.
 *
 * Also compute two maps to convert between the vertex key and the index of the matrix.
 *
 * @tparam T Vertex item data type.
 * @param[in] g is the graph.
 * @param[out] D is the distances matrix.
 */
template <class T>
void compute_weight_matrix(Graph<T, float> const &g,
                           FMatrix &D)
{
    D.resize(g.num_vertices(), g.num_vertices(),
             std::numeric_limits<float>::infinity());

    // TODO: Initialize the distances matrix traversing the graph by vertex and edges.
    auto v_it = g.vertices_begin();
    auto v_end = g.vertices_end();

     while(v_it != v_end){
        auto u = *v_it;
        auto e_it = g.edges_begin(v_it);
        auto e_end = g.edges_end(v_it);
        
        while(e_it != e_end){
            auto edge = *e_it;
            size_t src = u->label();
            size_t dst = edge->other(u)->label();
            D[src][dst] = edge->item();
            ++e_it;
        }
        ++v_it;
    }
    /*
    Recorre todos los vértices del grafo
    ·v_it es un iterador sobre los vértices del grafo g.
    ·Para cada vértice u, obtiene su lista de aristas incidentes.

    Para cada arista del vértice actual
    ·e_it recorre todas las aristas conectadas al vértice u.
    ·Para cada arista:
     ·edge->other(u) obtiene el vértice opuesto a u en esa arista.
     ·src es el label (índice) del vértice de origen u.
     ·dst es el label (índice) del vértice destino.
     ·edge->item() es el peso de la arista.

    Rellena la matriz de distancias D
    D[src][dst] = edge->item();
    ·Asigna el peso de la arista a la posición correspondiente en la matriz de distancias.

    Resumen:
    inicializa la matriz de distancias D para el algoritmo de Floyd-Warshall:
    ·Al principio, todas las distancias están a infinito
    ·Este bucle pone el peso real de cada arista en la matriz, de modo que D[i][j] contiene el peso de la arista directa de i a j (si existe).

    ·Recorre todos los vértices y sus aristas.
    ·Para cada arista, actualiza la matriz de distancias con el peso correspondiente.
    ·Así, la matriz D queda lista para que el algoritmo de Floyd-Warshall calcule los caminos mínimos entre todos los pares de vértices.
    */
    //
}

template <class T>
void floyd_algorithm(Graph<T, float> const &g,
                     FMatrix &D,
                     IMatrix &I)
{
    compute_weight_matrix(g, D);
    I.resize(g.num_vertices(), g.num_vertices(), -1);

    // TODO: Codify the Floyd algorithm.
    size_t n = g.num_vertices();
    
    for(size_t k = 0; k < n; ++k)
        for(size_t i = 0; i < n; ++i)
            for(size_t j = 0; j < n; ++j)
                if(D[i][k] + D[k][j] < D[i][j]){ //Comprueba si el camino de i a j pasando por k es más corto que el camino directo conocido hasta ahora.
                    D[i][j] = D[i][k] + D[k][j]; //se actualiza la distancia mínima de i a j.
                    I[i][j] = k; //Guarda que el camino más corto de i a j pasa por el vértice intermedio k.
                }
    /*
    El bucle externo (k) recorre todos los posibles vértices intermedios
    Los bucles internos (i, j) recorren todos los pares de vértices origen (i) y destino (j).

    Resumen:
    ·Calcula la distancia mínima entre todos los pares de vértices.
    ·Permite reconstruir el camino mínimo entre cualquier par usando la matriz I.
    ·Es útil para grafos densos o cuando necesitas conocer todos los caminos mínimos, no solo desde un origen.

    ·El algoritmo prueba, para cada par de vértices, si pasar por un vértice intermedio mejora la distancia.
    ·Si encuentra un camino más corto, actualiza la distancia y el intermedio.
    ·Al final, D[i][j] tiene la distancia mínima de i a j y I[i][j] permite reconstruir el camino.
    */
    //
}

std::list<size_t>
floyd_path(size_t src, size_t dst, IMatrix const &I)
{
    // Prec: distance (u,v) < inf
    std::list<size_t> path;

    // TODO: Find the path.
    // Hint: Think first. Is it necessary to build a binary tree? or it
    // is enough to do an first-depth search using an iterative approach with
    // a stack of pairs (u,v).
    std::stack<std::pair<size_t, size_t>> to_process;
    to_process.push({src, dst});

    while (!to_process.empty()) {
        auto [u, v] = to_process.top(); //Saca el par (u, v) del tope de la pila.
        to_process.pop();

        int k = I[u][v];
        if(k == -1){
            if(path.empty() || path.back() != u)
                path.push_back(u);
            if (u != v)
                path.push_back(v);
        } 
        else{
            to_process.push({k, v});
            to_process.push({u, k});
        }
        /*
        Consulta el intermedio k = I[u][v]:
        ·Si k == -1, no hay vértice intermedio entre u y v:
         ·Si el camino está vacío o el último vértice añadido no es u, añade u al camino.
         ·Si u y v son distintos, añade también v al camino.
        ·Si k != -1, sí hay vértice intermedio:
         ·El camino óptimo de u a v pasa por k.
         ·Por lo tanto, primero hay que encontrar el camino de u a k y luego de k a v.
         ·Se añaden ambos pares a la pila para seguir procesando.
        */
    }
    /*
    Resumen:
    ·Reconstruye el camino mínimo de src a dst usando la matriz de intermedios I.
    ·Lo hace de forma iterativa (usando una pila), evitando la recursión.
    ·El resultado es una lista ordenada de los vértices que forman el camino más corto.

    ·Si entre dos vértices no hay intermedio (k == -1), se añaden directamente al camino.
    ·Si hay intermedio, se descompone el problema en dos subcaminos: de u a k y de k a v, y se procesan ambos.
    ·Así, se reconstruye el camino mínimo completo entre src y dst.

    ·toma la matriz de intermedios de Floyd-Warshall y, usando una pila, reconstruye el camino mínimo entre dos vértices, añadiendo los vértices en orden a la lista path.
    */
    //
    return path;
}
