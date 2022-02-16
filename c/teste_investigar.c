#include "unity/src/unity.h"
#include "stdio.h"
#include "cidadeDorme.h"

void setUp(void){};
void tearDown(){};

void nao_comum(void){
    cidadeDorme__INITIALISATION();
    cidadeDorme__cadastrar(cidadeDorme__p1);
    cidadeDorme__cadastrar(cidadeDorme__p2);
    cidadeDorme__cadastrar(cidadeDorme__p3);
    cidadeDorme__cadastrar(cidadeDorme__p4);
    cidadeDorme__cadastrar(cidadeDorme__p5);
    cidadeDorme__cadastrar(cidadeDorme__p6);
    cidadeDorme__cadastrar(cidadeDorme__p7);
    cidadeDorme__terminar_cadastro();

    int resp;

    cidadeDorme__investigar(cidadeDorme__p1, &resp);
    TEST_ASSERT_EQUAL_INT(resp, 1);
    cidadeDorme__investigar(cidadeDorme__p3, &resp);
    TEST_ASSERT_EQUAL_INT(resp, 1);
}

void eh_comum(void){
    cidadeDorme__INITIALISATION();
    cidadeDorme__cadastrar(cidadeDorme__p1);
    cidadeDorme__cadastrar(cidadeDorme__p2);
    cidadeDorme__cadastrar(cidadeDorme__p3);
    cidadeDorme__cadastrar(cidadeDorme__p4);
    cidadeDorme__cadastrar(cidadeDorme__p5);
    cidadeDorme__cadastrar(cidadeDorme__p6);
    cidadeDorme__cadastrar(cidadeDorme__p7);
    cidadeDorme__terminar_cadastro();

    int resp;

    cidadeDorme__investigar(cidadeDorme__p5, &resp);
    TEST_ASSERT_EQUAL_INT(resp, 0);
    cidadeDorme__investigar(cidadeDorme__p6, &resp);
    TEST_ASSERT_EQUAL_INT(resp, 0);
    cidadeDorme__investigar(cidadeDorme__p7, &resp);
    TEST_ASSERT_EQUAL_INT(resp, 0);
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(nao_comum);
    RUN_TEST(eh_comum);
    return UNITY_END();
}