#include "unity/src/unity.h"
#include "stdio.h"
#include "cidadeDorme.h"

void setUp(void){};
void tearDown(){};

void ct1(void){
    cidadeDorme__Status_participante cidadeDorme__status_p[10];
    cidadeDorme__Papeis cidadeDorme__papel[10];
    // cidadeDorme__INITIALISATION();
    cidadeDorme__status_p[cidadeDorme__p1] = 1;
    cidadeDorme__papel[cidadeDorme__p1] = 0;

    int ss;

    cidadeDorme__atacar__test(cidadeDorme__p1, &ss);
    TEST_ASSERT_EQUAL_INT(-1, ss);
    printf("%d\n", ss);
}

void ct2(void){
    cidadeDorme__Status_participante cidadeDorme__status_p[10];
    cidadeDorme__Papeis cidadeDorme__papel[10];
    // cidadeDorme__INITIALISATION();
    cidadeDorme__status_p[cidadeDorme__p1] = 0;
    cidadeDorme__papel[cidadeDorme__p1] = 0;

    int ss;

    cidadeDorme__atacar__test(cidadeDorme__p1, &ss);
    TEST_ASSERT_EQUAL_INT(-1, ss);
    printf("%d\n", ss);
}

void ct3(void){
    cidadeDorme__Status_participante cidadeDorme__status_p[10];
    cidadeDorme__Papeis cidadeDorme__papel[10];
    // cidadeDorme__INITIALISATION();
    cidadeDorme__status_p[cidadeDorme__p1] = 1;
    cidadeDorme__papel[cidadeDorme__p1] = 1;

    int ss;

    cidadeDorme__atacar__test(cidadeDorme__p1, &ss);
    TEST_ASSERT_EQUAL_INT(3, ss);
    printf("%d\n", ss);
}

void ct4(void){
    // cidadeDorme__Status_participante cidadeDorme__status_p[10];
    // cidadeDorme__Papeis cidadeDorme__papel[10];
    // cidadeDorme__INITIALISATION();
    cidadeDorme__status_p[cidadeDorme__p1] = 1;
    cidadeDorme__papel[cidadeDorme__p1] = 2;

    int ss;

    cidadeDorme__atacar__test(cidadeDorme__p1, &ss);
    TEST_ASSERT_EQUAL_INT(-1, ss);
    printf("%d\n", ss);
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(ct1);
    RUN_TEST(ct2);
    RUN_TEST(ct3);
    RUN_TEST(ct4);
    return UNITY_END();
}