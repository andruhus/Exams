/*
 * Многочлен від трьох змінних з цілими коефіціентами можна подати зв'язним списком,
 * впорядкованим за зростанням степенів змінних, без зберігання одночленів з нульовими
 * коефіціентами. Написати функцію, яка обчислює значення многочлена при заданих
 * значеннях змінних
 */

#include <cmath>

//Type -  повинен містити номер змінної: a = 0, b = 1, c = 2 і т.д.
//Power - степінь
//K - коефіціент
struct Part
{
    int Power;
    int Type;
    int K;
};

//variables  a = 0, b = 1, c = 2
long List::CountPolynominal(double variables[], int numberOfVariables)
{
    if(!Root) throw;

    double sum = 0;

    Node* node = Root;
    while(node->Next)
    {
        if(node->Value.Type >= numberOfVariables) throw;
        double val = variables[node->Value.Type];
        if(val == 0) continue;
        val = std::pow(val, node->Value.Power);
        val *= node->Value.K;
        sum += val;
        node = node->Next;
    }
}