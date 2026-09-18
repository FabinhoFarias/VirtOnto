#include "model/Vector3D.hpp"
#include <cmath> // Necessário para usar std::sqrt (raiz quadrada)
#include <cassert>
#include <iostream>

namespace virtonto::model {

// 1. MÉTODO DE DISTÂNCIA
// O tipo de retorno (float) DEVE vir antes da resolução de escopo (Vector3D::)
float Vector3D::distanceTo(const Vector3D& other) const noexcept {
    float dx = x - other.x;
    float dy = y - other.y;
    float dz = z - other.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

// 2. OPERADOR SOMA (+)
// Gera e retorna um NOVO vetor na memória, sem alterar este (this) nem o recebido (other)
Vector3D Vector3D::operator+(const Vector3D& other) const noexcept {
    // Usa Inicialização Uniforme {} do C++11 para construir o retorno diretamente
    return {x + other.x, y + other.y, z + other.z};
}

// 3. OPERADOR SUBTRAÇÃO (-)
Vector3D Vector3D::operator-(const Vector3D& other) const noexcept {
    return {x - other.x, y - other.y, z - other.z};
}

// 4. OPERADOR MULTIPLICAÇÃO POR ESCALAR (*)
Vector3D Vector3D::operator*(float scalar) const noexcept {
    return {x * scalar, y * scalar, z * scalar};
}

// 5. ATRIBUIÇÃO COMPOSTA (+=)
// Altera os atributos DO PRÓPRIO OBJETO e retorna uma referência para ele mesmo (Vector3D&)
Vector3D& Vector3D::operator+=(const Vector3D& other) noexcept {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this; // 'this' é o ponteiro da instância; '*this' devolve o valor do objeto
}

// 6. ATRIBUIÇÃO COMPOSTA MULTIPLICAÇÃO (*=)
Vector3D& Vector3D::operator*=(float scalar) noexcept {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this; // Permite encadeamento de atribuições no C++
}

Vector3D& Vector3D::operator*=(const Vector3D& other) noexcept {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}
} // namespace virtonto::model


// --- BLOCO DE TESTE TEMPORÁRIO ---
// int main() {
//     using namespace virtonto::model;

//     Vector3D v1{1.0f, 2.0f, 3.0f};
//     Vector3D v2{4.0f, 5.0f, 6.0f};

//     // Teste de Soma
//     Vector3D soma = v1 + v2;
//     assert(soma.x == 5.0f && soma.y == 7.0f && soma.z == 9.0f);

//     // Teste de Multiplicação por Escalar
//     Vector3D mult = v1 * 2.0f;
//     assert(mult.x == 2.0f && mult.y == 4.0f && mult.z == 6.0f);
    
//     Vector3D enc = v1 += v2;
//     assert(enc.x == 5.0f && enc.y == 7.0f && enc.z == 9.0f);

//     Vector3D encMult = v1 *= 2.0f;
//     assert(encMult.x == 10.0f && encMult.y == 14.0f && encMult.z == 18.0f);
    
//     Vector3D encMult2 = soma *= soma;
//     assert(encMult2.x == 25.0f && encMult2.y == 49.0f && encMult2.z == 81.0f);
    
//     std::cout << "✅ Todos os testes do Vector3D passaram!" << std::endl;
//     return 0;
// }

// Copia
// g++ -std=c++17 CPP/src/model/Vector3D.cpp -ICPP/include -o test_vector && ./test_vector