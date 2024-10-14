# AED_2024  

*Notas sobre estructuras*  
- POLIMORFISMO
  class Animal {
public:
    // Método virtual que será sobrescrito en las clases derivadas
    virtual void hacerSonido() {
        std::cout << "El animal hace un sonido" << std::endl;
    }
class Perro : public Animal {
public:
    void hacerSonido() override {
        std::cout << "El perro ladra" << std::endl;
    }
};

class Gato : public Animal {
public:
    void hacerSonido() override {
        std::cout << "El gato maúlla" << std::endl;
    }
};  
- FUNCTORES
