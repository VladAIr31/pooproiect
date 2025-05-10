//
// Created by vladg on 5/5/2025.
//

#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <stdexcept>
#include <string>

// Baza pentru toate erorile specifice jocului
class RomopolyError : public std::runtime_error {
public:
    explicit RomopolyError(const std::string& message)
        : std::runtime_error("Eroare Romopoly: " + message) {}
};
class InsufficientFundsError : public RomopolyError {
    int needed;
    int available;

public:
    InsufficientFundsError(const std::string& playerName, int needed, int available)
        : RomopolyError("The player '" + playerName + " doesn't have enough money"),
          needed(needed), available(available)
    {}

    int getneeded() const { return needed; }
    int getDisponibil() const { return available; }


    const char* what() const noexcept override {
        static std::string msg_buffer;
        msg_buffer = std::runtime_error::what();
        msg_buffer += " Needed: " + std::to_string(needed)
                    + "Available: " + std::to_string(available);
        return msg_buffer.c_str();
    }
};



class PropertyUnavailableError : public RomopolyError {
public:
    explicit PropertyUnavailableError(const std::string& message)
       : RomopolyError("Unvailable proprety " + message) {}
};

class InvalidActionError : public RomopolyError {
public:
    explicit InvalidActionError(const std::string& message)
       : RomopolyError("Invalid Action " + message) {}
};


#endif //EXCEPTION_H
