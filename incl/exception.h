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
class FonduriInsuficienteError : public RomopolyError {
    int necesar;
    int disponibil;

public:
    FonduriInsuficienteError(const std::string& playerName, int needed, int available)
        : RomopolyError("Jucatorul '" + playerName + "' nu are suficiente fonduri."),
          necesar(needed), disponibil(available)
    {}

    int getNecesar() const { return necesar; }
    int getDisponibil() const { return disponibil; }


    const char* what() const noexcept override {
        static std::string msg_buffer;
        msg_buffer = std::runtime_error::what(); // Mesajul din RomopolyError
        msg_buffer += " Necesar: " + std::to_string(necesar)
                    + ", Disponibil: " + std::to_string(disponibil);
        return msg_buffer.c_str();
    }
};



class ProprietateIndisponibilaError : public RomopolyError {
public:
    explicit ProprietateIndisponibilaError(const std::string& message)
       : RomopolyError("Proprietate indisponibila: " + message) {}
};

class ActiuneInvalidaError : public RomopolyError {
public:
    explicit ActiuneInvalidaError(const std::string& message)
       : RomopolyError("Actiune invalida: " + message) {}
};


#endif //EXCEPTION_H
