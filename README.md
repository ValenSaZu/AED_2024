# AED_2024  

*Notas sobre estructuras*  
- POLIMORFISMO  
  class Animal {  
public:  
    virtual void hacerSonido() {  
        std::cout << "El animal hace un sonido" << std::endl;  
    }  class Perro : public Animal {  
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
class Sumar {  
public:  
    int operator()(int a, int b) {  
        return a + b;  
    }  
};  
int main() {  
    Sumar sumar;  
    int resultado = sumar(3, 5);  

    std::cout << "La suma es: " << resultado << std::endl;  
    return 0;  
}  
- FUNCIONES INLINE  
  Permite al compilador reemplazar las llamadas a la función con el cuerpo de la función, con el objetivo de optimizar el rendimiento y reducir la sobrecarga de llamadas a funciones  
inline int sumar(int a, int b) {  
    return a + b;  
}  
- PUNTEROS A FUNCION  
int sumar(int a, int b) {  
    return a + b;  
}  
int (*punteroSuma)(int, int);  
int main() {  
    punteroSuma = sumar;  
    int resultado = punteroSuma(3, 5);  
    std::cout << "La suma es: " << resultado << std::endl;  
    return 0;  
}  


