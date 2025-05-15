#ifndef OBJETIVO_H
#define OBJETIVO_H

#include "Tipos.h"

class Objetivo {
  public:
    
    Objetivo();

    Objetivo(const Color& objeto, const Color& receptaculo);

    const Color& objeto() const;
    
    const Color& receptaculo() const;

    bool operator==(Objetivo& obj) const;

    bool operator<(const Objetivo& obj) const;

  private:
    Color _objeto;
    Color _receptaculo;
};



#endif
