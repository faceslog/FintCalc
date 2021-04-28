#ifndef FINT_H
#define FINT_H

#include <limits>
#include <map>

// choix d'un type entier non signé
typedef unsigned long int int_t;
typedef unsigned long int mult_t;

// valeur maximum du type entier choisi
static const int_t MAX_INT_T = std::numeric_limits<int_t>::max();

// ------------------------------------------------------------------
// Définition partielle de la classe fint à compléter SANS MODIFIER
// les signatures des opérations fournies ci-après, ce qui permettra
// au professeur de compiler un programme utilisateur de son choix
// qui respecte cette spécification.
// ------------------------------------------------------------------
class fint {

public:
    /**
     * @brief Create a new fint representing the natural number 1.
     */
    fint();
    /**
     * @brief Create a new fint from a natural number.
     * 
     * @param n The represented natural number.
     * @exception std::invalid_argument if the natural number is 0.
     */
    fint(int_t n);
    /**
     * @brief Create a new fint from two lists of prime numbers and their multiplicity.
     * 
     * @param lf The list of prime numbers.
     * @param lm The list of prime number multiplicities.
     * @exception std::invalid_argument if the two lists are not the same size.
     */
    fint(const std::initializer_list<int_t>& lf, const std::initializer_list<mult_t>& lm);
    /**
     * @brief Create a copy of a fint.
     * 
     * @param f The fint to copy.
     */
    fint(const fint& f);

    /**
     * @brief Destroy the fint object.
     */
    ~fint();

    /**
     * @brief Convert the fint to a natural number.
     * 
     * @return The natural number represented by the fint.
     * @exception std::overflow_error if the fint is too large for the int_t type.
     */
    int_t to_int() const;

    /**
     * @brief Indicate whether the fint divides a fint.
     * 
     * @param a The fint to divide.
     * @return True if the fint divides the given one, false otherwise.
     */
    bool divides(const fint& a) const;

    // teste si this est premier
    /**
     * @brief Indicate whether the fint represents a prime number.
     * 
     * @return True if the fint is a prime number, false otherwise.
     */
    bool is_prime() const;

    /**
     * @brief Indicate whether two fint represent the same natural number.
     * 
     * @param a The first fint to compare.
     * @param b The second fint to compare.
     * @return True if the two fint are equal, false otherwise.
     */
    friend bool operator==(const fint& a, const fint& b);
    /**
     * @brief Indicate whether two fint represent a different natural number.
     * 
     * @param a The first fint to compare.
     * @param b The second fint to compare.
     * @return True if the two fint are different, false otherwise.
     */
    friend bool operator!=(const fint& a, const fint& b);

    /**
     * @brief Create the least common multiple of two fint.
     * 
     * @param a The first fint.
     * @param b The second fint.
     * @return A fint representing the least common multiple of the two given fint.
     */
    friend fint lcm(const fint& a, const fint& b);
    /**
     * @brief Replace the fint by its least common multiple with another fint.
     * 
     * @param b The other fint.
     * @return A reference to the object itself.
     */
    fint& lcm(const fint& b);

    /**
     * @brief Create the greatest common divisor of two fint.
     * 
     * @param a The first fint.
     * @param b The second fint.
     * @return A fint representing the greatest common divisor of the two given fint.
     */
    friend fint gcd(const fint& a, const fint& b);
    /**
     * @brief Replace the fint by its greatest common divisor with another fint.
     * 
     * @param b The other fint.
     * @return A reference to the object itself.
     */
    fint& gcd(const fint& b);

    /**
     * @brief Create the product of two fint.
     * 
     * @param a The first factor.
     * @param b The second factor.
     * @return A fint representing the product of the two given fint.
     */
    friend fint operator*(const fint& a, const fint& b);
    /**
     * @brief Multiply the fint by another fint.
     * 
     * @param b The other fint.
     * @return A reference to the object itself.
     */
    fint& operator*=(const fint& b);

    /**
     * @brief Create the quotient of dividing one integer by another.
     * 
     * @param a The divisor.
     * @param b The dividend.
     * @return A fint representing the quotient of dividing the two given fint.
     * @exception std::domain_error if the fint division is unresolvable with an integer.
     */
    friend fint operator/(const fint& a, const fint& b);
    /**
     * @brief Divide the fint by another fint.
     * 
     * @param b The other fint.
     * @return A reference to the object itself.
     * @exception std::domain_error if the fint division is unresolvable with an integer.
     */
    fint& operator/=(const fint& b);

    /**
     * @brief Create the smallest fraction of two fint.
     * 
     * @param f The fraction of fint.
     * @return A fint representing smallest fraction of the two given fint.
     */
    friend std::pair<fint, fint> frac(const std::pair<fint, fint>& f);
    /**
     * @brief Minimize the fraction of the fint with another one.
     * 
     * @param b The dividend.
     * @return A reference to the object itself.
     */
    fint& frac(fint& b);

    /**
     * @brief Create a copy of a fint to a given power.
     * 
     * @param a The fint.
     * @param n The power.
     * @return A fint representing the given fint to the given power.
     * @exception std::invalid_argument if the power is 0.
     */
    friend fint pow(const fint& a, unsigned int n);
    /**
     * @brief Set the fint to a given power.
     * 
     * @param n The power.
     * @return A reference to the object itself.
     * @exception std::invalid_argument if the power is 0.
     */
    fint& pow(unsigned int n);

    /**
     * @brief Convert the fint to a string.
     * 
     * @return A string representation of the fint.
     */
    std::string to_string() const;

    /**
     * @brief Insert a fint into an output stream.
     * 
     * @param os The output stream.
     * @param a  The fint to insert.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const fint& a);

private:
    /**
     * @brief The dictionary of prime numbers associated with their multiplicity.
     */
    std::map<int_t, mult_t> dico;

    /**
     * @brief Add a prime number to the dictionary if it is indeed a divisor of the corresponding
     *        natural number. Also remove it from the natural number.
     * 
     * @param a The natural number to remove the prime number from.
     * @param i The prime number.
     */
    void add_to_dico(int_t& a, const int_t& i);
};

#endif
