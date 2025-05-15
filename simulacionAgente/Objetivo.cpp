#include "Objetivo.h"

Objetivo::Objetivo() : _objeto(""), _receptaculo("") {}

Objetivo::Objetivo(const Color &objeto, const Color &receptaculo) : _objeto(objeto), _receptaculo(receptaculo) {}

const Color &Objetivo::objeto() const {
    return _objeto;
}

const Color &Objetivo::receptaculo() const {
    return _receptaculo;
}

bool Objetivo::operator==(Objetivo& obj) const {
    return objeto() == obj.objeto() && receptaculo() == obj.receptaculo();
}

bool Objetivo::operator<(const Objetivo& obj) const {
    bool res = false;
    if (objeto().size() < obj.objeto().size()){
        res = true;
    } else {
        if (obj.objeto().size() < objeto().size()){
            res = false;
        } else {
            res = receptaculo().size() < obj.receptaculo().size();
        }
    }
    return res;
}

