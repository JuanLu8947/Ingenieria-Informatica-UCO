/**
 * @file system.hpp
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
#include <vector>
#include "ip_utils.hpp"
#include "hash_table.hpp"

/**
 * @brief A log's entry.
 */
struct LogEntry
{
    /**
     *  @brief constructor
     *  Models a log entry "<arrival time> <remote ip>"
     */
    LogEntry(size_t arrival_time = 0, const IP &remote_ip = IP())
        : time(arrival_time), ip(remote_ip)
    {
    }
    size_t time; /** arrival time*/
    IP ip;       /** ip address from the access is.*/
};

/** @brief The system's log. */
typedef std::vector<LogEntry> Log;

/**
 * @brief Load the log from an stream.
 * @throw std::runtime_error("Wrong input format for log entry.")
 */
std::istream &operator>>(std::istream &in, Log &log) noexcept(false);

/**
 * @brief This class abstracts several OS's operations.
 */
class OS
{
public:
    /** @name Life cicle. */
    /** @{ */

    /** @brief constructor. */
    OS();

    /** @} */

    /** @name Observers. */
    /** @} */

    /**
     *  @brief Abstracts the time() os call.
     *  @see man 3 time
     */
    size_t time() const;

    /**
     * @brief Is banned this ip address?
     */
    bool is_banned(IP const &ip) const;

    /**
     * @brief Gets the the banned ips.
     * @return a vector with pairs <ip, ban end time>.
     */
    std::vector<std::pair<IP, size_t>> banned_ips() const;

    /** @} */

    /** @name Modifiers. */
    /** @} */

    /** @brief Abstracts the sleep() os call.
     * @see man 3 sleep
     */
    size_t sleep(size_t seconds);

    /**
     * @brief Add an ip address to the banned ips list.
     */
    void ban_ip(IP const &ip, size_t ban_time);

    /** @brief abstract the kill of the process. */
    void kill();

    /**
     * @brief Check if the banned time was finished for the banned ips
     * @arg now is the current system time.
     */
    void remove_banned_ips(size_t now);

    /** @} */

protected:
    size_t time_;
    bool kill_;
    HashTable<IP, size_t> banned_ips_;
};

std::ostream &operator<<(std::ostream &out,
                         std::vector<std::pair<IP, size_t>> const &ips);

/**
 * @brief The Operating System.
 * @return a reference that can be used as entry point to the OS.
 */
OS &System();
