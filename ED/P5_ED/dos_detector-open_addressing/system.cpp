/**
 * @file system.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <string>
#include <sstream>

#include "system.hpp"
#include "hash_table_imp.hpp"

void OS::remove_banned_ips(size_t now)
{
    std::vector<IP> ips;

    // TODO: Scan the table of banned ips to push back in vector ips the banned ips
    // whose ban time was finished at this moment (time <= now).
    for (auto iter = banned_ips_.begin(); iter != banned_ips_.end(); ++iter)
        if (iter.value() <= now)
            ips.push_back(iter.key());
    /*
    ·Este bloque recorre la tabla banned_ips_ para encontrar las direcciones IP cuyo tiempo de bloqueo ha expirado (es decir, ban_time <= now).
    ·Pasos principales:
     ·Se utiliza un iterador para recorrer todas las entradas de la tabla hash banned_ips_.
     ·Si el valor asociado a una IP (el tiempo de desbloqueo) es menor o igual a now, se agrega la IP al vector ips.
    */
    //

    std::cout << "IPs which ban time was finished at time " << now << " [";
    for (size_t i = 0; i < ips.size(); ++i)
        std::cout << ' ' << ips[i];
        
    std::cout << " ]" << std::endl;

    // TODO: Remove the ips from the banned_ips_ table.
    for (const auto &ip : ips){
        auto iter = banned_ips_.find(ip);
        if (iter.is_valid())
            banned_ips_.remove(iter);
    }
    /*
    ·Este bloque elimina las direcciones IP cuyo tiempo de bloqueo ha expirado de la tabla banned_ips_.
    ·Pasos principales:
     ·Se recorre el vector ips, que contiene las direcciones IP a eliminar.
     ·Para cada IP, se busca su posición en la tabla hash utilizando banned_ips_.find(ip).
     ·Si la entrada es válida, se elimina de la tabla con banned_ips_.remove(iter).
    */
    //

#ifndef NDEBUG
    for (auto const &ip : ips)
        assert(!banned_ips_.find(ip).is_valid());
#endif
}

void OS::ban_ip(IP const &ip, size_t ban_time)
{
    std::cout << "Ban ip: " << ip << " from time " << time_ << " to " << time_ + ban_time << std::endl;
    // TODO
    // Remember: Insert in banned_ips_ table the time when the ban
    // time will be finished.
    banned_ips_.insert(ip, time_ + ban_time);
    /*
    ·Este método bloquea una dirección IP durante un tiempo específico.
    ·Pasos principales:
     ·Calcula el tiempo en el que el bloqueo terminará: time_ + ban_time.
     ·Inserta la dirección IP en la tabla banned_ips_ con el tiempo de desbloqueo como valor asociado.
    */
    //
}

bool OS::is_banned(IP const &ip) const
{
    bool ret_val = false;
    // TODO
    // Hint: Has banned_ips_ table that ip?
    auto iter = banned_ips_.find(ip);
    ret_val = iter.is_valid();
    /*
    ·Este método verifica si una dirección IP está bloqueada.
    ·Pasos principales:
     ·Busca la dirección IP en la tabla banned_ips_ utilizando banned_ips_.find(ip).
     ·Si la entrada es válida (iter.is_valid()), significa que la IP está bloqueada.
    */
    //
    return ret_val;
}

std::vector<std::pair<IP, size_t>>
OS::banned_ips() const
{
    std::vector<std::pair<IP, size_t>> ips;
    // TODO
    // Hint: use const_cast to remove const from this.
    auto &non_const_this = const_cast<OS &>(*this);
    for (auto iter = non_const_this.banned_ips_.begin(); iter != non_const_this.banned_ips_.end(); ++iter)
        ips.emplace_back(iter.key(), iter.value());
    /*
    ·Este método devuelve un vector con todas las direcciones IP bloqueadas y sus tiempos de desbloqueo.
    ·Pasos principales:
     ·Se utiliza const_cast para eliminar el modificador const del objeto actual (this), ya que banned_ips_ no puede ser modificado directamente en un método const.
     ·Se recorre la tabla banned_ips_ con un iterador.
     ·Para cada entrada, se agrega un par (IP, tiempo de desbloqueo) al vector ips.
    */
    //
    return ips;
}

////////////////////////////////////////////////
// Other system operations.
///////////////////////////////////////////////

std::istream &
operator>>(std::istream &in, Log &log) noexcept(false)
{
    log.resize(0);
    std::string buffer;
    std::istringstream input;
    LogEntry entry;
    while (std::getline(in, buffer))
    {
        if (buffer == "")
            continue;
        input.str(buffer);
        input.clear();
        input >> entry.time >> entry.ip;
        if (!input)
            throw std::runtime_error("Wrong input format for log entry.");
        log.push_back(entry);
    }
    return in;
}

OS::OS() : time_(0), kill_(false), banned_ips_(16, ip_to_int,
                                               LPHash::create(UHash(16)))
{
}

size_t
OS::time() const
{
    return time_;
}

size_t
OS::sleep(size_t seconds)
{
    time_ += seconds;
    remove_banned_ips(time_);
    if (kill_)
        return seconds;
    else
        return 0;
}

void OS::kill()
{
    kill_ = true;
}

OS &System()
{
    static std::shared_ptr<OS> system_;
    if (!system_)
        system_ = std::make_shared<OS>();
    return *system_;
}

std::ostream &
operator<<(std::ostream &out, std::vector<std::pair<IP, size_t>> const &ips)
{
    out << "[";
    for (size_t i = 0; i < ips.size(); ++i)
        out << ' ' << ips[i].first << ':' << ips[i].second;
    out << " ]";
    return out;
}
