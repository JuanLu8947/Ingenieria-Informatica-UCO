/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <pattern.hpp>

Pattern::Pattern()
{
    // TODO
    _class_label = -1; //indica sin etiqueta  comprobado por assert
    _values = std::make_shared<std::valarray<float>>(0);
    //
    assert(dim() == 0);
    assert(class_label() == -1);
}

Pattern::Pattern(float *values, const size_t size, const int cl)
{
    assert(size > 0);
    // TODO
    //constructor, asignación
    _class_label = cl;
    _values = std::make_shared<std::valarray<float>>(values, size);
    //reserva memoria para ese vector con ese tamaño size
    //
    assert(dim() == size);
    assert(class_label() == cl);
}

Pattern::~Pattern()
{
    // TODO

    //
}

size_t Pattern::dim() const
{
    size_t d = 0;
    // TODO
    //GetDim
    d = _values->size(); //obtención del tamaño del vector usado
    //
    return d;
}

int Pattern::class_label() const
{
    int cl = -1;
    // TODO
    cl = _class_label; //GetLabel
    //
    return cl;
}

const std::valarray<float> &
Pattern::values() const
{
    // TODO
    //return std::valarray<float>(); // FIXME
    return *_values; //cte y sólo devuelve con referencia a los valores
    //
}

void Pattern::set_class_label(const int new_label)
{
    // TODO
    _class_label = new_label;
    //
    assert(class_label() == new_label);
}

std::valarray<float> &
Pattern::values()
{
    // TODO
    /*std::valarray<float> fixme;
    return fixme;*/
    return *_values;
    /*La función Pattern::values() devuelve una referencia a un std::valarray<float> que contiene los valores del patrón. */
    //
}

void Pattern::reset(float *values, const size_t size, const int cl)
{
    assert(size >= 0);
    // TODO
    //reseta los valores, por tanto:
    _class_label = cl;
    _values = std::make_shared<std::valarray<float>>(values, size);
    //
    assert(dim() == size);
    assert(class_label() == cl);
}

std::ostream &operator<<(std::ostream &output, const Pattern &p)
{
    // TODO
    // Remember: format "[ class_label [ v0 v1 ... vn-1 ] ]"
    output << "[ " << p.class_label() << " [ ";
    for(size_t i = 0; i < p.dim(); i++)
        output << p.values()[i] << " ";
        /*
        p: Es una referencia constante a un objeto de la clase Pattern.
        ·p.values(): Llama al método values() de la clase Pattern, que devuelve una referencia constante a un std::valarray<float>.
        ·p.values()[i]: Accede al elemento en la posición i del std::valarray<float> devuelto por values().
        */
    output << "] ]";
    //
    return output;
}

std::istream &operator>>(std::istream &in, Pattern &p) noexcept(false)
{
    // TODO
    // Remember: input format is "[ class_label [ v_0 v_1 ... v_size-1 ] ]"
    std::string token;
    in >> token; //como un token es [, vcada vez que se hace el volcado comprobamos
    if(token != "[")
        throw std::runtime_error("wrong input format");
    
    int cl; //declaración ClassLabel
    in >> cl; //volcamos de lo recibido a la etiqueta de clase
    p.set_class_label(cl); //uso del método set para estbalecer la etiqueta
    in >> token;
    if(token != "[")
        throw std::runtime_error("wrong input format");

    std::vector<float> values; //declaración vector values
    float value; //para los valores en sí
    
    while(in >> token && token != "]"){ //mientras se pueda volcar, es decir, haya algo que volcar y no sea el final
        std::istringstream iss(token);/* Esta línea crea un objeto std::istringstream a partir del token leído. std::istringstream es una clase de flujo de entrada que permite leer datos desde una cadena de texto (std::string).*/
        if(iss >> value)
            values.push_back(value);
        else{
            throw std::runtime_error("wrong input format");
        }
    }

    if (token != "]")
        throw std::runtime_error("wrong input format");

    if(!(in >> token) || token != "]")
        throw std::runtime_error("wrong input format");

    float *v = new float[values.size()]; //reserva de memoria para los valores
    for(size_t i = 0; i < values.size(); i++)
        v[i] = values[i];
    p.reset(v, values.size(), cl);
    //
    return in;
}

float distance_L2(const Pattern &a, const Pattern &b)
{
    assert(a.dim() == b.dim());
    float dist = 0.0;
    // TODO
    //*distance_L2(a, b) = sqrt(sum_i(a[i] - b[i]) ^ 2)
    float sum = 0.0;
    for (size_t i = 0; i < a.dim(); i++)
    {
        sum += pow(a.values()[i] - b.values()[i], 2);
    }
    dist = sqrt(sum);
    //
    assert(dist >= 0.0);
    return dist;
}

float distance_L1(const Pattern &a, const Pattern &b)
{
    assert(a.dim() == b.dim());
    float dist = 0.0;
    // TODO
    for(size_t i=0; i < a.dim(); i++)
        dist += std::abs(a.values()[i] - b.values()[i]);
    //distancia de toda la vida
    //
    assert(dist >= 0.0);
    return dist;
}

std::istream &
load_dataset(std::istream &input,
             std::vector<Pattern> &dts) noexcept(false)
{
    // TODO
    // Remember: input format is
    // "<size_t num_patterns> <size_t pattern_dimensions>
    // <p_0>
    // <p_1>
    // ...
    // <p_num_patterns-1>
    // "
    size_t num_patterns, pattern_dimensions;
    input >> num_patterns >> pattern_dimensions; //volcamos la entrada en las variables
    dts.resize(num_patterns); //redimensionamos el vector de patrones
    for(size_t i = 0; i < num_patterns; i++){
        Pattern p; //creamos un patrón p
        input >> p; //volacado de la entrada al patrón
        dts[i] = p; //asignamos el patrón al vector de patrones
        if(dts[i].dim() != pattern_dimensions) //comprobamos q es correcta la dimension de cada patrón
            throw std::runtime_error("wrong input format");
    }
    //
    return input;
}
