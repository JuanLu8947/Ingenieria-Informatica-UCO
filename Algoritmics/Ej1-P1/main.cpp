#include "medioNivel.hpp"

int main(){
    srand(time(0));
    int o;
    do{
        cout << "\n=== MENU PRINCIPAL ===\n"
             << "1. Ordenacion por seleccion" << endl
             << "2. Ordenacion por Quicksort" << endl
             << "3. Determinante de una matriz (Iterativo)" << endl
             << "4. Torres de Hanoi" << endl
             << "5. Torres de Hanoi con Ajuste Exponencial" << endl
             << "6. Torres de Hanoi con Ajuste Factorial" << endl
             << "7. Comparar Ajustes (Exponencial vs Factorial)" << endl
             /*<< "---- APARTADO OPCIONAL ----" << endl
             << "8. Selección (Validación 80%-20%)" << endl
             << "9. Quicksort (Validación 80%-20%)" << endl
             << "10. Determinante (Validación 80%-20%)" << endl*/
             << "-------------------------" << endl
             << "0. Salir" << endl
             << "Seleccione una opción: ";
        cin >> o;
        switch(o){
            case 1:
                ordenacionSeleccion();
                break;
            case 2:
                ordenacionQuicksort();
                break;
            case 3:
                determinanteIterativo();
                break;
            case 4:
                torresDeHanoi();
                break;
            case 5:
                torresDeHanoiConAjuste();
                break;
            case 6:
                torresDeHanoiConAjusteFactorial();
                break;
            case 7:
                compararAjustesHanoi();
                break;
            /*case 8:
                ordenacionSeleccionOpcional();
                break;
            case 9:
                ordenacionQuicksortOpcional();
                break;
            case 10:
                determinanteOpcional();
                break;*/
            case 0:
                cout << "\nSaliendo del programa..." << endl;
                exit(0);
                break;
            default:
                cout << "\nOpción no válida. Intente de nuevo.\n";
                break;
        }
    }while(o != 0);
}