/**
 * @file hash.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <cassert>
#include <cstdlib>
#include "hash.hpp"

/**Global object to generate random bits.*/
std::minstd_rand Generator;

double
uniform()
{
    double ret_v = 0.0;
    // TODO
    // Hint: Use std::uniform_real_distribution<double>
    // Remember: use Generator as random bit generator.
    std::uniform_real_distribution<double> dist(0.0, 1.0); //Genera un número aleatorio de forma uniforme entre a y b
    ret_v = dist(Generator); // Genera un número entero aleatorio en el rango [a, b] utilizando std::uniform_int_distribution (Generador global)
    //
    assert(0.0l <= ret_v && ret_v < 1.0l);
    return ret_v;
}

std::uint64_t
pick_at_random(std::uint64_t const &a, std::uint64_t const &b)
{
    assert(a < b);
    std::uint64_t ret_v = 0;
    // TODO
    // Hint: Use std::uniform_int_distribution<std::uint64_t>
    std::uniform_int_distribution<std::uint64_t> dist(a, b); //lo mismo de antes
    ret_v = dist(Generator);
    //
    assert(a <= ret_v && ret_v <= b);
    return ret_v;
}

//////////////////////////////////////////////////////////////
// Universal hash function.
//////////////////////////////////////////////////////////////

UHash::UHash()
{
    m_ = 2;
    p_ = 4294967311l;
    a_ = pick_at_random(std::uint64_t(1), p_);
    b_ = pick_at_random(std::uint64_t(0), p_);

    assert(m() == 2);
    assert(p() == 4294967311l);
    assert(0 < a() && a() < p());
    assert(0 <= b() && b() < p());
}

UHash::UHash(std::uint64_t M)
{
    assert(M > 1 && (M & (M - 1)) == 0); // m is two power.
    assert(M < 4294967311l);

    m_ = M;
    p_ = 4294967311l;
    a_ = pick_at_random(std::uint64_t(1), p_);
    b_ = pick_at_random(std::uint64_t(0), p_);

    assert(M == m());
    assert(p() == 4294967311l);
    assert(0 < a() && a() < p());
    assert(0 <= b() && b() < p());
}

UHash::Ref UHash::create(std::uint64_t m)
{
    return std::make_shared<UHash>(m);
}

UHash::UHash(std::uint64_t M, std::uint64_t P, std::uint64_t A,
             std::uint64_t B)
{
    assert(M > 1 && (M & (M - 1)) == 0); // m is two power.
    assert(M < P);
    assert(0 < A && A < P);
    assert(0 <= B && B < P);

    m_ = M;
    p_ = P;
    a_ = A;
    b_ = B;

    assert(M == m());
    assert(P == p());
    assert(A == a());
    assert(B == b());
}

UHash::Ref UHash::create(std::uint64_t m, std::uint64_t p, std::uint64_t a,
                         std::uint64_t b)
{
    return std::make_shared<UHash>(m, p, a, b);
}

UHash::Ref UHash::pick_at_new(std::uint64_t const &new_m) const
{
    assert(new_m > 1 && (new_m & (new_m - 1)) == 0); // new_m is two power.
    assert(new_m < p());

    UHash::Ref new_f;
    new_f = UHash::create(new_m);

    assert(new_f->m() == new_m);
    assert(new_f->p() == p());
    assert(new_f->a() != a() || new_f->b() != b());
    return new_f;
}

size_t
UHash::operator()(std::uint64_t k) const
{
    assert(k < p());
    size_t hash = 0;

    // TODO
    // Hint: use static_cast to static type conversions.
    hash = static_cast<size_t>(((a() * k + b()) % p()) % m());
        //((a·x + b) mod p) mod m
    //

    assert(hash < m());
    return hash;
}

std::uint64_t const &
UHash::m() const
{
    return m_;
}

std::uint64_t const &
UHash::p() const
{
    return p_;
}

std::uint64_t const &
UHash::a() const
{
    return a_;
}

std::uint64_t const &
UHash::b() const
{
    return b_;
}

//////////////////////////////////////////////////////////////
// Open Addressing Collision Resolution Methods.
//////////////////////////////////////////////////////////////

OACollisionResolution::OACollisionResolution(UHash const &hash_f)
    : hash_f_(hash_f)
{
}

UHash const &
OACollisionResolution::hash() const
{
    return hash_f_;
}
std::uint64_t
OACollisionResolution::m() const
{
    return hash().m();
}

std::uint64_t const &
OACollisionResolution::state() const
{
    return state_;
}

void OACollisionResolution::set_state(std::uint64_t new_state) const
{
    const_cast<OACollisionResolution *>(this)->state_ = new_state;
}

//////////////////////////////////////////////////////////////
// Linear Probing hash function.
//////////////////////////////////////////////////////////////

LPHash::LPHash(UHash const &hash_f)
    : OACollisionResolution(hash_f)
{
}

OACollisionResolution::Ref
LPHash::create(UHash const &hash_f)
{
    return std::make_shared<LPHash>(hash_f);
}

OACollisionResolution::Ref
LPHash::pick_at_new(std::uint64_t new_m) const
{
    assert(new_m > 1 && (new_m & (new_m - 1)) == 0);
    return LPHash::create(UHash(new_m));
}

size_t
LPHash::operator()(uint64_t k, size_t iter) const
{
    size_t ret_v = 0;
    // TODO
    // Remember: if iter == 0 (first attempt), compute the hash value.
    //          iter>0 means a collision happened so get the next proper value
    //          regarding the collision algorithm.
    // Hint: you can use state()/set_state to get/save the first value to avoid recompute it when
    //       a collision happened.
    if (iter == 0){
        ret_v = hash()(k);
        set_state(ret_v);
    }
    else{
        ret_v = (state() + iter) % m();
    }
    /*
    ·Implementa Linear Probing para resolver colisiones.
    ·Si es el primer intento (iter == 0):
     ·Calcula el valor hash inicial usando la función hash (hash()(k)).
     ·Guarda este valor en el estado interno (set_state()).
    ·Si ocurre una colisión (iter > 0):
     ·Calcula el siguiente índice desplazándose linealmente:
      ·ret_v = (state() + iter) % m();
       ·state() contiene el valor hash inicial.
    */
    //
    return ret_v;
}

//////////////////////////////////////////////////////////////
// Quadratic Probing hash function.
//////////////////////////////////////////////////////////////

QPHash::QPHash(UHash const &hash_f)
    : OACollisionResolution(hash_f)
{
}

OACollisionResolution::Ref
QPHash::create(UHash const &hash_f)
{
    return std::make_shared<QPHash>(hash_f);
}

OACollisionResolution::Ref
QPHash::pick_at_new(std::uint64_t new_m) const
{
    assert(new_m > 1 && (new_m & (new_m - 1)) == 0);
    return QPHash::create(UHash(new_m));
}

size_t
QPHash::operator()(std::uint64_t k, size_t iter) const
{
    size_t ret_v = 0;
    // TODO
    // Remember: if iter == 0 (first attempt), compute the hash value.
    //          iter>0 means a collision happened so get the next proper value
    //          regarding the collision algorithm.
    // Hint: you can use state()/set_state to get/save the first value to avoid recompute it when
    //       a collision happened.
    // Remember: m is two power and c1= c2 = 1/2.
    if (iter == 0){
        ret_v = hash()(k);
        set_state(ret_v);
    }
    else{
        std::uint64_t increment = (iter + iter * iter) / 2;
        ret_v = (state() + increment) % m();
    }
    /*
    ·Implementa Quadratic Probing para resolver colisiones.
    ·Si es el primer intento (iter == 0):
     ·Calcula el valor hash inicial y lo guarda en el estado interno.
    ·Si ocurre una colisión (iter > 0):
     ·Calcula el siguiente índice utilizando un desplazamiento cuadrático:
      ·increment = (iter + iter * iter) / 2;
      ·ret_v = (state() + increment) % m();
     ·Esto asegura que los índices probados sigan un patrón cuadrático.
    */
    //
    return ret_v;
}

//////////////////////////////////////////////////////////////
// Random Probing hash function.
//////////////////////////////////////////////////////////////

RPHash::RPHash(UHash const &hash_f, std::uint64_t c)
    : OACollisionResolution(hash_f)
{
    assert(!(c <= m()) || (m() % c != 0));
    assert(!(m() <= c) || (c % m() != 0));
    c_ = c;
}

RPHash::RPHash(UHash const &hash_f)
    : OACollisionResolution(hash_f)
{
    c_ = (m() >> 1) - 1;
}

OACollisionResolution::Ref
RPHash::create(UHash const &hash_f)
{
    return std::make_shared<RPHash>(hash_f);
}

OACollisionResolution::Ref
RPHash::create(UHash const &hash_f, std::uint64_t c)
{
    return std::make_shared<RPHash>(hash_f, c);
}

OACollisionResolution::Ref
RPHash::pick_at_new(std::uint64_t new_m) const
{
    assert(new_m > 1 && (new_m & (new_m - 1)) == 0);
    return RPHash::create(UHash(new_m));
}

std::uint64_t const &
RPHash::c() const
{
    return c_;
}

size_t
RPHash::operator()(std::uint64_t k, size_t iter) const
{
    size_t ret_v = 0;
    // TODO
    // Remember: if iter == 0 (first attempt), compute the hash value.
    //         iter>0 means a collision happened so get the next proper value
    //         regarding the collision algorithm.
    // Hint: you can use state()/set_state to get/save the current hash value to avoid recompute it when
    //       a collision happened.
    if (iter == 0){
        ret_v = hash()(k);
        set_state(ret_v);
    }
    else{
        ret_v = (state() + iter * c()) % m();
    }
    /*
    ·Implementa Random Probing para resolver colisiones.
    ·Si es el primer intento (iter == 0):
     ·Calcula el valor hash inicial y lo guarda en el estado interno.
    ·Si ocurre una colisión (iter > 0):
     ·Calcula el siguiente índice utilizando un desplazamiento aleatorio basado en una constante c:
      ·ret_v = (state() + iter * c()) % m();
    */
    //

    return ret_v;
}

//////////////////////////////////////////////////////////////
// Rehashing hash function.
//////////////////////////////////////////////////////////////

RHash::RHash(UHash const &hash_f, std::vector<UHash> const &hash_fs)
    : OACollisionResolution(hash_f)
{
#ifndef NDEBUG
    for (size_t i = 0; i < hash_fs.size(); ++i)
    {
        assert(hash_fs[i].m() == hash_f.m());
        assert(hash_fs[i].p() == hash_f.p());
    }
#endif
    hash_fs_ = hash_fs;
}

OACollisionResolution::Ref
RHash::create(UHash const &hash_f, std::vector<UHash> const &hash_fs)
{
    return std::make_shared<RHash>(hash_f, hash_fs);
}

const std::vector<UHash> &
RHash::hash_fs() const
{
    return hash_fs_;
}

OACollisionResolution::Ref
RHash::pick_at_new(std::uint64_t new_m) const
{
    assert(new_m > 1 && (new_m & (new_m - 1)) == 0);
    std::vector<UHash> new_hash_fs;
    for (size_t i = 0; i < hash_fs().size(); ++i)
        new_hash_fs.push_back(UHash(new_m));

    return RHash::create(UHash(new_m), new_hash_fs);
}

size_t
RHash::operator()(std::uint64_t k, size_t iter) const
{
    size_t ret_v = 0;
    // TODO
    // Remember: if iter == 0 (first attempt), compute the hash value using
    // the hash_fs()[0], iter==1 using hash_fs()[1], ..., for iter>=hash_fs().size()
    // use linear probing from the last hash value.
    // Hint: you can use state()/set_state to get/save the current hash value to avoid recompute it when
    //       a collision happened.
    if(iter == 0){
        ret_v = hash()(k);
        set_state(ret_v);
    }
    else if (iter <= hash_fs().size()){
        ret_v = hash_fs()[iter-1](k);
        set_state(ret_v);
    }
    else{
        ret_v = (state() + (iter - hash_fs().size())) % m();
    }
    /*
    ·Implementa Rehashing para resolver colisiones.
    ·Si es el primer intento (iter == 0):
     ·Calcula el valor hash inicial usando la función hash principal.
    ·Si iter está dentro del rango de funciones hash adicionales (iter <= hash_fs().size()):
     ·Usa la función hash correspondiente (hash_fs()[iter-1]).
    ·Si iter excede el número de funciones hash:
     ·Aplica Linear Probing desde el último valor hash calculado:
      ·ret_v = (state() + (iter - hash_fs().size())) % m();
    */
    //

    return ret_v;
}
