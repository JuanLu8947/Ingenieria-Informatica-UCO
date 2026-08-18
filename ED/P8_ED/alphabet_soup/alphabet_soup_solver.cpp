/**
 * @file alphabet_soup_solver.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <trie.hpp>
#include "alphabet_soup_solver.hpp"

/**
 * @brief scan a cell looking for the next letter of a word.
 * @param row and
 * @param col are the current cell coordinates.
 * @param dy and
 * @param dx are direction vector to follow the next letter.
 * @param soup is the alphabet soup where looking for.
 * @param trie is the current subtrie.
 * @param scan_result save the current chain. Is a pair of <word, cells_coordinates [row,col]>
 *
 */
void scan_cell(int row, int col, int dy, int dx, AlphabetSoup const &soup,
               Trie &trie, ScanResult &scan_result)
{
    // TODO
    // ALGORITHM
    // 1. If the trie's prefix is a key then
    //    a word is found. Save the key as the first item of the scan_result
    //    pair and return from this level of recursion.
    // 2. Else if there is a sub-trie for the symbol (row,col), there is two cases:
    // 2.1.1 (dx==dy==0) The cell (row,col) is the first letter of a word.
    //       If there is a sub-trie whose prefix is this symbol, start a new
    //       recursive scanning of the 3x3 neighborhood from this position
    //       using this sub-trie.
    // 2.1.2 (dx!=0 or dy!=0) The cell (row,col) is the next letter of a
    //       started scanning following the direction (dx,dy). If there is a
    //       sub-trie whose prefix is this symbol, continue the scanning
    //       following the direction (dx,dy) recursively.
    // 2.2 After recursion comes back, if a word was found (first item of
    //     the scan_result pair != ""), push the current cell's coordinates
    //     (row,col) into the second item of scan_result (the stack of
    //     coordinates).
    Trie node;
    if(trie.is_key()){ //Si el subtrie actual representa una palabra completa (es decir, el prefijo actual es una palabra buscada), guarda esa palabra en scan_result.first y termina la búsqueda recursiva por este camino.
        scan_result.first=trie.prefix();
        return;
    }
    /*
    Si el subtrie actual representa una palabra completa (es decir, el prefijo actual es una palabra buscada), 
     guarda esa palabra en scan_result.first y termina la búsqueda recursiva por este camino.
    */

    else{ //Si no es una palabra completa, verifica que la celda (row, col) esté dentro de los límites de la sopa.
        if(row>=0 && row<soup.rows() && col>=0 && col<soup.cols()){
            auto aux=soup.cell(row, col); //Obtiene el símbolo (letra) de la celda actual.
            if(trie.find_symbol(aux)){ //Comprueba si el Trie tiene un hijo con el símbolo de la celda actual.
                                       //Avanza el Trie a ese subtrie (con trie=trie.current()).
                node=trie;
                trie=trie.current();
                if(dx==dy && dx==0){ //Si es la primera llamada (no hay dirección de avance), explora todas las celdas vecinas (3x3 alrededor) recursivamente, buscando posibles continuaciones de palabras.
                    for(int r=std::max(0,row-1); r<row+2; r++)
                        for(int c=std::min(col-1, soup.cols()); c<col+2; c++)
                            if(r!=row || c!=col){
                                if(scan_result.first!="")//comprobar que no haya mostrado antes la solución
                                    break;
                                
                                scan_cell(r,c,c-col,r-row,soup,trie,scan_result);
                            }
                }
                else{ //Si ya se está siguiendo una dirección (dx o dy distinto de 0), sigue avanzando en esa dirección recursivamente.
                    scan_cell(row+dx, col+dy,dy, dx, soup, trie, scan_result);
                }
                if(scan_result.first!="") //Si se ha encontrado una palabra en la recursión, añade la celda actual a la pila de coordenadas de la solución
                    scan_result.second.push(std::make_pair(row, col));

                trie=node; //Restaura el Trie al estado anterior a la recursión, para no perder el contexto al volver de la llamada recursiva.
            }
        }
    }
    /*
    Resumen:
    La función busca recursivamente palabras en una sopa de letras usando un Trie. 
     El Trie representa todas las palabras a buscar, y se va "navegando" por él según las letras encontradas en la sopa.

    ·Si el prefijo es palabra, guarda y termina.
    ·Si no, busca la letra en el Trie.
     ·Si es la primera letra, explora todas las direcciones.
     ·Si ya hay dirección, sigue en esa dirección.
    ·Si encuentra palabra, apila la celda.
    ·Siempre restaura el Trie tras la recursión.
    */
    //
}

std::vector<ScanResult>
alphabet_soup_solver(AlphabetSoup &soup, std::vector<std::string> const &words)
{
    std::vector<ScanResult> results;
    Trie trie;

    // Generate a trie with the words to be found as keys.
    for (size_t i = 0; i < words.size(); ++i)
        trie.insert(words[i]);

    // We scan all the soup to find a first letter of any key.
    for (int row = 0; row < soup.rows(); ++row)
    {
        for (int col = 0; col < soup.cols(); ++col)
        {
            auto scan_result = std::make_pair(std::string(""),
                                              std::stack<std::pair<int, int>>());
            // Scan from this cell. This is the first letter so dx==dy==0.
            scan_cell(row, col, 0, 0, soup, trie, scan_result);
            if (scan_result.first != "")
                // A word was found so save it into the results.
                results.push_back(scan_result);
        }
    }
    return results;
}
