/**
 * @file hash.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once
#include <cstddef> //for size_t
#include <cstdint> //for uint64_t
#include <memory>
#include <vector>
#include <random> //To generate random numbers.

/**
 * @brief Use this random bit generator to generate random numbers.
 *
 */
extern std::minstd_rand Generator;

/**
 * @brief Generate an uniform random number in [0.0, 1.0) interval.
 * @return the random number.
 * @post ret_v in [0.0, 1.0)
 */
double uniform();

/**
 * @brief pick at random a value from the integer range [a, b).
 * @param a is lower bound of the range (inclusive).
 * @param b is upper bound of the range (exclusive).
 * @return the picked up value.
 * @prec a<b
 * @post ret_v in [a,b)
 */
std::uint64_t pick_at_random(std::uint64_t const &a, std::uint64_t const &b);

/**
 * @brief The Universal Hash function base class.
 *
 * A universal hash function is one pick at at random from the universal family
 * H_p : {h(K) = ((a*K+b)%p)%m) }
 * where p is a prime number greater than the cardinality of the set of keys,
 * 0<a<p and 0<=b<p. The parameter m is the size of the table and is usually a power of two.
 */
class UHash
{
public:
    /**
     * @brief A reference to a hash function.
     */
    typedef std::shared_ptr<UHash> Ref;
    /** @name Life cicle. */
    /** @{ */

    /**
     * @brief Create a hash function.
     * @post m()==2
     * @post p()==4294967311l
     * @post 0 < a() && a() < p()
     * @post 0 <= b() && b() < p()
     */
    UHash();

    /**
     * @brief Create a hash function.
     * The parameter P will be the prime number 4294967311l. The parameters 'a'
     * and 'b' are picked at random.
     * @param m is the table size.
     * @pre m is power of two greater than 1.
     * @pre m<4294967311l
     * @post m()==m
     * @post p()==4294967311l
     * @post 0 < a() && a() < p()
     * @post 0 <= b() && b() < p()
     */
    UHash(std::uint64_t m);

    /**
     * @brief Create a hash function.
     * The parameter P will be the prime number 4294967311l. The parameters 'a'
     * and 'b' are picked at random.
     * @param m is the table size.
     * @return a reference to the hash function.
     * @pre m is power of two greater than 1.
     * @pre m<4294967311l
     * @post m()==m
     * @post p()==4294967311l
     * @post 0 < a() && a() < p()
     * @post 0 <= b() && b() < p()
     */
    static Ref create(std::uint64_t m);

    /**
     * @brief Create a universal hash.
     * @param m is the table size.
     * @param p ,
     * @param a ,
     * @param b are the parameters of the Universal hash function.
     * @pre m is power of two greater than 1.
     * @pre p is a prime number
     * @pre m<p
     * @pre 1<=a<p
     * @pre 0<=b<p
     */
    UHash(std::uint64_t m, std::uint64_t p, std::uint64_t a, std::uint64_t b);

    /**
     * @brief Create a hash function.
     * @param m is the table size.
     * @param p ,
     * @param a ,
     * @param b are the parameters of the Universal hash function.
     * @pre m is power of two greater than 1.
     * @pre m<p
     * @pre p is a prime number.
     * @pre 1<=a<p
     * @pre 0<=b<p
     */
    static Ref create(std::uint64_t m, std::uint64_t p, std::uint64_t a,
                      std::uint64_t b);
    /** @} */

    /** @name Observers. */
    /** @} */

    /**
     * @brief Create a new hash function pick up at random from de Universal
     *        Family.
     * @param m is the new table size.
     * @return a reference a to the new hash function.
     * @pre m is power of two greater than 1.
     */
    virtual Ref pick_at_new(std::uint64_t const &m) const;

    /**
     * @brief hash a key.
     * Hash the key to get a table index.
     * @param k is the key to be hashed.
     * @return the table index.
     * @pre k<p()
     * @post 0<=ret_v<m()
     */
    size_t operator()(std::uint64_t k) const;

    /**
     * @brief the m parameter.
     */
    std::uint64_t const &m() const;

    /**
     * @brief the m parameter.
     */
    std::uint64_t const &p() const;

    /**
     * @brief the m parameter.
     */
    std::uint64_t const &a() const;

    /**
     * @brief the m parameter.
     */
    std::uint64_t const &b() const;

    /** @} */
protected:
    std::uint64_t m_;
    std::uint64_t p_;
    std::uint64_t a_;
    std::uint64_t b_;
};

/**
 * @brief Base class for Open Addressing Collision Resolution algorithms. *
 */
class OACollisionResolution
{
public:
    OACollisionResolution(UHash const &hash_f);

    /**
     * @brief A reference to a hash function.
     */
    typedef std::shared_ptr<OACollisionResolution> Ref;

    /**
     * @brief hash a key with collision resolution.
     * Hash the key to get a table index, giving alternatives for several probes.
     * When @a iter is 0, the value returned is the hashing for the given key @k.
     * When @a iter is greater than 0, the value returned is the next value of
     * the collision resolution algorithm.
     * @param k is the key to be hashed.
     * @param iter is the number of probes generates upto now.
     * @return the table index.
     * @pre k<p()
     */
    virtual size_t operator()(std::uint64_t k, size_t iter) const = 0;

    /**
     * @brief Get a new version of the algorithm with a new table.
     * A new hash function function will be choosen at random.
     * @param new_m is the new table size.
     * @pre new_m is power of two greater than 1.
     * @return a new version of the algorithm.
     */
    virtual OACollisionResolution::Ref pick_at_new(std::uint64_t new_m) const = 0;

    /**
     * @brief Return the cardinality of the hash function.
     *
     * @return the cardinality of the hash function.
     */
    virtual std::uint64_t m() const;

    /**
     * @brief Get the hash function used.
     *
     * @return UHash::Ref to the hash function.
     */
    UHash const &hash() const;

protected:
    /**
     * @brief get the state value.
     *
     * @return the state value.
     */
    std::uint64_t const &state() const;

    /**
     * @brief Set the state value.
     *
     * @param new_state
     */
    void set_state(std::uint64_t new_state) const;

    UHash hash_f_;        /**< the universal hash function for integers.*/
    std::uint64_t state_; /**< the first/last probe value of the hash function.*/
};

/**
 * @brief Models an Universal Family hash function using
 *        linear probing to resolve collisions.
 */
class LPHash : public OACollisionResolution
{
public:
    /** @name Life cycle. */
    /** @{ */

    /**
     * @brief Create a hash function using linear probing method for collision resolution.
     * @param hash_f is the universal hash function used.
     */
    LPHash(UHash const &hash_f);

    /**
     * @brief Create a hash function using linear probing method for collision resolution.
     * @param hash_f is the universal hash function used.
     */
    static OACollisionResolution::Ref create(UHash const &hash_f);

    /** @} */

    /** @name Observers. */
    /** @} */

    size_t operator()(std::uint64_t k, size_t iter = 0) const override;

    OACollisionResolution::Ref pick_at_new(std::uint64_t new_m) const override;

    /** @} */
};

/**
 * @brief Models an Universal Family hash function using
 *        quadratic probing to resolve collisions.
 *
 *        This function assume that the table size is two power and
 *        the parameters c1=c2=0.5
 */
class QPHash : public OACollisionResolution
{
public:
    /** @name Life cycle. */
    /** @{ */

    /**
     * @brief Create a hash function using quadratic probing method for collision resolution.
     * @param hash_f is the universal hash function used.
     */
    QPHash(UHash const &hash_f);

    /**
     * @brief Create a hash function using quadratic probing method for collision resolution.
     * @param hash_f is the universal hash function used.
     */
    static OACollisionResolution::Ref create(UHash const &hash_f);

    /** @} */

    /** @name Observers. */
    /** @} */

    size_t operator()(std::uint64_t k, size_t iter = 0) const override;
    OACollisionResolution::Ref pick_at_new(std::uint64_t new_m) const override;
};

/**
 * @brief Models an Universal Family hash function using  random probing to resolve collisions.
 *
 * The c parameter is set to (m/2)-1, so we assure c and m are prime relative.
 */
class RPHash : public OACollisionResolution
{
public:
    /** @name Life cycle. */
    /** @{ */
    /**
     * @brief Create a hash function using random probing method for collision resolution.
     * @param hash_f is the universal hash function used.
     * @post c()== m()/2 - 1
     */
    RPHash(UHash const &hash_f);

    /**
     * @brief Create a hash function using random probing method for collision resolution.
     * @param hash_f is the universal hash function used.
     * @post c()== m()/2 - 1
     */
    static OACollisionResolution::Ref create(UHash const &hash_f);

    /**
     * @brief Create a hash function using random probing method for collision resolution.
     * @param hash_f is the universal hash function used.
     * @param c is the random probing parameter.
     * @pre c < m() and m()%c != 0 || m()<c and c%m() != 0
     */
    RPHash(UHash const &hash_f, std::uint64_t c);

    /**
     * @brief Create a hash function using random probing method for collision resolution.
     * @param hash_f is the universal hash function used.
     * @param c is the random probing parameter.
     * @pre c < m() and m()%c != 0 || m()<c and c%m() != 0
     */
    static OACollisionResolution::Ref create(UHash const &hash_f, std::uint64_t c);

    /** @} */

    /** @name Observers. */
    /** @} */

    size_t operator()(std::uint64_t k, size_t iter = 0) const override;
    OACollisionResolution::Ref pick_at_new(std::uint64_t new_m) const override;

    /**
     * @brief Get the c parameter.
     *
     * @return the c parameter.
     */
    std::uint64_t const &c() const;

    /** @} */

protected:
    std::uint64_t c_;
};

/**
 * @brief Models an Universal Family hash function using double rehashing to resolve collisions.
 *
 * If at the end a collision still happens, linear probing will be used.
 *
 */
class RHash : public OACollisionResolution
{
public:
    /** @name Life cycle. */
    /** @{ */

    /**
     * @brief Create a hash function using rehashing method for collision resolution.
     * @param hash_f is the first hash function to use.
     * @param hash_fs is a vector with the rest of universal hash functions used in the rehashing process.
     * @pre all hash functions in @a hash_fs have same m and p parameters than @a hash_f
     */
    RHash(UHash const &hash_f, std::vector<UHash> const &hash_fs);

    /**
     * @brief Create a hash function using rehashing method for collision resolution.
     * @param hash_f is the first hash function to use.
     * @param hash_fs is a vector with the rest of universal hash functions used in the rehashing process.
     * @pre all hash functions in @a hash_fs have same m and p parameters.
     */
    static OACollisionResolution::Ref create(UHash const &hash_f,
                                             const std::vector<UHash> &hash_fs);

    /** @} */

    /** @name Observers. */
    /** @} */

    size_t operator()(std::uint64_t k, size_t iter = 0) const override;
    OACollisionResolution::Ref pick_at_new(std::uint64_t new_m) const override;

    /**
     * @brief Get the vector of hash functions.
     *
     * @return the vector of hash functions.
     */
    const std::vector<UHash> &hash_fs() const;

    /** @} */
protected:
    std::vector<UHash> hash_fs_;
};
